/*
 * tick_count.h
 *
 *  Created on: 2017Äê11ÔÂ5ÈÕ
 *      Author: Peter
 */

#ifndef KERBAL_UTILITY_TICK_COUNT_H_
#define KERBAL_UTILITY_TICK_COUNT_H_

#ifdef __linux
#include <time.h>
inline unsigned long GetTickCount()
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}
#endif

#ifdef __WINDOWS_
#include <windows.h>
#endif

#ifdef _WIN32
#include <windows.h>
#endif

#endif /* KERBAL_UTILITY_TICK_COUNT_H_ */
