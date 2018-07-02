/*
 * redis_context_pool.hpp
 *
 *  Created on: 2018年6月12日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_REDIS_REDIS_CONTEXT_POOL_HPP_
#define INCLUDE_KERBAL_REDIS_REDIS_CONTEXT_POOL_HPP_

#include <kerbal/redis/redis_context.hpp>
#include <kerbal/redis/redis_exception.hpp>
#include <thread>
#include <chrono>


namespace kerbal
{
	namespace redis
	{

		class ContextPoolInitFailedException: public kerbal::redis::RedisException
		{
			protected:
				typedef kerbal::redis::RedisException supper_t;

			public:
				ContextPoolInitFailedException(int n, const std::string & errstr) :
						supper_t("Redis context pool init failed, the failed index: " + std::to_string(n) + ", errstr: " + errstr)
				{
				}
		};

		class ContextPoolApplyFailedException: public kerbal::redis::RedisException
		{
			protected:
				typedef kerbal::redis::RedisException supper_t;

			public:
				ContextPoolApplyFailedException() :
						supper_t("Redis context pool apply failed")
				{
				}
		};

		template <unsigned short N>
		class RedisContextPool;

		template <unsigned short N>
		class ContextPoolRefence
		{
			protected:
				const size_t n;
				RedisContextPool<N> * const p_to_pool;

			public:
				ContextPoolRefence(size_t n, RedisContextPool<N> & pool) noexcept;
				~ContextPoolRefence() noexcept;

				operator kerbal::redis::Context&() noexcept;

				size_t get_id() const
				{
					return n;
				}

		};

		template <unsigned short N>
		class RedisContextPool
		{
			protected:
				Context pool[N];
				pid_t pids[N];

			public:
				RedisContextPool(const char ip[], int port, const std::chrono::milliseconds & ms)
				{
					for (size_t i = 0; i < 4; ++i) {
						pool[i].connectWithTimeout(ip, port, ms);
						if (!pool[i]) {
							throw ContextPoolInitFailedException(i, pool[i].errstr());
						}
						pids[i] = 0;
					}
				}

				ContextPoolRefence<N> apply(pid_t pid, const std::chrono::milliseconds & retry_interval = std::chrono::milliseconds(200),
													unsigned short try_times = 5)
				{
					while (try_times--) {
						for (size_t i = 0; i < N; ++i) {
							if (pids[i] == 0) {
								pids[i] = pid;
								std::cout << "context pool apply: " << i << std::endl;
								return ContextPoolRefence<N>(i, *this);
							}
						}
						std::this_thread::sleep_for(retry_interval);
					}
					throw ContextPoolApplyFailedException();
				}

				void revert(size_t n) noexcept
				{
					std::cout << "revert context" << n << std::endl;
#				if (TRACK_RESOURCE_FREE == true)
					std::cout << "revert context" << n << std::endl;
#				endif
					pids[n] = 0;
				}

				friend class ContextPoolRefence<N> ;
		};

		template <unsigned short N>
		ContextPoolRefence<N>::ContextPoolRefence(size_t n, RedisContextPool<N> & pool) noexcept :
				n(n), p_to_pool(&pool)
		{
		}

		template <unsigned short N>
		ContextPoolRefence<N>::~ContextPoolRefence() noexcept
		{
			p_to_pool->revert(n);
		}

		template <unsigned short N>
		ContextPoolRefence<N>::operator Context&() noexcept
		{
			return p_to_pool->pool[n];
		}

	}
}

#endif /* INCLUDE_KERBAL_REDIS_REDIS_CONTEXT_POOL_HPP_ */
