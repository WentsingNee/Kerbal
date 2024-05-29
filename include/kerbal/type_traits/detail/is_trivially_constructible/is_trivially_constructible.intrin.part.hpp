/**
 * @file       is_trivially_constructible.intrin.part.hpp
 * @brief
 * @date       2023-05-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_CONSTRUCTIBLE_IS_TRIVIALLY_CONSTRUCTIBLE_INTRIN_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_CONSTRUCTIBLE_IS_TRIVIALLY_CONSTRUCTIBLE_INTRIN_PART_HPP

#ifndef KERBAL_SUPPORTS_IS_TRIVIALLY_CONSTRUCTIBLE

#include <kerbal/type_traits/detail/compiler_intrinsics/compiler_intrinsics.hpp>

#if KERBAL_PRIVATE_HAS_INTRINSIC_IS_TRIVIALLY_CONSTRUCTIBLE
#	define KERBAL_SUPPORTS_IS_TRIVIALLY_CONSTRUCTIBLE 1
#endif



#if KERBAL_SUPPORTS_IS_TRIVIALLY_CONSTRUCTIBLE

#include <kerbal/type_traits/integral_constant.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#	include <kerbal/tmp/tppter.hpp>
#endif


namespace kerbal
{

	namespace type_traits
	{

#if __cplusplus >= 201103L

		template <typename T, typename ... Args>
		struct is_trivially_constructible :
			kerbal::type_traits::bool_constant<
				KERBAL_INTRINSIC_IS_TRIVIALLY_CONSTRUCTIBLE(T, Args...)
			>
		{
		};

#else // __cplusplus >= 201103L

#	define EMPTY
#	define LEFT_JOIN_COMMA(exp) , exp
#	define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i) = kerbal::tmp::tppter
#	define TARGS_DECL2(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#	define TARGS_USE(i) KERBAL_MACRO_CONCAT(Arg, i)

		template <typename T KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, 20)> \
		struct is_trivially_constructible;

#	define TBODY(i) \
		template <typename T KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL2, i)> \
		struct is_trivially_constructible<T KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_USE, i)> : \
			kerbal::type_traits::bool_constant< \
				KERBAL_INTRINSIC_IS_TRIVIALLY_CONSTRUCTIBLE(T KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_USE, i)) \
			> \
		{ \
		}; \

		KERBAL_PPEXPAND_N(TBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
		KERBAL_PPEXPAND_N(TBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 19)

#	undef EMPTY
#	undef LEFT_JOIN_COMMA
#	undef TARGS_DECL
#	undef TARGS_DECL2
#	undef TARGS_USE
#	undef TBODY


#endif // __cplusplus >= 201103L

	} // namespace type_traits

} // namespace kerbal

#endif // #if KERBAL_SUPPORTS_IS_TRIVIALLY_CONSTRUCTIBLE

#endif // #ifndef KERBAL_SUPPORTS_IS_TRIVIALLY_CONSTRUCTIBLE

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_CONSTRUCTIBLE_IS_TRIVIALLY_CONSTRUCTIBLE_INTRIN_PART_HPP
