/*
 * connection.hpp
 *
 *  Created on: 2018年10月2日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_REDIS_V2_CONNECTION_HPP_
#define INCLUDE_KERBAL_REDIS_V2_CONNECTION_HPP_

#include <string>
#include <chrono>
#include <hiredis/hiredis.h>

#include <kerbal/compatibility/compatibility_macro.hpp>

namespace kerbal
{

	namespace redis_v2
	{

		class connection
		{
			private:
				redisContext * conn;

			public:
				connection() KERBAL_NOEXCEPT:
						conn(NULL)
				{
				}

				connection(const connection & src) KERBAL_NOEXCEPT :
						conn(redisConnect(src.host(), src.port()))
				{
				}

#			if __cplusplus >= 201103L

				connection(connection && src) KERBAL_NOEXCEPT :
						conn(src.conn)
				{
					src.conn = nullptr;
				}

#			endif

				connection(const char ip[], int port) KERBAL_NOEXCEPT :
						conn(redisConnect(ip, port))
				{
				}

				connection(const char ip[], int port, const struct timeval tv) KERBAL_NOEXCEPT :
						conn(redisConnectWithTimeout(ip, port, tv))
				{
				}

				connection(const char ip[], int port, const std::chrono::milliseconds & ms) KERBAL_NOEXCEPT :
						conn(redisConnectWithTimeout(ip, port, timeval { .tv_sec = ms.count() / 1000, .tv_usec = ms.count() % 1000 }))
				{
				}

				connection(const std::string & ip, int port) KERBAL_NOEXCEPT :
						conn(redisConnect(ip.c_str(), port))
				{
				}

				connection(const std::string & ip, int port, const struct timeval tv) KERBAL_NOEXCEPT :
						conn(redisConnectWithTimeout(ip.c_str(), port, tv))
				{
				}

				connection(const std::string & ip, int port, const std::chrono::milliseconds & ms) KERBAL_NOEXCEPT :
						conn(redisConnectWithTimeout(ip.c_str(), port, timeval { .tv_sec = ms.count() / 1000, .tv_usec = ms.count() % 1000 }))
				{
				}

				~connection() KERBAL_NOEXCEPT
				{
					close();
				}

				connection& operator=(const connection & src) KERBAL_NOEXCEPT
				{
					this->conn = redisConnect(src.host(), src.port());
					return *this;
				}

#			if __cplusplus >= 201103L

				connection& operator=(connection && src) KERBAL_NOEXCEPT
				{
					this->conn = src.conn;
					src.conn = nullptr;
					return *this;
				}

#			endif

				operator bool() const KERBAL_NOEXCEPT
				{
					return this->conn != NULL;
				}

				void close() KERBAL_NOEXCEPT
				{
					redisFree(conn);
					conn = NULL;
				}

				const redisContext * get() const KERBAL_NOEXCEPT
				{
					return this->conn;
				}

				int reconnect() KERBAL_NOEXCEPT
				{
					return redisReconnect(conn);
				}

				int set_timeout(const struct timeval tv) KERBAL_NOEXCEPT
				{
					return redisSetTimeout(conn, tv);
				}

				int errnum() const KERBAL_NOEXCEPT
				{
					return conn->err;
				}

				const char * error() const KERBAL_NOEXCEPT
				{
					return conn->errstr;
				}

				const struct timeval & timeout() const KERBAL_NOEXCEPT
				{
					return *(conn->timeout);
				}

				const char * host() const KERBAL_NOEXCEPT
				{
					return conn->tcp.host;
				}

				const char * source_addr() const KERBAL_NOEXCEPT
				{
					return conn->tcp.source_addr;
				}

				int port() const KERBAL_NOEXCEPT
				{
					return conn->tcp.port;
				}

				const char * path() const KERBAL_NOEXCEPT
				{
					return conn->unix_sock.path;
				}

		};

	} /* namespace redis_v2 */

} /* namespace kerbal */


#endif /* INCLUDE_KERBAL_REDIS_V2_CONNECTION_HPP_ */
