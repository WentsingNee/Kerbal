/**
 * @file       is_nothrow_destructible.isdes.part.hpp
 * @brief
 * @date       2023-05-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_NOTHROW_DESTRUCTIBLE_IS_NOTHROW_DESTRUCTIBLE_ISDES_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_NOTHROW_DESTRUCTIBLE_IS_NOTHROW_DESTRUCTIBLE_ISDES_PART_HPP

#ifndef KERBAL_SUPPORTS_IS_NOTHROW_DESTRUCTIBLE

#if __cplusplus >= 201103L
#	include <kerbal/type_traits/detail/is_destructible/is_destructible.part.hpp>
#	if KERBAL_SUPPORTS_IS_DESTRUCTIBLE
#		define KERBAL_SUPPORTS_IS_NOTHROW_DESTRUCTIBLE 1
#	endif
#endif



#if KERBAL_SUPPORTS_IS_NOTHROW_DESTRUCTIBLE

#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_destructible.hpp>
#include <kerbal/type_traits/is_reference.hpp>
#include <kerbal/type_traits/logical.hpp>
#include <kerbal/type_traits/remove_all_extents.hpp>
#include <kerbal/utility/declval.hpp>


namespace kerbal
{

	namespace type_traits
	{

		namespace detail
		{

			template <typename T>
			struct is_nothrow_destructible_impl :
				kerbal::type_traits::bool_constant<
					noexcept(kerbal::utility::declval<T *>()->~T())
				>
			{
			};

		} // namespace detail

		template <typename T>
		struct is_nothrow_destructible :
			kerbal::type_traits::conjunction<
				kerbal::type_traits::is_destructible<T>,
				kerbal::type_traits::disjunction<
					kerbal::type_traits::is_reference<T>,
					kerbal::type_traits::detail::is_nothrow_destructible_impl<
						typename kerbal::type_traits::remove_all_extents<T>::type
					>
				>
			>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // #if KERBAL_SUPPORTS_IS_NOTHROW_DESTRUCTIBLE

#endif // #ifndef KERBAL_SUPPORTS_IS_NOTHROW_DESTRUCTIBLE

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_NOTHROW_DESTRUCTIBLE_IS_NOTHROW_DESTRUCTIBLE_ISDES_PART_HPP
