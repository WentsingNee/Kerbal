/**
 * @file       is_nothrow_assignable.traits11.part.hpp
 * @brief
 * @date       2023-05-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_NOTHROW_ASSIGNABLE_IS_NOTHROW_ASSIGNABLE_TRAITS11_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_NOTHROW_ASSIGNABLE_IS_NOTHROW_ASSIGNABLE_TRAITS11_PART_HPP

#ifndef KERBAL_HAS_IS_NOTHROW_ASSIGNABLE_SUPPORT

#if __cplusplus >= 201103L
#	include <kerbal/type_traits/detail/is_assignable/is_assignable.part.hpp>
#	if KERBAL_HAS_IS_ASSIGNABLE_SUPPORT
#		define KERBAL_HAS_IS_NOTHROW_ASSIGNABLE_SUPPORT 1
#	endif
#endif



#if KERBAL_HAS_IS_NOTHROW_ASSIGNABLE_SUPPORT

#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_assignable.hpp>
#include <kerbal/type_traits/logical.hpp>
#include <kerbal/utility/declval.hpp>


namespace kerbal
{

	namespace type_traits
	{

		namespace detail
		{

			template <typename T, typename U>
			struct is_nothrow_assignable_helper :
				kerbal::type_traits::bool_constant<
					noexcept(
						kerbal::utility::declval<T>() =
						kerbal::utility::declval<U>()
					)
				>
			{
			};

		} // namespace detail

		template <typename T, typename U>
		struct is_nothrow_assignable :
			kerbal::type_traits::conjunction<
				kerbal::type_traits::is_assignable<T, U>,
				kerbal::type_traits::detail::is_nothrow_assignable_helper<T, U>
			>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // #if KERBAL_HAS_IS_NOTHROW_ASSIGNABLE_SUPPORT

#endif // #ifndef KERBAL_HAS_IS_NOTHROW_ASSIGNABLE_SUPPORT

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_NOTHROW_ASSIGNABLE_IS_NOTHROW_ASSIGNABLE_TRAITS11_PART_HPP
