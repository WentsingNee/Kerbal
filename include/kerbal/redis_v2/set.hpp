/*
 * set.hpp
 *
 *  Created on: 2019年1月7日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_REDIS_V2_SET_HPP_
#define INCLUDE_KERBAL_REDIS_V2_SET_HPP_

#include <kerbal/redis_v2/connection.hpp>
#include <kerbal/type_traits/type_traits_details/enable_if.hpp>

namespace kerbal
{

	namespace redis_v2
	{

		class set
		{
			private:
				kerbal::redis_v2::connection * bind_conn;
				std::string bind_key;

			public:

				set(kerbal::redis_v2::connection & bind_conn, const char * bind_key) :
						bind_conn(&bind_conn), bind_key(bind_key)
				{
				}

				set(kerbal::redis_v2::connection & bind_conn, const std::string & bind_key) :
						bind_conn(&bind_conn), bind_key(bind_key)
				{
				}

				/**
				 * @brief Get the number of members in a set.
				 */
				long long scard() const
				{
					reply _reply = bind_conn->execute("scard %s", bind_key.c_str());
					switch (_reply.type()) {
						case reply_type::INTEGER:
							return _reply->integer;
						default:
							throw unexpected_case_exception(_reply.type(), "scard %s");
					}
				}

				/**
				 * @brief Add one or more members to a set.
				 */
				template <typename InputIterator>
				typename kerbal::type_traits::enable_if<
						kerbal::redis_v2::is_redis_execute_allow_type<typename std::iterator_traits<InputIterator>::value_type>::value,
				long long>::type
				sadd(InputIterator begin, InputIterator end)
				{
					std::vector<std::string> argv;
					argv.push_back("sadd");
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
				 * @brief Add one or more members to a set.
				 */
				template <typename Type, typename ... Args>
				long long
				sadd(const Type & value0, Args&& ... args)
				{
					std::string argv[] = { "sadd", this->bind_key, redis_cast_to_string(value0), redis_cast_to_string(args)... };
					reply _reply = bind_conn->argv_execute(begin(argv), end(argv));
					switch (_reply.type()) {
						case reply_type::INTEGER:
							return _reply->integer;
						default:
							throw unexpected_case_exception(_reply.type(), argv);
					}
				}

#	endif
		};
	}
}



#endif /* INCLUDE_KERBAL_REDIS_V2_SET_HPP_ */
