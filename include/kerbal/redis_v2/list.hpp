/*
 * list.hpp
 *
 *  Created on: 2018年12月14日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_REDIS_V2_LIST_HPP_
#define INCLUDE_KERBAL_REDIS_V2_LIST_HPP_

#include <kerbal/redis_v2/connection.hpp>
#include <kerbal/redis_v2/exception.hpp>
#include <kerbal/redis_v2/operation.hpp>
#include <kerbal/redis_v2/query.hpp>
#include <kerbal/redis_v2/reply.hpp>
#include <kerbal/redis_v2/type_traits.hpp>


namespace kerbal
{

	namespace redis_v2
	{

		class list
		{
			private:
				kerbal::redis_v2::connection * bind_conn;
				std::string bind_key;

			public:

				list(kerbal::redis_v2::connection & bind_conn, const char * bind_key) :
						bind_conn(&bind_conn), bind_key(bind_key)
				{
				}

				list(kerbal::redis_v2::connection & bind_conn, const std::string & bind_key) :
						bind_conn(&bind_conn), bind_key(bind_key)
				{
				}

				long long llen() const
				{
					reply _reply = bind_conn->execute("llen %s", bind_key.c_str());
					switch (_reply.type()) {
						case reply_type::INTEGER:
							return _reply->integer;
						default:
							throw unexpected_case_exception(_reply.type(), "llen %s");
					}
				}

				/**
				 * @brief Prepend one or multiple values to a list.
				 */
				template <typename InputIterator>
				typename kerbal::type_traits::enable_if<
						kerbal::redis_v2::is_redis_execute_allow_type<typename std::iterator_traits<InputIterator>::value_type>::value,
				long long>::type
				lpush(InputIterator begin, InputIterator end)
				{
					std::vector<std::string> argv;
					argv.push_back("lpush");
					argv.push_back(this->bind_key);
					while (begin != end) {
						argv.push_back(redis_cast_to_string(*begin));
						++begin;
					}
					reply _reply = bind_conn->argv_execute(argv.begin(), argv.end());
					switch (_reply.type()) {
						case reply_type::INTEGER:
							return _reply->integer;
						default:
							throw unexpected_case_exception(_reply.type(), argv.begin(), argv.end());
					}
				}

#	if __cplusplus >= 201103L

				/**
				 * @brief Prepend one or multiple values to a list.
				 */
				template <typename Type, typename ... Args>
				long long
				lpush(const Type & value0, Args&& ... args)
				{
					std::string argv[] = { "lpush", this->bind_key, redis_cast_to_string(value0), redis_cast_to_string(args)... };
					reply _reply = bind_conn->argv_execute(begin(argv), end(argv));
					switch (_reply.type()) {
						case reply_type::INTEGER:
							return _reply->integer;
						default:
							throw unexpected_case_exception(_reply.type(), argv);
					}
				}

#	endif

				/**
				 * @brief Prepend one or multiple values to a list.
				 */
				template <typename InputIterator>
				typename kerbal::type_traits::enable_if<
						kerbal::redis_v2::is_redis_execute_allow_type<typename std::iterator_traits<InputIterator>::value_type>::value,
				long long>::type
				rpush(InputIterator begin, InputIterator end)
				{
					std::vector<std::string> argv;
					argv.push_back("rpush");
					argv.push_back(this->bind_key);
					while (begin != end) {
						argv.push_back(redis_cast_to_string(*begin));
						++begin;
					}
					reply _reply = bind_conn->argv_execute(argv.begin(), argv.end());
					switch (_reply.type()) {
						case reply_type::INTEGER:
							return _reply->integer;
						default:
							throw unexpected_case_exception(_reply.type(), argv.begin(), argv.end());
					}
				}

#	if __cplusplus >= 201103L

				/**
				 * @brief Prepend one or multiple values to a list.
				 */
				template <typename Type, typename ... Args>
				long long
				rpush(const Type & value0, Args&& ... args)
				{
					std::string argv[] = { "rpush", this->bind_key, redis_cast_to_string(value0), redis_cast_to_string(args)... };
					reply _reply = bind_conn->argv_execute(begin(argv), end(argv));
					switch (_reply.type()) {
						case reply_type::INTEGER:
							return _reply->integer;
						default:
							throw unexpected_case_exception(_reply.type(), argv);
					}
				}

#	endif

#	if __cplusplus >= 201103L

				template <typename ValueType = std::string>
				typename kerbal::type_traits::enable_if<
						!kerbal::data_struct::is_optional<ValueType>::value && kerbal::redis_v2::is_redis_execute_allow_type<ValueType>::value,
				ValueType>::type
				blpop(const std::chrono::seconds & sec) const
				{
					reply _reply = bind_conn->execute("blpop %s %lld", this->bind_key, sec.count());
					switch (_reply.type()) {
						case reply_type::ARRAY:
							return redis_type_cast<ValueType>(_reply->element[1]->str);
						default:
							throw unexpected_case_exception(_reply.type(), "blpop %s %lld");
					}
				}

		};

#	endif

	} /* namespace redis_v2 */

} /* namespace kerbal */





#endif /* INCLUDE_KERBAL_REDIS_V2_LIST_HPP_ */
