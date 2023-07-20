/**
 * @file       thread.fwd.hpp
 * @brief
 * @date       2021-12-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_PARALLEL_THREAD_THREAD_FWD_HPP
#define KERBAL_PARALLEL_THREAD_THREAD_FWD_HPP


#ifndef KERBAL_PARALLEL_HAS_THREAD_SUPPORT

#	include <kerbal/config/system.hpp>

#	if KERBAL_SYSTEM == KERBAL_SYSTEM_LINUX || KERBAL_SYSTEM == KERBAL_SYSTEM_APPLE
#		define KERBAL_PARALLEL_HAS_THREAD_SUPPORT 1
#	elif KERBAL_SYSTEM == KERBAL_SYSTEM_WINDOWS
#		define KERBAL_PARALLEL_HAS_THREAD_SUPPORT 1
#	else
#		define KERBAL_PARALLEL_HAS_THREAD_SUPPORT 0
#	endif

#endif // ifndef KERBAL_PARALLEL_HAS_THREAD_SUPPORT


#if KERBAL_PARALLEL_HAS_THREAD_SUPPORT

#	define KERBAL_PARALLEL_THREAD_MODE_UNKNOWN			0
#	define KERBAL_PARALLEL_THREAD_MODE_POSIX			1
#	define KERBAL_PARALLEL_THREAD_MODE_WIN				2

#	ifndef KERBAL_PARALLEL_THREAD_MODE

#		include <kerbal/config/system.hpp>

#		if KERBAL_SYSTEM == KERBAL_SYSTEM_LINUX || KERBAL_SYSTEM == KERBAL_SYSTEM_APPLE
#			define KERBAL_PARALLEL_THREAD_MODE KERBAL_PARALLEL_THREAD_MODE_POSIX
#		elif KERBAL_SYSTEM == KERBAL_SYSTEM_WINDOWS
#			define KERBAL_PARALLEL_THREAD_MODE KERBAL_PARALLEL_THREAD_MODE_WIN
#		else
#			define KERBAL_PARALLEL_THREAD_MODE KERBAL_PARALLEL_THREAD_MODE_UNKNOWN
#		endif

#	endif // ifndef KERBAL_PARALLEL_THREAD_MODE

#	include <kerbal/parallel/thread/detail/thread.common.fwd.part.hpp>

#endif // if KERBAL_PARALLEL_HAS_THREAD_SUPPORT

#endif // KERBAL_PARALLEL_THREAD_THREAD_FWD_HPP
