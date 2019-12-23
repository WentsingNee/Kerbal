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


#ifndef KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_FUNCTION_DEDUCTION_HPP_
#define KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_FUNCTION_DEDUCTION_HPP_

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/type_traits/type_traits_details/integral_constant.hpp>
#include <kerbal/type_traits/type_traits_details/type_chooser.hpp>

#include <cstddef>

namespace kerbal
{
	namespace type_traits
	{
		MODULE_EXPORT
		template <typename >
		struct is_function : kerbal::type_traits::false_type {};

		MODULE_EXPORT
		template <typename >
		struct function_traits {};


#	if __cplusplus < 201103L

		template <typename Ret>
		struct is_function<Ret(void) > : kerbal::type_traits::true_type {};

		template <typename Ret>
		struct is_function<Ret(...) > : kerbal::type_traits::true_type {};

		template <typename Ret>
		struct is_function<Ret(void) const> : kerbal::type_traits::true_type {};

		template <typename Ret>
		struct is_function<Ret(...) const> : kerbal::type_traits::true_type {};

		template <typename Ret>
		struct is_function<Ret(void) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret>
		struct is_function<Ret(...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret>
		struct is_function<Ret(void) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret>
		struct is_function<Ret(...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0>
		struct is_function<Ret(T0) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0>
		struct is_function<Ret(T0, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0>
		struct is_function<Ret(T0) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0>
		struct is_function<Ret(T0, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0>
		struct is_function<Ret(T0) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0>
		struct is_function<Ret(T0, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0>
		struct is_function<Ret(T0) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0>
		struct is_function<Ret(T0, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1>
		struct is_function<Ret(T0, T1) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1>
		struct is_function<Ret(T0, T1, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1>
		struct is_function<Ret(T0, T1) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1>
		struct is_function<Ret(T0, T1, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1>
		struct is_function<Ret(T0, T1) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1>
		struct is_function<Ret(T0, T1, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1>
		struct is_function<Ret(T0, T1) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1>
		struct is_function<Ret(T0, T1, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2>
		struct is_function<Ret(T0, T1, T2) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2>
		struct is_function<Ret(T0, T1, T2, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2>
		struct is_function<Ret(T0, T1, T2) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2>
		struct is_function<Ret(T0, T1, T2, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2>
		struct is_function<Ret(T0, T1, T2) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2>
		struct is_function<Ret(T0, T1, T2, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2>
		struct is_function<Ret(T0, T1, T2) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2>
		struct is_function<Ret(T0, T1, T2, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3>
		struct is_function<Ret(T0, T1, T2, T3) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3>
		struct is_function<Ret(T0, T1, T2, T3, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3>
		struct is_function<Ret(T0, T1, T2, T3) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3>
		struct is_function<Ret(T0, T1, T2, T3, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3>
		struct is_function<Ret(T0, T1, T2, T3) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3>
		struct is_function<Ret(T0, T1, T2, T3, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3>
		struct is_function<Ret(T0, T1, T2, T3) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3>
		struct is_function<Ret(T0, T1, T2, T3, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4>
		struct is_function<Ret(T0, T1, T2, T3, T4) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4>
		struct is_function<Ret(T0, T1, T2, T3, T4, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4>
		struct is_function<Ret(T0, T1, T2, T3, T4) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4>
		struct is_function<Ret(T0, T1, T2, T3, T4, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4>
		struct is_function<Ret(T0, T1, T2, T3, T4) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4>
		struct is_function<Ret(T0, T1, T2, T3, T4, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4>
		struct is_function<Ret(T0, T1, T2, T3, T4) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4>
		struct is_function<Ret(T0, T1, T2, T3, T4, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, T48) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, T48, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, T48) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, T48, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, T48) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, T48, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, T48) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, T48, ...) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, T48, T49) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, T48, T49, ...) > : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, T48, T49) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, T48, T49, ...) const> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, T48, T49) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, T48, T49, ...) volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, T48, T49) const volatile> : kerbal::type_traits::true_type {};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49>
		struct is_function<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, T48, T49, ...) const volatile> : kerbal::type_traits::true_type {};


		template <typename Ret>
		struct function_traits<Ret(void) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret>
		struct function_traits<Ret(...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret>
		struct function_traits<Ret(void) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret>
		struct function_traits<Ret(...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret>
		struct function_traits<Ret(void) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret>
		struct function_traits<Ret(...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret>
		struct function_traits<Ret(void) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret>
		struct function_traits<Ret(...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0>
		struct function_traits<Ret(T0) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0>
		struct function_traits<Ret(T0, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0>
		struct function_traits<Ret(T0) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0>
		struct function_traits<Ret(T0, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0>
		struct function_traits<Ret(T0) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0>
		struct function_traits<Ret(T0, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0>
		struct function_traits<Ret(T0) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0>
		struct function_traits<Ret(T0, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1>
		struct function_traits<Ret(T0, T1) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1>
		struct function_traits<Ret(T0, T1, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1>
		struct function_traits<Ret(T0, T1) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1>
		struct function_traits<Ret(T0, T1, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1>
		struct function_traits<Ret(T0, T1) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1>
		struct function_traits<Ret(T0, T1, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1>
		struct function_traits<Ret(T0, T1) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1>
		struct function_traits<Ret(T0, T1, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2>
		struct function_traits<Ret(T0, T1, T2) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2>
		struct function_traits<Ret(T0, T1, T2, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2>
		struct function_traits<Ret(T0, T1, T2) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2>
		struct function_traits<Ret(T0, T1, T2, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2>
		struct function_traits<Ret(T0, T1, T2) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2>
		struct function_traits<Ret(T0, T1, T2, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2>
		struct function_traits<Ret(T0, T1, T2) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2>
		struct function_traits<Ret(T0, T1, T2, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3>
		struct function_traits<Ret(T0, T1, T2, T3) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3>
		struct function_traits<Ret(T0, T1, T2, T3, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3>
		struct function_traits<Ret(T0, T1, T2, T3) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3>
		struct function_traits<Ret(T0, T1, T2, T3, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3>
		struct function_traits<Ret(T0, T1, T2, T3) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3>
		struct function_traits<Ret(T0, T1, T2, T3, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3>
		struct function_traits<Ret(T0, T1, T2, T3) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3>
		struct function_traits<Ret(T0, T1, T2, T3, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4>
		struct function_traits<Ret(T0, T1, T2, T3, T4) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4>
		struct function_traits<Ret(T0, T1, T2, T3, T4, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4>
		struct function_traits<Ret(T0, T1, T2, T3, T4) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4>
		struct function_traits<Ret(T0, T1, T2, T3, T4, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4>
		struct function_traits<Ret(T0, T1, T2, T3, T4) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4>
		struct function_traits<Ret(T0, T1, T2, T3, T4, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4>
		struct function_traits<Ret(T0, T1, T2, T3, T4) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4>
		struct function_traits<Ret(T0, T1, T2, T3, T4, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, T48) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, T48, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, T48) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, T48, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, T48) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, T48, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, T48) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, T48, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, T48, T49) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, T48, T49, ...) >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, T48, T49) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, T48, T49, ...) const>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, T48, T49) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, T48, T49, ...) volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, T48, T49) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};

		template <typename Ret, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49>
		struct function_traits<Ret(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, T48, T49, ...) const volatile>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
		};


#	else

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args...)  > : kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args......)  > : kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args...) const > : kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args......) const > : kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args...) volatile > : kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args......) volatile > : kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args...) const volatile > : kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args......) const volatile > : kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args...)  &> : kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args......)  &> : kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args...) const &> : kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args......) const &> : kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args...) volatile &> : kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args......) volatile &> : kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args...) const volatile &> : kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args......) const volatile &> : kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args...)  &&> : kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args......)  &&> : kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args...) const &&> : kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args......) const &&> : kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args...) volatile &&> : kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args......) volatile &&> : kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args...) const volatile &&> : kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct is_function<Ret(Args......) const volatile &&> : kerbal::type_traits::true_type {};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args...)  >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
			typedef kerbal::type_traits::false_type     is_lreference;
			typedef kerbal::type_traits::false_type     is_rreference;
			typedef kerbal::type_traits::integral_constant<size_t, sizeof...(Args)>     arguments_num;

			template <size_t i>
			struct argument
			{
				typedef typename kerbal::type_traits::type_chooser<i, Args...>::type type;
			};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args......)  >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
			typedef kerbal::type_traits::false_type     is_lreference;
			typedef kerbal::type_traits::false_type     is_rreference;
			typedef kerbal::type_traits::integral_constant<size_t, sizeof...(Args)>     arguments_num;

			template <size_t i>
			struct argument
			{
				typedef typename kerbal::type_traits::type_chooser<i, Args...>::type type;
			};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args...) const >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
			typedef kerbal::type_traits::false_type     is_lreference;
			typedef kerbal::type_traits::false_type     is_rreference;
			typedef kerbal::type_traits::integral_constant<size_t, sizeof...(Args)>     arguments_num;

			template <size_t i>
			struct argument
			{
				typedef typename kerbal::type_traits::type_chooser<i, Args...>::type type;
			};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args......) const >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
			typedef kerbal::type_traits::false_type     is_lreference;
			typedef kerbal::type_traits::false_type     is_rreference;
			typedef kerbal::type_traits::integral_constant<size_t, sizeof...(Args)>     arguments_num;

			template <size_t i>
			struct argument
			{
				typedef typename kerbal::type_traits::type_chooser<i, Args...>::type type;
			};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args...) volatile >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
			typedef kerbal::type_traits::false_type     is_lreference;
			typedef kerbal::type_traits::false_type     is_rreference;
			typedef kerbal::type_traits::integral_constant<size_t, sizeof...(Args)>     arguments_num;

			template <size_t i>
			struct argument
			{
				typedef typename kerbal::type_traits::type_chooser<i, Args...>::type type;
			};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args......) volatile >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
			typedef kerbal::type_traits::false_type     is_lreference;
			typedef kerbal::type_traits::false_type     is_rreference;
			typedef kerbal::type_traits::integral_constant<size_t, sizeof...(Args)>     arguments_num;

			template <size_t i>
			struct argument
			{
				typedef typename kerbal::type_traits::type_chooser<i, Args...>::type type;
			};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args...) const volatile >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
			typedef kerbal::type_traits::false_type     is_lreference;
			typedef kerbal::type_traits::false_type     is_rreference;
			typedef kerbal::type_traits::integral_constant<size_t, sizeof...(Args)>     arguments_num;

			template <size_t i>
			struct argument
			{
				typedef typename kerbal::type_traits::type_chooser<i, Args...>::type type;
			};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args......) const volatile >
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
			typedef kerbal::type_traits::false_type     is_lreference;
			typedef kerbal::type_traits::false_type     is_rreference;
			typedef kerbal::type_traits::integral_constant<size_t, sizeof...(Args)>     arguments_num;

			template <size_t i>
			struct argument
			{
				typedef typename kerbal::type_traits::type_chooser<i, Args...>::type type;
			};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args...)  &>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
			typedef kerbal::type_traits::true_type      is_lreference;
			typedef kerbal::type_traits::false_type     is_rreference;
			typedef kerbal::type_traits::integral_constant<size_t, sizeof...(Args)>     arguments_num;

			template <size_t i>
			struct argument
			{
				typedef typename kerbal::type_traits::type_chooser<i, Args...>::type type;
			};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args......)  &>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
			typedef kerbal::type_traits::true_type      is_lreference;
			typedef kerbal::type_traits::false_type     is_rreference;
			typedef kerbal::type_traits::integral_constant<size_t, sizeof...(Args)>     arguments_num;

			template <size_t i>
			struct argument
			{
				typedef typename kerbal::type_traits::type_chooser<i, Args...>::type type;
			};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args...) const &>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
			typedef kerbal::type_traits::true_type      is_lreference;
			typedef kerbal::type_traits::false_type     is_rreference;
			typedef kerbal::type_traits::integral_constant<size_t, sizeof...(Args)>     arguments_num;

			template <size_t i>
			struct argument
			{
				typedef typename kerbal::type_traits::type_chooser<i, Args...>::type type;
			};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args......) const &>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
			typedef kerbal::type_traits::true_type      is_lreference;
			typedef kerbal::type_traits::false_type     is_rreference;
			typedef kerbal::type_traits::integral_constant<size_t, sizeof...(Args)>     arguments_num;

			template <size_t i>
			struct argument
			{
				typedef typename kerbal::type_traits::type_chooser<i, Args...>::type type;
			};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args...) volatile &>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
			typedef kerbal::type_traits::true_type      is_lreference;
			typedef kerbal::type_traits::false_type     is_rreference;
			typedef kerbal::type_traits::integral_constant<size_t, sizeof...(Args)>     arguments_num;

			template <size_t i>
			struct argument
			{
				typedef typename kerbal::type_traits::type_chooser<i, Args...>::type type;
			};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args......) volatile &>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
			typedef kerbal::type_traits::true_type      is_lreference;
			typedef kerbal::type_traits::false_type     is_rreference;
			typedef kerbal::type_traits::integral_constant<size_t, sizeof...(Args)>     arguments_num;

			template <size_t i>
			struct argument
			{
				typedef typename kerbal::type_traits::type_chooser<i, Args...>::type type;
			};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args...) const volatile &>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
			typedef kerbal::type_traits::true_type      is_lreference;
			typedef kerbal::type_traits::false_type     is_rreference;
			typedef kerbal::type_traits::integral_constant<size_t, sizeof...(Args)>     arguments_num;

			template <size_t i>
			struct argument
			{
				typedef typename kerbal::type_traits::type_chooser<i, Args...>::type type;
			};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args......) const volatile &>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
			typedef kerbal::type_traits::true_type      is_lreference;
			typedef kerbal::type_traits::false_type     is_rreference;
			typedef kerbal::type_traits::integral_constant<size_t, sizeof...(Args)>     arguments_num;

			template <size_t i>
			struct argument
			{
				typedef typename kerbal::type_traits::type_chooser<i, Args...>::type type;
			};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args...)  &&>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
			typedef kerbal::type_traits::false_type     is_lreference;
			typedef kerbal::type_traits::true_type      is_rreference;
			typedef kerbal::type_traits::integral_constant<size_t, sizeof...(Args)>     arguments_num;

			template <size_t i>
			struct argument
			{
				typedef typename kerbal::type_traits::type_chooser<i, Args...>::type type;
			};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args......)  &&>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
			typedef kerbal::type_traits::false_type     is_lreference;
			typedef kerbal::type_traits::true_type      is_rreference;
			typedef kerbal::type_traits::integral_constant<size_t, sizeof...(Args)>     arguments_num;

			template <size_t i>
			struct argument
			{
				typedef typename kerbal::type_traits::type_chooser<i, Args...>::type type;
			};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args...) const &&>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
			typedef kerbal::type_traits::false_type     is_lreference;
			typedef kerbal::type_traits::true_type      is_rreference;
			typedef kerbal::type_traits::integral_constant<size_t, sizeof...(Args)>     arguments_num;

			template <size_t i>
			struct argument
			{
				typedef typename kerbal::type_traits::type_chooser<i, Args...>::type type;
			};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args......) const &&>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::false_type     is_volatile;
			typedef kerbal::type_traits::false_type     is_lreference;
			typedef kerbal::type_traits::true_type      is_rreference;
			typedef kerbal::type_traits::integral_constant<size_t, sizeof...(Args)>     arguments_num;

			template <size_t i>
			struct argument
			{
				typedef typename kerbal::type_traits::type_chooser<i, Args...>::type type;
			};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args...) volatile &&>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
			typedef kerbal::type_traits::false_type     is_lreference;
			typedef kerbal::type_traits::true_type      is_rreference;
			typedef kerbal::type_traits::integral_constant<size_t, sizeof...(Args)>     arguments_num;

			template <size_t i>
			struct argument
			{
				typedef typename kerbal::type_traits::type_chooser<i, Args...>::type type;
			};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args......) volatile &&>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::false_type     is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
			typedef kerbal::type_traits::false_type     is_lreference;
			typedef kerbal::type_traits::true_type      is_rreference;
			typedef kerbal::type_traits::integral_constant<size_t, sizeof...(Args)>     arguments_num;

			template <size_t i>
			struct argument
			{
				typedef typename kerbal::type_traits::type_chooser<i, Args...>::type type;
			};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args...) const volatile &&>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::false_type     has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
			typedef kerbal::type_traits::false_type     is_lreference;
			typedef kerbal::type_traits::true_type      is_rreference;
			typedef kerbal::type_traits::integral_constant<size_t, sizeof...(Args)>     arguments_num;

			template <size_t i>
			struct argument
			{
				typedef typename kerbal::type_traits::type_chooser<i, Args...>::type type;
			};
		};

		MODULE_EXPORT
		template <typename Ret, typename ... Args>
		struct function_traits<Ret(Args......) const volatile &&>
		{
			typedef Ret return_type;
			typedef kerbal::type_traits::true_type      has_var_list;
			typedef kerbal::type_traits::true_type      is_const;
			typedef kerbal::type_traits::true_type      is_volatile;
			typedef kerbal::type_traits::false_type     is_lreference;
			typedef kerbal::type_traits::true_type      is_rreference;
			typedef kerbal::type_traits::integral_constant<size_t, sizeof...(Args)>     arguments_num;

			template <size_t i>
			struct argument
			{
				typedef typename kerbal::type_traits::type_chooser<i, Args...>::type type;
			};
		};

#	endif // c++11


	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_FUNCTION_DEDUCTION_HPP_


