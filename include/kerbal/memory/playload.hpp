/**
 * @file       playload.hpp
 * @brief
 * @date       2020-1-5
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_PLAYLOAD_HPP
#define KERBAL_MEMORY_PLAYLOAD_HPP

#include <kerbal/compatibility/alignof.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/method_overload_tag.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/aligned_storage.hpp>
#include <kerbal/type_traits/array_traits.hpp>
#include <kerbal/type_traits/const_deduction.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/utility/noncopyable.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif

#if __cplusplus >= 201103L
# include <initializer_list>
# include <type_traits>
#else
# include <kerbal/type_traits/fundamental_deduction.hpp>
# include <kerbal/type_traits/pointer_deduction.hpp>
#endif

namespace kerbal
{

	namespace memory
	{

#	if __cplusplus >= 201103L

		template <typename Type>
		struct is_trivial_stored_type:
				kerbal::type_traits::bool_constant<
					std::is_trivially_default_constructible<
						typename kerbal::type_traits::remove_all_extents<Type>::type
					>::value
					&&
					std::is_trivially_move_assignable<
						typename kerbal::type_traits::remove_const<
							typename kerbal::type_traits::remove_all_extents<Type>::type
						>::type
					>::value
					&&
					std::is_trivially_destructible<Type>::value
				>
		{
		};

#	else

		template <typename Type>
		struct is_trivial_stored_type:
				kerbal::type_traits::bool_constant<
					kerbal::type_traits::is_fundamental<typename kerbal::type_traits::remove_all_extents<Type>::type >::value ||
					kerbal::type_traits::is_pointer<typename kerbal::type_traits::remove_all_extents<Type>::type >::value
				>
		{
		};

#	endif

		namespace detail
		{

			template <typename Tp,
					bool /*is_trivial_stored_type*/ = kerbal::memory::is_trivial_stored_type<Tp>::value>
			class __playload_base;

			template <typename Tp>
			class __playload_base<Tp, true>
			{
				public:
					typedef typename kerbal::type_traits::remove_const<Tp>::type stored_type;

					typedef Tp						value_type;
					typedef const value_type		const_type;
					typedef value_type&				reference;
					typedef const value_type&		const_reference;
					typedef value_type*				pointer;
					typedef const value_type*		const_pointer;

#			if __cplusplus >= 201103L
					typedef value_type&&			rvalue_reference;
					typedef const value_type&&		const_rvalue_reference;
#			endif

				protected:
					stored_type value;

#			if __cplusplus >= 201103L
					constexpr __playload_base() noexcept
						: value()
					{
					}
#			else
					__playload_base() KERBAL_NOEXCEPT
					{
					}
#			endif

				public:

					KERBAL_CONSTEXPR14 // note: mustn't be constexpr11 otherwise the compile can't distinguish this method with the const version
					reference raw_value() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return this->value;
					}

					KERBAL_CONSTEXPR14
					const_reference raw_value() const KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return this->value;
					}

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					rvalue_reference raw_value() && noexcept
					{
						return static_cast<rvalue_reference>(this->value);
					}

					KERBAL_CONSTEXPR14
					const_rvalue_reference raw_value() const && noexcept
					{
						return static_cast<const_rvalue_reference>(this->value);
					}

#			endif

					KERBAL_CONSTEXPR14
					pointer raw_pointer() KERBAL_NOEXCEPT
					{
						return &(this->value);
					}

					KERBAL_CONSTEXPR14
					const_pointer raw_pointer() const KERBAL_NOEXCEPT
					{
						return &(this->value);
					}

			};

			template <typename Tp>
			class __playload_base<Tp, false>
			{
				public:
					typedef typename kerbal::type_traits::aligned_storage<sizeof(Tp),
							KERBAL_ALIGNOF(Tp)>::type stored_type;

					typedef Tp						value_type;
					typedef const value_type		const_type;
					typedef value_type&				reference;
					typedef const value_type&		const_reference;
					typedef value_type*				pointer;
					typedef const value_type*		const_pointer;

#			if __cplusplus >= 201103L
					typedef value_type&&			rvalue_reference;
					typedef const value_type&&		const_rvalue_reference;
#			endif

				protected:
					stored_type value;

//#			if __cplusplus >= 201103L
//					constexpr __playload_base() noexcept = default;
//#			else
//					__playload_base() KERBAL_NOEXCEPT
//					{
//					}
//#			endif

				public:

					reference raw_value() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return *this->raw_pointer();
					}

					const_reference raw_value() const KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return *this->raw_pointer();
					}

#			if __cplusplus >= 201103L

					rvalue_reference raw_value() && noexcept
					{
						return static_cast<rvalue_reference>(*this->raw_pointer());
					}

					const_rvalue_reference raw_value() const && noexcept
					{
						return static_cast<const_rvalue_reference>(*this->raw_pointer());
					}

#			endif

					pointer raw_pointer() KERBAL_NOEXCEPT
					{
						return reinterpret_cast<pointer>(&(this->value));
					}

					const_pointer raw_pointer() const KERBAL_NOEXCEPT
					{
						return reinterpret_cast<const_pointer>(&(this->value));
					}

			};





			template <typename Type, bool /*is_trival*/ =
					kerbal::memory::is_trivial_stored_type<Type>::value>
			class __playload_agent;


			template <typename Type>
			class __playload_agent<Type, true>: public kerbal::memory::detail::__playload_base<Type>
			{
				protected:
					typedef Type value_type;
					typedef value_type& reference;


//#			if __cplusplus >= 201103L
//					constexpr __playload_agent() noexcept = default;
//#			else
//					__playload_agent() KERBAL_NOEXCEPT
//					{
//					}
//#			endif

				public:

#			if __cplusplus < 201103L

					reference construct()
					{
						this->value = value_type();
						return this->raw_value();
					}

					template <typename Arg0>
					reference construct(const Arg0 & arg0)
					{
						this->value = value_type(arg0);
						return this->raw_value();
					}

					template <typename Arg0, typename Arg1>
					reference construct(const Arg0 & arg0, const Arg1& arg1)
					{
						this->value = value_type(arg0, arg1);
						return this->raw_value();
					}

					template <typename Arg0, typename Arg1, typename Arg2>
					reference construct(const Arg0 & arg0, const Arg1& arg1, const Arg2 & arg2)
					{
						this->value = value_type(arg0, arg1, arg2);
						return this->raw_value();
					}

					template <typename Arg0, typename Arg1, typename Arg2, typename Arg3>
					reference construct(const Arg0 & arg0, const Arg1& arg1, const Arg2 & arg2, const Arg3& arg3)
					{
						this->value = value_type(arg0, arg1, arg2, arg3);
						return this->raw_value();
					}

					template <typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
					reference construct(const Arg0 & arg0, const Arg1& arg1, const Arg2 & arg2, const Arg3& arg3, const Arg4 & arg4)
					{
						this->value = value_type(arg0, arg1, arg2, arg3, arg4);
						return this->raw_value();
					}

#			else

					template <typename ... Args>
					KERBAL_CONSTEXPR14
					reference construct(Args&&... args)
							KERBAL_CONDITIONAL_NOEXCEPT(
								(std::is_nothrow_constructible<value_type, Args...>::value)
							)
					{
						this->value = value_type(kerbal::utility::forward<Args>(args)...);
						return this->raw_value();
					}

#			endif

					KERBAL_CONSTEXPR14 void destroy() KERBAL_NOEXCEPT
					{
					}

			};



			template <typename Type, size_t N>
			class __playload_agent<Type[N], true>:
					public kerbal::memory::detail::__playload_base<Type[N]>
			{
				protected:
					typedef Type value_type [N];
					typedef value_type& reference;

//#			if __cplusplus >= 201103L
//					constexpr __playload_agent() noexcept = default;
//#			endif

				public:

					KERBAL_CONSTEXPR14
					reference construct() KERBAL_NOEXCEPT
					{
						return this->raw_value();
					}

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					reference construct(std::initializer_list<Type> list) KERBAL_NOEXCEPT
					{
						for (int i = 0; i < N; ++i) {
							this->raw_value()[i] = list[i];
						}
						return this->raw_value();
					}

#			endif

					KERBAL_CONSTEXPR14 void destroy() KERBAL_NOEXCEPT
					{
					}

			};


			template <typename Type>
			class __playload_agent<Type, false>:
					public kerbal::memory::detail::__playload_base<Type>
			{
				protected:
					typedef Type value_type;
					typedef value_type& reference;

//#			if __cplusplus >= 201103L
//					constexpr __playload_agent() noexcept = default;
//#			else
//					__playload_agent() KERBAL_NOEXCEPT
//					{
//					}
//#			endif

				public:

#			if __cplusplus < 201103L

					reference construct()
					{
						new (this->raw_pointer()) value_type();
						return this->raw_value();
					}

					template <typename Arg0>
					reference construct(const Arg0 & arg0)
					{
						new (this->raw_pointer()) value_type(arg0);
						return this->raw_value();
					}

					template <typename Arg0, typename Arg1>
					reference construct(const Arg0 & arg0, const Arg1& arg1)
					{
						new (this->raw_pointer()) value_type(arg0, arg1);
						return this->raw_value();
					}

					template <typename Arg0, typename Arg1, typename Arg2>
					reference construct(const Arg0 & arg0, const Arg1& arg1, const Arg2 & arg2)
					{
						new (this->raw_pointer()) value_type(arg0, arg1, arg2);
						return this->raw_value();
					}

					template <typename Arg0, typename Arg1, typename Arg2, typename Arg3>
					reference construct(const Arg0 & arg0, const Arg1& arg1, const Arg2 & arg2, const Arg3& arg3)
					{
						new (this->raw_pointer()) value_type(arg0, arg1, arg2, arg3);
						return this->raw_value();
					}

					template <typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
					reference construct(const Arg0 & arg0, const Arg1& arg1, const Arg2 & arg2, const Arg3& arg3, const Arg4 & arg4)
					{
						new (this->raw_pointer()) value_type(arg0, arg1, arg2, arg3, arg4);
						return this->raw_value();
					}

#			else

					template <typename ... Args>
					reference construct(Args&&... args)
							KERBAL_CONDITIONAL_NOEXCEPT(
								(std::is_nothrow_constructible<value_type, Args...>::value)
							)
					{
						new (this->raw_pointer()) value_type(kerbal::utility::forward<Args>(args)...);
						return this->raw_value();
					}

#			endif

					void destroy()
					{
						this->raw_pointer()->~value_type();
					}
			};

			template <typename Type, size_t N>
			class __playload_agent<Type[N], false>:
					public kerbal::memory::detail::__playload_base<Type[N]>
			{
				protected:
					typedef Type value_type [N];
					typedef value_type& reference;

				private:
					template <typename Up, size_t M>
					typename kerbal::type_traits::enable_if<kerbal::type_traits::rank<Up>::value >= 1>::type
					static __des_array(Up (&arr) [M])
					{
						size_t i = M;
						while (i-- != 0) {
							__des_array(arr[i]);
						}
					}

					template <typename Up, size_t M>
					typename kerbal::type_traits::enable_if<kerbal::type_traits::rank<Up>::value == 0>::type
					static __des_array(Up (&arr) [M])
					{
						size_t i = M;
						while (i-- != 0) {
							(arr + i)->~Up();
						}
					}

				protected:

//#			if __cplusplus >= 201103L
//					constexpr __playload_agent() noexcept = default;
//#			else
//					__playload_agent() KERBAL_NOEXCEPT
//					{
//					}
//#			endif

				public:

					reference construct()
					{
						for (size_t i = 0; i != N; ++i) {
							new (&this->raw_value()[i]) Type();
						}
						return this->raw_value();
					}

					void destroy()
					{
						__des_array(this->raw_value());
					}

			};

		} // namespace detail

		template <typename Type>
		class playload: public kerbal::memory::detail::__playload_agent<Type>
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


#			if __cplusplus >= 201103L
					constexpr playload() noexcept = default;
#			else
					playload() KERBAL_NOEXCEPT
					{
					}
#			endif


		};

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_PLAYLOAD_HPP
