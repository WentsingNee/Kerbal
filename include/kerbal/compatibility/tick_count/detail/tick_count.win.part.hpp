/**
 * @file       tick_count.win.part.hpp
 * @brief
 * @date       2023-06-04
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COMPATIBILITY_TICK_COUNT_DETAIL_TICK_COUNT_WIN_PART_HPP
#define KERBAL_COMPATIBILITY_TICK_COUNT_DETAIL_TICK_COUNT_WIN_PART_HPP

#ifndef KERBAL_HAS_TICK_COUNT_SUPPORT

#include <kerbal/config/system.hpp>

#if KERBAL_SYSTEM == KERBAL_SYSTEM_WINDOWS

#define KERBAL_HAS_TICK_COUNT_SUPPORT 1

#include <kerbal/compatibility/noexcept.hpp>

#ifndef NOMINMAX
#	define NOMINMAX
#endif

#include <windows.h>


namespace kerbal
{

	namespace compatibility
	{

		inline
		unsigned long get_tick_count() KERBAL_NOEXCEPT
		{
			return GetTickCount();
		}

	} // namespace compatibility

} // namespace kerbal


#endif // #if KERBAL_SYSTEM == KERBAL_SYSTEM_WINDOWS

#endif // #ifndef KERBAL_HAS_TICK_COUNT_SUPPORT

#endif // KERBAL_COMPATIBILITY_TICK_COUNT_DETAIL_TICK_COUNT_WIN_PART_HPP
