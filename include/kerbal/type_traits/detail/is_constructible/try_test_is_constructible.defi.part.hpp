/**
 * @file       try_test_is_constructible.defi.part.hpp
 * @brief
 * @date       2023-04-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_CONSTRUCTIBLE_TRY_TEST_IS_CONSTRUCTIBLE_DEFI_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_CONSTRUCTIBLE_TRY_TEST_IS_CONSTRUCTIBLE_DEFI_PART_HPP

#include <kerbal/type_traits/detail/is_constructible/is_constructible.part.hpp>

#include <kerbal/type_traits/tribool_constant.hpp>

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
		struct try_test_is_constructible :
				kerbal::type_traits::tribool_constant<
					!!kerbal::type_traits::is_constructible<T, Args...>::value
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
		struct try_test_is_constructible;

#	define TBODY(i) \
		template <typename T KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL2, i)> \
		struct try_test_is_constructible<T KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_USE, i)> : \
				kerbal::type_traits::tribool_constant< \
					!!kerbal::type_traits::is_constructible<T KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_USE, i)>::value \
				> \
		{ \
		};

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


#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_CONSTRUCTIBLE_TRY_TEST_IS_CONSTRUCTIBLE_DEFI_PART_HPP
