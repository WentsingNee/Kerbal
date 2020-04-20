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

#include <cstddef>

namespace kerbal
{
	namespace function
	{

		MODULE_EXPORT
		template <typename >
		struct function_traits;

#	if __cplusplus < 201103L

		template <typename Ret>
		struct function_traits<Ret()>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 0>		args_num;
		};

		template <typename Ret>
		struct function_traits<Ret(...)>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 0>		args_num;
		};

		template <typename Ret>
		struct function_traits<Ret() const>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 0>		args_num;
		};

		template <typename Ret>
		struct function_traits<Ret(...) const>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 0>		args_num;
		};

		template <typename Ret>
		struct function_traits<Ret() volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 0>		args_num;
		};

		template <typename Ret>
		struct function_traits<Ret(...) volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 0>		args_num;
		};

		template <typename Ret>
		struct function_traits<Ret() const volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 0>		args_num;
		};

		template <typename Ret>
		struct function_traits<Ret(...) const volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 0>		args_num;
		};

		template <typename Ret, typename T0>
		struct function_traits<Ret(T0)>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 1>		args_num;
		};

		template <typename Ret, typename T0>
		struct function_traits<Ret(T0, ...)>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 1>		args_num;
		};

		template <typename Ret, typename T0>
		struct function_traits<Ret(T0) const>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 1>		args_num;
		};

		template <typename Ret, typename T0>
		struct function_traits<Ret(T0, ...) const>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 1>		args_num;
		};

		template <typename Ret, typename T0>
		struct function_traits<Ret(T0) volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 1>		args_num;
		};

		template <typename Ret, typename T0>
		struct function_traits<Ret(T0, ...) volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 1>		args_num;
		};

		template <typename Ret, typename T0>
		struct function_traits<Ret(T0) const volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 1>		args_num;
		};

		template <typename Ret, typename T0>
		struct function_traits<Ret(T0, ...) const volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 1>		args_num;
		};

		template <typename Ret, typename T0, typename T1>
		struct function_traits<Ret(T0, T1)>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 2>		args_num;
		};

		template <typename Ret, typename T0, typename T1>
		struct function_traits<Ret(T0, T1, ...)>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 2>		args_num;
		};

		template <typename Ret, typename T0, typename T1>
		struct function_traits<Ret(T0, T1) const>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 2>		args_num;
		};

		template <typename Ret, typename T0, typename T1>
		struct function_traits<Ret(T0, T1, ...) const>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 2>		args_num;
		};

		template <typename Ret, typename T0, typename T1>
		struct function_traits<Ret(T0, T1) volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 2>		args_num;
		};

		template <typename Ret, typename T0, typename T1>
		struct function_traits<Ret(T0, T1, ...) volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 2>		args_num;
		};

		template <typename Ret, typename T0, typename T1>
		struct function_traits<Ret(T0, T1) const volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 2>		args_num;
		};

		template <typename Ret, typename T0, typename T1>
		struct function_traits<Ret(T0, T1, ...) const volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 2>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2>
		struct function_traits<Ret(T0, T1, T2)>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 3>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2>
		struct function_traits<Ret(T0, T1, T2, ...)>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 3>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2>
		struct function_traits<Ret(T0, T1, T2) const>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 3>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2>
		struct function_traits<Ret(T0, T1, T2, ...) const>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 3>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2>
		struct function_traits<Ret(T0, T1, T2) volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 3>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2>
		struct function_traits<Ret(T0, T1, T2, ...) volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 3>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2>
		struct function_traits<Ret(T0, T1, T2) const volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 3>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2>
		struct function_traits<Ret(T0, T1, T2, ...) const volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 3>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3>
		struct function_traits<Ret(T0, T1, T2, T3)>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 4>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3>
		struct function_traits<Ret(T0, T1, T2, T3, ...)>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 4>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3>
		struct function_traits<Ret(T0, T1, T2, T3) const>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 4>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3>
		struct function_traits<Ret(T0, T1, T2, T3, ...) const>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 4>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3>
		struct function_traits<Ret(T0, T1, T2, T3) volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 4>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3>
		struct function_traits<Ret(T0, T1, T2, T3, ...) volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 4>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3>
		struct function_traits<Ret(T0, T1, T2, T3) const volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 4>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3>
		struct function_traits<Ret(T0, T1, T2, T3, ...) const volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 4>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4>
		struct function_traits<Ret(T0, T1, T2, T3, T4)>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 5>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4>
		struct function_traits<Ret(T0, T1, T2, T3, T4, ...)>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 5>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4>
		struct function_traits<Ret(T0, T1, T2, T3, T4) const>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 5>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4>
		struct function_traits<Ret(T0, T1, T2, T3, T4, ...) const>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 5>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4>
		struct function_traits<Ret(T0, T1, T2, T3, T4) volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 5>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4>
		struct function_traits<Ret(T0, T1, T2, T3, T4, ...) volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 5>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4>
		struct function_traits<Ret(T0, T1, T2, T3, T4) const volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 5>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4>
		struct function_traits<Ret(T0, T1, T2, T3, T4, ...) const volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 5>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5)>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 6>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, ...)>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 6>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5) const>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 6>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, ...) const>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 6>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5) volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 6>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, ...) volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 6>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5) const volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 6>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, ...) const volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 6>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6)>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 7>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, ...)>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 7>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6) const>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 7>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, ...) const>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 7>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6) volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 7>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, ...) volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 7>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6) const volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 7>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, ...) const volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 7>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7)>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 8>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, ...)>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 8>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7) const>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 8>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, ...) const>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 8>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7) volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 8>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, ...) volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 8>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7) const volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 8>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, ...) const volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 8>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8)>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 9>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, ...)>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 9>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8) const>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 9>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, ...) const>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 9>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8) volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 9>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, ...) volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 9>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8) const volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 9>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, ...) const volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 9>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9)>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 10>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, ...)>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 10>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9) const>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 10>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, ...) const>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 10>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9) volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 10>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, ...) volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 10>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9) const volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 10>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, ...) const volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 10>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10)>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 11>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, ...)>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 11>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10) const>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 11>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, ...) const>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 11>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10) volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 11>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, ...) volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 11>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10) const volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 11>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, ...) const volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 11>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11)>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 12>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, ...)>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 12>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11) const>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 12>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, ...) const>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 12>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11) volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 12>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, ...) volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 12>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11) const volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 12>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, ...) const volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 12>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12)>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 13>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, ...)>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 13>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12) const>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 13>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, ...) const>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 13>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12) volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 13>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, ...) volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 13>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12) const volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 13>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, ...) const volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 13>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13)>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 14>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, ...)>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 14>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13) const>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 14>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, ...) const>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 14>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13) volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 14>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, ...) volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 14>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13) const volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 14>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, ...) const volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 14>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14)>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 15>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, ...)>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 15>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14) const>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 15>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, ...) const>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 15>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14) volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 15>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, ...) volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 15>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14) const volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 15>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, ...) const volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 15>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15)>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 16>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, ...)>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 16>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15) const>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 16>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, ...) const>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 16>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15) volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 16>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, ...) volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 16>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15) const volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 16>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, ...) const volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 16>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16)>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 17>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, ...)>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 17>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16) const>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 17>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, ...) const>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 17>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16) volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 17>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, ...) volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 17>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16) const volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 17>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, ...) const volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 17>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17)>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 18>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, ...)>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 18>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17) const>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 18>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, ...) const>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 18>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17) volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 18>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, ...) volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 18>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17) const volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 18>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, ...) const volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 18>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18)>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 19>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, ...)>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 19>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18) const>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 19>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, ...) const>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 19>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18) volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 19>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, ...) volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 19>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18) const volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 19>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, ...) const volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 19>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19)>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 20>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, ...)>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 20>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19) const>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 20>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, ...) const>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 20>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19) volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 20>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, ...) volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 20>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19) const volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 20>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, ...) const volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 20>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20)>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 21>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, ...)>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 21>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20) const>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 21>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, ...) const>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 21>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20) volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 21>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, ...) volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 21>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20) const volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 21>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, ...) const volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 21>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21)>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 22>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, ...)>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 22>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21) const>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 22>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, ...) const>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 22>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21) volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 22>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, ...) volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 22>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21) const volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 22>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, ...) const volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 22>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22)>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 23>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, ...)>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 23>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22) const>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 23>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, ...) const>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 23>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22) volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 23>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, ...) volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 23>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22) const volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 23>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, ...) const volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 23>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23)>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 24>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, ...)>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 24>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23) const>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 24>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, ...) const>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 24>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23) volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 24>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, ...) volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 24>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23) const volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 24>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, ...) const volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 24>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24)>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 25>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, ...)>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 25>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24) const>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 25>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, ...) const>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::false_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 25>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24) volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 25>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, ...) volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::false_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 25>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24) const volatile>
		{
				typedef kerbal::type_traits::false_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 25>		args_num;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, ...) const volatile>
		{
				typedef kerbal::type_traits::true_type			has_var_list;
				typedef kerbal::type_traits::true_type			is_const;
				typedef kerbal::type_traits::true_type			is_volatile;

				typedef Ret										return_type;
				typedef kerbal::type_traits::integral_constant<int, 25>		args_num;
		};

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


