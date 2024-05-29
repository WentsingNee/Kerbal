/**
 * @file       is_nothrow_default_constructible.isntc.part.hpp
 * @brief
 * @date       2023-05-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE_ISNTC_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE_ISNTC_PART_HPP

#ifndef KERBAL_SUPPORTS_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE

#include <kerbal/type_traits/detail/is_nothrow_constructible/is_nothrow_constructible.part.hpp>

#if KERBAL_SUPPORTS_IS_NOTHROW_CONSTRUCTIBLE
#	define KERBAL_SUPPORTS_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE 1
#endif



#if KERBAL_SUPPORTS_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE

#include <kerbal/type_traits/is_unbounded_array.hpp>
#include <kerbal/type_traits/logical.hpp>
#include <kerbal/type_traits/remove_all_extents.hpp>


namespace kerbal
{

	namespace type_traits
	{

		template <typename T>
		struct is_nothrow_default_constructible :
			kerbal::type_traits::conjunction<
				kerbal::type_traits::negation<
					kerbal::type_traits::is_unbounded_array<T>
				>,
				kerbal::type_traits::is_nothrow_constructible<
					typename kerbal::type_traits::remove_all_extents<T>::type
				>
			>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // #if KERBAL_SUPPORTS_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE

#endif // #ifndef KERBAL_SUPPORTS_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE_ISNTC_PART_HPP
