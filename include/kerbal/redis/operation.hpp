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
#include <tuple>

#include <kerbal/redis/redis_command.hpp>
#include <kerbal/redis/redis_context.hpp>
#include <kerbal/redis/redis_reply.hpp>
#include <kerbal/redis/redis_type_traits.hpp>
#include <kerbal/redis/redis_type_cast.hpp>
#include <kerbal/redis/united_string_helper.hpp>

namespace kerbal
{
	namespace redis
	{
		namespace optional_ns = std;

		template <int i>
		class mget_helper;

		template <>
		class mget_helper<0>
		{
				friend class Operation;

				friend class mget_helper<1> ;

				template <typename ...Types>
				mget_helper(std::tuple<Types...> & res, const RedisReply & reply)
				{
					switch ((RedisReplyType) (reply->element[0]->type)) {
						case RedisReplyType::STRING:
							typedef typename std::remove_reference<decltype(std::get<0>(res))>::type ele_type;
							std::get<0>(res) = redisTypeCast<ele_type>(reply->element[0]->str);
							break;
						case RedisReplyType::NIL:
							throw RedisNilException(std::to_string(0));
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}
		};

		template <int i>
		class mget_helper
		{
				friend class Operation;

				friend class mget_helper<i + 1> ;

				template <typename ...Types>
				mget_helper(std::tuple<Types...> & res, const RedisReply & reply)
				{
					switch ((RedisReplyType) (reply->element[i]->type)) {
						case RedisReplyType::STRING:
							typedef typename std::remove_reference<decltype(std::get<i>(res))>::type ele_type;
							std::get<i>(res) = redisTypeCast<ele_type>(reply->element[i]->str);
							break;
						case RedisReplyType::NIL:
							throw RedisNilException(std::to_string(i));
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}

					mget_helper<i - 1>(res, reply);
				}
		};

		class Operation
		{
			protected:
				template <typename Type>
				static void make_execute_args_template(std::ostringstream & templ, const RedisUnitedStringHelper &, const Type &)
				{
					templ << " %s " << redis_type_traits<Type>::placeholder;
				}

				template <typename Type, typename ... Args>
				static void make_execute_args_template(std::ostringstream & templ, const RedisUnitedStringHelper &, const Type &, Args&& ... args)
				{
					templ << " %s " << redis_type_traits<Type>::placeholder;
					make_execute_args_template(templ, std::forward<Args>(args)...);
				}

				template <typename Type, typename ... Args>
				static std::string make_execute_args_template(const RedisUnitedStringHelper & key0, const Type & value0, Args&& ... args)
				{
					std::ostringstream templ;
					make_execute_args_template(templ, key0, value0, std::forward<Args>(args)...);
					return templ.str();
				}

				static std::string make_key_args_template(size_t args_size)
				{
					std::string templ;
					templ.reserve(3 * args_size);
					for (size_t i = 0; i < args_size; ++i) {
						templ += " %s";
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
					redis_key_list_type_checker(std::forward<Args>(args)...);
				}

				RedisContext conn;

			public:

				Operation(const RedisContext & conn) :
						conn(conn)
				{
				}

				RedisContext& getContext()
				{
					return conn;
				}

				const RedisContext& getContext() const
				{
					return conn;
				}

				std::string type(RedisUnitedStringHelper key) const
				{
					static RedisCommand cmd("type %s");
					RedisReply reply = cmd.execute(conn, key);
					switch (reply.replyType()) {
						case RedisReplyType::STRING: {
							return reply->str;
						}
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				template <typename ReturnType = std::list<std::string> >
				ReturnType keys(RedisUnitedStringHelper key) const
				{
					static RedisCommand cmd("keys %s");
					RedisReply reply = cmd.execute(conn, key);
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
				ValueType get(RedisUnitedStringHelper key) const
				{
					static RedisCommand cmd("get %s");
					RedisReply reply = cmd.execute(conn, key);
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
				std::string set(RedisUnitedStringHelper key, const ValueType & value)
				{
					static RedisCommand cmd(std::string("set %s ") + redis_type_traits<ValueType>::placeholder);
					RedisReply reply = cmd.execute(conn, key, value);
					switch (reply.replyType()) {
						case RedisReplyType::STATUS:
							return reply->str;
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				template <typename ValueType>
				std::string set(const std::pair<std::string, ValueType> & key_value)
				{
					return set(conn, key_value.first, key_value.second);
				}

				std::string rename(RedisUnitedStringHelper key, RedisUnitedStringHelper newKey)
				{
					static RedisCommand cmd("rename %s %s");
					RedisReply reply = cmd.execute(conn, key, newKey);
					switch (reply.replyType()) {
						case RedisReplyType::STATUS:
							return reply->str;
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				bool del(RedisUnitedStringHelper key)
				{
					static RedisCommand cmd("del %s");
					RedisReply reply = cmd.execute(conn, key);
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER:
							return reply->integer;
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				template <typename ... Args>
				long long del(RedisUnitedStringHelper key0, Args&& ... keys)
				{
					redis_key_list_type_checker(key0, std::forward<Args>(keys)...);
					static RedisCommand cmd("del %s" + make_key_args_template(sizeof...(keys)));
					RedisReply reply = cmd.execute(conn, key0, std::forward<Args>(keys)...);
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER:
							return reply->integer;
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				bool exists(RedisUnitedStringHelper key) const
				{
					static RedisCommand cmd("exists %s");
					RedisReply reply = cmd.execute(conn, key);
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER:
							return reply->integer;
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				/**
				 * @brief Check how many objects exists.
				 * @param key0 the first object's key
				 * @param args the remaining objects' key
				 * @return Existed object number.
				 */
				template <typename ... Args>
				long long exists(RedisUnitedStringHelper key0, Args&& ... keys) const
				{
					redis_key_list_type_checker(key0, std::forward<Args>(keys)...);
					static RedisCommand cmd("exists %s" + make_key_args_template(sizeof...(keys)));
					RedisReply reply = cmd.execute(conn, key0, std::forward<Args>(keys)...);
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER:
							return reply->integer;
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				long long pexpire(RedisUnitedStringHelper key, const std::chrono::milliseconds & ms)
				{
					static RedisCommand cmd("pexpire %s %lld");
					RedisReply reply = cmd.execute(conn, key, ms.count());
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER:
							return reply->integer;
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				long long expire(RedisUnitedStringHelper key, const std::chrono::seconds & sec)
				{
					static RedisCommand cmd("expire %s %lld");
					RedisReply reply = cmd.execute(conn, key, sec.count());
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER:
							return reply->integer;
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				long long persist(RedisUnitedStringHelper key)
				{
					static RedisCommand cmd("persist %s");
					RedisReply reply = cmd.execute(conn, key);
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER:
							return reply->integer;
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				std::chrono::milliseconds pttl(RedisUnitedStringHelper key) const
				{
					static RedisCommand cmd("pttl %s");
					RedisReply reply = cmd.execute(conn, key);
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER:
							return std::chrono::milliseconds(reply->integer);
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				std::chrono::seconds ttl(RedisUnitedStringHelper key) const
				{
					static RedisCommand cmd("ttl %s");
					RedisReply reply = cmd.execute(conn, key);
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER:
							return std::chrono::seconds(reply->integer);
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				template <typename Type, typename ... Args>
				std::string mset(RedisUnitedStringHelper key0, const Type & value0, Args&& ... args)
				{
					static RedisCommand cmd("mset" + make_execute_args_template(key0, value0, std::forward<Args>(args)...));
					RedisReply reply = cmd.execute(conn, key0, value0, std::forward<Args>(args)...);
					switch (reply.replyType()) {
						case RedisReplyType::STATUS:
							return reply->str;
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

			public:

				template <typename ...Types, typename ... Args>
				std::tuple<Types...> mget_tuple(RedisUnitedStringHelper key0, Args&& ... keys)
				{
					static_assert(sizeof...(Types) != sizeof...(Args), "Mismatched arguments number");
					redis_key_list_type_checker(key0, std::forward<Args>(keys)...);

					static RedisCommand cmd("mget %s" + make_key_args_template(sizeof...(keys)));
					RedisReply reply = cmd.execute(conn, key0, std::forward<Args>(keys)...);
					switch (reply.replyType()) {
						case RedisReplyType::ARRAY: {
							std::tuple<Types...> res;
							mget_helper<sizeof...(Types) - 1>(res, reply);
							return res;
						}
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}


				template <typename ... Args>
				std::vector<std::string>
				mget(RedisUnitedStringHelper key0, Args&& ... keys) const
				{
					redis_key_list_type_checker(key0, std::forward<Args>(keys)...);

					static RedisCommand cmd("mget %s" + make_key_args_template(sizeof...(keys)));
					RedisReply reply = cmd.execute(conn, key0, std::forward<Args>(keys)...);
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
				ReturnType hget(RedisUnitedStringHelper key, RedisUnitedStringHelper field) const
				{
					static RedisCommand cmd("hget %s %s");
					RedisReply reply = cmd.execute(conn, key, field);
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
				int hset(RedisUnitedStringHelper key, RedisUnitedStringHelper field, const ValueType & value)
				{
					static RedisCommand cmd(std::string("hset %s %s ") + redis_type_traits<ValueType>::placeholder);
					RedisReply reply = cmd.execute(conn, key, field, value);
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER:
							return reply->integer;
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				template <typename Type, typename ... Args>
				std::string hmset(RedisUnitedStringHelper key, RedisUnitedStringHelper field0, const Type & value0, Args&& ... args)
				{
					static RedisCommand cmd("hmset %s" + make_execute_args_template(field0, value0, std::forward<Args>(args)...));
					RedisReply reply = cmd.execute(conn, key, field0, value0, std::forward<Args>(args)...);
					switch (reply.replyType()) {
						case RedisReplyType::STATUS:
							return reply->str;
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				template <typename ... Args>
				std::vector<std::string>
				hmget(RedisUnitedStringHelper key, RedisUnitedStringHelper field0, Args&& ... field)
				{
					redis_key_list_type_checker(field0, std::forward<Args>(field)...);

					static RedisCommand cmd("hmget %s %s" + make_key_args_template(sizeof...(field)));
					RedisReply reply = cmd.execute(conn, key, field0, std::forward<Args>(field)...);
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

				std::unordered_map<std::string, std::string>
				hgetall(RedisUnitedStringHelper key) const
				{
					static RedisCommand cmd("hgetall %s");
					RedisReply reply = cmd.execute(conn, key);
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
				lrange(RedisUnitedStringHelper key, int start, int end = -1) const
				{
					static RedisCommand cmd("lrange %s %d %d");
					RedisReply reply = cmd.execute(conn, key, start, end);
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
