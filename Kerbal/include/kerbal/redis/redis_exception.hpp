/*
 * redis_exception.hpp
 *
 *  Created on: 2018年5月29日
 *      Author: peter
 */

#ifndef SRC_REDIS_REDIS_EXCEPTION_HPP_
#define SRC_REDIS_REDIS_EXCEPTION_HPP_

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

		class RedisUnexceptedCaseException: RedisException
		{
			public:
				RedisUnexceptedCaseException() :
						RedisException("an unexcepted situation occured")
				{
				}
		};

		class RedisCommandExcuteFailedException: RedisException
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
