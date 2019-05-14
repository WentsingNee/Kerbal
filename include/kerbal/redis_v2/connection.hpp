/*
 * connection.hpp
 *
 *  Created on: 2018年10月2日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_REDIS_V2_CONNECTION_HPP_
#define INCLUDE_KERBAL_REDIS_V2_CONNECTION_HPP_

#include <string>
#include <cstring>
#include <vector>
#include <stdexcept>

#if __cplusplus >= 201103L
#	include <chrono>
#endif

#include <hiredis/hiredis.h>
#include <kerbal/compatibility/compatibility_macro.hpp>
#include <kerbal/compatibility/va_arg_compatible_cast.hpp>
#include <kerbal/redis_v2/exception.hpp>
#include <kerbal/redis_v2/type_traits.hpp>
#include <kerbal/type_traits/type_traits_details/enable_if.hpp>
#include <kerbal/type_traits/type_traits_details/is_same.hpp>
#include <kerbal/type_traits/type_traits_details/cv_deduction.hpp>

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
						conn(src.conn == NULL? NULL: redisConnect(src.host(), src.port()))
				{
				}

#			if __cplusplus >= 201103L

				connection(connection && src) noexcept :
						conn(src.conn)
				{
					src.conn = nullptr;
				}

#			endif

				connection(const char ip[], int port) KERBAL_NOEXCEPT :
						conn(redisConnect(ip, port))
				{
				}

				connection(const std::string & ip, int port) KERBAL_NOEXCEPT :
						conn(redisConnect(ip.c_str(), port))
				{
				}

				connection(const char ip[], int port, const struct timeval & tv) KERBAL_NOEXCEPT :
						conn(redisConnectWithTimeout(ip, port, tv))
				{
				}

				connection(const std::string & ip, int port, const struct timeval & tv) KERBAL_NOEXCEPT :
						conn(redisConnectWithTimeout(ip.c_str(), port, tv))
				{
				}

#			if __cplusplus >= 201103L

				connection(const char ip[], int port, const std::chrono::milliseconds & ms) noexcept :
						conn(redisConnectWithTimeout(ip, port, timeval { .tv_sec = ms.count() / 1000, .tv_usec = ms.count() % 1000 }))
				{
				}

				connection(const std::string & ip, int port, const std::chrono::milliseconds & ms) noexcept :
						conn(redisConnectWithTimeout(ip.c_str(), port, timeval { .tv_sec = ms.count() / 1000, .tv_usec = ms.count() % 1000 }))
				{
				}

#			endif

				~connection() KERBAL_NOEXCEPT
				{
					close();
				}

				connection& operator=(const connection & src) KERBAL_NOEXCEPT
				{
					this->conn = src.conn == NULL ? NULL : redisConnect(src.host(), src.port());
					return *this;
				}

#			if __cplusplus >= 201103L

				connection& operator=(connection && src) noexcept
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

				int set_timeout(const struct timeval tv) KERBAL_NOEXCEPT
				{
					return redisSetTimeout(conn, tv);
				}

				int errnum() const
				{
					assert_null_conn();
					return conn->err;
				}

				const char * error() const
				{
					assert_null_conn();
					return conn->errstr;
				}

				const struct timeval & timeout() const
				{
					assert_null_conn();
					return *(conn->timeout);
				}

				const char * host() const
				{
					assert_null_conn();
					return conn->tcp.host;
				}

				const char * source_addr() const
				{
					assert_null_conn();
					return conn->tcp.source_addr;
				}

				int port() const
				{
					assert_null_conn();
					return conn->tcp.port;
				}

				const char * path() const
				{
					assert_null_conn();
					return conn->unix_sock.path;
				}

#			if __cplusplus >= 201103L
				template <typename ...Args>
				typename kerbal::type_traits::enable_if<is_redis_execute_list<Args...>::value, reply>::type
				execute(const char * command, Args && ...args) const
				{
					::redisReply * raw_reply = (::redisReply*)::redisCommand(this->conn, command,
												kerbal::compatibility::va_arg_compatible_cast(std::forward<Args>(args))...);
					if (raw_reply == nullptr) {
						throw bad_context_exception();
					}

					if (raw_reply->type == reply_type::ERROR) {
						execute_failed_exception e(raw_reply->str, command);
						::freeReplyObject(raw_reply);
						throw e;
					}

					return reply(raw_reply);
				}

				template <typename ...Args>
				typename kerbal::type_traits::enable_if<is_redis_execute_list<Args...>::value, reply>::type
				execute(const std::string & command, Args && ...args) const
				{
					return this->execute(command.c_str(), std::forward<Args>(args)...);
				}

#			endif

			private:
				reply argv_execute(int argc, const char **argv, const size_t *argvlen)
				{
					::redisReply * raw_reply = (::redisReply*) ::redisCommandArgv(this->conn, argc, argv, argvlen);
					if (raw_reply == nullptr) {
						throw bad_context_exception();
					}

					if (raw_reply->type == reply_type::ERROR) {
						execute_failed_exception e(raw_reply->str, argv, argv + argc);
						::freeReplyObject(raw_reply);
						throw e;
					}

					return reply(raw_reply);
				}

			public:
				template <typename InputIterator>
				typename kerbal::type_traits::enable_if<
					kerbal::type_traits::is_same<
						typename kerbal::type_traits::remove_cvref<typename std::iterator_traits<InputIterator>::value_type>::type,
						const char *
					>::value ||
					kerbal::type_traits::is_same<
						typename kerbal::type_traits::remove_cvref<typename std::iterator_traits<InputIterator>::value_type>::type,
						char *
					>::value
					,
				reply>::type
				argv_execute(InputIterator begin, InputIterator end)
				{
					std::vector<const char *> argv;
					std::vector<size_t> argv_len;

					while(begin != end) {
						argv.push_back(*begin);
						argv_len.push_back(std::strlen(*begin));
						++begin;
					}
#	if __cplusplus < 201103L
					return this->argv_execute(argv.size(), &argv[0], &argv_len[0]);
#	else
					return this->argv_execute(argv.size(), argv.data(), argv_len.data());
#	endif
				}


				template <typename InputIterator>
				typename kerbal::type_traits::enable_if<
					kerbal::type_traits::is_same<
						typename kerbal::type_traits::remove_cvref<typename std::iterator_traits<InputIterator>::value_type>::type,
						std::string
					>::value ||
					kerbal::type_traits::is_same<
						typename kerbal::type_traits::remove_cvref<typename std::iterator_traits<InputIterator>::value_type>::type,
						kerbal::utility::string_ref
					>::value,
				reply>::type
				argv_execute(InputIterator begin, InputIterator end)
				{
					std::vector<const char *> argv;
					std::vector<size_t> argv_len;

					while(begin != end) {
						argv.push_back(begin->c_str());
						argv_len.push_back(begin->length());
						++begin;
					}
#	if __cplusplus < 201103L
					return this->argv_execute(argv.size(), &argv[0], &argv_len[0]);
#	else
					return this->argv_execute(argv.size(), argv.data(), argv_len.data());
#	endif
				}




			private:
				void assert_null_conn() const
				{
					if(conn == NULL) {
						throw null_context_exception();
					}
				}

		};

	} /* namespace redis_v2 */

} /* namespace kerbal */


#endif /* INCLUDE_KERBAL_REDIS_V2_CONNECTION_HPP_ */
