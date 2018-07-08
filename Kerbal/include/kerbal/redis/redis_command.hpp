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
#include <kerbal/redis/auto_free_reply.hpp>
#include <kerbal/redis/redis_exception.hpp>

#include <boost/format.hpp>

namespace kerbal
{
	namespace redis
	{

		class RedisCommand
		{
			private:
				std::string cmd;

				friend class RedisUnexpectedCaseException;

#if __cplusplus < 201703L
				template <typename ...Args>
				static std::string format_va_args(const RedisUnitedStringHelper & templ, Args&& ...args)
				{
					boost::format fmt(templ.c_str());
					std::initializer_list<char> { (fmt % std::forward<Args>(args), '\0')... };
					return fmt.str();
				}
#else //C++17 fold expressions
				template <typename ...Args>
				static std::string format_va_args(const RedisUnitedStringHelper & templ, Args&& ...args) {
					return (boost::format(templ.c_str()) % ... % std::forward<Args>(args) ).str();
				}
#endif

			public:
				RedisCommand() :
						cmd()
				{
				}

				template <typename ...Args>
				RedisCommand(const RedisUnitedStringHelper & command, Args&& ...args) :
						cmd(format_va_args(command, args...))
				{
				}

				template <typename ...Args>
				void resetCommand(const RedisUnitedStringHelper & command, Args&& ...args)
				{
					cmd = format_va_args(command, args...);
				}

			protected:
				static void redis_execute_allow_type_checker() noexcept
				{
				}

				template <typename Type, typename ...Args>
				static constexpr void redis_execute_allow_type_checker(const Type &, Args&& ... args) noexcept
				{
					static_assert(redis_type_traits<Type>::is_execute_allowed_type, "RedisCommand.execute doesn't allow args type");
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
				cast_to_va_arg_compatible_type(const T& t) noexcept
				{
					return (int)t;
				}

				template <typename T>
				static constexpr
				typename std::enable_if<!std::is_enum<T>::value, const T&>::type
				cast_to_va_arg_compatible_type(const T& t) noexcept
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
				AutoFreeReply execute(const Context & conn, Args && ...args)
				{
					redis_execute_allow_type_checker(args...);

					AutoFreeReply reply = (redisReply *) redisCommand(conn.get(), cmd.c_str(), cast_to_va_arg_compatible_type(std::forward<Args>(args))...);
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
