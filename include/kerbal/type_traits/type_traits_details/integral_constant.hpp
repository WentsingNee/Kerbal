/*
 * integral_constant.hpp
 *
 *  Created on: 2019年4月29日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_INTEGRAL_CONSTANT_HPP_
#define INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_INTEGRAL_CONSTANT_HPP_

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>

namespace kerbal
{

	namespace type_traits
	{

		MODULE_EXPORT
		template <typename Type, Type val>
		struct integral_constant
		{
#			if __cplusplus >= 201103L
				static constexpr Type value = val;
#			else
				static const Type value = val;
#			endif

				typedef Type value_type;
				typedef integral_constant<Type, val> type;

				KERBAL_CONSTEXPR operator value_type() const KERBAL_NOEXCEPT
				{
					return value;
				}
		};

		MODULE_EXPORT
		struct false_type : integral_constant<bool, false>
		{
		};

		MODULE_EXPORT
		struct true_type : integral_constant<bool, true>
		{
		};

	}
}

#endif /* INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_INTEGRAL_CONSTANT_HPP_ */
