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

				friend std::ostream& operator<<(std::ostream & out, ListReference<Type> src)
				{
					return out << (Type) src;
				}
		};

		template<typename Type>
		class ListIterator
		{
			protected:
				const List<Type> * pToList = nullptr;
				size_t index;

			public:
				ListIterator(const List<Type> * pToList, size_t index) :
						pToList(pToList), index(index)
				{
				}

				ListReference<Type> operator*() const
				{
					return ListReference<Type>(pToList, index);
				}

				ListIterator& operator++()
				{
					++index;
					return *this;
				}

				const ListIterator operator++(int)
				{
					ListIterator tmp(*this);
					++index;
					return tmp;
				}

				ListIterator& operator--()
				{
					--index;
					return *this;
				}

				const ListIterator operator--(int)
				{
					ListIterator tmp(*this);
					--index;
					return tmp;
				}

				ListIterator operator+(int delta) const
				{
					return ListIterator(this->pToList, this->index + delta);
				}

				ListIterator operator-(int delta) const
				{
					return ListIterator(this->pToList, this->index - delta);
				}

				bool operator==(const ListIterator & with) const
				{
					return this->pToList == with.pToList && this->index == with.index;
				}

				bool operator!=(const ListIterator & with) const
				{
					return this->pToList != with.pToList || this->index != with.index;
				}

		};

		template <typename Type>
		class List
		{
			protected:
				const Context * pToContext = nullptr;
				std::string key;

				friend class ListReference<Type>;
				friend class ListIterator<Type> ;

			public:
				List(const Context & conn, const std::string & key) :
						pToContext(&conn), key(key)
				{
				}

				operator std::vector<Type>()
				{
					return Operation().lrange<Type>(*pToContext, key, 0, -1);
				}

				std::vector<Type> lrange(int begin, int end)
				{
					return Operation().lrange<Type>(*pToContext, key, begin, end);
				}

				const std::vector<Type> lrange(int begin, int end) const
				{
					return Operation().lrange<Type>(*pToContext, key, begin, end);
				}

				bool empty() const
				{
					RedisCommand command("exists %s", key);
					return !command.excute(*pToContext)->integer;
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
				size_t push_front(const Type & head, Args&& ... args)
				{
					std::initializer_list<const Type *> list = { &args... };
					std::ostringstream ss;
					ss << head;
					for (auto ele : list) {
						ss << ' ' << *ele;
					}
					return push_front(ss.str());
				}

				size_t push_back(const Type & value)
				{
					RedisCommand command("rpush %s %s", key, value);
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
				size_t push_back(const Type & head, Args&& ... args)
				{
					std::initializer_list<const Type *> list = { &args... };
					std::ostringstream ss;
					ss << head;
					for (auto ele : list) {
						ss << ' ' << *ele;
					}
					return push_back(ss.str());
				}

				/**
				 * @brief Prepend a value to a list, only if the list exists
				 * @since 2.2.0
				 * @return The size of the list after insert
				 */
				size_t lpushx(const Type & value)
				{
					RedisCommand command("lpushx %s %s", key, value);
					AutoFreeReply reply = command.excute(*pToContext);
					switch (reply.replyType()) {
						case Redis_reply_type::INTEGER: {
							return reply->integer;
						}
						default:
							throw RedisUnexceptedCaseException();
					}
				}

				size_t rpushx(const Type & value)
				{
					RedisCommand command("rpushx %s %s", key, value);
					AutoFreeReply reply = command.excute(*pToContext);
					switch (reply.replyType()) {
						case Redis_reply_type::INTEGER: {
							return reply->integer;
						}
						default:
							throw RedisUnexceptedCaseException();
					}
				}

				Type lpop()
				{
					RedisCommand command("lpop %s", key);
					AutoFreeReply reply = command.excute(*pToContext);
					switch (reply.replyType()) {
						case Redis_reply_type::STRING: {
							return reply->str;
						}
						case Redis_reply_type::NIL:
							throw RedisNilException(key);
						default:
							throw RedisUnexceptedCaseException();
					}
				}

				const Type operator[](size_t index) const
				{
					return ListReference<Type>(this, index);
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
					RedisCommand command("del %s", key);
					AutoFreeReply reply = command.excute(*pToContext);
					switch (reply.replyType()) {
						case Redis_reply_type::INTEGER:
							return reply->integer;
						default:
							throw RedisUnexceptedCaseException();
					}
				}

				size_t remove(const Type & value)
				{
					RedisCommand command("lrem %s 0 %s", key, value);
					AutoFreeReply reply = command.excute(*pToContext);
					switch (reply.replyType()) {
						case Redis_reply_type::INTEGER:
							return reply->integer;
						default:
							throw RedisUnexceptedCaseException();
					}
				}

				size_t remove(const Type & value, int count)
				{
					RedisCommand command("lrem %s %d %s", key, count, value);
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
