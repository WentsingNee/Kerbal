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

#ifndef KERBAL_MEMORY_RAW_STORAGE_HPP
#define KERBAL_MEMORY_RAW_STORAGE_HPP

#include <kerbal/compatibility/alignof.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/method_overload_tag.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/uninitialized.hpp>
#include <kerbal/type_traits/aligned_storage.hpp>
#include <kerbal/type_traits/array_traits.hpp>
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

	namespace memory
	{

		template <typename Type>
		struct is_trivial_stored_type;

#	if __cplusplus >= 201103L

		template <typename Type>
		struct is_trivial_stored_type:
				kerbal::type_traits::bool_constant<
					std::is_trivially_default_constructible<typename kerbal::type_traits::remove_all_extents<Type>::type>::value &&
					std::is_trivially_destructible<typename kerbal::type_traits::remove_all_extents<Type>::type>::value
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



		template <typename ValueType, bool is_trivally_stored = is_trivial_stored_type<ValueType>::value>
		class _K_rawst_base;

		template <typename ValueType>
		class _K_rawst_base<ValueType, true>:
						private kerbal::utility::noncopyable
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

				storage_type _K_storage;

			protected:

#		if __cplusplus < 201103L
				_K_rawst_base() KERBAL_NOEXCEPT {}
#		else
				_K_rawst_base() = default;
#		endif

			public:

				KERBAL_CONSTEXPR14 // note: mustn't be constexpr11 otherwise the compile can't distinguish this method with the const version
				reference raw_value() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->_K_storage;
				}

				KERBAL_CONSTEXPR14
				const_reference raw_value() const KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->_K_storage;
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				rvalue_reference raw_value() && noexcept
				{
					return static_cast<rvalue_reference>(this->_K_storage);
				}

				KERBAL_CONSTEXPR14
				const_rvalue_reference raw_value() const && noexcept
				{
					return static_cast<const_rvalue_reference>(this->_K_storage);
				}

#		endif

				KERBAL_CONSTEXPR14
				pointer raw_pointer() KERBAL_NOEXCEPT
				{
					return &(this->_K_storage);
				}

				KERBAL_CONSTEXPR14
				const_pointer raw_pointer() const KERBAL_NOEXCEPT
				{
					return &(this->_K_storage);
				}

				KERBAL_CONSTEXPR14
				void destroy() KERBAL_NOEXCEPT
				{
				}

		};

		template <typename ValueType>
		class _K_rawst_base<ValueType, false>:
						private kerbal::utility::noncopyable
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

				storage_type _K_storage;

			protected:

#		if __cplusplus < 201103L
				_K_rawst_base() KERBAL_NOEXCEPT {}
#		else
				_K_rawst_base() = default;
#		endif

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
					return reinterpret_cast<pointer>(&(this->_K_storage));
				}

				const_pointer raw_pointer() const KERBAL_NOEXCEPT
				{
					return reinterpret_cast<const_pointer>(&(this->_K_storage));
				}

				void destroy() KERBAL_NOEXCEPT
				{
					kerbal::memory::destroy_at(this->raw_pointer());
				}

		};



		template <typename Type>
		class _K_rawst_agent;

		template <typename Type>
		class _K_rawst_agent:
				public kerbal::memory::_K_rawst_base<Type>
		{
			private:
				typedef _K_rawst_agent this_type;

			protected:
				typedef Type value_type;

			protected:

#		if __cplusplus < 201103L
				_K_rawst_agent() KERBAL_NOEXCEPT {}
#		else
				_K_rawst_agent() = default;
#		endif

			public:

#		if __cplusplus < 201103L

				void construct()
				{
					kerbal::memory::construct_at(this->raw_pointer());
				}

				template <typename Arg0>
				void construct(const Arg0 & arg0)
				{
					kerbal::memory::construct_at(this->raw_pointer(), arg0);
				}

				template <typename Arg0, typename Arg1>
				void construct(const Arg0 & arg0, const Arg1& arg1)
				{
					kerbal::memory::construct_at(this->raw_pointer(), arg0, arg1);
				}

				template <typename Arg0, typename Arg1, typename Arg2>
				void construct(const Arg0 & arg0, const Arg1& arg1, const Arg2 & arg2)
				{
					kerbal::memory::construct_at(this->raw_pointer(), arg0, arg1, arg2);
				}

				template <typename Arg0, typename Arg1, typename Arg2, typename Arg3>
				void construct(const Arg0 & arg0, const Arg1& arg1, const Arg2 & arg2, const Arg3& arg3)
				{
					kerbal::memory::construct_at(this->raw_pointer(), arg0, arg1, arg2, arg3);
				}

				template <typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
				void construct(const Arg0 & arg0, const Arg1& arg1, const Arg2 & arg2, const Arg3& arg3, const Arg4 & arg4)
				{
					kerbal::memory::construct_at(this->raw_pointer(), arg0, arg1, arg2, arg3, arg4);
				}

#		else

				template <typename ... Args>
				KERBAL_CONSTEXPR14
				void construct(Args&&... args)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(
								kerbal::memory::construct_at(
									kerbal::utility::declthis<this_type>()->raw_pointer(),
									kerbal::utility::forward<Args>(args)...
								)
							)
						)
				{
					kerbal::memory::construct_at(this->raw_pointer(), kerbal::utility::forward<Args>(args)...);
				}

#		endif

		};


		template <typename Type, size_t N>
		class _K_rawst_agent<Type[N]>:
				public kerbal::memory::_K_rawst_base<Type[N]>
		{
			private:
				typedef _K_rawst_agent this_type;

			protected:
				typedef Type value_type [N];
				typedef const value_type&		const_reference;

#		if __cplusplus >= 201103L
				typedef value_type&&			rvalue_reference;
#		endif

			protected:

#		if __cplusplus < 201103L
				_K_rawst_agent() KERBAL_NOEXCEPT {}
#		else
				_K_rawst_agent() = default;
#		endif

			public:

				KERBAL_CONSTEXPR14
				void construct()
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::memory::construct_at(kerbal::utility::declthis<this_type>()->raw_pointer()))
						)
				{
					kerbal::memory::construct_at(this->raw_pointer());
				}

				KERBAL_CONSTEXPR14
				void construct(const_reference src)
						KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(kerbal::memory::construct_at(kerbal::utility::declthis<this_type>()->raw_pointer(), src))
						)
				{
					kerbal::memory::construct_at(this->raw_pointer(), src);
				}

				template <typename Up>
				KERBAL_CONSTEXPR14
				void construct(const Up (&src)[N])
						KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(kerbal::memory::construct_at(kerbal::utility::declthis<this_type>()->raw_pointer(), src))
						)
				{
					kerbal::memory::construct_at(this->raw_pointer(), src);
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				void construct(rvalue_reference src)
						KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(kerbal::memory::construct_at(kerbal::utility::declthis<this_type>()->raw_pointer(), kerbal::compatibility::move(src)))
						)
				{
					kerbal::memory::construct_at(this->raw_pointer(), kerbal::compatibility::move(src));
				}

				template <typename Up>
				KERBAL_CONSTEXPR14
				void construct(Up (&&src)[N])
						KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(kerbal::memory::construct_at(kerbal::utility::declthis<this_type>()->raw_pointer(), kerbal::compatibility::move(src)))
						)
				{
					kerbal::memory::construct_at(this->raw_pointer(), kerbal::compatibility::move(src));
				}

#		endif

		};



		template <typename Type>
		class raw_storage: public kerbal::memory::_K_rawst_agent<Type>
		{
			private:
				typedef kerbal::memory::_K_rawst_agent<Type> super;

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

#		if __cplusplus >= 201103L
				using super::super;
#		endif

		};

	} // namespace memory

} // namespace kerbal


#endif // KERBAL_MEMORY_RAW_STORAGE_HPP
