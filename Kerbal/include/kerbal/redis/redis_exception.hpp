/*
 * redis_exception.hpp
 *
 *  Created on: 2018年5月29日
 *      Author: peter
 */

#ifndef SRC_REDIS_REDIS_EXCEPTION_HPP_
#define SRC_REDIS_REDIS_EXCEPTION_HPP_

#include <exception>
#include <sstream>

namespace kerbal
{
	namespace redis
	{
		class RedisException: public std::exception
		{
			protected:
				std::string reason;

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

				static std::string redis_reply_type_cast(RedisReplyType correctType)
				{
					std::ostringstream ss;
					ss << correctType;
					return ss.str();
				}

			public:
				RedisUnexceptedCaseException(const std::string & excute_command = "(unknown command)") :
						RedisException("redis returns an unexcepted case when excute command: " + excute_command), excute_command(excute_command)
				{
				}

				RedisUnexceptedCaseException(RedisReplyType correctType, const std::string & excute_command = "(unknown command)") :
						RedisException("redis returns an unexcepted case when excute command: " + excute_command + " , correct type is: " + redis_reply_type_cast(correctType))
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

#endif /* SRC_REDIS_REDIS_EXCEPTION_HPP_ */
