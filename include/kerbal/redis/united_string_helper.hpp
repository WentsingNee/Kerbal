/*
 * united_string_helper.hpp
 *
 *  Created on: 2018年6月23日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_REDIS_UNITED_STRING_HELPER_HPP_
#define INCLUDE_KERBAL_REDIS_UNITED_STRING_HELPER_HPP_

#include <string>

namespace kerbal
{
	namespace redis
	{
		class RedisUnitedStringHelper
		{
			private:
				const char * s;

				constexpr const char * c_str() const
				{
					return s;
				}

				friend std::string operator+(const RedisUnitedStringHelper & s, const char * with)
				{
					return s.c_str() + std::string(with);
				}

				friend std::string operator+(const char * with, const RedisUnitedStringHelper & s)
				{
					return std::string(with) + s.c_str();
				}

				friend std::string operator+(const RedisUnitedStringHelper & s, const std::string & with)
				{
					return s.c_str() + with;
				}

				friend std::string operator+(const std::string & with, const RedisUnitedStringHelper & s)
				{
					return with + s.c_str();
				}

			public:
				RedisUnitedStringHelper(const RedisUnitedStringHelper&);
				RedisUnitedStringHelper& operator=(const RedisUnitedStringHelper&);

				constexpr RedisUnitedStringHelper(const char * s) :
						s(s)
				{
				}

				RedisUnitedStringHelper(const std::string & s) :
						s(s.c_str())
				{
				}

				friend class Operation;
				friend class RedisCommand;
		};
	}
}


#endif /* INCLUDE_KERBAL_REDIS_UNITED_STRING_HELPER_HPP_ */
