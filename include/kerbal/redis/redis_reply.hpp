/*
 * auto_free_reply.hpp
 *
 *  Created on: 2018年5月29日
 *      Author: peter
 */

#ifndef INCLUDE_REDIS_REDIS_REPLY_HPP_
#define INCLUDE_REDIS_REDIS_REPLY_HPP_

#include <iostream>
#include <memory>

#include <hiredis/hiredis.h>

namespace kerbal
{
	namespace redis
	{
		/**
		 * @brief redis 执行结果类型
		 */
		enum class RedisReplyType
		{
			/// @brief String
			STRING = REDIS_REPLY_STRING,

			/// @brief Array，like the reply type of command 'mget'
			ARRAY = REDIS_REPLY_ARRAY,

			/// @brief Integer
			INTEGER = REDIS_REPLY_INTEGER,

			/// @brief Nil
			NIL = REDIS_REPLY_NIL,

			/// @brief Status，like the reply of ‘OK’ if command 'set' executed successfully
			STATUS = REDIS_REPLY_STATUS,

			/// @brief Error if redis command execute failed
			ERROR = REDIS_REPLY_ERROR

		};

		template <typename ReturnType = std::string>
		ReturnType redisReplyTypeName(RedisReplyType type);

		template <>
		inline const char * redisReplyTypeName(RedisReplyType type)
		{
			switch (type) {
				case RedisReplyType::STRING:
					return "STRING";
				case RedisReplyType::ARRAY:
					return "ARRAY";
				case RedisReplyType::INTEGER:
					return "INTEGER";
				case RedisReplyType::NIL:
					return "NIL";
				case RedisReplyType::STATUS:
					return "STATUS";
				case RedisReplyType::ERROR:
					return "ERROR";
				default:
					return "OTHER UNKNOWN";
			}
		}

		template <>
		inline std::string redisReplyTypeName(RedisReplyType type)
		{
			return redisReplyTypeName<const char *>(type);
		}

		inline std::ostream& operator <<(std::ostream & out, RedisReplyType type)
		{
			return out << redisReplyTypeName<const char *>(type);
		}


		/**
		 * @brief An auto-free redis reply.
		 */
		class RedisReply: protected std::unique_ptr<redisReply, void (*)(redisReply *)>
		{
			private:
				static void redisReplyDealloctor(redisReply * reply_ptr) noexcept
				{
#if (TRACK_RESOURCE_FREE == true)
					std::cout << "free redisReply   " << reply_ptr << std::endl;
#endif
					freeReplyObject(reply_ptr);
				}

				typedef std::unique_ptr<redisReply, void (*)(redisReply *)> supper_t;

			protected:
				RedisReply(redisReply * redis_reply) noexcept :
						supper_t(redis_reply, redisReplyDealloctor)
				{
				}

				friend class RedisCommand;

			public:
				RedisReply() noexcept :
						supper_t(nullptr, redisReplyDealloctor)
				{
				}

				RedisReply(std::nullptr_t) noexcept :
						supper_t(nullptr, redisReplyDealloctor)
				{
				}

				/**
				 * @brief Get the type of reply.
				 * @return The type of reply.
				 * @throws The method never throws any exception.
				 */
				enum RedisReplyType replyType() const noexcept
				{
					return (RedisReplyType) this->get()->type;
				}

				bool operator==(std::nullptr_t)
				{
					return this->get() == nullptr;
				}

				using supper_t::operator ->;

		};

	}
}



#endif /* INCLUDE_REDIS_REDIS_REPLY_HPP_ */
