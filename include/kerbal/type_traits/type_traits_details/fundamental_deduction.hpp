/*
 * fundamental_deduction.hpp
 *
 *  Created on: 2019年5月9日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_FUNDAMENTAL_DEDUCTION_HPP_
#define INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_FUNDAMENTAL_DEDUCTION_HPP_

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/type_traits/type_traits_details/integral_constant.hpp>
#include <kerbal/type_traits/type_traits_details/conditional.hpp>
#include <kerbal/type_traits/type_traits_details/cv_deduction.hpp>

#if __cplusplus >= 201103L
#	include <type_traits>
#endif

namespace kerbal
{

	namespace type_traits
	{
		template <typename >
		struct __is_void_helper: kerbal::type_traits::false_type
		{
		};

		template <>
		struct __is_void_helper<void> : kerbal::type_traits::true_type
		{
		};

		/// is_void
		MODULE_EXPORT
		template <typename Tp>
		struct is_void: __is_void_helper<typename kerbal::type_traits::remove_cv<Tp>::type>
		{
		};

		template <typename >
		struct __is_floating_point_helper: kerbal::type_traits::false_type
		{
		};

		template <>
		struct __is_floating_point_helper<float> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct __is_floating_point_helper<double> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct __is_floating_point_helper<long double> : kerbal::type_traits::true_type
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_floating_point: kerbal::type_traits::__is_floating_point_helper<
												typename kerbal::type_traits::remove_cv<Tp>::type
										>
		{
		};

		template <typename>
		struct __is_integral_helper : kerbal::type_traits::false_type
		{
		};

		template <>
		struct __is_integral_helper<bool> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct __is_integral_helper<char> : kerbal::type_traits::true_type
		{
		};

#	if __cplusplus >= 201103L

		template <>
		struct __is_integral_helper<char16_t> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct __is_integral_helper<char32_t> : kerbal::type_traits::true_type
		{
		};

#	endif

		template <>
		struct __is_integral_helper<signed char> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct __is_integral_helper<short> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct __is_integral_helper<int> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct __is_integral_helper<long> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct __is_integral_helper<long long> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct __is_integral_helper<unsigned char> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct __is_integral_helper<unsigned short> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct __is_integral_helper<unsigned int> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct __is_integral_helper<unsigned long> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct __is_integral_helper<unsigned long long> : kerbal::type_traits::true_type
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_integral: kerbal::type_traits::__is_integral_helper<
										typename kerbal::type_traits::remove_cv<Tp>::type
								>
		{
		};

		MODULE_EXPORT
		template <class Tp>
		struct is_arithmetic: kerbal::type_traits::conditional_boolean<
											is_integral<Tp>::value ||
											is_floating_point<Tp>::value
									>
		{
		};

#	if __cplusplus < 201103L
		/// is_fundamental
		MODULE_EXPORT
		template <typename Tp>
		struct is_fundamental: kerbal::type_traits::conditional_boolean<
											is_arithmetic<Tp>::value ||
											is_void<Tp>::value
									>
		{
		};
#	else
		/// is_fundamental
		MODULE_EXPORT
		template <typename Tp>
		struct is_fundamental: kerbal::type_traits::conditional_boolean<
											is_arithmetic<Tp>::value ||
											is_void<Tp>::value ||
											std::is_null_pointer<Tp>::value
									>
		{
		};
#	endif

	}
}
#endif /* INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_FUNDAMENTAL_DEDUCTION_HPP_ */
