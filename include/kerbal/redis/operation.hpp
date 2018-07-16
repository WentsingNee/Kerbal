/*
 * option.hpp
 *
 *  Created on: 2018年5月29日
 *      Author: peter
 */

#ifndef INCLUDE_REDIS_OPERATION_HPP_
#define INCLUDE_REDIS_OPERATION_HPP_

#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <unordered_map>
#include <map>
#include <chrono>

#include <kerbal/redis/auto_free_reply.hpp>
#include <kerbal/redis/redis_command.hpp>
#include <kerbal/redis/redis_context.hpp>
#include <kerbal/redis/redis_type_traits.hpp>
#include <kerbal/redis/redis_type_cast.hpp>
#include <kerbal/redis/united_string_helper.hpp>

namespace kerbal
{
	namespace redis
	{
		namespace optional_ns = std;

		class Operation
		{
			protected:
				template <typename Type>
				static void make_execute_args_template(std::ostringstream & templ, const RedisUnitedStringHelper &, const Type &)
				{
					templ << " %%s %" << redis_type_traits<Type>::placeholder;
				}

				template <typename Type, typename ... Args>
				static void make_execute_args_template(std::ostringstream & templ, const RedisUnitedStringHelper &, const Type &, Args&& ... args)
				{
					templ << " %%s %" << redis_type_traits<Type>::placeholder;
					make_execute_args_template(templ, args...);
				}

				template <typename Type, typename ... Args>
				static std::string make_execute_args_template(const RedisUnitedStringHelper & key0, const Type & value0, Args&& ... args)
				{
					std::ostringstream templ;
					make_execute_args_template(templ, key0, value0, args...);
					return templ.str();
				}

				static std::string make_key_args_template(size_t args_size)
				{
					std::string templ;
					templ.reserve(4 * args_size);
					for (size_t i = 0; i < args_size; ++i) {
						templ += " %%s";
					}
					return templ;
				}

				template <typename Type>
				constexpr static void redis_key_list_type_checker(const Type &)
				{
					static_assert(redis_type_traits<Type>::is_key_type, "not allowed key type");
				}

				template <typename Type, typename ... Args>
				constexpr static void redis_key_list_type_checker(const Type &, Args&& ... args)
				{
					static_assert(redis_type_traits<Type>::is_key_type, "not allowed key type");
					redis_key_list_type_checker(args...);
				}


			public:
				template<typename ReturnType = std::list<std::string> >
				ReturnType keys(const Context & conn, RedisUnitedStringHelper key) const
				{
					static RedisCommand cmd("keys %%s");
					AutoFreeReply reply = cmd.execute(conn, key);
					switch (reply.replyType()) {
						case RedisReplyType::ARRAY: {
							ReturnType res;
							for (size_t i = 0; i < reply->elements; ++i) {
								switch ((RedisReplyType) (reply->element[i]->type)) {
									case RedisReplyType::STRING:
										res.push_back(reply->element[i]->str);
										break;
									case RedisReplyType::NIL:
										res.push_back("");
										break;
									default:
										throw RedisUnexpectedCaseException(reply.replyType());
								}
							}
							return res;
						}
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				template <typename ValueType = std::string>
				ValueType get(const Context & conn, RedisUnitedStringHelper key) const
				{
					static RedisCommand cmd("get %%s");
					AutoFreeReply reply = cmd.execute(conn, key);
					switch (reply.replyType()) {
						case RedisReplyType::STRING:
							return redisTypeCast<ValueType>(reply->str);
						case RedisReplyType::NIL:
							throw RedisNilException(key.c_str());
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				template <typename ValueType>
				std::string set(const Context & conn, RedisUnitedStringHelper key, const ValueType & value)
				{
					static RedisCommand cmd(std::string("set %%s %") + redis_type_traits<ValueType>::placeholder);
					AutoFreeReply reply = cmd.execute(conn, key, value);
					switch (reply.replyType()) {
						case RedisReplyType::STATUS:
							return reply->str;
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				template <typename ValueType>
				std::string set(const Context & conn, const std::pair<std::string, ValueType> & key_value)
				{
					return set(conn, key_value.first, key_value.second);
				}

				std::string rename(const Context & conn, RedisUnitedStringHelper key, RedisUnitedStringHelper newKey)
				{
					static RedisCommand cmd("rename %%s %%s");
					AutoFreeReply reply = cmd.execute(conn, key, newKey);
					switch (reply.replyType()) {
						case RedisReplyType::STATUS:
							return reply->str;
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				bool del(const Context & conn, RedisUnitedStringHelper key)
				{
					static RedisCommand cmd("del %%s");
					AutoFreeReply reply = cmd.execute(conn, key);
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER:
							return reply->integer;
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				template <typename ... Args>
				long long del(const Context & conn, RedisUnitedStringHelper key0, Args&& ... args)
				{
					redis_key_list_type_checker(key0, args...);
					static RedisCommand cmd("del %%s" + make_key_args_template(sizeof...(args)));
					AutoFreeReply reply = cmd.execute(conn, key0, args...);
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER:
							return reply->integer;
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				bool exists(const Context & conn, RedisUnitedStringHelper key) const
				{
					static RedisCommand cmd("exists %%s");
					AutoFreeReply reply = cmd.execute(conn, key);
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER:
							return reply->integer;
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				template <typename ... Args>
				long long exists(const Context & conn, RedisUnitedStringHelper key0, Args&& ... args) const
				{
					redis_key_list_type_checker(key0, args...);
					static RedisCommand cmd("exists %%s" + make_key_args_template(sizeof...(args)));
					AutoFreeReply reply = cmd.execute(conn, key0, args...);
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER:
							return reply->integer;
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				long long pexpire(const Context & conn, RedisUnitedStringHelper key, const std::chrono::milliseconds & ms)
				{
					static RedisCommand cmd("pexpire %%s %%lld");
					AutoFreeReply reply = cmd.execute(conn, key, ms.count());
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER:
							return reply->integer;
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				long long expire(const Context & conn, RedisUnitedStringHelper key, const std::chrono::seconds & sec)
				{
					static RedisCommand cmd("expire %%s %%lld");
					AutoFreeReply reply = cmd.execute(conn, key, sec.count());
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER:
							return reply->integer;
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				long long persist(const Context & conn, RedisUnitedStringHelper key)
				{
					static RedisCommand cmd("persist %%s");
					AutoFreeReply reply = cmd.execute(conn, key);
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER:
							return reply->integer;
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				std::chrono::milliseconds pttl(const Context & conn, RedisUnitedStringHelper key) const
				{
					static RedisCommand cmd("pttl %%s");
					AutoFreeReply reply = cmd.execute(conn, key);
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER:
							return std::chrono::milliseconds(reply->integer);
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				std::chrono::seconds ttl(const Context & conn, RedisUnitedStringHelper key) const
				{
					static RedisCommand cmd("ttl %%s");
					AutoFreeReply reply = cmd.execute(conn, key);
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER:
							return std::chrono::seconds(reply->integer);
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				template <typename Type, typename ... Args>
				std::string mset(const Context & conn, RedisUnitedStringHelper key0, const Type & value0, Args&& ... args)
				{
					static RedisCommand cmd("mset" + make_execute_args_template(key0, value0, args...));
					AutoFreeReply reply = cmd.execute(conn, key0, value0, args...);
					switch (reply.replyType()) {
						case RedisReplyType::STATUS:
							return reply->str;
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

//			protected:
//				template <typename Type, typename ... Args>
//				bool mget_execute(const Context & conn, const char templ[], const char key0[], Args&& ... args)
//				{
//					RedisCommand cmd(templ);
//					AutoFreeReply reply = cmd.execute(conn, key0, redis_execute_profect_match(args)...);
//					switch (reply.replyType()) {
//						case RedisReplyType::STATUS:
//							return reply->str;
//						default:
//							throw RedisUnexpectedCaseException();
//					}
//				}
//
//			public:
//
//				template <typename Type, typename ... Args>
//				std::tuple<Type, Args...> mget(const Context & conn, const char key0[], Args&& ... args)
//				{
//					std::string templ = "mget %%s";
//					for (size_t i = 0; i < sizeof...(args); ++i) {
//						templ += " %%s";
//					}
//					return mget_execute(conn, templ.c_str(), key0, value0, args...);
//				}


			public:

				template <typename ... Args>
				std::vector<std::string>
				mget(const Context & conn, RedisUnitedStringHelper key0, Args&& ... args) const
				{
					redis_key_list_type_checker(key0, args...);

					static RedisCommand cmd("mget %%s" + make_key_args_template(sizeof...(args)));
					AutoFreeReply reply = cmd.execute(conn, key0, args...);
					switch (reply.replyType()) {
						case RedisReplyType::ARRAY: {
							std::vector<std::string> res;
							res.reserve(reply->elements);
							for (size_t i = 0; i < reply->elements; ++i) {
								switch ((RedisReplyType)(reply->element[i]->type)) {
									case RedisReplyType::STRING:
										res.push_back(reply->element[i]->str);
										break;
									case RedisReplyType::NIL:
										res.push_back("");
										break;
									default:
										throw RedisUnexpectedCaseException(reply.replyType());
								}
							}
							return res;
						}
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				template <typename ReturnType = std::string>
				ReturnType hget(const Context & conn, RedisUnitedStringHelper key, RedisUnitedStringHelper field) const
				{
					static RedisCommand cmd("hget %%s %%s");
					AutoFreeReply reply = cmd.execute(conn, key, field);
					switch (reply.replyType()) {
						case RedisReplyType::STRING:
							return redisTypeCast<ReturnType>(reply->str);
						case RedisReplyType::NIL:
							throw RedisNilException(key + " : " + field);
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				template <typename ValueType>
				int hset(const Context & conn, RedisUnitedStringHelper key, RedisUnitedStringHelper field, const ValueType & value)
				{
					static RedisCommand cmd(std::string("hset %%s %%s %") + redis_type_traits<ValueType>::placeholder);
					AutoFreeReply reply = cmd.execute(conn, key, field, value);
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER:
							return reply->integer;
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				template <typename Type, typename ... Args>
				std::string hmset(const Context & conn, RedisUnitedStringHelper key, RedisUnitedStringHelper field0, const Type & value0, Args&& ... args)
				{
					static RedisCommand cmd("hmset %%s" + make_execute_args_template(field0, value0, args...));
					AutoFreeReply reply = cmd.execute(conn, key, field0, value0, args...);
					switch (reply.replyType()) {
						case RedisReplyType::STATUS:
							return reply->str;
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				std::unordered_map<std::string, std::string>
				hgetall(const Context & conn, RedisUnitedStringHelper key) const
				{
					static RedisCommand cmd("hgetall %%s");
					AutoFreeReply reply = cmd.execute(conn, key);
					switch (reply.replyType()) {
						case RedisReplyType::ARRAY: {
							std::unordered_map<std::string, std::string> res;
							res.reserve(reply->elements / 2);
							for (size_t i = 0; i < reply->elements; i += 2) {
								res[reply->element[i]->str] = reply->element[i + 1]->str;
							}
							return res;
						}
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				template<typename Type = std::string>
				std::vector<Type>
				lrange(const Context & conn, RedisUnitedStringHelper key, int start, int end = -1) const
				{
					static RedisCommand cmd("lrange %%s %%d %%d");
					AutoFreeReply reply = cmd.execute(conn, key, start, end);
					switch (reply.replyType()) {
						case RedisReplyType::ARRAY: {
							std::vector<Type> res;
							res.reserve(reply->elements);
							for (size_t i = 0; i < reply->elements; ++i) {
								res.push_back(redisTypeCast<Type>(reply->element[i]->str));
							}
							return res;
						}
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

		};

	}
}

#endif /* INCLUDE_REDIS_OPERATION_HPP_ */
