/**
 * @file       thread.posix.decl.part.hpp
 * @brief
 * @date       2022-05-17
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_PARALLEL_THREAD_DETAIL_THREAD_POSIX_DECL_PART_HPP
#define KERBAL_PARALLEL_THREAD_DETAIL_THREAD_POSIX_DECL_PART_HPP

#include <pthread.h>


namespace kerbal
{

	namespace parallel
	{

		namespace detail
		{
			typedef ::pthread_t thread_native_handle_type;
		}

	} // namespace parallel

} // namespace kerbal


#endif // KERBAL_PARALLEL_THREAD_DETAIL_THREAD_POSIX_DECL_PART_HPP
