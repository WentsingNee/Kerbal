/**
 * @file       lock_guard.decl.hpp
 * @brief
 * @date       2025-09-11
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_PARALLEL_LOCK_GUARD_LOCK_GUARD_DECL_HPP
#define KERBAL_PARALLEL_LOCK_GUARD_LOCK_GUARD_DECL_HPP

#include <kerbal/parallel/lock_guard/lock_guard.fwd.hpp>


namespace kerbal
{

	namespace parallel
	{

		template <typename Lock>
		class lock_guard
		{
			public:
				typedef Lock lock_type;

			private:
				lock_type & k_lock;

			public:

				explicit
				lock_guard(lock_type & lock) :
					k_lock(lock)
				{
					this->k_lock.lock();
				}

				~lock_guard()
				{
					this->k_lock.unlock();
				}
		};

#	if __cplusplus >= 201703L

		template <typename Lock>
		lock_guard(Lock &) ->
		lock_guard<Lock>;

#	endif

	} // namespace parallel

} // namespace kerbal

#endif // KERBAL_PARALLEL_LOCK_GUARD_LOCK_GUARD_DECL_HPP
