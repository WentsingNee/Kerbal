/**
 * @file       spin_lock.fwd.hpp
 * @brief
 * @date       2025-09-11
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_PARALLEL_SPIN_LOCK_SPIN_LOCK_DECL_HPP
#define KERBAL_PARALLEL_SPIN_LOCK_SPIN_LOCK_DECL_HPP

#include <kerbal/parallel/spin_lock/spin_lock.fwd.hpp>

#include <kerbal/compatibility/noexcept.hpp>

#include <atomic>
#include <thread>
#include <bits/this_thread_sleep.h>


namespace kerbal
{

	namespace parallel
	{

		class spin_lock
		{
			private:
				std::atomic_flag k_lock;

			public:
				void lock() KERBAL_NOEXCEPT
				{
					while (this->k_lock.test_and_set(std::memory_order_acquire)) {
						std::this_thread::yield();
					}
				}

				void unlock() KERBAL_NOEXCEPT
				{
					this->k_lock.clear(std::memory_order_release);
				}

		};

	} // namespace parallel

} // namespace kerbal

#endif // KERBAL_PARALLEL_SPIN_LOCK_SPIN_LOCK_DECL_HPP
