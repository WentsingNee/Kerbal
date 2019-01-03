/*
 * string.hpp
 *
 *  Created on: 2018年12月2日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_REDIS_V2_STRING_HPP_
#define INCLUDE_KERBAL_REDIS_V2_STRING_HPP_

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

		class string
		{
			private:
				kerbal::redis_v2::connection * bind_conn;
				std::string bind_key;

			public:
//				string() :
//						bind_key()
//				{
//				}

				string(kerbal::redis_v2::connection & bind_conn, const char * bind_key) :
						bind_conn(&bind_conn), bind_key(bind_key)
				{
				}

				string(kerbal::redis_v2::connection & bind_conn, const std::string & bind_key) :
						bind_conn(&bind_conn), bind_key(bind_key)
				{
				}

				long long append(const kerbal::utility::string_ref & value)
				{
					reply _reply = bind_conn->execute("append %s %s", bind_key.c_str(), value.c_str());
					switch (_reply.type()) {
						case reply_type::INTEGER:
							return _reply->integer;
						default:
							throw unexpected_case_exception(_reply.type(), "append %s %s");
					}
				}

				long long bitcount() const
				{
					reply _reply = bind_conn->execute("bitcount %s", bind_key.c_str());
					switch (_reply.type()) {
						case reply_type::INTEGER:
							return _reply->integer;
						default:
							throw unexpected_case_exception(_reply.type(), "bitcount %s");
					}
				}

				long long bitcount(long long begin, long long end) const
				{
					reply _reply = bind_conn->execute("bitcount %s %lld %lld", bind_key.c_str(), begin, end);
					switch (_reply.type()) {
						case reply_type::INTEGER:
							return _reply->integer;
						default:
							throw unexpected_case_exception(_reply.type(), "bitcount %s %lld %lld");
					}
				}

				long long decr()
				{
					reply _reply = bind_conn->execute("decr %s", bind_key.c_str());
					switch (_reply.type()) {
						case reply_type::INTEGER:
							return _reply->integer;
						default:
							throw unexpected_case_exception(_reply.type(), "decr %s");
					}
				}

				long long incr()
				{
					reply _reply = bind_conn->execute("incr %s", bind_key.c_str());
					switch (_reply.type()) {
						case reply_type::INTEGER:
							return _reply->integer;
						default:
							throw unexpected_case_exception(_reply.type(), "incr %s");
					}
				}

				long long decrby(long long decrement)
				{
					reply _reply = bind_conn->execute("decrby %s %lld", bind_key.c_str(), decrement);
					switch (_reply.type()) {
						case reply_type::INTEGER:
							return _reply->integer;
						default:
							throw unexpected_case_exception(_reply.type(), "decrby %s %lld");
					}
				}

#	if __cplusplus < 201103L
				std::string get() const
				{
					return this->get<std::string>();
				}
#	endif

				template <typename ReturnType
#	if __cplsuplus >= 201103L
							= kerbal::data_struct::optional<std::string>
#	endif
				>
				ReturnType get() const
				{
					reply _reply = bind_conn->execute("get %s", bind_key.c_str());
					switch (_reply.type()) {
						case reply_type::STRING:
							return ReturnType(_reply->str);
						case reply_type::NIL:
							return ReturnType();
						default:
							throw unexpected_case_exception(_reply.type(), "get %s");
					}
				}

		};


	} /* namespace redis_v2 */

} /* namespace kerbal */



#endif /* INCLUDE_KERBAL_REDIS_V2_STRING_HPP_ */
