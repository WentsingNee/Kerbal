/**
 * @file       tick_count.hpp
 * @brief
 * @date       2017-11-05
 * @author     Peter
 * @remark     renamed from tick_count.h
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COMPATIBILITY_TICK_COUNT_HPP
#define KERBAL_COMPATIBILITY_TICK_COUNT_HPP

#include <kerbal/compatibility/tick_count/detail/tick_count.unix.part.hpp>
#include <kerbal/compatibility/tick_count/detail/tick_count.wasm.part.hpp>
#include <kerbal/compatibility/tick_count/detail/tick_count.win.part.hpp>

#ifndef KERBAL_SUPPORTS_TICK_COUNT
#	define KERBAL_SUPPORTS_TICK_COUNT 0
#endif

#endif // KERBAL_COMPATIBILITY_TICK_COUNT_HPP
