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
