/**
 * @file       is_default_constructible.isc.part.hpp
 * @brief
 * @date       2023-06-12
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_DEFAULT_CONSTRUCTIBLE_IS_DEFAULT_CONSTRUCTIBLE_ISC_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_DEFAULT_CONSTRUCTIBLE_IS_DEFAULT_CONSTRUCTIBLE_ISC_PART_HPP

#ifndef KERBAL_HAS_IS_DEFAULT_CONSTRUCTIBLE_SUPPORT

#include <kerbal/type_traits/detail/is_constructible/is_constructible.part.hpp>

#if KERBAL_HAS_IS_CONSTRUCTIBLE_SUPPORT
#	define KERBAL_HAS_IS_DEFAULT_CONSTRUCTIBLE_SUPPORT 1
#endif



#if KERBAL_HAS_IS_DEFAULT_CONSTRUCTIBLE_SUPPORT

#include <kerbal/type_traits/is_unbounded_array.hpp>
#include <kerbal/type_traits/logical.hpp>
#include <kerbal/type_traits/remove_all_extents.hpp>


namespace kerbal
{

	namespace type_traits
	{

		template <typename T>
		struct is_default_constructible :
			kerbal::type_traits::conjunction<
				kerbal::type_traits::negation<
					kerbal::type_traits::is_unbounded_array<T>
				>,
				kerbal::type_traits::is_constructible<
					typename kerbal::type_traits::remove_all_extents<T>::type
				>
			>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // #if KERBAL_HAS_IS_DEFAULT_CONSTRUCTIBLE_SUPPORT

#endif // #ifndef KERBAL_HAS_IS_DEFAULT_CONSTRUCTIBLE_SUPPORT

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_DEFAULT_CONSTRUCTIBLE_IS_DEFAULT_CONSTRUCTIBLE_ISC_PART_HPP
