/*
 * list.hpp
 *
 *  Created on: 2018年6月1日
 *      Author: peter
 */

#ifndef SRC_REDIS_REDISDATASTRUCT_LIST_HPP_
#define SRC_REDIS_REDISDATASTRUCT_LIST_HPP_

#include <kerbal/redis/auto_free_reply.hpp>
#include <kerbal/redis/redis_command.hpp>

namespace kerbal
{
	namespace redis
	{

		template <typename Type>
		class List;

		template <typename Type>
		class ListConstReferenceBase
		{
			protected:
				const List<Type> * pToList = nullptr;
				size_t index;

			public:
				ListConstReferenceBase(const List<Type> * pToList, size_t index) :
						pToList(pToList), index(index)
				{
				}

				bool exists() const
				{
					static RedisCommand cmd("llen %%s");
					size_t len = cmd.excute(*pToList->pToContext, pToList->key)->integer;
					return -len <= index && index < len;
				}

				operator Type()
				{
					using namespace std;

					static RedisCommand cmd("lindex %%s %%d");
					AutoFreeReply reply = cmd.excute(*pToList->pToContext, pToList->key, index);
					switch (reply.replyType()) {
						case RedisReplyType::STRING: {
							return redisTypeCast < Type > (reply->str);
						}
						case RedisReplyType::NIL:
							throw RedisNilException(pToList->key);
						default:
							throw RedisUnexceptedCaseException();
					}
				}

				friend std::ostream& operator<<(std::ostream & out, ListConstReferenceBase<Type> src)
				{
					return out << (Type) src;
				}
		};

		template <typename Type>
		class ListReferenceBase : public ListConstReferenceBase<Type>
		{
			protected:
				typedef ListConstReferenceBase<Type> supper_t;

			public:
				ListReferenceBase(const List<Type> * pToList, size_t index) :
						supper_t(pToList, index)
				{
				}

				ListReferenceBase operator=(const Type & src)
				{
					using namespace std;

					static RedisCommand command("lset %%s %%d %"s + placeholder_traits < Type > ::value);
					AutoFreeReply reply = command.excute(*supper_t::pToList->pToContext, supper_t::pToList->key,
												supper_t::index, src);
					switch (reply.replyType()) {
						case RedisReplyType::STATUS: {
							//TODO failed
							return *this;
						}
						case RedisReplyType::NIL:
							throw RedisNilException(supper_t::pToList->key);
						default:
							throw RedisUnexceptedCaseException();
					}
				}

				friend std::istream& operator>> (std::istream & in, ListReferenceBase<Type> src)
				{
					Type buff;
					in >> buff;
					src = buff;
					return in;
				}
		};

		template<typename Type>
		class ListRealReference: public ListReferenceBase<Type>
		{
			protected:
				typedef ListReferenceBase<Type> supper_t;

			public:
				ListRealReference(const List<Type> * pToList, size_t index) :
						supper_t(pToList, index)
				{
				}

				ListRealReference& operator=(const Type & src)
				{
					supper_t::operator=(src);
					return *this;
				}

				template <typename AnotherType>
				ListRealReference& operator+=(const AnotherType & with)
				{
					return *this = (Type) (*this) + with;
				}

				template <typename AnotherType>
				ListRealReference& operator-=(const AnotherType & with)
				{
					return *this = (Type) (*this) - with;
				}

				template <typename AnotherType>
				ListRealReference& operator*=(const AnotherType & with)
				{
					return *this = (Type) (*this) * with;
				}

				template <typename AnotherType>
				ListRealReference& operator/=(const AnotherType & with)
				{
					return *this = (Type) (*this) / with;
				}
		};

		template<typename Type>
		class ListIntegerReference: public ListRealReference<Type>
		{
			protected:
				typedef ListRealReference<Type> supper_t;

			public:
				ListIntegerReference(const List<Type> * pToList, size_t index) :
						supper_t(pToList, index)
				{
				}

				ListIntegerReference& operator=(const Type & src)
				{
					supper_t::operator=(src);
					return *this;
				}

				ListIntegerReference& operator++()
				{
					supper_t::operator=((Type) (*this) + 1);
					return *this;
				}

				const Type operator++(int)
				{
					Type tmp = *this;
					supper_t::operator=((Type) (*this) + 1);
					return tmp;
				}

				ListIntegerReference& operator--()
				{
					supper_t::operator=((Type) (*this) - 1);
					return *this;
				}

				const Type operator--(int)
				{
					Type tmp = *this;
					supper_t::operator=((Type) (*this) - 1);
					return tmp;
				}

				template <typename AnotherType>
				ListIntegerReference& operator%=(const AnotherType & with)
				{
					return *this = (Type) (*this) % with;
				}
		};

		template <typename Type>
		class ListReference : public
			std::conditional<CheckIsIntegerType<Type>::value, ListIntegerReference<Type>,
			typename std::conditional<CheckIsRealType<Type>::value, ListRealReference<Type>,
																			ListReferenceBase<Type> >::type>::type
		{
			protected:
				typedef typename std::conditional<CheckIsIntegerType<Type>::value, ListIntegerReference<Type>,
								   typename std::conditional<CheckIsRealType<Type>::value, ListRealReference<Type>,
								   	   	   	   	   	   	   	   	   	   	   ListReferenceBase<Type> >::type>::type
						supper_t;
			public:
				ListReference(const List<Type> * pToList, size_t index) :
						supper_t(pToList, index)
				{
				}

				ListReference& operator=(const Type & src)
				{
					supper_t::operator=(src);
					return *this;
				}
		};

		template <typename Type>
		class ListConstReference : public ListConstReferenceBase<Type>
		{
			protected:
				typedef ListConstReferenceBase<Type> supper_t;

			public:
				ListConstReference(const List<Type> * pToList, size_t index) :
						supper_t(pToList, index)
				{
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
		class ConstReferenceBase;

		template <typename Type>
		class List
		{
			public:
				typedef ListIterator<Type> iterator;

			protected:
				const Context * pToContext = nullptr;
				std::string key;

				friend class ListConstReferenceBase<Type> ;
				friend class ListReferenceBase<Type>;
				friend class ListIterator<Type>;

			public:
				List(const Context & conn, const std::string & key) :
						pToContext(&conn), key(key)
				{
				}

				operator std::vector<Type>()
				{
					static Operation opt;
					return opt.lrange < Type > (*pToContext, key, 0, -1);
				}

				std::vector<Type> lrange(int begin, int end)
				{
					static Operation opt;
					return opt.lrange < Type > (*pToContext, key, begin, end);
				}

				const std::vector<Type> lrange(int begin, int end) const
				{
					static Operation opt;
					return opt.lrange < Type > (*pToContext, key, begin, end);
				}

				bool empty() const
				{
					static Operation opt;
					return !opt.exists(*pToContext, key);
				}

				size_t size() const
				{
					//llen 命令执行结果仅会返回 error 或 integer (error 情形已由 excute 方法处理)
					static RedisCommand cmd("llen %%s");
					return cmd.excute(*pToContext, key)->integer;
				}

				size_t push_front(const Type & value)
				{
					using namespace std;
					static RedisCommand cmd("lpush %%s %"s + placeholder_traits < Type > ::value);
					AutoFreeReply reply = cmd.excute(*pToContext, key, value);
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER: {
							return reply->integer;
						}
						case RedisReplyType::NIL:
							throw RedisNilException(key);
						default:
							throw RedisUnexceptedCaseException();
					}
				}

//				template <typename ...Args>
//				size_t push_front(const Type & head, Args&& ... args)
//				{
//					std::initializer_list<const Type *> list = { &args... };
//					std::ostringstream ss;
//					ss << head;
//					for (auto ele : list) {
//						ss << ' ' << *ele;
//					}
//					return push_front(ss.str());
//				}

				size_t push_back(const Type & value)
				{
					using namespace std;
					static RedisCommand cmd("rpush %%s %"s + placeholder_traits < Type > ::value);
					AutoFreeReply reply = cmd.excute(*pToContext, key, value);
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER: {
							return reply->integer;
						}
						case RedisReplyType::NIL:
							throw RedisNilException(key);
						default:
							throw RedisUnexceptedCaseException();
					}
				}

//				template <typename ...Args>
//				size_t push_back(const Type & head, Args&& ... args)
//				{
//					std::initializer_list<const Type *> list = { &args... };
//					std::ostringstream ss;
//					ss << head;
//					for (auto ele : list) {
//						ss << ' ' << *ele;
//					}
//					return push_back(ss.str());
//				}

				/**
				 * @brief Prepend a value to a list, only if the list exists
				 * @since 2.2.0
				 * @return The size of the list after insert
				 */
				size_t lpushx(const Type & value)
				{
					using namespace std;
					static RedisCommand cmd("lpushx %%s %"s + placeholder_traits < Type > ::value);
					AutoFreeReply reply = cmd.excute(*pToContext, key, value);
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER: {
							return reply->integer;
						}
						default:
							throw RedisUnexceptedCaseException();
					}
				}

				size_t rpushx(const Type & value)
				{
					using namespace std;
					static RedisCommand cmd("rpushx %%s %"s + placeholder_traits < Type > ::value);
					AutoFreeReply reply = cmd.excute(*pToContext, key, value);
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER: {
							return reply->integer;
						}
						default:
							throw RedisUnexceptedCaseException();
					}
				}

				Type lpop()
				{
					static RedisCommand cmd("lpop %%s");
					AutoFreeReply reply = cmd.excute(*pToContext, key);
					switch (reply.replyType()) {
						case RedisReplyType::STRING: {
							return redisTypeCast < Type > (reply->str);
						}
						case RedisReplyType::NIL:
							throw RedisNilException(key);
						default:
							throw RedisUnexceptedCaseException();
					}
				}

				Type rpop()
				{
					static RedisCommand cmd("rpop %%s");
					AutoFreeReply reply = cmd.excute(*pToContext, key);
					switch (reply.replyType()) {
						case RedisReplyType::STRING: {
							return redisTypeCast < Type > (reply->str);
						}
						case RedisReplyType::NIL:
							throw RedisNilException(key);
						default:
							throw RedisUnexceptedCaseException();
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
					return Operation().del(*pToContext, key);
				}

				size_t remove(const Type & value)
				{
					using namespace std;
					static RedisCommand cmd("lrem %%s 0 %"s + placeholder_traits < Type > ::value);
					AutoFreeReply reply = cmd.excute(*pToContext, key, value);
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER:
							return reply->integer;
						default:
							throw RedisUnexceptedCaseException();
					}
				}

				size_t remove(const Type & value, int count)
				{
					using namespace std;
					static RedisCommand cmd("lrem %%s %%d %"s + placeholder_traits < Type > ::value);
					AutoFreeReply reply = cmd.excute(*pToContext, key, count, value);
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER:
							return reply->integer;
						default:
							throw RedisUnexceptedCaseException();
					}
				}
		};
	}
}



#endif /* SRC_REDIS_REDISDATASTRUCT_LIST_HPP_ */
