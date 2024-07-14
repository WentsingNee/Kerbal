/**
 * @file       config.hpp
 * @brief
 * @date       2021-03-21
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COROUTINE_CONFIG_HPP
#define KERBAL_COROUTINE_CONFIG_HPP

#define KERBAL_COROUTINE_STD_LIB_ID_STD			0
#define KERBAL_COROUTINE_STD_LIB_ID_STD_EXP		1

#if __has_include(<coroutine>)

#	include <coroutine>
#	define KERBAL_COROUTINE_STD_LIB_ID		KERBAL_COROUTINE_STD_LIB_ID_STD
#	define KERBAL_SUPPORT_COROUTINE			1

#elif __has_include(<experimental/coroutine>)

#	include <experimental/coroutine>
#	define KERBAL_COROUTINE_STD_LIB_ID		KERBAL_COROUTINE_STD_LIB_ID_STD_EXP
#	define KERBAL_SUPPORT_COROUTINE			1

#endif

#endif // KERBAL_COROUTINE_CONFIG_HPP
