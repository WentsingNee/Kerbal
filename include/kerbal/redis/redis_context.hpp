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
		/**
		 * @brief An auto-closed redis context.
		 */
		class RedisContext: protected std::shared_ptr<redisContext>
		{
			private:
				static void redisContextDealloctor(redisContext * conn) noexcept
				{
#if (TRACK_RESOURCE_FREE == true)
					std::cout << "free redisContext   " << conn << std::endl;
#endif
					redisFree(conn);
				}

				typedef std::shared_ptr<redisContext> supper_t;

			public:

				/**
				 * @brief Construct an empty context.
				 * @throws The constructor will never throw any exception.
				 */
				RedisContext() noexcept :
						supper_t(nullptr)
				{
				}

				RedisContext(const char ip[], int port) noexcept
				{
					redisContext * tmp = redisConnect(ip, port);
					if (tmp == nullptr) {
						reset();
					} else {
						reset(tmp, redisContextDealloctor);
					}
				}

				RedisContext(const char ip[], int port, const struct timeval tv) noexcept
				{
					redisContext * tmp = redisConnectWithTimeout(ip, port, tv);
					if (tmp == nullptr) {
						reset();
					} else {
						reset(tmp, redisContextDealloctor);
					}
				}

				RedisContext(const char ip[], int port, const std::chrono::milliseconds & ms) noexcept
				{
					struct timeval tv;
					tv.tv_sec = ms.count() / 1000;
					tv.tv_usec = ms.count() % 1000;
					redisContext * tmp = redisConnectWithTimeout(ip, port, tv);
					if (tmp == nullptr) {
						reset();
					} else {
						reset(tmp, redisContextDealloctor);
					}
				}

				int reconnect() noexcept
				{
					return redisReconnect(this->get());
				}

				/**
				 * @brief Test whether the context is valid.
				 * @throws The constructor will never throw any exception.
				 */
				operator bool() const noexcept
				{
					return this->isValid();
				}

				/**
				 * @brief Test whether the context is valid.
				 * @return True if valid, false otherwise.
				 */
				bool isValid() const noexcept
				{
					return this->get() != nullptr && this->get()->err == 0;
				}

				/**
				 * @brief Get the string which describes the error.
				 * @return Error string
				 */
				std::string errstr() const
				{
					return this->get()->errstr;
				}

				friend class Option;
				friend class RedisCommand;

				using supper_t::operator ->;

		};

		inline RedisContext getContext(const char ip[], int port) noexcept
		{
			return RedisContext(ip, port);
		}

		inline RedisContext getContext(const char ip[], int port, const struct timeval tv) noexcept
		{
			return RedisContext(ip, port, tv);
		}

		inline RedisContext getContext(const char ip[], int port, const std::chrono::milliseconds & ms) noexcept
		{
			struct timeval tv;
			tv.tv_sec = ms.count() / 1000;
			tv.tv_usec = ms.count() % 1000;
			return RedisContext(ip, port, tv);
		}
	}
}

#endif /* INCLUDE_REDIS_REDIS_CONTEXT_HPP_ */
