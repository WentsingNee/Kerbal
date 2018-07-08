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

		class RedisContextPool;

		class ContextPoolReference
		{
			protected:
				size_t n;
				RedisContextPool * p_to_pool;

				friend class RedisContextPool;

				ContextPoolReference(size_t n, RedisContextPool & pool) noexcept;

			public:
				ContextPoolReference(ContextPoolReference&&) noexcept;
				ContextPoolReference(volatile ContextPoolReference&&) noexcept;
				ContextPoolReference(const ContextPoolReference&) = delete;
				~ContextPoolReference() noexcept;

				operator kerbal::redis::Context&() noexcept;
				operator const kerbal::redis::Context&() const noexcept;

				void convert();
				void release();

				size_t get_id() const;
		};

		class RedisContextPool
		{
			protected:
				const size_t N;
				Context pool[50];
				pid_t pids[50];

			public:
				RedisContextPool(size_t N, const char ip[], int port, const std::chrono::milliseconds & ms) :
						N(N)
				{
					for (size_t i = 0; i < N; ++i) {
						pool[i].connectWithTimeout(ip, port, ms);
						if (!pool[i]) {
							throw ContextPoolInitFailedException(i, pool[i].errstr());
						}
						pids[i] = 0;
					}
				}

				ContextPoolReference apply(pid_t pid, const std::chrono::milliseconds & retry_interval = std::chrono::milliseconds(200),
													unsigned short try_times = 5)
				{
					while (try_times--) {

						for (size_t i = 0; i < N; ++i) {
							if (pids[i] == 0) {
								pids[i] = pid;
								return ContextPoolReference(i, *this);
							}
						}
						std::this_thread::sleep_for(retry_interval);
					}
					throw ContextPoolApplyFailedException();
				}

				void revert(const ContextPoolReference & ref) noexcept
				{
					size_t n = ref.n;
#				if (TRACK_RESOURCE_FREE == true)
					std::cout << "revert context" << n << std::endl;
#				endif
					pids[n] = 0;
				}

				friend class ContextPoolReference ;
		};

		inline ContextPoolReference::ContextPoolReference(size_t n, RedisContextPool & pool) noexcept :
				n(n), p_to_pool(&pool)
		{
		}

		inline ContextPoolReference::ContextPoolReference(ContextPoolReference && src) noexcept :
				n(src.n), p_to_pool(src.p_to_pool)
		{
			src.n = -1;
			src.p_to_pool = nullptr;
		}

		inline ContextPoolReference::ContextPoolReference(volatile ContextPoolReference && src) noexcept :
				n(src.n), p_to_pool(src.p_to_pool)
		{
			src.n = -1;
			src.p_to_pool = nullptr;
		}

		inline ContextPoolReference::~ContextPoolReference() noexcept
		{
			this->convert();
		}

		inline ContextPoolReference::operator Context&() noexcept
		{
			return p_to_pool->pool[n];
		}

		inline ContextPoolReference::operator const Context&() const noexcept
		{
			return p_to_pool->pool[n];
		}

		inline void ContextPoolReference::convert()
		{
			if (p_to_pool != nullptr) {
				p_to_pool->revert(*this);
				p_to_pool = nullptr;
			}
		}

		inline void ContextPoolReference::release()
		{
			p_to_pool = nullptr;
		}

		inline size_t ContextPoolReference::get_id() const
		{
			return n;
		}
	}
}

#endif /* INCLUDE_KERBAL_REDIS_REDIS_CONTEXT_POOL_HPP_ */
