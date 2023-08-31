/**
 * @file       construct_at.cxx11.part.hpp
 * @brief
 * @date       2023-08-31
 * @remark     split from <kerbal/memory/uninitalized/construct.hpp>, 2023-08-31
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_UNINITIALIZED_DETAIL_CONSTRUCT_AT_CONSTRUCT_AT_CXX11_PART_HPP
#define KERBAL_MEMORY_UNINITIALIZED_DETAIL_CONSTRUCT_AT_CONSTRUCT_AT_CXX11_PART_HPP

#if __cplusplus < 201103L
#	error This file requires compiler and library support for the ISO C++ 2011 standard.
#endif

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_trivially_constructible.hpp>
#include <kerbal/type_traits/is_trivially_destructible.hpp>
#include <kerbal/type_traits/is_trivially_move_assignable.hpp>
#include <kerbal/type_traits/tribool_constant.hpp>
#include <kerbal/utility/declval.hpp>
#include <kerbal/utility/forward.hpp>


namespace kerbal
{

	namespace memory
	{

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> CONSTRUCT_AT_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1> CONSTRUCT_AT_VER_TRIVIAL;

			template <typename T, typename ... Args>
			struct construct_at_impl_overload_ver :
					kerbal::type_traits::conditional<
						typename kerbal::type_traits::tribool_conjunction<
							kerbal::type_traits::try_test_is_trivially_constructible<T, Args...>,
							kerbal::type_traits::try_test_is_trivially_move_assignable<T>,
							kerbal::type_traits::try_test_is_trivially_destructible<T>
						>::result::IS_TRUE::value,
						CONSTRUCT_AT_VER_TRIVIAL,
						CONSTRUCT_AT_VER_DEFAULT
					>::type
			{
			};


			template <typename Ver, typename T, typename ... Args>
			struct construct_at_impl_is_nothrow_impl;

			template <typename T, typename ... Args>
			struct construct_at_impl_is_nothrow_impl<CONSTRUCT_AT_VER_DEFAULT, T, Args...> :
					kerbal::type_traits::bool_constant<
						noexcept(::new (kerbal::utility::declval<void*>())
							T (kerbal::utility::declval<Args>()...))
					>
			{
			};

			template <typename T, typename ... Args>
			struct construct_at_impl_is_nothrow_impl<CONSTRUCT_AT_VER_TRIVIAL, T, Args...> :
					kerbal::type_traits::true_type
			{
			};

			template <typename T, typename ... Args>
			struct construct_at_impl_is_nothrow :
					construct_at_impl_is_nothrow_impl<
						typename construct_at_impl_overload_ver<T, Args...>::type, T, Args...
					>
			{
			};

			template <typename T, typename ... Args>
			T * construct_at_impl(CONSTRUCT_AT_VER_DEFAULT, T * p, Args&& ... args)
					KERBAL_CONDITIONAL_NOEXCEPT((
						construct_at_impl_is_nothrow<T, Args&& ...>::value
					))
			{
				return ::new (const_cast<void*>(static_cast<const volatile void*>(p)))
						T (kerbal::utility::forward<Args>(args)...);
			}

			template <typename T, typename ... Args>
			KERBAL_CONSTEXPR14
			T * construct_at_impl(CONSTRUCT_AT_VER_TRIVIAL, T * p, Args&& ... args) KERBAL_NOEXCEPT
			{
				*p = T(kerbal::utility::forward<Args>(args)...);
				return p;
			}

		} // namespace detail


		template <typename T, typename ... Args>
		KERBAL_CONSTEXPR14
		T * construct_at(T * p, Args&& ... args)
				KERBAL_CONDITIONAL_NOEXCEPT((
					kerbal::memory::detail::construct_at_impl_is_nothrow<T, Args&& ...>::value
				))
		{
			typedef kerbal::memory::detail::construct_at_impl_overload_ver<T, Args&&...> VER;
			return kerbal::memory::detail::construct_at_impl(VER(), p, kerbal::utility::forward<Args>(args)...);
		}

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_UNINITIALIZED_DETAIL_CONSTRUCT_AT_CONSTRUCT_AT_CXX11_PART_HPP
