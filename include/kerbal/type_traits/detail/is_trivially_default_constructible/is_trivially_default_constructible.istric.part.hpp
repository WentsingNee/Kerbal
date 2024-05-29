/**
 * @file       is_trivially_default_constructible.istric.part.hpp
 * @brief
 * @date       2023-05-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_ISTRIC_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_ISTRIC_PART_HPP

#ifndef KERBAL_SUPPORTS_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE

#include <kerbal/type_traits/detail/is_trivially_constructible/is_trivially_constructible.part.hpp>

#if KERBAL_SUPPORTS_IS_TRIVIALLY_CONSTRUCTIBLE
#	define KERBAL_SUPPORTS_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE 1
#endif



#if KERBAL_SUPPORTS_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE

#include <kerbal/type_traits/is_unbounded_array.hpp>
#include <kerbal/type_traits/logical.hpp>
#include <kerbal/type_traits/remove_all_extents.hpp>


namespace kerbal
{

	namespace type_traits
	{

		template <typename T>
		struct is_trivially_default_constructible :
			kerbal::type_traits::conjunction<
				kerbal::type_traits::negation<
					kerbal::type_traits::is_unbounded_array<T>
				>,
				kerbal::type_traits::is_trivially_constructible<
					typename kerbal::type_traits::remove_all_extents<T>::type
				>
			>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // #if KERBAL_SUPPORTS_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE

#endif // #ifndef KERBAL_SUPPORTS_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_ISTRIC_PART_HPP
