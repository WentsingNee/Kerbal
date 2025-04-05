/**
 * @file       invoke_overload_ver.hpp
 * @brief
 * @date       2023-10-13
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_FUNCTION_INVOKE_DETAIL_INVOKE_OVERLOAD_VER_HPP
#define KERBAL_FUNCTION_INVOKE_DETAIL_INVOKE_OVERLOAD_VER_HPP

#include <kerbal/type_traits/integral_constant.hpp>


namespace kerbal
{

	namespace function
	{

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, -1> INVOKE_OVERLOAD_VER_NOT_INVOCABLE;
			typedef kerbal::type_traits::integral_constant<int, 0>  INVOKE_OVERLOAD_VER_CALLABLE;
			typedef kerbal::type_traits::integral_constant<int, 1>  INVOKE_OVERLOAD_VER_MEM_OBJ;
			typedef kerbal::type_traits::integral_constant<int, 2>  INVOKE_OVERLOAD_VER_MEM_FUN;

		} // namespace detail

	} // namespace function

} // namespace kerbal

#endif // KERBAL_FUNCTION_INVOKE_DETAIL_INVOKE_OVERLOAD_VER_HPP
