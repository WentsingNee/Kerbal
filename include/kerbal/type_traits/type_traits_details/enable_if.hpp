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

#	if __cplusplus < 201103L
		template <
				typename T0 = void,
				typename = T0,
				typename = T0,
				typename = T0,
				typename = T0,
				typename = T0,
				typename = T0,
				typename = T0,
				typename = T0,
				typename = T0,
				typename = T0,
				typename = T0,
				typename = T0,
				typename = T0>
		struct __void_type
		{
				typedef void type;
		};
#	else

		MODULE_EXPORT
		template <typename ... Args>
		struct __void_type
		{
				typedef void type;
		};

#	endif

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
