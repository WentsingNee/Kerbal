/*
 * reference_base.hpp
 *
 *  Created on: 2018年6月7日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_REDIS_REDIS_DATA_STRUCT_REFERENCE_BASE_HPP_
#define INCLUDE_KERBAL_REDIS_REDIS_DATA_STRUCT_REFERENCE_BASE_HPP_

#include <string>

#include <kerbal/redis/operation.hpp>
#include <kerbal/redis/redis_type_cast.hpp>

namespace kerbal
{
	namespace redis
	{

		template <typename Type>
		class ConstReferenceBase
		{
			protected:
				Operation opt;
				std::string key;

				ConstReferenceBase(const RedisContext & conn, const char key[]) :
						opt(conn), key(key)
				{
				}

				ConstReferenceBase(const RedisContext & conn, const std::string & key) :
						opt(conn), key(key)
				{
				}

			public:
				bool exists() const
				{
					return opt.exists(key);
				}

				operator Type() const
				{
					RedisCommand command("get %s");
					RedisReply reply = command.execute(opt.getContext(), key);
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

				friend std::ostream& operator<<(std::ostream& out, const ConstReferenceBase & src)
				{
					return out << (Type) src;
				}
		};

		template<typename Type>
		class ReferenceBase: public ConstReferenceBase<Type>
		{
			private:
				typedef ConstReferenceBase<Type> supper_t;

			protected:
				ReferenceBase(const RedisContext & conn, const char key[]) :
						supper_t(conn, key)
				{
				}

				ReferenceBase(const RedisContext & conn, const std::string & key) :
						supper_t(conn, key)
				{
				}

				ReferenceBase& operator=(const Type & src)
				{
					static RedisCommand command(std::string("set %s ") + redis_type_traits<Type>::placeholder);
					command.execute(this->opt.getContext(), this->key, src);
					return *this;
				}

			public:
				friend std::istream& operator>>(std::istream& in, ReferenceBase & src)
				{
					Type buff;
					in >> buff;
					src = buff;
					return in;
				}
		};

		class BoolReferenceBase: public ReferenceBase<bool>
		{
			private:
				typedef ReferenceBase<bool> supper_t;

			protected:
				BoolReferenceBase(const RedisContext & conn, const char key[]) :
						supper_t(conn, key)
				{
				}

				BoolReferenceBase(const RedisContext & conn, const std::string & key) :
						supper_t(conn, key)
				{
				}

				BoolReferenceBase& operator=(bool src)
				{
					supper_t::operator =(src);
					return *this;
				}
		};

		template<typename Type>
		class RealReferenceBase: public ReferenceBase<Type>
		{
			private:
				typedef ReferenceBase<Type> supper_t;

			protected:
				RealReferenceBase(const RedisContext & conn, const char key[]) :
						supper_t(conn, key)
				{
				}

				RealReferenceBase(const RedisContext & conn, const std::string & key) :
						supper_t(conn, key)
				{
				}

				RealReferenceBase& operator=(const Type & src)
				{
					supper_t::operator=(src);
					return *this;
				}

			public:
				template <typename AnotherType>
				RealReferenceBase& operator+=(const AnotherType & with)
				{
					RedisCommand command(std::string("incrbyfloat %s ") + redis_type_traits<Type>::placeholder);
					RedisReply reply = command.execute(this->opt.getContext(), this->key, with);
					switch (reply.replyType()) {
						case RedisReplyType::STRING:
							return *this;
						case RedisReplyType::NIL:
							throw RedisNilException(this->key);
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				template <typename AnotherType>
				RealReferenceBase& operator-=(const AnotherType & with)
				{
					RedisCommand command(std::string("decrbyfloat %s ") + redis_type_traits<Type>::placeholder);
					RedisReply reply = command.execute(this->opt.getContext(), this->key, with);
					switch (reply.replyType()) {
						case RedisReplyType::STRING:
							return *this;
						case RedisReplyType::NIL:
							throw RedisNilException(this->key);
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				template <typename AnotherType>
				RealReferenceBase& operator*=(const AnotherType & with)
				{
					return *this = (Type) (*this) * with;
				}

				template <typename AnotherType>
				RealReferenceBase& operator/=(const AnotherType & with)
				{
					return *this = (Type) (*this) / with;
				}
		};

		template<typename Type>
		class IntegerReferenceBase: public RealReferenceBase<Type>
		{
			private:
				typedef RealReferenceBase<Type> supper_t;

			protected:
				IntegerReferenceBase(const RedisContext & conn, const char key[]) :
						supper_t(conn, key)
				{
				}

				IntegerReferenceBase(const RedisContext & conn, const std::string & key) :
						supper_t(conn, key)
				{
				}

				IntegerReferenceBase& operator=(const Type & src)
				{
					supper_t::operator=(src);
					return *this;
				}

			public:
				template <typename AnotherType>
				IntegerReferenceBase& operator+=(const AnotherType & with)
				{
					RedisCommand command(std::string("incrby %s ") + redis_type_traits<Type>::placeholder);
					RedisReply reply = command.execute(this->opt.getContext(), this->key, with);
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER:
							return *this;
						case RedisReplyType::NIL:
							throw RedisNilException(this->key);
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				template <typename AnotherType>
				IntegerReferenceBase& operator-=(const AnotherType & with)
				{
					RedisCommand command(std::string("decrby %s ") + redis_type_traits<Type>::placeholder);
					RedisReply reply = command.execute(this->opt.getContext(), this->key, with);
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER:
							return *this;
						case RedisReplyType::NIL:
							throw RedisNilException(this->key);
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				template <typename AnotherType>
				IntegerReferenceBase& operator%=(const AnotherType & with)
				{
					return *this = (Type) (*this) % with;
				}

				IntegerReferenceBase& operator++()
				{
					RedisCommand command("incr %s");
					RedisReply reply = command.execute(this->opt.getContext(), this->key);
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER:
							return *this;
						case RedisReplyType::NIL:
							throw RedisNilException(this->key);
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				const Type operator++(int)
				{
					Type tmp = *this;
					++(*this);
					return tmp;
				}

				IntegerReferenceBase& operator--()
				{
					RedisCommand command("decr %s");
					RedisReply reply = command.execute(this->opt.getContext(), this->key);
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER:
							return *this;
						case RedisReplyType::NIL:
							throw RedisNilException(this->key);
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				const Type operator--(int)
				{
					Type tmp = *this;
					--(*this);
					return tmp;
				}
		};

		class ConstStringReferenceBase: public ConstReferenceBase<std::string>
		{
			private:
				typedef ConstReferenceBase<std::string> supper_t;

			protected:
				ConstStringReferenceBase(const RedisContext & conn, const char key[]) :
						supper_t(conn, key)
				{
				}

				ConstStringReferenceBase(const RedisContext & conn, const std::string & key) :
						supper_t(conn, key)
				{
				}

			public:
				std::string operator+(const ConstStringReferenceBase & with) const
				{
					return (std::string) (*this) + (std::string) (with);
				}

				size_t length() const
				{
					RedisCommand command("strlen %s");
					RedisReply reply = command.execute(opt.getContext(), this->key);
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER:
							return reply->integer;
						case RedisReplyType::NIL:
							throw RedisNilException(this->key);
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}
		};

		class StringReferenceBase: public ConstStringReferenceBase
		{
			private:
				typedef ConstStringReferenceBase supper_t;

			protected:
				StringReferenceBase(const RedisContext & conn, const char key[]) :
						supper_t(conn, key)
				{
				}

				StringReferenceBase(const RedisContext & conn, const std::string & key) :
						supper_t(conn, key)
				{
				}

				StringReferenceBase& operator=(const char * with)
				{
					RedisCommand command("set %s %s");
					RedisReply reply = command.execute(opt.getContext(), key, with);
					switch (reply.replyType()) {
						case RedisReplyType::STATUS: {
							return *this;
						}
						case RedisReplyType::NIL:
							throw RedisNilException(key);
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				StringReferenceBase& operator=(const std::string & with)
				{
					RedisCommand command("set %s %s");
					RedisReply reply = command.execute(opt.getContext(), key, with);
					switch (reply.replyType()) {
						case RedisReplyType::STATUS: {
							return *this;
						}
						case RedisReplyType::NIL:
							throw RedisNilException(key);
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				StringReferenceBase& operator=(const StringReferenceBase & with)
				{
					return *this = (std::string) (with);
				}

			public:
				StringReferenceBase& operator+=(const char * with)
				{
					RedisCommand command("append %s %s");
					RedisReply reply = command.execute(opt.getContext(), this->key, with);
					switch (reply.replyType()) {
						case RedisReplyType::INTEGER:
							return *this;
						case RedisReplyType::NIL:
							throw RedisNilException(this->key);
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

				StringReferenceBase& operator+=(const std::string & with)
				{
					return *this += with.c_str();
				}

				StringReferenceBase& operator+=(const StringReferenceBase & with)
				{
					return *this += (std::string) with;
				}

				friend std::istream& operator>>(std::istream& in, StringReferenceBase& to)
				{
					std::string buff;
					in >> buff;
					to = buff;
					return in;
				}
		};

		template <typename Type>
		struct ReferenceBaseChooser;

		template <>
		struct ReferenceBaseChooser<bool>
		{
				typedef BoolReferenceBase type;
		};

		template <>
		struct ReferenceBaseChooser<float>
		{
				typedef RealReferenceBase<float> type;
		};

		template <>
		struct ReferenceBaseChooser<double>
		{
				typedef RealReferenceBase<double> type;
		};

		template <>
		struct ReferenceBaseChooser<int>
		{
				typedef IntegerReferenceBase<int> type;
		};

		template <>
		struct ReferenceBaseChooser<unsigned int>
		{
				typedef IntegerReferenceBase<unsigned int> type;
		};

		template <>
		struct ReferenceBaseChooser<long>
		{
				typedef IntegerReferenceBase<long> type;
		};

		template <>
		struct ReferenceBaseChooser<unsigned long>
		{
				typedef IntegerReferenceBase<unsigned long> type;
		};

		template <>
		struct ReferenceBaseChooser<std::string>
		{
				typedef StringReferenceBase type;
		};

		template <typename Type>
		class Reference: public ReferenceBaseChooser<Type>::type
		{
			private:
				typedef typename ReferenceBaseChooser<Type>::type supper_t;

			public:
				Reference(const RedisContext & conn, const char key[]) :
						supper_t(conn, key)
				{
				}

				Reference(const RedisContext & conn, const std::string & key) :
						supper_t(conn, key)
				{
				}

				Reference& operator=(const Type & src)
				{
					supper_t::operator=(src);
					return *this;
				}
		};

		template <typename Type>
		class ConstReference : public ConstReferenceBase<Type>
		{
			private:
				typedef ConstReferenceBase<Type> supper_t;

			public:
				ConstReference(const RedisContext & conn, const char key[]) :
						supper_t(conn, key)
				{
				}

				ConstReference(const RedisContext & conn, const std::string & key) :
						supper_t(conn, key)
				{
				}
		};

		template <>
		class ConstReference<std::string> : public ConstStringReferenceBase
		{
			private:
				typedef ConstStringReferenceBase supper_t;

			public:
				ConstReference(const RedisContext & conn, const char key[]) :
						supper_t(conn, key)
				{
				}

				ConstReference(const RedisContext & conn, const std::string & key) :
						supper_t(conn, key)
				{
				}
		};
	}
}


#endif /* INCLUDE_KERBAL_REDIS_REDIS_DATA_STRUCT_REFERENCE_BASE_HPP_ */
