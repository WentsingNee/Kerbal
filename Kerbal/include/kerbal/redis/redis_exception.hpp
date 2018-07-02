/*
 * redis_exception.hpp
 *
 *  Created on: 2018年5月29日
 *      Author: peter
 */

#ifndef INCLUDE_REDIS_REDIS_EXCEPTION_HPP_
#define INCLUDE_REDIS_REDIS_EXCEPTION_HPP_

#include <exception>
#include <sstream>

#include <kerbal/redis/auto_free_reply.hpp>

namespace kerbal
{
	namespace redis
	{
		class RedisException: public std::exception
		{
			protected:
				const std::string reason;

			public:
				RedisException(const std::string & reason) :
						reason(reason)
				{
				}

				virtual const char * what() const noexcept
				{
					return reason.c_str();
				}
		};

		class RedisNilException: public RedisException
		{
			public:
				const std::string keyName;

				RedisNilException(const std::string & keyName) :
						RedisException("try to get nil objects. key name : " + keyName), keyName(keyName)
				{
				}
		};

		class RedisUnexceptedCaseException: public RedisException
		{
			protected:
				const std::string excute_command;

			public:
				RedisUnexceptedCaseException(const std::string & excute_command = "(unknown command)") :
						RedisException("redis returns an unexcepted case when excute command: " + excute_command), excute_command(excute_command)
				{
				}

				RedisUnexceptedCaseException(RedisReplyType correctType, const std::string & excute_command = "(unknown command)") :
						RedisException("redis returns an unexcepted case when excute command: " + excute_command + " , correct type is: " + redisReplyTypeName(correctType))
				{
				}
		};

		class RedisCommandExcuteFailedException: public RedisException
		{
			public:
				RedisCommandExcuteFailedException(const std::string & failedInfo) :
						RedisException("redis command excute failed : " + failedInfo)
				{
				}
		};
	}
}

#endif /* INCLUDE_REDIS_REDIS_EXCEPTION_HPP_ */
