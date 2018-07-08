/*
 * auto_free_reply.hpp
 *
 *  Created on: 2018年5月29日
 *      Author: peter
 */

#ifndef INCLUDE_REDIS_AUTO_FREE_REPLY_HPP_
#define INCLUDE_REDIS_AUTO_FREE_REPLY_HPP_

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
			/** @brief 字符串 */
			STRING = REDIS_REPLY_STRING,

			/** @brief 数组，例如 mget 返回值 */
			ARRAY = REDIS_REPLY_ARRAY,

			/** @brief 数字类型 */
			INTEGER = REDIS_REPLY_INTEGER,

			/** @brief 空 */
			NIL = REDIS_REPLY_NIL,

			/** @brief 状态，例如set成功返回的‘OK’ */
			STATUS = REDIS_REPLY_STATUS,

			/** @brief 执行失败 */
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
		 * @brief 一个可以智能释放的 redis reply 指针
		 */
		class AutoFreeReply: public std::unique_ptr<redisReply, void (*)(redisReply *)>
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

			public:
				AutoFreeReply(redisReply * redis_reply = nullptr) noexcept :
						supper_t(redis_reply, redisReplyDealloctor)
				{
				}

				enum RedisReplyType replyType() const noexcept
				{
					return (RedisReplyType) this->get()->type;
				}
		};

	}
}



#endif /* INCLUDE_REDIS_AUTO_FREE_REPLY_HPP_ */
