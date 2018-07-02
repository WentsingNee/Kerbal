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

#if __cplusplus < 201703L
				template <typename ...Args>
				static std::string format_va_args(const RedisUnitedStringHelper & templ, Args&& ...args)
				{
					boost::format fmt(templ.c_str());
					std::initializer_list<char> { (fmt % args, '\0')... };
					return fmt.str();
				}
#else //C++17 fold expressions
				template <typename ...Args>
				static std::string format_va_args(const RedisUnitedStringHelper & templ, Args&& ...args) {
					return (boost::format(templ.c_str()) % ... % args ).str();
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
				static void redis_excute_allow_type_checker() noexcept
				{
				}

				template <typename Type, typename ...Args>
				static constexpr void redis_excute_allow_type_checker(const Type &, Args&& ... args) noexcept
				{
					static_assert(is_redis_excute_allow_type<Type>::value, "RedisCommand.excute doesn't allow args type");
					redis_excute_allow_type_checker(args...);
				}

				template <typename T>
				static constexpr const T& cast_to_va_arg_compatible_type(const T& t) noexcept
				{
					return t;
				}

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
				AutoFreeReply excute(const Context & conn, Args && ...args)
				{
					redis_excute_allow_type_checker(args...);

					AutoFreeReply reply = (redisReply *) redisCommand(conn.get(), cmd.c_str(), cast_to_va_arg_compatible_type(args)...);
					if (reply.replyType() == RedisReplyType::ERROR) {
						throw RedisCommandExcuteFailedException(std::string("redis reply error: ") + reply->str);
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
