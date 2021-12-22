/**
 * @file       function_traits.hpp
 * @brief
 * @date       2020-4-19
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_FUNCTION_FUNCTION_TRAITS_HPP
#define KERBAL_FUNCTION_FUNCTION_TRAITS_HPP

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

	namespace function
	{

		MODULE_EXPORT
		template <typename >
		struct function_traits;

#	if __cplusplus < 201103L

#	define EMPTY
#	define REMAINF(exp) exp
#	define LEFT_JOIN_COMMA(exp) , exp
#	define RIGHT_JOIN_COMMA(exp) exp ,
#	define TARGS_DECL(i) KERBAL_MACRO_CONCAT(typename T, i)
#	define TARGS_USE(i) KERBAL_MACRO_CONCAT(T, i)
#	define VAR_LIST ...

#	define FUNCTION_TRAITS_VAR_LIST_DEF(i, VAR_L, HAS_VAR_LIST, CV_QUALIFIER, IS_CONST, IS_VOLATILE) \
		template <typename Ret KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
		struct function_traits<Ret(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, TARGS_USE, i) VAR_L) CV_QUALIFIER> \
		{ \
				typedef kerbal::type_traits::HAS_VAR_LIST		has_var_list; \
				typedef kerbal::type_traits::IS_CONST			is_const; \
				typedef kerbal::type_traits::IS_VOLATILE		is_volatile; \
 \
				typedef Ret										return_type; \
				typedef kerbal::type_traits::integral_constant<int, i>		args_num; \
		};

#	define FUNCTION_TRAITS_CV_DEF(i, CV_QUALIFIER, IS_CONST, IS_VOLATILE) \
		FUNCTION_TRAITS_VAR_LIST_DEF(i, EMPTY,    false_type, CV_QUALIFIER, IS_CONST, IS_VOLATILE) \
		FUNCTION_TRAITS_VAR_LIST_DEF(i, VAR_LIST, true_type,  CV_QUALIFIER, IS_CONST, IS_VOLATILE)

#	define DBODY(i) \
		FUNCTION_TRAITS_CV_DEF(i, EMPTY, false_type, false_type) \
		FUNCTION_TRAITS_CV_DEF(i, const, true_type, false_type) \
		FUNCTION_TRAITS_CV_DEF(i, volatile, false_type, true_type) \
		FUNCTION_TRAITS_CV_DEF(i, const volatile, true_type, true_type)

		KERBAL_PPEXPAND_N(DBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
		KERBAL_PPEXPAND_N(DBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#	undef EMPTY
#	undef REMAINF
#	undef LEFT_JOIN_COMMA
#	undef RIGHT_JOIN_COMMA
#	undef TARGS_DECL
#	undef TARGS_USE
#	undef VAR_LIST
#	undef FUNCTION_TRAITS_VAR_LIST_DEF
#	undef FUNCTION_TRAITS_CV_DEF
#	undef DBODY


#	else // __cplusplus >= 201103L

#	define EMPTY
#	define VAR_LIST ,...

#if __cplusplus < 201703L
#	define IS_NOEXCEPT_DEF(IS_NOEXCEPT)
#else
#	define IS_NOEXCEPT_DEF(IS_NOEXCEPT) typedef kerbal::type_traits::IS_NOEXCEPT			is_noexcept;
#endif // __cplusplus < 201703L

#	define FUNCTION_TRAITS_VAR_LIST_DEF(VAR_L, HAS_VAR_LIST, CV_QUALIFIER, IS_CONST, IS_VOLATILE, REF_QUALIFIER, IS_LREF, IS_RREF, NOEXCEPT_QUALIFIER, IS_NOEXCEPT) \
		MODULE_EXPORT \
		template <typename Ret, typename ... Args> \
		struct function_traits<Ret(Args... VAR_L) CV_QUALIFIER REF_QUALIFIER NOEXCEPT_QUALIFIER> \
		{ \
				typedef kerbal::type_traits::HAS_VAR_LIST		has_var_list; \
				typedef kerbal::type_traits::IS_CONST			is_const; \
				typedef kerbal::type_traits::IS_VOLATILE		is_volatile; \
				typedef kerbal::type_traits::IS_LREF			is_lref; \
				typedef kerbal::type_traits::IS_RREF			is_rref; \
				IS_NOEXCEPT_DEF(IS_NOEXCEPT) \
				typedef Ret										return_type; \
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num; \
				template <size_t i> \
				struct argument: kerbal::type_traits::type_chooser<i, Args...> \
				{ \
				}; \
		};

#	define FUNCTION_TRAITS_CV_DEF(CV_QUALIFIER, IS_CONST, IS_VOLATILE, REF_QUALIFIER, IS_LREF, IS_RREF, NOEXCEPT_QUALIFIER, IS_NOEXCEPT) \
		FUNCTION_TRAITS_VAR_LIST_DEF(EMPTY,    false_type, CV_QUALIFIER, IS_CONST, IS_VOLATILE, REF_QUALIFIER, IS_LREF, IS_RREF, NOEXCEPT_QUALIFIER, IS_NOEXCEPT) \
		FUNCTION_TRAITS_VAR_LIST_DEF(VAR_LIST, true_type,  CV_QUALIFIER, IS_CONST, IS_VOLATILE, REF_QUALIFIER, IS_LREF, IS_RREF, NOEXCEPT_QUALIFIER, IS_NOEXCEPT)

#	define FUNCTION_TRAITS_REF_DEF(REF_QUALIFIER, IS_LREF, IS_RREF, NOEXCEPT_QUALIFIER, IS_NOEXCEPT) \
		FUNCTION_TRAITS_CV_DEF(EMPTY,          false_type, false_type, REF_QUALIFIER, IS_LREF, IS_RREF, NOEXCEPT_QUALIFIER, IS_NOEXCEPT) \
		FUNCTION_TRAITS_CV_DEF(const,          true_type,  false_type, REF_QUALIFIER, IS_LREF, IS_RREF, NOEXCEPT_QUALIFIER, IS_NOEXCEPT) \
		FUNCTION_TRAITS_CV_DEF(volatile,       false_type, true_type,  REF_QUALIFIER, IS_LREF, IS_RREF, NOEXCEPT_QUALIFIER, IS_NOEXCEPT) \
		FUNCTION_TRAITS_CV_DEF(const volatile, true_type,  true_type,  REF_QUALIFIER, IS_LREF, IS_RREF, NOEXCEPT_QUALIFIER, IS_NOEXCEPT)

#	define FUNCTION_TRAITS_NOEXCEPT_DEF(NOEXCEPT_QUALIFIER, IS_NOEXCEPT) \
		FUNCTION_TRAITS_REF_DEF(EMPTY, false_type, false_type, NOEXCEPT_QUALIFIER, IS_NOEXCEPT) \
		FUNCTION_TRAITS_REF_DEF(&,     true_type,  false_type, NOEXCEPT_QUALIFIER, IS_NOEXCEPT) \
		FUNCTION_TRAITS_REF_DEF(&&,    false_type, true_type,  NOEXCEPT_QUALIFIER, IS_NOEXCEPT)


		FUNCTION_TRAITS_NOEXCEPT_DEF(EMPTY,    false_type)
#	if __cplusplus >= 201703L
		FUNCTION_TRAITS_NOEXCEPT_DEF(noexcept, true_type)
#	endif // __cplusplus >= 201703L


#	undef EMPTY
#	undef VAR_LIST
#	undef IS_NOEXCEPT_DEF
#	undef FUNCTION_TRAITS_VAR_LIST_DEF
#	undef FUNCTION_TRAITS_CV_DEF
#	undef FUNCTION_TRAITS_REF_DEF
#	undef FUNCTION_TRAITS_NOEXCEPT_DEF


#	endif // __cplusplus < 201103L


	} // namespace function

} // namespace kerbal

#endif // KERBAL_FUNCTION_FUNCTION_TRAITS_HPP


