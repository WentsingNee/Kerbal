/**
 * @file       is_union.intrin.part.hpp
 * @brief
 * @date       2023-04-27
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_UNION_IS_UNION_INTRIN_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_UNION_IS_UNION_INTRIN_PART_HPP

#ifndef KERBAL_SUPPORTS_IS_UNION

#include <kerbal/type_traits/detail/compiler_intrinsics/compiler_intrinsics.hpp>

#if KERBAL_PRIVATE_HAS_INTRINSIC_IS_UNION
#	define KERBAL_SUPPORTS_IS_UNION 1
#endif



#if KERBAL_SUPPORTS_IS_UNION

#include <kerbal/type_traits/integral_constant.hpp>


namespace kerbal
{

	namespace type_traits
	{

		template <typename T>
		struct is_union :
			kerbal::type_traits::bool_constant<KERBAL_INTRINSIC_IS_UNION(T)>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // #if KERBAL_SUPPORTS_IS_UNION

#endif // #ifndef KERBAL_SUPPORTS_IS_UNION

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_UNION_IS_UNION_INTRIN_PART_HPP
