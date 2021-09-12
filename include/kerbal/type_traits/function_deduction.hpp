/**
 * @file       function_deduction.hpp
 * @brief
 * @date       2019-6-25
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_FUNCTION_DEDUCTION_HPP
#define KERBAL_TYPE_TRAITS_FUNCTION_DEDUCTION_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/type_chooser.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#include <cstddef>


namespace kerbal
{

	namespace type_traits
	{

		MODULE_EXPORT
		template <typename >
		struct is_function: kerbal::type_traits::false_type {};

#	if __cplusplus < 201103L

#	define EMPTY
#	define REMAINF(exp) exp
#	define LEFT_JOIN_COMMA(exp) , exp
#	define RIGHT_JOIN_COMMA(exp) exp ,
#	define TARGS_DECL(i) KERBAL_MACRO_CONCAT(typename T, i)
#	define TARGS_USE(i) KERBAL_MACRO_CONCAT(T, i)
#	define DBODY(i) \
		template <typename Ret KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
		struct is_function<Ret(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, TARGS_USE, i))>: kerbal::type_traits::true_type {}; \
 \
		template <typename Ret KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
		struct is_function<Ret(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(RIGHT_JOIN_COMMA, EMPTY, TARGS_USE, i) ...)>: kerbal::type_traits::true_type {}; \
 \
		template <typename Ret KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
		struct is_function<Ret(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, TARGS_USE, i)) const>: kerbal::type_traits::true_type {}; \
 \
		template <typename Ret KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
		struct is_function<Ret(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(RIGHT_JOIN_COMMA, EMPTY, TARGS_USE, i) ...) const>: kerbal::type_traits::true_type {}; \
 \
		template <typename Ret KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
		struct is_function<Ret(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, TARGS_USE, i)) volatile>: kerbal::type_traits::true_type {}; \
 \
		template <typename Ret KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
		struct is_function<Ret(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(RIGHT_JOIN_COMMA, EMPTY, TARGS_USE, i) ...) volatile>: kerbal::type_traits::true_type {}; \
 \
		template <typename Ret KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
		struct is_function<Ret(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, TARGS_USE, i)) const volatile>: kerbal::type_traits::true_type {}; \
 \
		template <typename Ret KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
		struct is_function<Ret(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(RIGHT_JOIN_COMMA, EMPTY, TARGS_USE, i) ...) const volatile>: kerbal::type_traits::true_type {};

		KERBAL_PPEXPAND_N(DBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
		KERBAL_PPEXPAND_N(DBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#	undef EMPTY
#	undef REMAINF
#	undef LEFT_JOIN_COMMA
#	undef RIGHT_JOIN_COMMA
#	undef TARGS_DECL
#	undef TARGS_USE
#	undef DBODY


#	else // __cplusplus < 201103L

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args...)>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args..., ...)>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args...) const>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args..., ...) const>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args...) volatile>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args..., ...) volatile>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args...) const volatile>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args..., ...) const volatile>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args...) &>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args..., ...) &>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args...) const &>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args..., ...) const &>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args...) volatile &>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args..., ...) volatile &>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args...) const volatile &>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args..., ...) const volatile &>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args...) &&>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args..., ...) &&>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args...) const &&>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args..., ...) const &&>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args...) volatile &&>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args..., ...) volatile &&>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args...) const volatile &&>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args..., ...) const volatile &&>: kerbal::type_traits::true_type {};

#		if __cplusplus >= 201703L

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args...) noexcept>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args..., ...) noexcept>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args...) const noexcept>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args..., ...) const noexcept>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args...) volatile noexcept>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args..., ...) volatile noexcept>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args...) const volatile noexcept>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args..., ...) const volatile noexcept>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args...) & noexcept>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args..., ...) & noexcept>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args...) const & noexcept>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args..., ...) const & noexcept>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args...) volatile & noexcept>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args..., ...) volatile & noexcept>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args...) const volatile & noexcept>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args..., ...) const volatile & noexcept>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args...) && noexcept>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args..., ...) && noexcept>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args...) const && noexcept>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args..., ...) const && noexcept>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args...) volatile && noexcept>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args..., ...) volatile && noexcept>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args...) const volatile && noexcept>: kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args..., ...) const volatile && noexcept>: kerbal::type_traits::true_type {};

#		endif // __cplusplus >= 201703L

#	endif // __cplusplus < 201103L


	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_FUNCTION_DEDUCTION_HPP


