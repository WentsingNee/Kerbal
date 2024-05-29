/**
 * @file       is_trivially_move_constructible.intrin.part.hpp
 * @brief
 * @date       2023-05-04
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_INTRIN_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_INTRIN_PART_HPP

#ifndef KERBAL_SUPPORTS_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE

#include <kerbal/type_traits/detail/compiler_intrinsics/compiler_intrinsics.hpp>

#if KERBAL_PRIVATE_HAS_INTRINSIC_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE
#	define KERBAL_SUPPORTS_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE 1
#endif



#if KERBAL_SUPPORTS_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE

#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_array.hpp>
#include <kerbal/type_traits/is_function.hpp>
#include <kerbal/type_traits/is_reference.hpp>
#include <kerbal/type_traits/logical.hpp>


namespace kerbal
{

	namespace type_traits
	{

		template <typename T>
		struct is_trivially_move_constructible :
			kerbal::type_traits::conditional<
				kerbal::type_traits::disjunction<
					kerbal::type_traits::is_array<T>,
					kerbal::type_traits::is_function<T>
				>::value,
				kerbal::type_traits::false_type,
				kerbal::type_traits::disjunction<
					kerbal::type_traits::is_reference<T>,
					kerbal::type_traits::bool_constant<KERBAL_INTRINSIC_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE(T)>
				>
			>::type
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // #if KERBAL_SUPPORTS_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE

#endif // #ifndef KERBAL_SUPPORTS_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_INTRIN_PART_HPP
