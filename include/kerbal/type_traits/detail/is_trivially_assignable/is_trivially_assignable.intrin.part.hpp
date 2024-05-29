/**
 * @file       is_trivially_assignable.intrin.part.hpp
 * @brief
 * @date       2023-05-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_ASSIGNABLE_IS_TRIVIALLY_ASSIGNABLE_INTRIN_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_ASSIGNABLE_IS_TRIVIALLY_ASSIGNABLE_INTRIN_PART_HPP

#ifndef KERBAL_SUPPORTS_IS_TRIVIALLY_ASSIGNABLE

#include <kerbal/type_traits/detail/compiler_intrinsics/compiler_intrinsics.hpp>

#if KERBAL_PRIVATE_HAS_INTRINSIC_IS_TRIVIALLY_ASSIGNABLE
#	define KERBAL_SUPPORTS_IS_TRIVIALLY_ASSIGNABLE 1
#endif



#if KERBAL_SUPPORTS_IS_TRIVIALLY_ASSIGNABLE

#include <kerbal/type_traits/integral_constant.hpp>


namespace kerbal
{

	namespace type_traits
	{

		template <typename T, typename U>
		struct is_trivially_assignable :
			kerbal::type_traits::bool_constant<KERBAL_INTRINSIC_IS_TRIVIALLY_ASSIGNABLE(T, U)>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // #if KERBAL_SUPPORTS_IS_TRIVIALLY_ASSIGNABLE

#endif // #ifndef KERBAL_SUPPORTS_IS_TRIVIALLY_ASSIGNABLE

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_ASSIGNABLE_IS_TRIVIALLY_ASSIGNABLE_INTRIN_PART_HPP
