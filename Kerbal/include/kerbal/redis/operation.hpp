/*
 * option.hpp
 *
 *  Created on: 2018年5月29日
 *      Author: peter
 */

#ifndef SRC_REDIS_OPERATION_HPP_
#define SRC_REDIS_OPERATION_HPP_

#include <vector>
#include <unordered_map>
#include <map>

#include <kerbal/redis/redis_type_traits.hpp>

namespace kerbal
{
	namespace redis
	{
		namespace optional_ns = std;

		class Operation
		{
			protected:
				template <typename Type>
				static void make_excute_args_template(std::ostringstream & templ, const char key0[], const Type & value0)
				{
					templ << " %%s %" << placeholder_traits<Type>::value;
				}

				template <typename Type>
				static void make_excute_args_template(std::ostringstream & templ, const std::string & key0, const Type & value0)
				{
					make_excute_args_template(templ, key0.c_str(), value0);
				}

				template <typename Type, typename ... Args>
				static void make_excute_args_template(std::ostringstream & templ, const char key0[], const Type & value0, Args&& ... args)
				{
					templ << " %%s %" << placeholder_traits<Type>::value;
					make_excute_args_template(templ, args...);
				}

				template <typename Type, typename ... Args>
				static void make_excute_args_template(std::ostringstream & templ, const std::string & key0, const Type & value0, Args&& ... args)
				{
					make_excute_args_template(templ, key0.c_str(), value0, args...);
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
				static void redis_key_list_type_checker(const Type &)
				{
					static_assert(is_redis_key_type<Type>::value, "not allowed key type");
				}

				template <typename Type, typename ... Args>
				static void redis_key_list_type_checker(const Type &, Args&& ... args)
				{
					static_assert(is_redis_key_type<Type>::value, "not allowed key type");
					redis_key_list_type_checker(args...);
				}

			public:
				template <typename ReturnType = std::string>
				ReturnType get(const Context & conn, const char key[]) const;

				template <typename ReturnType = std::string>
				ReturnType get(const Context & conn, const std::string & key) const
				{
					return get<ReturnType>(conn, key.c_str());
				}


				template <typename ValueType>
				std::string set(const Context & conn, const char key[], const ValueType & value)
				{
					using namespace std;
					static RedisCommand cmd("set %%s %"s + placeholder_traits<ValueType>::value);
					AutoFreeReply reply = cmd.excute(conn, key, value);
					switch (reply.replyType()) {
						case RedisReplyType::STATUS:
							return reply->str;
						default:
							throw RedisUnexceptedCaseException();
					}
				}

				template <typename ValueType>
				std::string set(const Context & conn, const std::string & key, const ValueType & value)
				{
					return set(conn, key.c_str(), value);
				}

				template <typename ValueType>
				std::string set(const Context & conn, const std::pair<std::string, ValueType> & key_value)
				{
					return set(conn, key_value.first.c_str(), key_value.second);
				}

				bool del(const Context & conn, const char key[])
				{
					static RedisCommand cmd("del %%s");
					AutoFreeReply reply = cmd.excute(conn, key);
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER:
							return reply->integer;
						default:
							throw RedisUnexceptedCaseException();
					}
				}

				bool del(const Context & conn, const std::string & key)
				{
					return del(conn, key.c_str());
				}

				template <typename ... Args>
				long long del(const Context & conn, const char key0[], Args&& ... args)
				{
					redis_key_list_type_checker(key0, args...);
					static RedisCommand cmd("del %%s" + make_key_args_template(sizeof...(args)));
					AutoFreeReply reply = cmd.excute(conn, key0, args...);
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER:
							return reply->integer;
						default:
							throw RedisUnexceptedCaseException();
					}
				}

				template <typename ... Args>
				long long del(const Context & conn, const std::string & key0, Args&& ... args)
				{
					return del(conn, key0.c_str(), args...);
				}

				bool exists(const Context & conn, const char key[]) const
				{
					static RedisCommand cmd("exists %%s");
					AutoFreeReply reply = cmd.excute(conn, key);
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER:
							return reply->integer;
						default:
							throw RedisUnexceptedCaseException();
					}
				}

				bool exists(const Context & conn, const std::string & key) const
				{
					return exists(conn, key.c_str());
				}

				template <typename ... Args>
				long long exists(const Context & conn, const char key0[], Args&& ... args) const
				{
					redis_key_list_type_checker(key0, args...);
					static RedisCommand cmd("exists %%s" + make_key_args_template(sizeof...(args)));
					AutoFreeReply reply = cmd.excute(conn, key0, args...);
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER:
							return reply->integer;
						default:
							throw RedisUnexceptedCaseException();
					}
				}

				template <typename ... Args>
				long long exists(const Context & conn, const std::string & key0, Args&& ... args) const
				{
					return exists(conn, key0.c_str(), args...);
				}

				template <typename Type, typename ... Args>
				std::string mset(const Context & conn, const char key0[], const Type & value0, Args&& ... args)
				{
					std::ostringstream templ;
					templ << "mset";
					make_excute_args_template(templ, key0, value0, args...);

					RedisCommand cmd(templ.str());
					AutoFreeReply reply = cmd.excute(conn, key0, value0, args...);
					switch (reply.replyType()) {
						case RedisReplyType::STATUS:
							return reply->str;
						default:
							throw RedisUnexceptedCaseException();
					}
				}

				template <typename Type, typename ... Args>
				std::string mset(const Context & conn, const std::string & key0, const Type & value0, Args&& ... args)
				{
					return mset(conn, key0.c_str(), value0, args...);
				}

//			protected:
//				template <typename Type, typename ... Args>
//				bool mget_excute(const Context & conn, const char templ[], const char key0[], Args&& ... args)
//				{
//					RedisCommand cmd(templ);
//					AutoFreeReply reply = cmd.excute(conn, key0, redis_excute_profect_match(args)...);
//					switch (reply.replyType()) {
//						case RedisReplyType::STATUS:
//							return reply->str;
//						default:
//							throw RedisUnexceptedCaseException();
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
//					return mget_excute(conn, templ.c_str(), key0, value0, args...);
//				}


			public:

				template <typename ... Args>
				std::vector<std::string>
				mget(const Context & conn, const char key0[], Args&& ... args) const
				{
					redis_key_list_type_checker(key0, args...);

					static RedisCommand cmd("mget %%s" + make_key_args_template(sizeof...(args)));
					AutoFreeReply reply = cmd.excute(conn, key0, args...);
					switch (reply.replyType()) {
						case RedisReplyType::ARRAY: {
							std::vector < std::string > res;
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
										throw RedisUnexceptedCaseException();
								}
							}
							return res;
						}
						default:
							throw RedisUnexceptedCaseException();
					}
				}

				template <typename ... Args>
				std::vector<std::string>
				mget(const Context & conn, const std::string & key0, Args&& ... args) const
				{
					return mget(conn, key0.c_str(), args...);
				}

				template <typename ReturnType>
				ReturnType hget(const Context & conn, const char key[], const char field[]) const
				{
					using namespace std;

					static RedisCommand cmd("hget %%s %%s");
					AutoFreeReply reply = cmd.excute(conn, key, field);
					switch (reply.replyType()) {
						case RedisReplyType::STRING:
							return redisTypeCast<ReturnType>(reply->str);
						case RedisReplyType::NIL:
							throw RedisNilException(key + " : "s + field);
						default:
							throw RedisUnexceptedCaseException();
					}
				}

				template <typename ReturnType>
				ReturnType hget(const Context & conn, const char key[], const std::string & field) const
				{
					return hget<ReturnType>(conn, key, field.c_str());
				}

				template <typename ReturnType>
				ReturnType hget(const Context & conn, const std::string & key, const char field[]) const
				{
					return hget<ReturnType>(conn, key.c_str(), field);
				}

				template <typename ReturnType>
				ReturnType hget(const Context & conn, const std::string & key, const std::string & field) const
				{
					return hget<ReturnType>(conn, key.c_str(), field.c_str());
				}

				template <typename ValueType>
				std::string hset(const Context & conn, const char key[], const char field[], const ValueType & value)
				{
					using namespace std;

					static RedisCommand cmd("hset %%s %%s %"s + placeholder_traits<ValueType>::value);
					AutoFreeReply reply = cmd.excute(conn, key, field, value);
					switch (reply.replyType()) {
						case RedisReplyType::STATUS:
							return reply->str;
						default:
							throw RedisUnexceptedCaseException();
					}
				}

				template <typename ValueType>
				std::string hset(const Context & conn, const std::string & key, const char field[], const ValueType & value)
				{
					return hset(conn, key.c_str(), field, value);
				}

				template <typename ValueType>
				std::string hset(const Context & conn, const char key[], const std::string & field, const ValueType & value)
				{
					return hset(conn, key, field.c_str(), value);
				}

				template <typename ValueType>
				std::string hset(const Context & conn, const std::string & key, const std::string & field, const ValueType & value)
				{
					return hset(conn, key.c_str(), field.c_str(), value);
				}


				template <typename Type, typename ... Args>
				std::string hmset(const Context & conn, const char key[], const char field0[], const Type & value0, Args&& ... args)
				{
					std::ostringstream templ;
					templ << "hmset %%s";
					make_excute_args_template(templ, field0, value0, args...);

					RedisCommand cmd(templ.str());
					AutoFreeReply reply = cmd.excute(conn, key, field0, value0, args...);
					switch (reply.replyType()) {
						case RedisReplyType::STATUS:
							return reply->str;
						default:
							throw RedisUnexceptedCaseException();
					}
				}

				template <typename Type, typename ... Args>
				std::string hmset(const Context & conn, const std::string & key, const char field0[], const Type & value0, Args&& ... args)
				{
					return hmset(conn, key.c_str(), field0, value0, args...);
				}

				template <typename Type, typename ... Args>
				std::string hmset(const Context & conn, const char key[], const std::string & field0, const Type & value0, Args&& ... args)
				{
					return hmset(conn, key, field0.c_str(), value0, args...);
				}

				template <typename Type, typename ... Args>
				std::string hmset(const Context & conn, const std::string & key, const std::string & field0, const Type & value0, Args&& ... args)
				{
					return hmset(conn, key.c_str(), field0.c_str(), value0, args...);
				}

				std::unordered_map<std::string, std::string>
				hgetall(const Context & conn, const char key[]) const
				{
					static RedisCommand cmd("hgetall %%s");
					AutoFreeReply reply = cmd.excute(conn, key);
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
							throw RedisUnexceptedCaseException();
					}
				}

				std::unordered_map<std::string, std::string>
				hgetall(const Context & conn, const std::string & key) const
				{
					return hgetall(conn, key.c_str());
				}

				template<typename Type = std::string>
				std::vector<Type>
				lrange(const Context & conn, const char key[], int start, int end = -1) const
				{
					RedisCommand cmd("lrange %%s %%d %%d");
					AutoFreeReply reply = cmd.excute(conn, key, start, end);
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
							throw RedisUnexceptedCaseException();
					}
				}

				template<typename Type = std::string>
				std::vector<Type>
				lrange(const Context & conn, const std::string & key, int start, int end = -1) const
				{
					return lrange<Type>(conn, key.c_str(), start, end);
				}

		};

		template <>
		inline std::string
		Operation::get<std::string>(const Context & conn, const char key[]) const
		{
			static RedisCommand cmd("get %%s");
			AutoFreeReply reply = cmd.excute(conn, key);
			switch (reply.replyType()) {
				case RedisReplyType::STRING:
					return std::string(reply->str);
				case RedisReplyType::NIL:
					throw RedisNilException(key);
				default:
					throw RedisUnexceptedCaseException();
			}
		}

		template <typename ValueType>
		ValueType Operation::get(const Context & conn, const char key[]) const
		{
			return redisTypeCast<ValueType>(get<std::string>(conn, key));
		}

	}
}

#endif /* SRC_REDIS_OPERATION_HPP_ */
