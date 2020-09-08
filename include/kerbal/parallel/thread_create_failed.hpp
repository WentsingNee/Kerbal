/**
 * @file       thread_create_failed.hpp
 * @brief
 * @date       2020-07-21
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_PARALLEL_THREAD_CREATE_FAILED_HPP
#define KERBAL_PARALLEL_THREAD_CREATE_FAILED_HPP

#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/utility/throw_this_exception.hpp>

#include <stdexcept>

namespace kerbal
{

	namespace parallel
	{

		class thread;

		class thread_create_failed:
				public kerbal::utility::throw_this_exception_helper<thread_create_failed>,
				public std::runtime_error
		{
			private:
				friend class kerbal::parallel::thread;
				friend class kerbal::utility::throw_this_exception_helper<thread_create_failed>;

				thread_create_failed() KERBAL_NOEXCEPT:
						std::runtime_error("can't create thread")
				{
				}

		};

	} // namespace parallel

} // namespace kerbal

#endif // KERBAL_PARALLEL_THREAD_CREATE_FAILED_HPP
