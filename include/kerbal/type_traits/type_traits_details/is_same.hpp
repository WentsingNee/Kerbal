/*
 * is_same.hpp
 *
 *  Created on: 2019年4月29日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_IS_SAME_HPP_
#define INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_IS_SAME_HPP_

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/type_traits/type_traits_details/conditional.hpp>

namespace kerbal
{

	namespace type_traits
	{

#	if __cplusplus < 201103L

		template <
				typename Tp,   typename Up  , typename = Up, typename = Up, typename = Up,
				typename = Up, typename = Up, typename = Up, typename = Up, typename = Up,
				typename = Up, typename = Up, typename = Up, typename = Up, typename = Up>
		struct is_same : kerbal::type_traits::false_type
		{
		};

#	else

		MODULE_EXPORT
		template <typename Tp, typename Up, typename ... Types>
		struct is_same: kerbal::type_traits::conditional_boolean<
									kerbal::type_traits::is_same<Tp, Up>::value &&
									kerbal::type_traits::is_same<Up, Types...>::value
							>
		{
		};

		MODULE_EXPORT
		template <typename Tp, typename Up>
		struct is_same<Tp, Up> : kerbal::type_traits::false_type
		{
		};

#endif

		MODULE_EXPORT
		template <typename Tp>
		struct is_same<Tp, Tp> : kerbal::type_traits::true_type
		{
		};

	}
}

#endif /* INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_IS_SAME_HPP_ */
