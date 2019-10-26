/**
 * @file       void_type.hpp
 * @brief
 * @date       2019-10-25
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_VOID_TYPE_HPP_
#define KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_VOID_TYPE_HPP_

#include <kerbal/ts/modules_ts/modules_ts.hpp>

namespace kerbal
{

	namespace type_traits
	{

#	if __cplusplus < 201103L

		template <
				typename T0 = void, typename = T0, typename = T0, typename = T0, typename = T0,
				typename    = T0,   typename = T0, typename = T0, typename = T0, typename = T0,
				typename    = T0,   typename = T0, typename = T0, typename = T0, typename = T0>
		struct void_type
		{
				typedef void type;
		};

#	else

		MODULE_EXPORT
		template <typename ... Args>
		struct void_type
		{
				typedef void type;
		};

#	endif

	}
}

#endif /* KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_VOID_TYPE_HPP_ */
