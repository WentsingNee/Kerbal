/**
 * @file       raw_storage.hpp
 * @brief
 * @date       2019-4-19
 * @author     peter
 * @copyright
 *      peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_DATA_STRUCT_RAW_STORAGE_HPP
#define KERBAL_DATA_STRUCT_RAW_STORAGE_HPP

#include <kerbal/compatibility/alignof.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/method_overload_tag.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/operators/generic_assign.hpp>
#include <kerbal/type_traits/aligned_storage.hpp>
#include <kerbal/type_traits/array_traits.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/utility/declval.hpp>
#include <kerbal/utility/noncopyable.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif

#if __cplusplus >= 201103L
#	include <type_traits>
#else
#	include <kerbal/type_traits/fundamental_deduction.hpp>
#	include <kerbal/type_traits/member_pointer_deduction.hpp>
#	include <kerbal/type_traits/pointer_deduction.hpp>
#endif

namespace kerbal
{

	namespace data_struct
	{

		template <typename Type>
		struct is_trivial_stored_type;

#	if __cplusplus >= 201103L

		template <typename Type>
		struct is_trivial_stored_type:
				kerbal::type_traits::bool_constant<
						std::is_trivial<Type>::value
				>
		{
		};

#	else

		template <typename Type>
		struct is_trivial_stored_type:
				kerbal::type_traits::bool_constant<
					kerbal::type_traits::is_fundamental<typename kerbal::type_traits::remove_all_extents<Type>::type>::value ||
					kerbal::type_traits::is_member_pointer<typename kerbal::type_traits::remove_all_extents<Type>::type>::value ||
					kerbal::type_traits::is_pointer<typename kerbal::type_traits::remove_all_extents<Type>::type>::value
				>
		{
		};

#	endif



		template <typename ValueType, bool is_trival = is_trivial_stored_type<ValueType>::value>
		class __rawst_base;

		template <typename ValueType>
		class __rawst_base<ValueType, true>
						: kerbal::utility::noncopyable
		{
			protected:
				typedef ValueType				value_type;
				typedef const value_type		const_type;
				typedef value_type&				reference;
				typedef const value_type&		const_reference;
				typedef value_type*				pointer;
				typedef const value_type*		const_pointer;

#		if __cplusplus >= 201103L
				typedef value_type&&			rvalue_reference;
				typedef const value_type&&		const_rvalue_reference;
#		endif

				typedef ValueType				storage_type;

				storage_type storage;

				KERBAL_CONSTEXPR
				__rawst_base() KERBAL_NOEXCEPT
						: storage()
				{
				}

			public:

				KERBAL_CONSTEXPR14 // note: mustn't be constexpr11 otherwise the compile can't distinguish this method with the const version
				reference raw_value() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->storage;
				}

				KERBAL_CONSTEXPR14
				const_reference raw_value() const KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->storage;
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				rvalue_reference raw_value() && noexcept
				{
					return static_cast<rvalue_reference>(this->storage);
				}

				KERBAL_CONSTEXPR14
				const_rvalue_reference raw_value() const && noexcept
				{
					return static_cast<const_rvalue_reference>(this->storage);
				}

#		endif

				KERBAL_CONSTEXPR14
				pointer raw_pointer() KERBAL_NOEXCEPT
				{
					return &(this->storage);
				}

				KERBAL_CONSTEXPR14
				const_pointer raw_pointer() const KERBAL_NOEXCEPT
				{
					return &(this->storage);
				}

		};

		template <typename ValueType>
		class __rawst_base<ValueType, false>
						: kerbal::utility::noncopyable
		{
			protected:
				typedef ValueType				value_type;
				typedef const value_type		const_type;
				typedef value_type&				reference;
				typedef const value_type&		const_reference;
				typedef value_type*				pointer;
				typedef const value_type*		const_pointer;

#		if __cplusplus >= 201103L
				typedef value_type&&			rvalue_reference;
				typedef const value_type&&		const_rvalue_reference;
#		endif

				typedef
					typename kerbal::type_traits::aligned_storage<sizeof(ValueType), KERBAL_ALIGNOF(ValueType)>::type
				storage_type;

				storage_type storage;

				KERBAL_CONSTEXPR
				__rawst_base() KERBAL_NOEXCEPT
						: storage()
				{
				}

			public:

				reference raw_value() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return *this->raw_pointer();
				}

				const_reference raw_value() const KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return *this->raw_pointer();
				}

#		if __cplusplus >= 201103L

				rvalue_reference raw_value() && noexcept
				{
					return static_cast<rvalue_reference>(*this->raw_pointer());
				}

				const_rvalue_reference raw_value() const && noexcept
				{
					return static_cast<const_rvalue_reference>(*this->raw_pointer());
				}

#		endif

				pointer raw_pointer() KERBAL_NOEXCEPT
				{
					return reinterpret_cast<pointer>(&(this->storage));
				}

				const_pointer raw_pointer() const KERBAL_NOEXCEPT
				{
					return reinterpret_cast<const_pointer>(&(this->storage));
				}

		};



		template <typename Type, bool is_trival = is_trivial_stored_type<Type>::value>
		class __rawst_agent;

		template <typename Type>
		class __rawst_agent<Type, true>: public kerbal::data_struct::__rawst_base<Type>
		{
			protected:
				typedef Type value_type;
				typedef const value_type&		const_reference;

#		if __cplusplus >= 201103L
				typedef value_type&&			rvalue_reference;
#		endif

				KERBAL_CONSTEXPR
				__rawst_agent() KERBAL_NOEXCEPT
				{
				}

			public:

				KERBAL_CONSTEXPR14
				void construct(const_reference src) KERBAL_NOEXCEPT
				{
					this->raw_value() = src;
				}

#		if __cplusplus < 201103L

				void construct() KERBAL_NOEXCEPT
				{
					this->raw_value() = value_type();
				}

				template <typename Arg0>
				void construct(const Arg0 & arg0) KERBAL_NOEXCEPT
				{
					this->raw_value() = value_type(arg0);
				}

				template <typename Arg0, typename Arg1>
				void construct(const Arg0 & arg0, const Arg1& arg1) KERBAL_NOEXCEPT
				{
					this->raw_value() = value_type(arg0, arg1);
				}

				template <typename Arg0, typename Arg1, typename Arg2>
				void construct(const Arg0 & arg0, const Arg1& arg1, const Arg2 & arg2) KERBAL_NOEXCEPT
				{
					this->raw_value() = value_type(arg0, arg1, arg2);
				}

				template <typename Arg0, typename Arg1, typename Arg2, typename Arg3>
				void construct(const Arg0 & arg0, const Arg1& arg1, const Arg2 & arg2, const Arg3& arg3) KERBAL_NOEXCEPT
				{
					this->raw_value() = value_type(arg0, arg1, arg2, arg3);
				}

				template <typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
				void construct(const Arg0 & arg0, const Arg1& arg1, const Arg2 & arg2, const Arg3& arg3, const Arg4 & arg4) KERBAL_NOEXCEPT
				{
					this->raw_value() = value_type(arg0, arg1, arg2, arg3, arg4);
				}

#		else

				KERBAL_CONSTEXPR14
				void construct(rvalue_reference src) noexcept
				{
					this->raw_value() = kerbal::compatibility::move(src);
				}

				template <typename ... Args>
				KERBAL_CONSTEXPR14
				void construct(Args&&... args) noexcept
				{
					this->raw_value() = value_type(kerbal::utility::forward<Args>(args)...);
				}

#		endif

				KERBAL_CONSTEXPR14
				void destroy() KERBAL_NOEXCEPT
				{
				}

		};

		template <typename Type, size_t N>
		class __rawst_agent<Type[N], true>: public kerbal::data_struct::__rawst_base<Type[N]>
		{
			protected:
				typedef Type value_type [N];
				typedef const value_type&		const_reference;

#		if __cplusplus >= 201103L
				typedef value_type&&			rvalue_reference;
#		endif

				KERBAL_CONSTEXPR
				__rawst_agent() KERBAL_NOEXCEPT
				{
				}

			public:

				KERBAL_CONSTEXPR14
				void construct() KERBAL_NOEXCEPT
				{
				}

				KERBAL_CONSTEXPR14
				void construct(const_reference src) KERBAL_NOEXCEPT
				{
					for (size_t i = 0; i < N; ++i) {
						kerbal::operators::generic_assign(this->storage[i], src[i]);
					}
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				void construct(rvalue_reference src) KERBAL_NOEXCEPT
				{
					for (size_t i = 0; i < N; ++i) {
						kerbal::operators::generic_assign(this->storage[i], kerbal::compatibility::move(src[i]));
					}
				}

#		endif

				KERBAL_CONSTEXPR14
				void destroy() KERBAL_NOEXCEPT
				{
				}

		};


		template <typename Type>
		class __rawst_agent<Type, false>:
				public kerbal::data_struct::__rawst_base<Type>
		{
			protected:
				typedef Type value_type;

				KERBAL_CONSTEXPR
				__rawst_agent() KERBAL_NOEXCEPT
				{
				}

			public:

#		if __cplusplus < 201103L

				void construct()
				{
					new (this->raw_pointer()) value_type();
				}

				template <typename Arg0>
				void construct(const Arg0 & arg0)
				{
					new (this->raw_pointer()) value_type(arg0);
				}

				template <typename Arg0, typename Arg1>
				void construct(const Arg0 & arg0, const Arg1& arg1)
				{
					new (this->raw_pointer()) value_type(arg0, arg1);
				}

				template <typename Arg0, typename Arg1, typename Arg2>
				void construct(const Arg0 & arg0, const Arg1& arg1, const Arg2 & arg2)
				{
					new (this->raw_pointer()) value_type(arg0, arg1, arg2);
				}

				template <typename Arg0, typename Arg1, typename Arg2, typename Arg3>
				void construct(const Arg0 & arg0, const Arg1& arg1, const Arg2 & arg2, const Arg3& arg3)
				{
					new (this->raw_pointer()) value_type(arg0, arg1, arg2, arg3);
				}

				template <typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
				void construct(const Arg0 & arg0, const Arg1& arg1, const Arg2 & arg2, const Arg3& arg3, const Arg4 & arg4)
				{
					new (this->raw_pointer()) value_type(arg0, arg1, arg2, arg3, arg4);
				}

#		else

				template <typename ... Args>
				void construct(Args&&... args)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<value_type, Args...>::value)
										)
				{
					new (this->raw_pointer()) value_type(kerbal::utility::forward<Args>(args)...);
				}

#		endif

				void destroy()
										KERBAL_CONDITIONAL_NOEXCEPT(
												std::is_nothrow_destructible<value_type>::value
										)
				{
					this->raw_pointer()->~value_type();
				}
		};

		template <typename Type, size_t N>
		class __rawst_agent<Type[N], false>:
				public kerbal::data_struct::__rawst_base<Type[N]>
		{
			private:
				typedef __rawst_agent this_type;

			protected:
				typedef Type value_type [N];
				typedef const value_type&		const_reference;

#		if __cplusplus >= 201103L
				typedef value_type&&			rvalue_reference;
#		endif

			private:
				template <typename Up, size_t M>
				typename kerbal::type_traits::enable_if<kerbal::type_traits::rank<Up>::value >= 1>::type
				static __des_array(Up (&arr) [M])
												KERBAL_CONDITIONAL_NOEXCEPT(
														noexcept(this_type::__des_array(arr[0]))
												)
				{
					size_t i = M;
					while (i != 0) {
						--i;
						__des_array(arr[i]);
					}
				}

				template <typename Up, size_t M>
				typename kerbal::type_traits::enable_if<kerbal::type_traits::rank<Up>::value == 0>::type
				static __des_array(Up (&arr) [M])
												KERBAL_CONDITIONAL_NOEXCEPT(
														std::is_nothrow_destructible<Up>::value
												)
				{
					size_t i = M;
					while (i != 0) {
						--i;
						(arr + i)->~Up();
					}
				}

			protected:

				KERBAL_CONSTEXPR
				__rawst_agent() KERBAL_NOEXCEPT
				{
				}

			public:

				void construct()
												KERBAL_CONDITIONAL_NOEXCEPT(
														std::is_nothrow_default_constructible<Type>::value
												)
				{
					for (size_t i = 0; i != N; ++i) {
						new (&this->raw_value()[i]) Type();
					}
				}

				void construct(const_reference src)
				{
					for (size_t i = 0; i != N; ++i) {
						new (&this->raw_value()[i]) Type(src[i]);
					}
				}

				template <typename Up>
				void construct(const Up (&src)[N])
				{
					for (size_t i = 0; i != N; ++i) {
						new (&this->raw_value()[i]) Type(src[i]);
					}
				}

#		if __cplusplus >= 201103L

				void construct(rvalue_reference src)
				{
					for (size_t i = 0; i != N; ++i) {
						new (&this->raw_value()[i]) Type(kerbal::compatibility::move(src[i]));
					}
				}

				template <typename Up>
				void construct(Up (&&src)[N])
				{
					for (size_t i = 0; i != N; ++i) {
						new (&this->raw_value()[i]) Type(kerbal::utility::forward<Up>(src[i]));
					}
				}

#		endif

				void destroy()
												KERBAL_CONDITIONAL_NOEXCEPT(
														noexcept(__des_array(kerbal::utility::declthis<this_type>()->raw_value()))
												)
				{
					__des_array(this->raw_value());
				}

		};



		template <typename Type>
		class raw_storage: public kerbal::data_struct::__rawst_agent<Type>
		{
			public:
				typedef Type						value_type;
				typedef const value_type			const_type;
				typedef value_type&					reference;
				typedef const value_type&			const_reference;
				typedef value_type*					pointer;
				typedef const value_type*			const_pointer;

#		if __cplusplus >= 201103L
				typedef value_type&&				rvalue_reference;
				typedef const value_type&&			const_rvalue_reference;
#		endif

			public:

				KERBAL_CONSTEXPR
				raw_storage() KERBAL_NOEXCEPT
				{
				}

		};

	} // namespace data_struct

} // namespace kerbal


#endif // KERBAL_DATA_STRUCT_RAW_STORAGE_HPP
