/**
 * @file       tick_count.h
 * @brief
 * @date       2017-11-05
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_TICK_COUNT_H
#define KERBAL_UTILITY_TICK_COUNT_H

#include <kerbal/config/system.hpp>

#if KERBAL_SYSTEM == KERBAL_SYSTEM_LINUX || \
    KERBAL_SYSTEM == KERBAL_SYSTEM_APPLE

# include <time.h>
# include <unistd.h>
# include <pwd.h>

inline
unsigned long GetTickCount()
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

#elif KERBAL_SYSTEM == KERBAL_SYSTEM_WINDOWS

#	include <windows.h>

#endif

#endif // KERBAL_UTILITY_TICK_COUNT_H
