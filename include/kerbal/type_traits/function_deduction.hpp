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
#include <kerbal/compatibility/cv_qualified_function.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

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

#if __cplusplus < 201103L

#	define EMPTY
#	define REMAINF(exp) exp
#	define LEFT_JOIN_COMMA(exp) , exp
#	define RIGHT_JOIN_COMMA(exp) exp ,
#	define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(T, i)
#	define TARGS_USE(i) KERBAL_MACRO_CONCAT(T, i)
#	define DBODY_BASIC(i, CV_QUALIFIER) \
		template <typename Ret KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
		struct is_function<Ret(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, TARGS_USE, i)) CV_QUALIFIER>: kerbal::type_traits::true_type {}; \
 \
		template <typename Ret KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
		struct is_function<Ret(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(RIGHT_JOIN_COMMA, EMPTY, TARGS_USE, i) ...) CV_QUALIFIER>: kerbal::type_traits::true_type {};

#if KERBAL_HAS_CV_QUALIFIED_FUNCTION_SUPPORT
#	define DBODY(i) \
		DBODY_BASIC(i, EMPTY) \
		DBODY_BASIC(i, const) \
		DBODY_BASIC(i, volatile) \
		DBODY_BASIC(i, const volatile)
#else
#	define DBODY(i) \
		DBODY_BASIC(i, EMPTY)
#endif

		KERBAL_PPEXPAND_N(DBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
		KERBAL_PPEXPAND_N(DBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#	undef EMPTY
#	undef REMAINF
#	undef LEFT_JOIN_COMMA
#	undef RIGHT_JOIN_COMMA
#	undef TARGS_DECL
#	undef TARGS_USE
#	undef DBODY_BASIC
#	undef DBODY


#else // __cplusplus < 201103L


#	define EMPTY
#	define VAR_LIST ,...

#	define IS_FUNCTION_VAR_LIST_DEF(VAR_L, CV_QUALIFIER, REF_QUALIFIER, NOEXCEPT_QUALIFIER) \
		MODULE_EXPORT \
		template <typename Ret, typename ... Args> \
		struct is_function<Ret(Args... VAR_L) CV_QUALIFIER REF_QUALIFIER NOEXCEPT_QUALIFIER>: kerbal::type_traits::true_type {}; \

#	define IS_FUNCTION_CV_DEF(CV_QUALIFIER, REF_QUALIFIER, NOEXCEPT_QUALIFIER) \
		IS_FUNCTION_VAR_LIST_DEF(EMPTY,    CV_QUALIFIER, REF_QUALIFIER, NOEXCEPT_QUALIFIER) \
		IS_FUNCTION_VAR_LIST_DEF(VAR_LIST, CV_QUALIFIER, REF_QUALIFIER, NOEXCEPT_QUALIFIER)

#	define IS_FUNCTION_REF_DEF(REF_QUALIFIER, NOEXCEPT_QUALIFIER) \
		IS_FUNCTION_CV_DEF(EMPTY,          REF_QUALIFIER, NOEXCEPT_QUALIFIER) \
		IS_FUNCTION_CV_DEF(const,          REF_QUALIFIER, NOEXCEPT_QUALIFIER) \
		IS_FUNCTION_CV_DEF(volatile,       REF_QUALIFIER, NOEXCEPT_QUALIFIER) \
		IS_FUNCTION_CV_DEF(const volatile, REF_QUALIFIER, NOEXCEPT_QUALIFIER)

#	define IS_FUNCTION_NOEXCEPT_DEF(NOEXCEPT_QUALIFIER) \
		IS_FUNCTION_REF_DEF(EMPTY, NOEXCEPT_QUALIFIER) \
		IS_FUNCTION_REF_DEF(&,     NOEXCEPT_QUALIFIER) \
		IS_FUNCTION_REF_DEF(&&,    NOEXCEPT_QUALIFIER)


		IS_FUNCTION_NOEXCEPT_DEF(EMPTY)
#	if __cplusplus >= 201703L
		IS_FUNCTION_NOEXCEPT_DEF(noexcept)
#	endif // __cplusplus >= 201703L

#	undef EMPTY
#	undef VAR_LIST
#	undef IS_FUNCTION_VAR_LIST_DEF
#	undef IS_FUNCTION_CV_DEF
#	undef IS_FUNCTION_REF_DEF
#	undef IS_FUNCTION_NOEXCEPT_DEF


#endif // __cplusplus < 201103L


	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_FUNCTION_DEDUCTION_HPP
