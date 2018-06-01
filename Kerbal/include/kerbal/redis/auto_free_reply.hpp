/*
 * auto_free_reply.hpp
 *
 *  Created on: 2018年5月29日
 *      Author: peter
 */

#ifndef SRC_REDIS_AUTO_FREE_REPLY_HPP_
#define SRC_REDIS_AUTO_FREE_REPLY_HPP_

namespace kerbal
{
	namespace redis
	{
		/**
		 * @brief redis 执行结果类型
		 */
		enum class Redis_reply_type
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

		/**
		 * @brief 一个可以智能释放的 redis reply 指针
		 */
		class AutoFreeReply: public std::unique_ptr<redisReply, void (*)(redisReply *)>
		{
			private:
				static void redisReplyDealloctor(redisReply * reply_ptr)
				{
#if (TRACK_RESOURCE_FREE == true)
					std::cout << "free redisReply   " << reply_ptr << std::endl;
#endif
					freeReplyObject(reply_ptr);
				}

				using father_t = std::unique_ptr<redisReply, void (*)(redisReply *)>;

			public:
				AutoFreeReply(redisReply * redis_reply = nullptr) :
						father_t(redis_reply, redisReplyDealloctor)
				{
				}

				enum Redis_reply_type replyType() const
				{
					return (Redis_reply_type) this->get()->type;
				}
		};


		inline std::ostream& operator <<(std::ostream & out, Redis_reply_type type)
		{
			using Redis_reply_type = Redis_reply_type;
			switch (type) {
				case Redis_reply_type::STRING:
					return out << "STRING";
				case Redis_reply_type::ARRAY:
					return out << "ARRAY";
				case Redis_reply_type::INTEGER:
					return out << "INTEGER";
				case Redis_reply_type::NIL:
					return out << "NIL";
				case Redis_reply_type::STATUS:
					return out << "STATUS";
				case Redis_reply_type::ERROR:
					return out << "ERROR";
				default:
					return out << "OTHER UNKNOWN";
			}
		}

	}
}



#endif /* SRC_REDIS_AUTO_FREE_REPLY_HPP_ */
