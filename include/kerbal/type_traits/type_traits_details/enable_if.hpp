/*
 * enable_if.hpp
 *
 *  Created on: 2019年4月29日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_ENABLE_IF_HPP_
#define INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_ENABLE_IF_HPP_

#include <kerbal/ts/modules_ts/modules_ts.hpp>

namespace kerbal
{

	namespace type_traits
	{

		MODULE_EXPORT
		template <bool condition, typename Tp = void>
		struct enable_if
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct enable_if<true, Tp>
		{
				typedef Tp type;
		};

	}
}

#endif /* INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_ENABLE_IF_HPP_ */
