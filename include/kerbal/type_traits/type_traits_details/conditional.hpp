/*
 * conditional.hpp
 *
 *  Created on: 2019年4月29日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_CONDITIONAL_HPP_
#define INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_CONDITIONAL_HPP_

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/type_traits/type_traits_details/integral_constant.hpp>

namespace kerbal
{

	namespace type_traits
	{

		MODULE_EXPORT
		template <bool condition, typename TrueType, typename FalseType>
		struct conditional
		{
				typedef TrueType type;
		};

		MODULE_EXPORT
		template <typename TrueType, typename FalseType>
		struct conditional<false, TrueType, FalseType>
		{
				typedef FalseType type;
		};

		MODULE_EXPORT
		template <bool condition>
		struct conditional_boolean : kerbal::type_traits::conditional<condition,
													kerbal::type_traits::true_type,
													kerbal::type_traits::false_type
											>::type
		{
		};

	}
}

#endif /* INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_CONDITIONAL_HPP_ */
