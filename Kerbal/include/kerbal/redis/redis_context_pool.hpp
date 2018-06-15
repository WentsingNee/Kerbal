/*
 * redis_context_pool.hpp
 *
 *  Created on: 2018年6月12日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_REDIS_REDIS_CONTEXT_POOL_HPP_
#define INCLUDE_KERBAL_REDIS_REDIS_CONTEXT_POOL_HPP_

#include <thread>
#include <chrono>

#include <kerbal/redis/context.hpp>
#include <kerbal/redis/redis_exception.hpp>

namespace kerbal
{
	namespace redis
	{

		template <unsigned short N>
		class RedisContextPool;

		class ContextPoolInitFailedException;

		template <unsigned short N>
		class ContextPoolRefence
		{
			protected:
				const size_t n;
				RedisContextPool<N> * const p_to_pool;

			public:
				ContextPoolRefence(size_t n, RedisContextPool<N> & pool);
				~ContextPoolRefence();

				operator kerbal::redis::Context&();


		};

		template <unsigned short N>
		class RedisContextPool
		{
			protected:
				kerbal::redis::Context pool[N];
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

				ContextPoolRefence<N> apply(pid_t pid, const std::chrono::milliseconds & retry_interval = std::chrono::milliseconds(200))
				{
					while (true) {
						for (size_t i = 0; i < N; ++i) {
							if (pids[i] == 0) {
								pids[i] = pid;
								return ContextPoolRefence<N>(i, *this);
							}
						}
						std::this_thread::sleep_for(retry_interval);
					}
				}

				void revert(size_t n)
				{
					pids[n] = 0;
				}

				friend class ContextPoolRefence<N> ;
		};

		template <unsigned short N>
		ContextPoolRefence<N>::ContextPoolRefence(size_t n, RedisContextPool<N> & pool) :
				n(n), p_to_pool(&pool)
		{

		}

		template <unsigned short N>
		ContextPoolRefence<N>::~ContextPoolRefence()
		{
			std::cout << "revert" << std::endl;
			p_to_pool->revert(n);
		}

		template <unsigned short N>
		ContextPoolRefence<N>::operator kerbal::redis::Context&()
		{
			return p_to_pool->pool[n];
		}

		class ContextPoolInitFailedException: public kerbal::redis::RedisException
		{
			protected:
				using supper_t = kerbal::redis::RedisException;

			public:
				ContextPoolInitFailedException(int n, const std::string & errstr) :
						supper_t("Redis context pool init failed, the failed index: " + std::to_string(n) + " errstr: " + errstr)
				{
				}
		};
	}
}

#endif /* INCLUDE_KERBAL_REDIS_REDIS_CONTEXT_POOL_HPP_ */
