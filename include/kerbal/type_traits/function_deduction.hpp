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

#include <cstddef>

namespace kerbal
{
	namespace type_traits
	{

		MODULE_EXPORT
		template <typename >
		struct is_function: kerbal::type_traits::false_type {};

#	if __cplusplus < 201103L

		template <typename Ret>
		struct is_function<Ret()>: kerbal::type_traits::true_type {};

		template <typename Ret>
		struct is_function<Ret(...)>: kerbal::type_traits::true_type {};

		template <typename Ret>
		struct is_function<Ret() const>: kerbal::type_traits::true_type {};

		template <typename Ret>
		struct is_function<Ret(...) const>: kerbal::type_traits::true_type {};

		template <typename Ret>
		struct is_function<Ret() volatile>: kerbal::type_traits::true_type {};

		template <typename Ret>
		struct is_function<Ret(...) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret>
		struct is_function<Ret() const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret>
		struct is_function<Ret(...) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0>
		struct is_function<Ret(T0)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0>
		struct is_function<Ret(T0, ...)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0>
		struct is_function<Ret(T0) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0>
		struct is_function<Ret(T0, ...) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0>
		struct is_function<Ret(T0) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0>
		struct is_function<Ret(T0, ...) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0>
		struct is_function<Ret(T0) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0>
		struct is_function<Ret(T0, ...) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1>
		struct is_function<Ret(T0, T1)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1>
		struct is_function<Ret(T0, T1, ...)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1>
		struct is_function<Ret(T0, T1) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1>
		struct is_function<Ret(T0, T1, ...) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1>
		struct is_function<Ret(T0, T1) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1>
		struct is_function<Ret(T0, T1, ...) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1>
		struct is_function<Ret(T0, T1) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1>
		struct is_function<Ret(T0, T1, ...) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2>
		struct is_function<Ret(T0, T1, T2)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2>
		struct is_function<Ret(T0, T1, T2, ...)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2>
		struct is_function<Ret(T0, T1, T2) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2>
		struct is_function<Ret(T0, T1, T2, ...) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2>
		struct is_function<Ret(T0, T1, T2) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2>
		struct is_function<Ret(T0, T1, T2, ...) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2>
		struct is_function<Ret(T0, T1, T2) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2>
		struct is_function<Ret(T0, T1, T2, ...) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3>
		struct is_function<Ret(T0, T1, T2, T3)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3>
		struct is_function<Ret(T0, T1, T2, T3, ...)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3>
		struct is_function<Ret(T0, T1, T2, T3) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3>
		struct is_function<Ret(T0, T1, T2, T3, ...) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3>
		struct is_function<Ret(T0, T1, T2, T3) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3>
		struct is_function<Ret(T0, T1, T2, T3, ...) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3>
		struct is_function<Ret(T0, T1, T2, T3) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3>
		struct is_function<Ret(T0, T1, T2, T3, ...) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4>
		struct is_function<Ret(T0, T1, T2, T3, T4)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4>
		struct is_function<Ret(T0, T1, T2, T3, T4, ...)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4>
		struct is_function<Ret(T0, T1, T2, T3, T4) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4>
		struct is_function<Ret(T0, T1, T2, T3, T4, ...) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4>
		struct is_function<Ret(T0, T1, T2, T3, T4) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4>
		struct is_function<Ret(T0, T1, T2, T3, T4, ...) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4>
		struct is_function<Ret(T0, T1, T2, T3, T4) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4>
		struct is_function<Ret(T0, T1, T2, T3, T4, ...) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, ...)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, ...) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, ...) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, ...) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, ...)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, ...) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, ...) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, ...) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, ...)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, ...) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, ...) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, ...) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, ...)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, ...) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, ...) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, ...) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, ...)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, ...) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, ...) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, ...) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, ...)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, ...) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, ...) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, ...) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, ...)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, ...) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, ...) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, ...) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, ...)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, ...) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, ...) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, ...) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, ...)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, ...) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, ...) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, ...) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, ...)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, ...) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, ...) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, ...) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, ...)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, ...) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, ...) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, ...) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, ...)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, ...) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, ...) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, ...) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, ...)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, ...) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, ...) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, ...) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, ...)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, ...) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, ...) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, ...) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, ...)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, ...) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, ...) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, ...) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, ...)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, ...) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, ...) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, ...) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, ...)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, ...) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, ...) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, ...) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, ...)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, ...) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, ...) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, ...) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, ...)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, ...) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, ...) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, ...) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, ...)>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, ...) const>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, ...) volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24) const volatile>: kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, ...) const volatile>: kerbal::type_traits::true_type {};

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


