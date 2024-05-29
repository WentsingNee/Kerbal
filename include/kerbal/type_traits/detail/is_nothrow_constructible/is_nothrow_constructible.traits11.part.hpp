/**
 * @file       is_nothrow_constructible.traits11.part.hpp
 * @brief
 * @date       2023-04-29
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_NOTHROW_CONSTRUCTIBLE_IS_NOTHROW_CONSTRUCTIBLE_TRAITS11_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_NOTHROW_CONSTRUCTIBLE_IS_NOTHROW_CONSTRUCTIBLE_TRAITS11_PART_HPP

#ifndef KERBAL_SUPPORTS_IS_NOTHROW_CONSTRUCTIBLE

#if __cplusplus >= 201103L
#	include <kerbal/type_traits/detail/is_constructible/is_constructible.part.hpp>
#	if KERBAL_SUPPORTS_IS_CONSTRUCTIBLE
#		define KERBAL_SUPPORTS_IS_NOTHROW_CONSTRUCTIBLE 1
#	endif
#endif



#if KERBAL_SUPPORTS_IS_NOTHROW_CONSTRUCTIBLE

#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/logical.hpp>
#include <kerbal/utility/declval.hpp>


namespace kerbal
{

	namespace type_traits
	{

		namespace detail
		{

			template <typename T, typename ... Args>
			struct is_nothrow_constructible_helper :
				kerbal::type_traits::bool_constant<
					noexcept(T(kerbal::utility::declval<Args>()...))
				>
			{
			};

		} // namespace detail

		template <typename T, typename ... Args>
		struct is_nothrow_constructible :
			kerbal::type_traits::conjunction<
				kerbal::type_traits::is_constructible<T, Args...>,
				kerbal::type_traits::detail::is_nothrow_constructible_helper<T, Args...>
			>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // #if KERBAL_SUPPORTS_IS_NOTHROW_CONSTRUCTIBLE

#endif // #ifndef KERBAL_SUPPORTS_IS_NOTHROW_CONSTRUCTIBLE

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_NOTHROW_CONSTRUCTIBLE_IS_NOTHROW_CONSTRUCTIBLE_TRAITS11_PART_HPP
