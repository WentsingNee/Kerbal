/**
 * @file       is_empty.intrin.part.hpp
 * @brief
 * @date       2023-04-27
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_EMPTY_IS_EMPTY_INTRIN_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_EMPTY_IS_EMPTY_INTRIN_PART_HPP

#ifndef KERBAL_HAS_IS_EMPTY_SUPPORT

#include <kerbal/type_traits/detail/compiler_intrinsics/compiler_intrinsics.hpp>

#if KERBAL_HAS_INTRINSIC_IS_EMPTY_SUPPORT

#include <kerbal/type_traits/integral_constant.hpp>


namespace kerbal
{

	namespace type_traits
	{

		template <typename T>
		struct is_empty : kerbal::type_traits::bool_constant<KERBAL_INTRINSIC_IS_EMPTY(T)>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#define KERBAL_HAS_IS_EMPTY_SUPPORT 1

#endif // #if KERBAL_HAS_INTRINSIC_IS_EMPTY_SUPPORT

#endif // #ifndef KERBAL_HAS_IS_EMPTY_SUPPORT

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_EMPTY_IS_EMPTY_INTRIN_PART_HPP
