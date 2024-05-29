/**
 * @file       is_move_constructible.intrin.part.hpp
 * @brief
 * @date       2023-06-11
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_MOVE_CONSTRUCTIBLE_IS_MOVE_CONSTRUCTIBLE_INTRIN_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_MOVE_CONSTRUCTIBLE_IS_MOVE_CONSTRUCTIBLE_INTRIN_PART_HPP

#ifndef KERBAL_HAS_IS_MOVE_CONSTRUCTIBLE_SUPPORT

#include <kerbal/type_traits/detail/compiler_intrinsics/compiler_intrinsics.hpp>

#if KERBAL_PRIVATE_HAS_INTRINSIC_IS_MOVE_CONSTRUCTIBLE
#	define KERBAL_HAS_IS_MOVE_CONSTRUCTIBLE_SUPPORT 1
#endif



#if KERBAL_HAS_IS_MOVE_CONSTRUCTIBLE_SUPPORT

#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_array.hpp>
#include <kerbal/type_traits/is_function.hpp>
#include <kerbal/type_traits/logical.hpp>


namespace kerbal
{

	namespace type_traits
	{

		template <typename T>
		struct is_move_constructible :
			kerbal::type_traits::conditional<
				kerbal::type_traits::disjunction<
					kerbal::type_traits::is_array<T>,
					kerbal::type_traits::is_function<T>
				>::value,
				kerbal::type_traits::false_type,
				kerbal::type_traits::bool_constant<KERBAL_INTRINSIC_IS_MOVE_CONSTRUCTIBLE(T)>
			>::type
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // #if KERBAL_HAS_IS_MOVE_CONSTRUCTIBLE_SUPPORT

#endif // #ifndef KERBAL_HAS_IS_MOVE_CONSTRUCTIBLE_SUPPORT

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_MOVE_CONSTRUCTIBLE_IS_MOVE_CONSTRUCTIBLE_INTRIN_PART_HPP
