/*
 * redis_command.hpp
 *
 *  Created on: 2018年5月29日
 *      Author: peter
 */

#ifndef SRC_REDIS_REDIS_COMMAND_HPP_
#define SRC_REDIS_REDIS_COMMAND_HPP_

namespace kerbal
{
	namespace redis
	{
		class RedisCommand
		{
			private:
				std::string cmd;

			public:
				RedisCommand() :
						cmd()
				{
				}

#if __cplusplus >= 201703L
				template <typename ...Args>
				RedisCommand(const std::string command, Args ...args):
					cmd(((boost::format(command) % ... % args ).str()))
				{
				}

				template <typename ...Args>
				void setCommand(const std::string command, Args ...args)
				{
					cmd = ((boost::format(command) % ... % args ).str());
				}
#endif

				AutoFreeReply excute(const Context & conn)
				{
					using namespace std;

					AutoFreeReply reply = (redisReply *) redisCommand(conn.get(), cmd.c_str());
					if (reply->type == (int) Redis_reply_type::ERROR) {
						throw RedisCommandExcuteFailedException("redis reply error : "s + reply->str);
					}
					if (reply == nullptr) {
						throw RedisException("redis reply null exception");
					}
					return reply;
				}

				~RedisCommand()
				{
				}


				};
	}
}


#endif /* SRC_REDIS_REDIS_COMMAND_HPP_ */
