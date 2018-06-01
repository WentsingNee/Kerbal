/*
 * list.hpp
 *
 *  Created on: 2018年6月1日
 *      Author: peter
 */

#ifndef SRC_REDIS_REDISDATASTRUCT_LIST_HPP_
#define SRC_REDIS_REDISDATASTRUCT_LIST_HPP_

namespace kerbal
{
	namespace redis
	{

		template <typename Type>
		class List;

		template <typename Type>
		class ListReference
		{
			protected:
				const List<Type> * pToList = nullptr;
				size_t index;

			public:
				ListReference(const List<Type> * pToList, size_t index) :
						pToList(pToList), index(index)
				{
				}

				operator Type()
				{
					RedisCommand command("lindex %s %s", pToList->key, index);
					AutoFreeReply reply = command.excute(*pToList->pToContext);
					switch (reply.replyType()) {
						case Redis_reply_type::STRING: {
							stringstream ss;
							ss << reply->str;
							Type res;
							ss >> res;
							return res;
						}
						case Redis_reply_type::NIL:
							throw RedisNilException(pToList->key);
						default:
							throw RedisUnexceptedCaseException();
					}
				}

				ListReference operator=(const Type & src)
				{
					RedisCommand command("lset %s %s %s", pToList->key, index, src);
					AutoFreeReply reply = command.excute(*pToList->pToContext);
					switch (reply.replyType()) {
						case Redis_reply_type::STATUS: {
							//TODO failed
							return *this;
						}
						case Redis_reply_type::NIL:
							throw RedisNilException(pToList->key);
						default:
							throw RedisUnexceptedCaseException();
					}
				}

				friend std::istream& operator>> (std::istream & in, ListReference<Type> src)
				{
					Type buff;
					in >> buff;
					src = buff;
					return in;
				}
		};

		template <typename Type>
		class List
		{
			protected:
				const Context * pToContext = nullptr;
				std::string key;

				friend class ListReference<Type>;

			public:
				List(const Context & conn, const std::string & key) :
						pToContext(&conn), key(key)
				{
				}

				operator std::vector<Type>()
				{
					return Operation().lrange<Type>(*pToContext, key, 0, -1);
				}

				size_t size() const
				{
					RedisCommand command("llen %s", key);
					AutoFreeReply reply = command.excute(*pToContext);
					switch (reply.replyType()) {
						case Redis_reply_type::INTEGER: {
							return reply->integer;
						}
						case Redis_reply_type::NIL:
							throw RedisNilException(key);
						default:
							throw RedisUnexceptedCaseException();
					}
				}

				size_t push_front(const Type & value)
				{
					RedisCommand command("lpush %s %s", key, value);
					AutoFreeReply reply = command.excute(*pToContext);
					switch (reply.replyType()) {
						case Redis_reply_type::INTEGER: {
							return reply->integer;
						}
						case Redis_reply_type::NIL:
							throw RedisNilException(key);
						default:
							throw RedisUnexceptedCaseException();
					}
				}

				template <typename ...Args>
				size_t push_front(const Type & value, Args ... args)
				{
					return this->push_front(value) + this->push_front(args...);
				}

				const Type operator[](size_t index) const
				{
					return ListReference<Type>(this, index);
				}

				ListReference<Type> operator[](size_t index)
				{
					return ListReference<Type>(this, index);
				}

				bool clear()
				{
					RedisCommand command("del %s", key);
					AutoFreeReply reply = command.excute(*pToContext);
					switch (reply.replyType()) {
						case Redis_reply_type::INTEGER:
							return reply->integer;
						default:
							throw RedisUnexceptedCaseException();
					}
				}
		};
	}
}



#endif /* SRC_REDIS_REDISDATASTRUCT_LIST_HPP_ */
