/*
 * list_referene_base.hpp
 *
 *  Created on: 2018年8月1日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_REDIS_REDIS_DATA_STRUCT_LIST_REFERENE_BASE_HPP_
#define INCLUDE_KERBAL_REDIS_REDIS_DATA_STRUCT_LIST_REFERENE_BASE_HPP_

#include <iterator>

#include <kerbal/redis/operation.hpp>
#include <kerbal/redis/redis_type_traits.hpp>
#include <kerbal/redis/redis_type_cast.hpp>

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
				ListConstReferenceBase(const List<Type> * pToList, size_t index) noexcept :
						pToList(pToList), index(index)
				{
				}

				bool exists() const
				{
					static RedisCommand cmd("llen %s");
					size_t len = cmd.execute(pToList->conn, pToList->key)->integer;
					return -len <= index && index < len;
				}

				operator Type()
				{
					static RedisCommand cmd("lindex %s %d");
					RedisReply reply = cmd.execute(pToList->conn, pToList->key, index);
					switch (reply.replyType()) {
						case RedisReplyType::STRING: {
							return redisTypeCast<Type>(reply->str);
						}
						case RedisReplyType::NIL:
							throw RedisNilException(pToList->key);
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
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
			private:
				typedef ListConstReferenceBase<Type> supper_t;

			protected:
				ListReferenceBase& operator=(const Type & src)
				{
					static RedisCommand command(std::string("lset %s %d ") + redis_type_traits<Type>::placeholder);
					RedisReply reply = command.execute(supper_t::pToList->opt.getContext(), supper_t::pToList->key, supper_t::index, src);
					switch (reply.replyType()) {
						case RedisReplyType::STATUS: {
							return *this;
						}
						default:
							throw RedisUnexpectedCaseException(reply.replyType());
					}
				}

			public:
				ListReferenceBase(const List<Type> * pToList, size_t index) noexcept :
						supper_t(pToList, index)
				{
				}

				friend std::istream& operator>> (std::istream & in, ListReferenceBase<Type> src)
				{
					src = *std::istream_iterator<Type>(in);
					return in;
				}
		};

		template<typename Type>
		class ListRealReference: public ListReferenceBase<Type>
		{
			private:
				typedef ListReferenceBase<Type> supper_t;

			protected:
				ListRealReference& operator=(const Type & src)
				{
					supper_t::operator=(src);
					return *this;
				}

			public:
				ListRealReference(const List<Type> * pToList, size_t index) noexcept :
						supper_t(pToList, index)
				{
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
			private:
				typedef ListRealReference<Type> supper_t;

			protected:
				ListIntegerReference& operator=(const Type & src)
				{
					supper_t::operator=(src);
					return *this;
				}

			public:
				ListIntegerReference(const List<Type> * pToList, size_t index) noexcept :
						supper_t(pToList, index)
				{
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
			private:
				typedef typename std::conditional<CheckIsIntegerType<Type>::value, ListIntegerReference<Type>,
								   typename std::conditional<CheckIsRealType<Type>::value, ListRealReference<Type>,
								   	   	   	   	   	   	   	   	   	   	   ListReferenceBase<Type> >::type>::type
						supper_t;
			public:
				ListReference(const List<Type> * pToList, size_t index) noexcept :
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
			private:
				typedef ListConstReferenceBase<Type> supper_t;

			public:
				ListConstReference(const List<Type> * pToList, size_t index) noexcept :
						supper_t(pToList, index)
				{
				}
		};

		template<typename Type>
		class ListIterator : public std::random_access_iterator_tag
		{
			protected:
				const List<Type> * pToList = nullptr;
				size_t index;

			public:
				ListIterator(const List<Type> * pToList, size_t index) noexcept :
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
					return !(*this == with);
				}

		};
	}
}



#endif /* INCLUDE_KERBAL_REDIS_REDIS_DATA_STRUCT_LIST_REFERENE_BASE_HPP_ */
