/*
 * redis_command.hpp
 *
 *  Source from: 2018年4月18日建立的 auto_redis.hpp, auto_redis.cpp 文件
 *  Created on: 2018年5月29日
 *      Author: peter
 */

#ifndef INCLUDE_REDIS_REDIS_COMMAND_HPP_
#define INCLUDE_REDIS_REDIS_COMMAND_HPP_

#include <string>
#include <kerbal/redis/redis_type_traits.hpp>
#include <kerbal/redis/redis_context.hpp>
#include <kerbal/redis/redis_reply.hpp>
#include <kerbal/redis/redis_exception.hpp>

namespace kerbal
{
	namespace redis
	{

		class RedisCommand
		{
			private:
				std::string cmd;

				friend class RedisUnexpectedCaseException;

			public:
				RedisCommand() :
						cmd()
				{
				}

				RedisCommand(const std::string & command) :
						cmd(command)
				{
				}

#if __cplusplus >= 201103L

				RedisCommand(std::string && command) :
						cmd(std::move(command))
				{
				}

#endif

				RedisCommand(const char * command) :
						cmd(command)
				{
				}

				void resetCommand(const std::string & command)
				{
					cmd = command;
				}

#if __cplusplus >= 201103L

				void resetCommand(std::string && command)
				{
					cmd = std::move(command);
				}

#endif

				void resetCommand(const char * command)
				{
					cmd.assign(command);
				}

				const std::string & getCommand() const
				{
					return cmd;
				}

			protected:
				static void redis_execute_allow_type_checker() noexcept
				{
				}

				template <typename Type, typename ...Args>
				static void redis_execute_allow_type_checker(const Type &, Args && ... args) noexcept
				{
					static_assert(redis_type_traits<Type>::is_execute_allowed_type,
									"RedisCommand.execute doesn't allow args type");
					redis_execute_allow_type_checker(std::forward<Args>(args)...);
				}

#if __cplusplus < 201103L
				template <typename T>
				static constexpr const T& cast_to_va_arg_compatible_type(const T& t) noexcept
				{
					return t;
				}
#else

				template <typename T>
				static constexpr
				typename std::enable_if<std::is_enum<T>::value, int>::type
				cast_to_va_arg_compatible_type(const T & t) noexcept
				{
					return (int) t;
				}

				template <typename T>
				static constexpr
				typename std::enable_if<!std::is_enum<T>::value, const T &>::type
				cast_to_va_arg_compatible_type(const T & t) noexcept
				{
					return t;
				}

#endif

				static const char * cast_to_va_arg_compatible_type(const std::string & t) noexcept
				{
					return t.c_str();
				}

				static constexpr const char * cast_to_va_arg_compatible_type(const RedisUnitedStringHelper & t) noexcept
				{
					return t.c_str();
				}

			public:

				template <typename ...Args>
				RedisReply execute(const RedisContext & conn, Args && ...args)
				{
					redis_execute_allow_type_checker(std::forward<Args>(args)...);
					RedisReply reply = (redisReply *) redisCommand(conn.get(), cmd.c_str(),
								cast_to_va_arg_compatible_type( std::forward<Args>(args))...);
					if (reply.replyType() == RedisReplyType::ERROR) {
						throw RedisCommandExecuteFailedException(std::string("redis reply error: ") + reply->str);
					}
					if (reply == nullptr) {
						throw RedisException("redis reply null exception");
					}
					return reply;
				}
		};
	}
}

#endif /* INCLUDE_REDIS_REDIS_COMMAND_HPP_ */
