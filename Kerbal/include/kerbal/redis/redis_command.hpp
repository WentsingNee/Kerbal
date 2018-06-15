/*
 * redis_command.hpp
 *
 *  Source from: 2018年4月18日建立的 auto_redis.hpp, auto_redis.cpp 文件
 *  Created on: 2018年5月29日
 *      Author: peter
 */

#ifndef SRC_REDIS_REDIS_COMMAND_HPP_
#define SRC_REDIS_REDIS_COMMAND_HPP_

#include <string>
#include <kerbal/redis/redis_type_traits.hpp>
#include <kerbal/redis/auto_free_reply.hpp>
#include <kerbal/redis/redis_exception.hpp>

#include <boost/format.hpp>

namespace kerbal
{
	namespace redis
	{

		template <typename T>
		const T& redis_excute_profect_match(const T& t)
		{
			return t;
		}

		const char * redis_excute_profect_match(const std::string & t)
		{
			return t.c_str();
		}

		class RedisCommand
		{
			private:
				std::string cmd;

			public:
				RedisCommand() :
						cmd()
				{
				}

				static boost::format & format_va_args(boost::format & templ)
				{
					return templ;
				}

				template <typename Type, typename ...Args>
				static boost::format & format_va_args(boost::format & templ, const Type & value0, Args&& ...args)
				{
					return format_va_args(templ % value0, args...);
				}

#if __cplusplus < 201703L
				template <typename ...Args>
				static std::string format_va_args(const std::string & templ, Args&& ...args)
				{
					boost::format fmt(templ);
					return format_va_args(fmt, args...).str();
				}
#else //C++17 fold expressions
				template <typename ...Args>
				static std::string format_va_args(const std::string & templ, Args&& ...args) {
					return (boost::format(templ) % ... % args ).str();
				}
#endif

				template <typename ...Args>
				RedisCommand(const std::string & command, Args&& ...args) :
						cmd(format_va_args(command, args...))
				{
				}

				template <typename ...Args>
				void resetCommand(const char command[], Args&& ...args)
				{
					cmd = format_va_args(command, args...);
				}

				template <typename ...Args>
				void resetCommand(const std::string & command, Args&& ...args)
				{
					return setCommand(command.c_str(), args...);
				}

			protected:
				constexpr void redis_excute_allow_type_checker()
				{
				}

				template <typename Type, typename ...Args>
				constexpr void redis_excute_allow_type_checker(const Type &, Args&& ... args)
				{
					static_assert(is_redis_excute_allow_type<Type>::value, "RedisCommand.excute doesn't allow args type");
					redis_excute_allow_type_checker(args...);
				}

			public:
				template <typename ...Args>
				AutoFreeReply excute(const Context & conn, Args && ...args)
				{
					redis_excute_allow_type_checker(args...);

					using namespace std;

					AutoFreeReply reply = (redisReply *) redisCommand(conn.get(), cmd.c_str(), redis_excute_profect_match(args)...);
					if (reply->type == (int) RedisReplyType::ERROR) {
						throw RedisCommandExcuteFailedException("redis reply error: "s + reply->str);
					}
					if (reply == nullptr) {
						throw RedisException("redis reply null exception");
					}
					return reply;
				}
		};
	}
}

#endif /* SRC_REDIS_REDIS_COMMAND_HPP_ */
