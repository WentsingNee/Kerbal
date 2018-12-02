/*
 * reply.hpp
 *
 *  Created on: 2018年10月4日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_REDIS_V2_REPLY_HPP_
#define INCLUDE_KERBAL_REDIS_V2_REPLY_HPP_

#include <hiredis/hiredis.h>

#include <string>
#include <iostream>

#include <kerbal/compatibility/compatibility_macro.hpp>
#include <kerbal/utility/noncopyable.hpp>

namespace kerbal
{

	namespace redis_v2
	{

#if __cplsuplus < 201103L

		/**
		 * @brief redis 执行结果类型
		 */
		enum reply_type
		{
			STRING = REDIS_REPLY_STRING, ///< @brief String
			ARRAY = REDIS_REPLY_ARRAY, ///< @brief Array，like the reply type of command 'mget'
			INTEGER = REDIS_REPLY_INTEGER, ///< @brief Integer
			NIL = REDIS_REPLY_NIL, ///< @brief Nil
			STATUS = REDIS_REPLY_STATUS, ///< @brief Status, like the reply of ‘OK’ if command 'set' executed successfully
			ERROR = REDIS_REPLY_ERROR ///< @brief Error if redis command execute failed
		};


#else
		/**
		 * @brief redis 执行结果类型
		 */
		enum class reply_type
		{
			STRING = REDIS_REPLY_STRING, ///< @brief String
			ARRAY = REDIS_REPLY_ARRAY, ///< @brief Array，like the reply type of command 'mget'
			INTEGER = REDIS_REPLY_INTEGER, ///< @brief Integer
			NIL = REDIS_REPLY_NIL, ///< @brief Nil
			STATUS = REDIS_REPLY_STATUS, ///< @brief Status, like the reply of ‘OK’ if command 'set' executed successfully
			ERROR = REDIS_REPLY_ERROR ///< @brief Error if redis command execute failed
		};

		using reply_type_cmp = reply_type;
#endif

		template <typename ReturnType = std::string>
		ReturnType reply_type_name(reply_type type);

		template <>
		inline const char * reply_type_name(reply_type type) KERBAL_NOEXCEPT
		{
			switch (type) {
				case reply_type::STRING:
					return "STRING";
				case reply_type::ARRAY:
					return "ARRAY";
				case reply_type::INTEGER:
					return "INTEGER";
				case reply_type::NIL:
					return "NIL";
				case reply_type::STATUS:
					return "STATUS";
				case reply_type::ERROR:
					return "ERROR";
			}
		}

		template <>
		inline std::string reply_type_name(reply_type type)
		{
			return reply_type_name<const char *>(type);
		}

		inline std::ostream& operator<<(std::ostream & out, reply_type type)
		{
			return out << reply_type_name<const char *>(type);
		}

		class reply: kerbal::utility::nonassignable, kerbal::utility::noncopyable
		{
			private:
				typedef ::redisReply raw_redis_reply_t;

				raw_redis_reply_t * reply_ptr;

			public:
				reply() KERBAL_NOEXCEPT :
						reply_ptr(NULL)
				{
				}

				explicit reply(raw_redis_reply_t * raw_reply_ptr) KERBAL_NOEXCEPT :
						reply_ptr(raw_reply_ptr)
				{
				}

#			if __cplusplus >= 201103L

				constexpr reply(std::nullptr_t) noexcept :
						reply_ptr(nullptr)
				{
				}

				reply(reply && src) noexcept :
						reply_ptr(src.reply_ptr)
				{
					src.reply_ptr = nullptr;
				}

#			endif

				~reply() KERBAL_NOEXCEPT
				{
					clear();
				}

#			if __cplusplus >= 201103L

				reply& operator=(std::nullptr_t) noexcept
				{
					clear();
					return *this;
				}

				reply& operator=(reply && src) noexcept
				{
					clear();
					this->reply_ptr = src.reply_ptr;
					src.reply_ptr = nullptr;
					return *this;
				}

#			endif

				void clear() KERBAL_NOEXCEPT
				{
					if (reply_ptr != NULL) {
						::freeReplyObject(reply_ptr);
						reply_ptr = NULL;
					}
				}

				/**
				 * @brief Get the type of reply.
				 * @return The type of reply.
				 * @throws The method never throws any exception.
				 */
				reply_type type() const KERBAL_NOEXCEPT
				{
					return reply_type(this->reply_ptr->type);
				}

				const raw_redis_reply_t * get() const KERBAL_NOEXCEPT
				{
					return this->reply_ptr;
				}

				const raw_redis_reply_t * operator->() const KERBAL_NOEXCEPT
				{
					return this->get();
				}

#			if __cplusplus >= 201103L

				bool operator==(std::nullptr_t) noexcept
				{
					return this->get() == nullptr;
				}

				bool operator!=(std::nullptr_t) noexcept
				{
					return this->get() != nullptr;
				}

#			endif

		};

	} /* namespace redis_v2 */

} /* namespace kerbal */

#endif /* INCLUDE_KERBAL_REDIS_V2_REPLY_HPP_ */
