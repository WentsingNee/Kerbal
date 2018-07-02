/*
 * set.hpp
 *
 *  Created on: 2018年6月11日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_REDIS_REDIS_DATA_STRUCT_SET_HPP_
#define INCLUDE_KERBAL_REDIS_REDIS_DATA_STRUCT_SET_HPP_

#include <set>

#include <kerbal/redis/operation.hpp>
#include <kerbal/redis/redis_type_cast.hpp>

namespace kerbal
{
	namespace redis
	{
		template <typename Type>
		class Set
		{
			protected:
				const Context * pToContext = nullptr;
				std::string key;

			public:
				Set(const Context & conn, const std::string & key) :
						pToContext(&conn), key(key)
				{
				}

				operator std::set<Type>()
				{
					static RedisCommand cmd("smembers %%s");
					AutoFreeReply reply = cmd.excute(*pToContext, key);
					switch (reply.replyType()) {
						case RedisReplyType::ARRAY: {
							std::set<Type> set;
							for (size_t i = 0; i < reply->elements; ++i) {
								set.insert(redisTypeCast < Type > (reply->element[i]->str));
							}
							return set;
						}
						default:
							throw RedisUnexceptedCaseException(reply.replyType());
					}
				}

				bool empty() const
				{
					static Operation opt;
					return !opt.exists(*pToContext, key);
				}

				size_t size() const
				{
					static RedisCommand cmd("scard %%s");
					return cmd.excute(*pToContext, key)->integer;
				}

				bool member_exist(const Type & member) const
				{
					static RedisCommand cmd(std::string("sismember %%s %") + placeholder_traits<Type>::value);
					return cmd.excute(*pToContext, key, member)->integer;
				}

			protected:
				template <typename ...Args>
				constexpr static void set_member_args_checker(const Type & value0)
				{
				}

				template <typename ...Args>
				constexpr static void set_member_args_checker(const Type &, Args&& ... args)
				{
					set_member_args_checker(args...);
				}

				template <typename ...Args>
				static std::string make_set_member_placeholder(const Type &, Args&& ... args)
				{
					std::string placeholder_list;
					placeholder_list.reserve(4 + 4 * sizeof...(args));

					for (size_t i = 0; i < 1 + sizeof...(args); ++i) {
						placeholder_list += " %";
						placeholder_list += placeholder_traits<Type>::value;
					}
					return placeholder_list;
				}

			public:
				template <typename ...Args>
				long long insert(const Type & value0, Args&& ... args)
				{
					//notes: never get nil result when excuting sadd
					set_member_args_checker(value0, args...);
					static RedisCommand cmd("sadd %%s" + make_set_member_placeholder(value0, args...));
					return cmd.excute(*pToContext, key, value0, args...)->integer;
				}

				template <typename ...Args>
				long long remove(const Type & value0, Args&& ... args)
				{
					//notes: never get nil result when excuting srem
					set_element_args_checker(value0, args...);
					static RedisCommand cmd("srem %%s" + make_set_member_placeholder(value0, args...));
					return cmd.excute(*pToContext, key, value0, args...)->integer;
				}

				/**
				 * @brief Remove and return a random member from a set
				 */
				Type pop()
				{
					static RedisCommand cmd("spop %%s");
					AutoFreeReply reply = cmd.excute(*pToContext, key);
					switch (reply.replyType()) {
						case RedisReplyType::STRING: {
							return redisTypeCast<Type>(reply->str);
						}
						case RedisReplyType::NIL:
							throw RedisNilException(key);
						default:
							throw RedisUnexceptedCaseException();
					}
				}
		};
	}
}



#endif /* INCLUDE_KERBAL_REDIS_REDIS_DATA_STRUCT_SET_HPP_ */
