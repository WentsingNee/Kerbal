/*
 * list.hpp
 *
 *  Created on: 2018年6月1日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_REDIS_REDIS_DATA_STRUCT_LIST_HPP_
#define INCLUDE_KERBAL_REDIS_REDIS_DATA_STRUCT_LIST_HPP_

#include <string>

#include <kerbal/redis/redis_data_struct/list_referene_base.hpp>

namespace kerbal
{
	namespace redis
	{
		/**
		 * @brief
		 * @tparam Type
		 */
		template <typename Type>
		class List
		{
			public:
				typedef Type value_type;
				typedef ListIterator<Type> iterator;

			protected:
				Operation opt;
				std::string key;

				friend class ListConstReferenceBase<Type> ;
				friend class ListReferenceBase<Type>;
				friend class ListIterator<Type>;

			public:
				/**
				 * @brief Establish reference to a list object.
				 * @param conn An accessible redis context
				 * @param key The redis list object's key name
				 */
				List(const RedisContext & conn, const std::string & key) :
						opt(conn), key(key)
				{
				}

				/**
				 * @brief Cast the referenced list object to an instance of std::vector.
				 */
				operator std::vector<Type>()
				{
					return opt.lrange<Type>(key, 0, -1);
				}

				/**
				 * @brief Fetch the elements in range [begin, end) of the referenced list object.
				 * @param begin The start index
				 * @param end The end index + 1
				 * @return An instance of std::vector contains elements in range [begin, end)
				 */
				std::vector<Type> lrange(int begin, int end)
				{
					return opt.lrange<Type>(key, begin, end);
				}

				/**
				 * @brief Fetch the elements in range [begin, end) of the referenced list object.
				 * @param begin The start index
				 * @param end The end index + 1
				 * @return An constant instance of std::vector contains elements in range [begin, end)
				 */
				const std::vector<Type> lrange(int begin, int end) const
				{
					return opt.lrange<Type>(key, begin, end);
				}

				/**
				 * @brief Test whether the referenced list object is empty.
				 * @return True if empty, false if not empty
				 */
				bool empty() const
				{
					return !opt.exists(key);
				}

				/**
				 * @brief Count how many elements in the referenced list object.
				 * @return Elements number in the referenced list object
				 */
				size_t size() const
				{
					//llen 命令执行结果仅会返回 error 或 integer (error 情形已由 execute 方法处理)
					static RedisCommand cmd("llen %s");
					return cmd.execute(opt.getContext(), key)->integer;
				}

			protected:
				template <typename ...Args>
				constexpr static void list_member_args_checker(const Type & value0)
				{
				}

				template <typename ...Args>
				constexpr static void list_member_args_checker(const Type &, Args&& ... args)
				{
					list_member_args_checker(args...);
				}

				template <typename ...Args>
				static std::string make_list_member_placeholder(const Type &, Args&& ... args)
				{
					std::string placeholder_list;
					placeholder_list.reserve(3 + 3 * sizeof...(args));

					for (size_t i = 0; i < 1 + sizeof...(args); ++i) {
						placeholder_list += " ";
						placeholder_list += redis_type_traits<Type>::placeholder;
					}
					return placeholder_list;
				}

			public:
				template <typename ...Args>
				size_t push_front(const Type & value0, Args&& ... args)
				{
					list_member_args_checker(value0, args...);
					static RedisCommand cmd("lpush %s" + make_list_member_placeholder(value0, args...));
					RedisReply reply = cmd.execute(opt.getContext(), key, value0, args...);
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER: {
							return reply->integer;
						}
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				template <typename ...Args>
				size_t push_back(const Type & value0, Args&& ... args)
				{
					list_member_args_checker(value0, args...);
					static RedisCommand cmd("rpush %s" + make_list_member_placeholder(value0, args...));
					RedisReply reply = cmd.execute(opt.getContext(), key, value0, args...);
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER: {
							return reply->integer;
						}
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				/**
				 * @brief Prepend a value to a list, only if the referenced list object exists.
				 * @param value The value to be prepended
				 * @return The size of the referenced list object after insert
				 */
				size_t push_front_x(const Type & value)
				{
					static RedisCommand cmd(std::string("lpushx %s ") + redis_type_traits<Type>::placeholder);
					RedisReply reply = cmd.execute(opt.getContext(), key, value);
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER: {
							return reply->integer;
						}
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				size_t push_back_x(const Type & value)
				{
					static RedisCommand cmd(std::string("rpushx %s ") + redis_type_traits<Type>::placeholder);
					RedisReply reply = cmd.execute(opt.getContext(), key, value);
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER: {
							return reply->integer;
						}
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				Type pop_front()
				{
					static RedisCommand cmd("lpop %s");
					RedisReply reply = cmd.execute(opt.getContext(), key);
					switch (reply.replyType()) {
						case RedisReplyType::STRING: {
							return redisTypeCast<Type>(reply->str);
						}
						case RedisReplyType::NIL:
							throw RedisNilException(key);
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				Type block_pop_front(const std::chrono::seconds & sec)
				{
					static RedisCommand cmd("blpop %s %d");
					RedisReply reply = cmd.execute(opt.getContext(), key, sec.count());
					switch (reply.replyType()) {
						case RedisReplyType::ARRAY: {
							return redisTypeCast<Type>(reply->element[1]->str);
						}
						case RedisReplyType::NIL:
							throw RedisNilException(key);
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				Type pop_back()
				{
					static RedisCommand cmd("rpop %s");
					RedisReply reply = cmd.execute(opt.getContext(), key);
					switch (reply.replyType()) {
						case RedisReplyType::STRING: {
							return redisTypeCast<Type>(reply->str);
						}
						case RedisReplyType::NIL:
							throw RedisNilException(key);
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				Type block_pop_back(const std::chrono::seconds & sec)
				{
					static RedisCommand cmd("brpop %s %d");
					RedisReply reply = cmd.execute(opt.getContext(), key, sec.count());
					switch (reply.replyType()) {
						case RedisReplyType::ARRAY: {
							return redisTypeCast<Type>(reply->element[1]->str);
						}
						case RedisReplyType::NIL:
							throw RedisNilException(key);
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				ListConstReference<Type> operator[](size_t index) const
				{
					return ListConstReference<Type>(this, index);
				}

				ListReference<Type> operator[](size_t index)
				{
					return ListReference<Type>(this, index);
				}

				ListIterator<Type> begin()
				{
					return ListIterator<Type>(this, 0);
				}

				ListIterator<Type> end()
				{
					return ListIterator<Type>(this, this->size());
				}

				bool clear()
				{
					return opt.del(key);
				}

				size_t remove(const Type & value, int count = 0)
				{
					static RedisCommand cmd(std::string("lrem %s %d ") + redis_type_traits<Type>::placeholder);
					RedisReply reply = cmd.execute(opt.getContext(), key, count, value);
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER:
							return reply->integer;
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}
		};
	}
}

#endif /* INCLUDE_KERBAL_REDIS_REDIS_DATA_STRUCT_LIST_HPP_ */
