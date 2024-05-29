/**
 * @file       tick_count.unix.part.hpp
 * @brief
 * @date       2023-06-04
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COMPATIBILITY_TICK_COUNT_DETAIL_TICK_COUNT_UNIX_PART_HPP
#define KERBAL_COMPATIBILITY_TICK_COUNT_DETAIL_TICK_COUNT_UNIX_PART_HPP

#ifndef KERBAL_SUPPORTS_TICK_COUNT

#include <kerbal/config/system.hpp>

#if KERBAL_SYSTEM == KERBAL_SYSTEM_LINUX || \
    KERBAL_SYSTEM == KERBAL_SYSTEM_APPLE

#define KERBAL_SUPPORTS_TICK_COUNT 1

#include <kerbal/compatibility/noexcept.hpp>

#include <time.h>
#include <unistd.h>
#include <pwd.h>


namespace kerbal
{

	namespace compatibility
	{

		inline
		unsigned long get_tick_count() KERBAL_NOEXCEPT
		{
			struct timespec ts;
			clock_gettime(CLOCK_MONOTONIC, &ts);
			return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
		}

	} // namespace compatibility

} // namespace kerbal


#endif

#endif // #ifndef KERBAL_SUPPORTS_TICK_COUNT

#endif // KERBAL_COMPATIBILITY_TICK_COUNT_DETAIL_TICK_COUNT_UNIX_PART_HPP
