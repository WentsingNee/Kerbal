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
#	define DBODY(i) \
		template <typename Ret KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
		struct function_traits<Ret(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, TARGS_USE, i))> \
		{ \
				typedef kerbal::type_traits::false_type			has_var_list; \
				typedef kerbal::type_traits::false_type			is_const; \
				typedef kerbal::type_traits::false_type			is_volatile; \
 \
				typedef Ret										return_type; \
				typedef kerbal::type_traits::integral_constant<int, i>		args_num; \
		}; \
 \
		template <typename Ret KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
		struct function_traits<Ret(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(RIGHT_JOIN_COMMA, EMPTY, TARGS_USE, i) ...)> \
		{ \
				typedef kerbal::type_traits::true_type			has_var_list; \
				typedef kerbal::type_traits::false_type			is_const; \
				typedef kerbal::type_traits::false_type			is_volatile; \
 \
				typedef Ret										return_type; \
				typedef kerbal::type_traits::integral_constant<int, i>		args_num; \
		}; \
 \
		template <typename Ret KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
		struct function_traits<Ret(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, TARGS_USE, i)) const> \
		{ \
				typedef kerbal::type_traits::false_type			has_var_list; \
				typedef kerbal::type_traits::true_type			is_const; \
				typedef kerbal::type_traits::false_type			is_volatile; \
 \
				typedef Ret										return_type; \
				typedef kerbal::type_traits::integral_constant<int, i>		args_num; \
		}; \
 \
		template <typename Ret KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
		struct function_traits<Ret(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(RIGHT_JOIN_COMMA, EMPTY, TARGS_USE, i) ...) const> \
		{ \
				typedef kerbal::type_traits::true_type			has_var_list; \
				typedef kerbal::type_traits::true_type			is_const; \
				typedef kerbal::type_traits::false_type			is_volatile; \
 \
				typedef Ret										return_type; \
				typedef kerbal::type_traits::integral_constant<int, i>		args_num; \
		}; \
 \
		template <typename Ret KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
		struct function_traits<Ret(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, TARGS_USE, i)) volatile> \
		{ \
				typedef kerbal::type_traits::false_type			has_var_list; \
				typedef kerbal::type_traits::false_type			is_const; \
				typedef kerbal::type_traits::true_type			is_volatile; \
 \
				typedef Ret										return_type; \
				typedef kerbal::type_traits::integral_constant<int, i>		args_num; \
		}; \
 \
		template <typename Ret KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
		struct function_traits<Ret(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(RIGHT_JOIN_COMMA, EMPTY, TARGS_USE, i) ...) volatile> \
		{ \
				typedef kerbal::type_traits::true_type			has_var_list; \
				typedef kerbal::type_traits::false_type			is_const; \
				typedef kerbal::type_traits::true_type			is_volatile; \
 \
				typedef Ret										return_type; \
				typedef kerbal::type_traits::integral_constant<int, i>		args_num; \
		}; \
 \
		template <typename Ret KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
		struct function_traits<Ret(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, TARGS_USE, i)) const volatile> \
		{ \
				typedef kerbal::type_traits::false_type			has_var_list; \
				typedef kerbal::type_traits::true_type			is_const; \
				typedef kerbal::type_traits::true_type			is_volatile; \
 \
				typedef Ret										return_type; \
				typedef kerbal::type_traits::integral_constant<int, i>		args_num; \
		}; \
 \
		template <typename Ret KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
		struct function_traits<Ret(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(RIGHT_JOIN_COMMA, EMPTY, TARGS_USE, i) ...) const volatile> \
		{ \
				typedef kerbal::type_traits::true_type			has_var_list; \
				typedef kerbal::type_traits::true_type			is_const; \
				typedef kerbal::type_traits::true_type			is_volatile; \
 \
				typedef Ret										return_type; \
				typedef kerbal::type_traits::integral_constant<int, i>		args_num; \
		};

		KERBAL_PPEXPAND_N(DBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
		KERBAL_PPEXPAND_N(DBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#	undef EMPTY
#	undef REMAINF
#	undef LEFT_JOIN_COMMA
#	undef RIGHT_JOIN_COMMA
#	undef TARGS_DECL
#	undef TARGS_USE
#	undef DBODY


#	else // __cplusplus >= 201103L

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args...)>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;
				typedef kerbal::type_traits::false_type			is_lref;
				typedef kerbal::type_traits::false_type			is_rref;
#	if __cplusplus >= 201703L
				typedef kerbal::type_traits::false_type			is_noexcept;
#	endif // __cplusplus >= 201703L

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args..., ...)>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;
				typedef kerbal::type_traits::false_type			is_lref;
				typedef kerbal::type_traits::false_type			is_rref;
#	if __cplusplus >= 201703L
				typedef kerbal::type_traits::false_type			is_noexcept;
#	endif // __cplusplus >= 201703L

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args...) const>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;
				typedef kerbal::type_traits::false_type			is_lref;
				typedef kerbal::type_traits::false_type			is_rref;
#	if __cplusplus >= 201703L
				typedef kerbal::type_traits::false_type			is_noexcept;
#	endif // __cplusplus >= 201703L

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args..., ...) const>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;
				typedef kerbal::type_traits::false_type			is_lref;
				typedef kerbal::type_traits::false_type			is_rref;
#	if __cplusplus >= 201703L
				typedef kerbal::type_traits::false_type			is_noexcept;
#	endif // __cplusplus >= 201703L

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args...) volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;
				typedef kerbal::type_traits::false_type			is_lref;
				typedef kerbal::type_traits::false_type			is_rref;
#	if __cplusplus >= 201703L
				typedef kerbal::type_traits::false_type			is_noexcept;
#	endif // __cplusplus >= 201703L

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args..., ...) volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;
				typedef kerbal::type_traits::false_type			is_lref;
				typedef kerbal::type_traits::false_type			is_rref;
#	if __cplusplus >= 201703L
				typedef kerbal::type_traits::false_type			is_noexcept;
#	endif // __cplusplus >= 201703L

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args...) const volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;
				typedef kerbal::type_traits::false_type			is_lref;
				typedef kerbal::type_traits::false_type			is_rref;
#	if __cplusplus >= 201703L
				typedef kerbal::type_traits::false_type			is_noexcept;
#	endif // __cplusplus >= 201703L

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args..., ...) const volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;
				typedef kerbal::type_traits::false_type			is_lref;
				typedef kerbal::type_traits::false_type			is_rref;
#	if __cplusplus >= 201703L
				typedef kerbal::type_traits::false_type			is_noexcept;
#	endif // __cplusplus >= 201703L

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args...) &>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;
				typedef kerbal::type_traits::true_type			is_lref;
				typedef kerbal::type_traits::false_type			is_rref;
#	if __cplusplus >= 201703L
				typedef kerbal::type_traits::false_type			is_noexcept;
#	endif // __cplusplus >= 201703L

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args..., ...) &>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;
				typedef kerbal::type_traits::true_type			is_lref;
				typedef kerbal::type_traits::false_type			is_rref;
#	if __cplusplus >= 201703L
				typedef kerbal::type_traits::false_type			is_noexcept;
#	endif // __cplusplus >= 201703L

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args...) const &>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;
				typedef kerbal::type_traits::true_type			is_lref;
				typedef kerbal::type_traits::false_type			is_rref;
#	if __cplusplus >= 201703L
				typedef kerbal::type_traits::false_type			is_noexcept;
#	endif // __cplusplus >= 201703L

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args..., ...) const &>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;
				typedef kerbal::type_traits::true_type			is_lref;
				typedef kerbal::type_traits::false_type			is_rref;
#	if __cplusplus >= 201703L
				typedef kerbal::type_traits::false_type			is_noexcept;
#	endif // __cplusplus >= 201703L

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args...) volatile &>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;
				typedef kerbal::type_traits::true_type			is_lref;
				typedef kerbal::type_traits::false_type			is_rref;
#	if __cplusplus >= 201703L
				typedef kerbal::type_traits::false_type			is_noexcept;
#	endif // __cplusplus >= 201703L

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args..., ...) volatile &>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;
				typedef kerbal::type_traits::true_type			is_lref;
				typedef kerbal::type_traits::false_type			is_rref;
#	if __cplusplus >= 201703L
				typedef kerbal::type_traits::false_type			is_noexcept;
#	endif // __cplusplus >= 201703L

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args...) const volatile &>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;
				typedef kerbal::type_traits::true_type			is_lref;
				typedef kerbal::type_traits::false_type			is_rref;
#	if __cplusplus >= 201703L
				typedef kerbal::type_traits::false_type			is_noexcept;
#	endif // __cplusplus >= 201703L

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args..., ...) const volatile &>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;
				typedef kerbal::type_traits::true_type			is_lref;
				typedef kerbal::type_traits::false_type			is_rref;
#	if __cplusplus >= 201703L
				typedef kerbal::type_traits::false_type			is_noexcept;
#	endif // __cplusplus >= 201703L

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args...) &&>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;
				typedef kerbal::type_traits::false_type			is_lref;
				typedef kerbal::type_traits::true_type			is_rref;
#	if __cplusplus >= 201703L
				typedef kerbal::type_traits::false_type			is_noexcept;
#	endif // __cplusplus >= 201703L

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args..., ...) &&>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;
				typedef kerbal::type_traits::false_type			is_lref;
				typedef kerbal::type_traits::true_type			is_rref;
#	if __cplusplus >= 201703L
				typedef kerbal::type_traits::false_type			is_noexcept;
#	endif // __cplusplus >= 201703L

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args...) const &&>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;
				typedef kerbal::type_traits::false_type			is_lref;
				typedef kerbal::type_traits::true_type			is_rref;
#	if __cplusplus >= 201703L
				typedef kerbal::type_traits::false_type			is_noexcept;
#	endif // __cplusplus >= 201703L

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args..., ...) const &&>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;
				typedef kerbal::type_traits::false_type			is_lref;
				typedef kerbal::type_traits::true_type			is_rref;
#	if __cplusplus >= 201703L
				typedef kerbal::type_traits::false_type			is_noexcept;
#	endif // __cplusplus >= 201703L

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args...) volatile &&>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;
				typedef kerbal::type_traits::false_type			is_lref;
				typedef kerbal::type_traits::true_type			is_rref;
#	if __cplusplus >= 201703L
				typedef kerbal::type_traits::false_type			is_noexcept;
#	endif // __cplusplus >= 201703L

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args..., ...) volatile &&>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;
				typedef kerbal::type_traits::false_type			is_lref;
				typedef kerbal::type_traits::true_type			is_rref;
#	if __cplusplus >= 201703L
				typedef kerbal::type_traits::false_type			is_noexcept;
#	endif // __cplusplus >= 201703L

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args...) const volatile &&>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;
				typedef kerbal::type_traits::false_type			is_lref;
				typedef kerbal::type_traits::true_type			is_rref;
#	if __cplusplus >= 201703L
				typedef kerbal::type_traits::false_type			is_noexcept;
#	endif // __cplusplus >= 201703L

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args..., ...) const volatile &&>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;
				typedef kerbal::type_traits::false_type			is_lref;
				typedef kerbal::type_traits::true_type			is_rref;
#	if __cplusplus >= 201703L
				typedef kerbal::type_traits::false_type			is_noexcept;
#	endif // __cplusplus >= 201703L

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

#		if __cplusplus >= 201703L

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args...) noexcept>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;
				typedef kerbal::type_traits::false_type			is_lref;
				typedef kerbal::type_traits::false_type			is_rref;
				typedef kerbal::type_traits::true_type			is_noexcept;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args..., ...) noexcept>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;
				typedef kerbal::type_traits::false_type			is_lref;
				typedef kerbal::type_traits::false_type			is_rref;
				typedef kerbal::type_traits::true_type			is_noexcept;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args...) const noexcept>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;
				typedef kerbal::type_traits::false_type			is_lref;
				typedef kerbal::type_traits::false_type			is_rref;
				typedef kerbal::type_traits::true_type			is_noexcept;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args..., ...) const noexcept>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;
				typedef kerbal::type_traits::false_type			is_lref;
				typedef kerbal::type_traits::false_type			is_rref;
				typedef kerbal::type_traits::true_type			is_noexcept;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args...) volatile noexcept>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;
				typedef kerbal::type_traits::false_type			is_lref;
				typedef kerbal::type_traits::false_type			is_rref;
				typedef kerbal::type_traits::true_type			is_noexcept;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args..., ...) volatile noexcept>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;
				typedef kerbal::type_traits::false_type			is_lref;
				typedef kerbal::type_traits::false_type			is_rref;
				typedef kerbal::type_traits::true_type			is_noexcept;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args...) const volatile noexcept>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;
				typedef kerbal::type_traits::false_type			is_lref;
				typedef kerbal::type_traits::false_type			is_rref;
				typedef kerbal::type_traits::true_type			is_noexcept;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args..., ...) const volatile noexcept>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;
				typedef kerbal::type_traits::false_type			is_lref;
				typedef kerbal::type_traits::false_type			is_rref;
				typedef kerbal::type_traits::true_type			is_noexcept;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args...) & noexcept>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;
				typedef kerbal::type_traits::true_type			is_lref;
				typedef kerbal::type_traits::false_type			is_rref;
				typedef kerbal::type_traits::true_type			is_noexcept;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args..., ...) & noexcept>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;
				typedef kerbal::type_traits::true_type			is_lref;
				typedef kerbal::type_traits::false_type			is_rref;
				typedef kerbal::type_traits::true_type			is_noexcept;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args...) const & noexcept>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;
				typedef kerbal::type_traits::true_type			is_lref;
				typedef kerbal::type_traits::false_type			is_rref;
				typedef kerbal::type_traits::true_type			is_noexcept;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args..., ...) const & noexcept>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;
				typedef kerbal::type_traits::true_type			is_lref;
				typedef kerbal::type_traits::false_type			is_rref;
				typedef kerbal::type_traits::true_type			is_noexcept;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args...) volatile & noexcept>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;
				typedef kerbal::type_traits::true_type			is_lref;
				typedef kerbal::type_traits::false_type			is_rref;
				typedef kerbal::type_traits::true_type			is_noexcept;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args..., ...) volatile & noexcept>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;
				typedef kerbal::type_traits::true_type			is_lref;
				typedef kerbal::type_traits::false_type			is_rref;
				typedef kerbal::type_traits::true_type			is_noexcept;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args...) const volatile & noexcept>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;
				typedef kerbal::type_traits::true_type			is_lref;
				typedef kerbal::type_traits::false_type			is_rref;
				typedef kerbal::type_traits::true_type			is_noexcept;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args..., ...) const volatile & noexcept>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;
				typedef kerbal::type_traits::true_type			is_lref;
				typedef kerbal::type_traits::false_type			is_rref;
				typedef kerbal::type_traits::true_type			is_noexcept;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args...) && noexcept>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;
				typedef kerbal::type_traits::false_type			is_lref;
				typedef kerbal::type_traits::true_type			is_rref;
				typedef kerbal::type_traits::true_type			is_noexcept;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args..., ...) && noexcept>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;
				typedef kerbal::type_traits::false_type			is_lref;
				typedef kerbal::type_traits::true_type			is_rref;
				typedef kerbal::type_traits::true_type			is_noexcept;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args...) const && noexcept>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;
				typedef kerbal::type_traits::false_type			is_lref;
				typedef kerbal::type_traits::true_type			is_rref;
				typedef kerbal::type_traits::true_type			is_noexcept;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args..., ...) const && noexcept>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;
				typedef kerbal::type_traits::false_type			is_lref;
				typedef kerbal::type_traits::true_type			is_rref;
				typedef kerbal::type_traits::true_type			is_noexcept;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args...) volatile && noexcept>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;
				typedef kerbal::type_traits::false_type			is_lref;
				typedef kerbal::type_traits::true_type			is_rref;
				typedef kerbal::type_traits::true_type			is_noexcept;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args..., ...) volatile && noexcept>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;
				typedef kerbal::type_traits::false_type			is_lref;
				typedef kerbal::type_traits::true_type			is_rref;
				typedef kerbal::type_traits::true_type			is_noexcept;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args...) const volatile && noexcept>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;
				typedef kerbal::type_traits::false_type			is_lref;
				typedef kerbal::type_traits::true_type			is_rref;
				typedef kerbal::type_traits::true_type			is_noexcept;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args..., ...) const volatile && noexcept>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;
				typedef kerbal::type_traits::false_type			is_lref;
				typedef kerbal::type_traits::true_type			is_rref;
				typedef kerbal::type_traits::true_type			is_noexcept;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
				template <size_t i>
				struct argument: kerbal::type_traits::type_chooser<i, Args...>
				{
				};
		};

#		endif // __cplusplus >= 201703L

#	endif // __cplusplus < 201103L


	} // namespace function

} // namespace kerbal

#endif // KERBAL_FUNCTION_FUNCTION_TRAITS_HPP


