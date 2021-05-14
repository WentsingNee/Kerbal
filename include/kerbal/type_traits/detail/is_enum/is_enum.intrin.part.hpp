/**
 * @file       is_enum.intrin.part.hpp
 * @brief
 * @date       2023-04-27
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_ENUM_IS_ENUM_INTRIN_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_ENUM_IS_ENUM_INTRIN_PART_HPP

#ifndef KERBAL_HAS_IS_ENUM_SUPPORT

#include <kerbal/type_traits/detail/compiler_intrinsics/compiler_intrinsics.hpp>

#if KERBAL_HAS_INTRINSIC_IS_ENUM_SUPPORT

#include <kerbal/type_traits/integral_constant.hpp>


namespace kerbal
{

	namespace type_traits
	{

		template <typename T>
		struct is_enum : kerbal::type_traits::bool_constant<KERBAL_INTRINSIC_IS_ENUM(T)>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#define KERBAL_HAS_IS_ENUM_SUPPORT 1

#endif // #if KERBAL_HAS_INTRINSIC_IS_ENUM_SUPPORT

#endif // #ifndef KERBAL_HAS_IS_ENUM_SUPPORT

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_ENUM_IS_ENUM_INTRIN_PART_HPP
