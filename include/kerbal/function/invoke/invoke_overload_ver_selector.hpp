/**
 * @file       invoke_overload_ver_selector.hpp
 * @brief
 * @date       2023-07-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_FUNCTION_INVOKE_INVOKE_OVERLOAD_VER_SELECTOR_HPP
#define KERBAL_FUNCTION_INVOKE_INVOKE_OVERLOAD_VER_SELECTOR_HPP

#if __cplusplus >= 201103L
#	include <kerbal/function/invoke/detail/invoke_overload_ver_selector.cxx11.part.hpp>
#else
#	include <kerbal/function/invoke/detail/invoke_overload_ver_selector.cxx98.part.hpp>
#endif

#endif // KERBAL_FUNCTION_INVOKE_INVOKE_OVERLOAD_VER_SELECTOR_HPP
