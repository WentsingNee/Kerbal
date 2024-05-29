/**
 * @file       is_standard_layout.intrin.part.hpp
 * @brief
 * @date       2023-05-05
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_STANDARD_LAYOUT_IS_STANDARD_LAYOUT_INTRIN_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_STANDARD_LAYOUT_IS_STANDARD_LAYOUT_INTRIN_PART_HPP

#ifndef KERBAL_SUPPORTS_IS_STANDARD_LAYOUT

#include <kerbal/type_traits/detail/compiler_intrinsics/compiler_intrinsics.hpp>

#if KERBAL_PRIVATE_HAS_INTRINSIC_IS_STANDARD_LAYOUT
#	define KERBAL_SUPPORTS_IS_STANDARD_LAYOUT 1
#endif



#if KERBAL_SUPPORTS_IS_STANDARD_LAYOUT

#include <kerbal/type_traits/integral_constant.hpp>


namespace kerbal
{

	namespace type_traits
	{

		template <typename T>
		struct is_standard_layout :
			kerbal::type_traits::bool_constant<KERBAL_INTRINSIC_IS_STANDARD_LAYOUT(T)>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // #if KERBAL_SUPPORTS_IS_STANDARD_LAYOUT

#endif // #ifndef KERBAL_SUPPORTS_IS_STANDARD_LAYOUT

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_STANDARD_LAYOUT_IS_STANDARD_LAYOUT_INTRIN_PART_HPP
