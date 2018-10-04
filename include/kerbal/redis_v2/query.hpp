/*
 * query.hpp
 *
 *  Created on: 2018年10月4日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_REDIS_V2_QUERY_HPP_
#define INCLUDE_KERBAL_REDIS_V2_QUERY_HPP_

#include <sstream>

#include <kerbal/redis_v2/connection.hpp>
#include <kerbal/redis_v2/reply.hpp>
#include <kerbal/redis_v2/type_traits.hpp>

namespace kerbal
{

	namespace redis_v2
	{

		class query : public std::ostringstream
		{
			private:
				typedef std::ostringstream supper_t;

			public:
				query() :
						supper_t()
				{
				}

				template <typename T>
				static KERBAL_CONSTEXPR const T& cast_to_va_arg_compatible_type(const T& t) noexcept
				{
					return t;
				}

				static KERBAL_CONSTEXPR const char * cast_to_va_arg_compatible_type(const std::string & t) noexcept
				{
					return t.c_str();
				}

//				static KERBAL_CONSTEXPR const char * cast_to_va_arg_compatible_type(const RedisUnitedStringHelper & t) noexcept
//				{
//					return t.c_str();
//				}

#if __cplusplus >= 201103L

				template <typename T>
				static constexpr T&& cast_to_va_arg_compatible_type(T&& t) noexcept
				{
					return t;
				}

				template <typename T>
				static constexpr const char * cast_to_va_arg_compatible_type(std::string&& t) noexcept
				{
					return t.c_str();
				}

#endif

#			if __cplusplus >= 201103L
				template <typename ...Args,
							typename = typename kerbal::type_traits::enable_if<is_redis_execute_list<Args...>::value>::type>
				reply execute(const connection & conn, Args && ...args)
				{
					reply reply((redisReply *) redisCommand((::redisContext*)conn.get(), this->str().c_str(),
													cast_to_va_arg_compatible_type(std::forward<Args>(args))...));
								
					if (reply == nullptr) {
//						throw RedisException("redis reply null exception");
					}
					if (reply.type() == reply_type::ERROR) {
//						throw RedisCommandExecuteFailedException(std::string("redis reply error: ") + reply->str);
					}
					return reply;
				}
#			endif

		};

	} /* namespace redis_v2 */

} /* namespace kerbal */


#endif /* INCLUDE_KERBAL_REDIS_V2_QUERY_HPP_ */
