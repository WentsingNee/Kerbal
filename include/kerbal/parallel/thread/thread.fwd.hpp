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

#include <memory>


#ifndef KERBAL_PARALLEL_THREAD_MODE

#	define KERBAL_PARALLEL_THREAD_MODE_UNKNOWN    0
#	define KERBAL_PARALLEL_THREAD_MODE_POSIX      1
#	define KERBAL_PARALLEL_THREAD_MODE_WIN        2

#	include <kerbal/config/system.hpp>

#	if KERBAL_SYSTEM == KERBAL_SYSTEM_LINUX || KERBAL_SYSTEM == KERBAL_SYSTEM_APPLE
#		define KERBAL_PARALLEL_THREAD_MODE KERBAL_PARALLEL_THREAD_MODE_POSIX
#	elif KERBAL_SYSTEM == KERBAL_SYSTEM_WINDOWS
#		define KERBAL_PARALLEL_THREAD_MODE KERBAL_PARALLEL_THREAD_MODE_WIN
#	else
#		define KERBAL_PARALLEL_THREAD_MODE KERBAL_PARALLEL_THREAD_MODE_UNKNOWN
#		error "Not implemented yet"
#	endif

#endif


namespace kerbal
{

	namespace parallel
	{

		template <typename Allocator>
		class basic_thread;

		typedef basic_thread<std::allocator<char> > thread;

	} // namespace parallel

} // namespace kerbal

#endif // KERBAL_PARALLEL_THREAD_THREAD_FWD_HPP
