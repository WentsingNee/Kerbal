/**
 * @file       fundamental_deduction.hpp
 * @brief
 * @date       2019-5-9
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_FUNDAMENTAL_DEDUCTION_HPP
#define KERBAL_TYPE_TRAITS_FUNDAMENTAL_DEDUCTION_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/type_traits/cv_deduction.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#if __cplusplus >= 201103L
#	include <cstddef>
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
		struct is_arithmetic: kerbal::type_traits::bool_constant<
											kerbal::type_traits::is_integral<Tp>::value ||
											kerbal::type_traits::is_floating_point<Tp>::value
									>
		{
		};

#	if __cplusplus >= 201103L

		template <class Tp>
		struct __is_null_pointer_helper: kerbal::type_traits::false_type
		{
		};

		template <>
		struct __is_null_pointer_helper<std::nullptr_t>: kerbal::type_traits::true_type
		{
		};

		/// is_null_pointer
		MODULE_EXPORT
		template <class Tp>
		struct is_null_pointer: kerbal::type_traits::__is_null_pointer_helper<
									typename kerbal::type_traits::remove_cv<Tp>::type
								>
		{
		};

#	endif


#	if __cplusplus < 201103L
		/// is_fundamental
		MODULE_EXPORT
		template <typename Tp>
		struct is_fundamental: kerbal::type_traits::bool_constant<
											kerbal::type_traits::is_arithmetic<Tp>::value ||
											kerbal::type_traits::is_void<Tp>::value
									>
		{
		};

#	else

		/// is_fundamental
		MODULE_EXPORT
		template <typename Tp>
		struct is_fundamental: kerbal::type_traits::bool_constant<
											kerbal::type_traits::is_arithmetic<Tp>::value ||
											kerbal::type_traits::is_void<Tp>::value ||
											kerbal::type_traits::is_null_pointer<Tp>::value
									>
		{
		};

#	endif

		MODULE_EXPORT
		template <typename Tp>
		struct is_compound: kerbal::type_traits::bool_constant<!is_fundamental<Tp>::value>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_FUNDAMENTAL_DEDUCTION_HPP
