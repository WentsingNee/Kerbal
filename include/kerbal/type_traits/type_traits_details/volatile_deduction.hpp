/*
 * volatile_deduction.hpp
 *
 *  Created on: 2019年4月29日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_VOLATILE_DEDUCTION_HPP_
#define INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_VOLATILE_DEDUCTION_HPP_

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/type_traits/type_traits_details/integral_constant.hpp>

namespace kerbal
{

	namespace type_traits
	{

		MODULE_EXPORT
		template <typename >
		struct is_volatile: kerbal::type_traits::false_type
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_volatile<Tp volatile> : kerbal::type_traits::true_type
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct remove_volatile
		{
				typedef Tp type;
		};

		MODULE_EXPORT
		template <typename Tp>
		struct remove_volatile<Tp volatile>
		{
				typedef Tp type;
		};

	}
}

#endif /* INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_VOLATILE_DEDUCTION_HPP_ */
