/**
 * @file       is_trivially_destructible.intrin.part.hpp
 * @brief
 * @date       2023-05-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_DESTRUCTIBLE_IS_TRIVIALLY_DESTRUCTIBLE_INTRIN_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_DESTRUCTIBLE_IS_TRIVIALLY_DESTRUCTIBLE_INTRIN_PART_HPP

#ifndef KERBAL_SUPPORTS_IS_TRIVIALLY_DESTRUCTIBLE

#include <kerbal/type_traits/detail/compiler_intrinsics/compiler_intrinsics.hpp>

#if KERBAL_PRIVATE_HAS_INTRINSIC_IS_TRIVIALLY_DESTRUCTIBLE
#	include <kerbal/type_traits/detail/is_destructible/is_destructible.part.hpp>
#	if KERBAL_SUPPORTS_IS_DESTRUCTIBLE
#		define KERBAL_SUPPORTS_IS_TRIVIALLY_DESTRUCTIBLE 1
#	endif
#endif



#if KERBAL_SUPPORTS_IS_TRIVIALLY_DESTRUCTIBLE

#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/logical.hpp>


namespace kerbal
{

	namespace type_traits
	{

		template <typename T>
		struct is_trivially_destructible :
			kerbal::type_traits::conjunction<
				kerbal::type_traits::is_destructible<T>, // under gcc, intrinsic is_trivially_destructible gives wrong answer when the type's destructor is deleted
				kerbal::type_traits::bool_constant<
					KERBAL_INTRINSIC_IS_TRIVIALLY_DESTRUCTIBLE(T)
				>
			>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // #if KERBAL_SUPPORTS_IS_TRIVIALLY_DESTRUCTIBLE

#endif // #ifndef KERBAL_SUPPORTS_IS_TRIVIALLY_DESTRUCTIBLE

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_DESTRUCTIBLE_IS_TRIVIALLY_DESTRUCTIBLE_INTRIN_PART_HPP
