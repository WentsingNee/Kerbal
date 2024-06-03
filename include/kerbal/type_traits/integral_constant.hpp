/**
 * @file       integral_constant.hpp
 * @brief
 * @date       2019-4-29
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP
#define KERBAL_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>


namespace kerbal
{

	namespace type_traits
	{

		KERBAL_MODULE_EXPORT
		template <typename T, T val>
		struct integral_constant
		{
				static
				KERBAL_CONSTEXPR
				T const value = val;

				typedef T value_type;
				typedef integral_constant<T, val> type;

				KERBAL_CONSTEXPR
				operator value_type() const KERBAL_NOEXCEPT
				{
					return value;
				}
		};

		template <typename T, T val>
		KERBAL_CONSTEXPR
		T const
		integral_constant<T, val>::value;


		KERBAL_MODULE_EXPORT
		struct false_type : integral_constant<bool, false>
		{
		};

		KERBAL_MODULE_EXPORT
		struct true_type : integral_constant<bool, true>
		{
		};

		KERBAL_MODULE_EXPORT
		template <bool>
		struct bool_constant;

		template <>
		struct bool_constant<true> : kerbal::type_traits::true_type
		{
		};

		template <>
		struct bool_constant<false> : kerbal::type_traits::false_type
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP
