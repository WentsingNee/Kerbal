/**
 * @file       tuple.fwd.hpp
 * @brief
 * @date       2021-11-22
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TUPLE_TUPLE_TUPLE_FWD_HPP
#define KERBAL_TUPLE_TUPLE_TUPLE_FWD_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/remove_cvref.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#	include <kerbal/tmp/tppter.hpp>
#endif


namespace kerbal
{

	namespace utility
	{

		struct tuple_partially_init_t {};

#if __cplusplus < 201103L


#	define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i) = kerbal::tmp::tppter

		template <KERBAL_PPEXPAND_WITH_COMMA_N(TARGS_DECL, 20)> \
		struct tuple;

#	undef TARGS_DECL


#	define EMPTY
#	define REMAINF(exp) exp
#	define THEAD_NOT_EMPTY(exp) template <exp>
#	define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#	define TARGS_USE(i) KERBAL_MACRO_CONCAT(Arg, i)
#	define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#	define FBODY(i) \
		KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
		inline \
		kerbal::utility::tuple<KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, TARGS_USE, i)> \
		make_tuple(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)); \

		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 19)

#	undef EMPTY
#	undef REMAINF
#	undef THEAD_NOT_EMPTY
#	undef TARGS_DECL
#	undef TARGS_USE
#	undef ARGS_DECL
#	undef FBODY


#	define EMPTY
#	define REMAINF(exp) exp
#	define THEAD_NOT_EMPTY(exp) template <exp>
#	define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#	define TARGS_USE(i) KERBAL_MACRO_CONCAT(Arg, i) &
#	define ARGS_DECL(i) KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#	define FBODY(i) \
		KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
		inline \
		kerbal::utility::tuple<KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, TARGS_USE, i)> \
		tie(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)); \

		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 19)

#	undef EMPTY
#	undef REMAINF
#	undef THEAD_NOT_EMPTY
#	undef TARGS_DECL
#	undef TARGS_USE
#	undef ARGS_DECL
#	undef FBODY


#else

		template <typename ... Args>
		struct tuple;

		template <typename ... Args>
		KERBAL_CONSTEXPR
		kerbal::utility::tuple<typename kerbal::type_traits::remove_cvref<Args>::type...>
		make_tuple(Args && ... args);

		template <typename ... Args>
		KERBAL_CONSTEXPR
		kerbal::utility::tuple<Args & ...>
		tie(Args & ... args) KERBAL_NOEXCEPT;

		template <typename ... Args>
		KERBAL_CONSTEXPR
		kerbal::utility::tuple<Args && ...>
		forward_as_tuple(Args && ... args);

#endif


		template <std::size_t I, typename Tp>
		struct tuple_element;

	} // namespace utility

} // namespace kerbal


#endif // KERBAL_TUPLE_TUPLE_TUPLE_FWD_HPP
