/*
 * Context.hpp
 *
 *  Created on: 2018年5月29日
 *      Author: peter
 */

#ifndef INCLUDE_REDIS_REDIS_CONTEXT_HPP_
#define INCLUDE_REDIS_REDIS_CONTEXT_HPP_

#include <iostream>
#include <string>
#include <memory>
#include <chrono>

#include <hiredis/hiredis.h>

namespace kerbal
{
	namespace redis
	{
		class Context: protected std::unique_ptr<redisContext, void (*)(redisContext *)>
		{
			private:
				static void redisContextDealloctor(redisContext * conn) noexcept
				{
#if (TRACK_RESOURCE_FREE == true)
					std::cout << "free redisContext   " << conn << std::endl;
#endif
					redisFree(conn);
				}

				typedef std::unique_ptr<redisContext, void (*)(redisContext *)> supper_t;

			public:

				Context() noexcept :
						supper_t(nullptr, redisContextDealloctor)
				{
				}

				void close() noexcept
				{
					this->reset(nullptr);
				}

				bool connect(const char ip[], int port) noexcept
				{
					supper_t::reset(redisConnect(ip, port));
					return this->isValid();
				}

				bool connectWithTimeout(const char ip[], int port, const struct timeval tv) noexcept
				{
					supper_t::reset(redisConnectWithTimeout(ip, port, tv));
					return this->isValid();
				}

				bool connectWithTimeout(const char ip[], int port, const std::chrono::milliseconds & ms) noexcept
				{
					struct timeval tv;
					tv.tv_sec = ms.count() / 1000;
					tv.tv_usec = ms.count() % 1000;
					return connectWithTimeout(ip, port, tv);
				}

				int reconnect() noexcept
				{
					return redisReconnect(this->get());
				}

				operator bool() const noexcept
				{
					return this->isValid();
				}

				bool isValid() const noexcept
				{
					return this->get() != nullptr && this->get()->err == 0;
				}

				void free() noexcept
				{
					this->reset(nullptr);
				}

				std::string errstr() const
				{
					return this->get()->errstr;
				}

				friend class Option;
				friend class RedisCommand;

		};
	}
}

#endif /* INCLUDE_REDIS_REDIS_CONTEXT_HPP_ */
