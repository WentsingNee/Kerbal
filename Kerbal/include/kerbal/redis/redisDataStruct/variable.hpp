/*
 * variable.hpp
 *
 *  Created on: 2018年6月1日
 *      Author: peter
 */

#ifndef SRC_REDIS_REDISDATASTRUCT_VARIABLE_HPP_
#define SRC_REDIS_REDISDATASTRUCT_VARIABLE_HPP_

#include <iostream>
#include <type_traits>

namespace kerbal
{
	namespace redis
	{

		template <typename Type>
		class Variable_base
		{
			protected:
				const Context * pToContext = nullptr;
				std::string key;

			public:
				Variable_base(const Context & conn, const std::string & key) :
						pToContext(&conn), key(key)
				{
				}

				bool exists() const
				{
					RedisCommand command("exists %s", key);
					return command.excute(*pToContext)->integer;
				}

				operator Type() const
				{
					RedisCommand command("get %s", key);
					AutoFreeReply reply = command.excute(*pToContext);
					switch (reply.replyType()) {
						case Redis_reply_type::STRING: {
							std::stringstream ss;
							Type res;
							ss << reply->str;
							ss >> res;
							return res;
						}
						case Redis_reply_type::NIL:
							throw RedisNilException(key);
						default:
							throw RedisUnexceptedCaseException();
					}
				}

				Variable_base& operator=(const Type & src)
				{
					RedisCommand command("set %s %s", key, src);
					command.excute(*pToContext);
					return *this;
				}

				friend std::istream& operator>>(std::istream& in, Variable_base & src)
				{
					Type buff;
					in >> buff;
					src = buff;
					return in;
				}

				friend std::ostream& operator<<(std::ostream& out, const Variable_base & src)
				{
					return out << (Type) src;
				}
		};

		template <typename Type>
		class Increase_decrease_base: public Variable_base<Type>
		{
			public:
				Increase_decrease_base(const Context & conn, const std::string & key) :
						Variable_base<Type>(conn, key)
				{
				}

				Increase_decrease_base& operator++()
				{
					RedisCommand command("incr %s", this->key);
					AutoFreeReply reply = command.excute(*this->pToContext);
					switch (reply.replyType()) {
						case Redis_reply_type::INTEGER:
							return *this;
						case Redis_reply_type::NIL:
							throw RedisNilException(this->key);
						default:
							throw RedisUnexceptedCaseException();
					}
				}

				const Type operator++(int)
				{
					Type tmp = *this;
					RedisCommand command("incr %s", this->key);
					AutoFreeReply reply = command.excute(*this->pToContext);
					switch (reply.replyType()) {
						case Redis_reply_type::INTEGER:
							return tmp;
						case Redis_reply_type::NIL:
							throw RedisNilException(this->key);
						default:
							throw RedisUnexceptedCaseException();
					}
				}

				Increase_decrease_base& operator--()
				{
					RedisCommand command("decr %s", this->key);
					AutoFreeReply reply = command.excute(*this->pToContext);
					switch (reply.replyType()) {
						case Redis_reply_type::INTEGER:
							return *this;
						case Redis_reply_type::NIL:
							throw RedisNilException(this->key);
						default:
							throw RedisUnexceptedCaseException();
					}
				}

				const Type operator--(int)
				{
					Type tmp = *this;
					RedisCommand command("decr %s", this->key);
					AutoFreeReply reply = command.excute(*this->pToContext);
					switch (reply.replyType()) {
						case Redis_reply_type::INTEGER:
							return tmp;
						case Redis_reply_type::NIL:
							throw RedisNilException(this->key);
						default:
							throw RedisUnexceptedCaseException();
					}
				}
		};

		template<typename Type>
		struct Indecreaseable : public
			std::conditional<
				std::__and_<std::is_integral<Type>, std::__not_ <std::is_same<Type, bool> > >::value,
				std::true_type,
				std::false_type>::type
		{
		};

		template <typename Type>
		class Variable:
			public std::conditional<Indecreaseable<Type>::value,
					Increase_decrease_base<Type>,
					Variable_base<Type> >::type
		{
			protected:
				typedef typename std::conditional<Indecreaseable<Type>::value,
						Increase_decrease_base<Type>,
						Variable_base<Type> >::type father_t1;

			public:
				Variable(const Context & conn, const std::string & key) :
					father_t1(conn, key)
				{
				}

				Variable& operator=(const Type & src)
				{
					Variable_base<Type>::operator=(src);
					return *this;
				}
		};

		template<>
		class Variable<std::string>:
				public Variable_base<std::string>
		{
			protected:
				typedef Variable_base<std::string> father_t1;

			public:
				Variable(const Context & conn, const std::string & key) :
						father_t1(conn, key)
				{
				}

				Variable& operator=(const std::string & src)
				{
					Variable_base<std::string>::operator=(src);
					return *this;
				}

				size_t length() const
				{
					return ((std::string) (*this)).length();
				}
		};

	}
}


#endif /* SRC_REDIS_REDISDATASTRUCT_VARIABLE_HPP_ */
