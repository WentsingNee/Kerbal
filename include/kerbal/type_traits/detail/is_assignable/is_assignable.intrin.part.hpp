/**
 * @file       is_assignable.intrin.part.hpp
 * @brief
 * @date       2023-04-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_ASSIGNABLE_IS_ASSIGNABLE_INTRIN_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_ASSIGNABLE_IS_ASSIGNABLE_INTRIN_PART_HPP

#ifndef KERBAL_HAS_IS_ASSIGNABLE_SUPPORT

#include <kerbal/type_traits/detail/compiler_intrinsics/compiler_intrinsics.hpp>

#if KERBAL_HAS_INTRINSIC_IS_ASSIGNABLE_SUPPORT
#	define KERBAL_HAS_IS_ASSIGNABLE_SUPPORT 1
#endif



#if KERBAL_HAS_IS_ASSIGNABLE_SUPPORT

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/type_traits/integral_constant.hpp>


namespace kerbal
{

	namespace type_traits
	{

		KERBAL_MODULE_EXPORT
		template <typename T, typename U>
		struct is_assignable :
			kerbal::type_traits::bool_constant<KERBAL_INTRINSIC_IS_ASSIGNABLE(T, U)>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // #if KERBAL_HAS_IS_ASSIGNABLE_SUPPORT

#endif // #ifndef KERBAL_HAS_IS_ASSIGNABLE_SUPPORT

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_ASSIGNABLE_IS_ASSIGNABLE_INTRIN_PART_HPP
