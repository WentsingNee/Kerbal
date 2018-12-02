/*
 * exception.hpp
 *
 *  Created on: 2018年12月1日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_REDIS_V2_EXCEPTION_HPP_
#define INCLUDE_KERBAL_REDIS_V2_EXCEPTION_HPP_

#include <kerbal/redis_v2/reply.hpp>

namespace kerbal
{

	namespace redis_v2
	{

		class redis_exception : public std::runtime_error
		{
			public:
				redis_exception() :
						std::runtime_error("An redis exception")
				{
				}

				redis_exception(const char * error) :
						std::runtime_error(error)
				{
				}

				redis_exception(const std::string & error) :
						std::runtime_error(error)
				{
				}

#	if __cplusplus >= 201103L

				redis_exception(std::string && error) :
						std::runtime_error(error)
				{
				}
#	endif

		};

		class null_context_exception : public redis_exception
		{
			public:
				null_context_exception() :
					redis_exception("Null redis context")
				{
				}
		};

		class bad_context_exception : public redis_exception
		{
			public:
				bad_context_exception() :
					redis_exception("Bad redis context")
				{
				}
		};

		class execute_failed_exception: public redis_exception
		{
			private:
				template <typename InputIterator>
				std::string command_concatenate(InputIterator cmd_begin, InputIterator cmd_end)
				{
					std::string res;
					while (cmd_begin != cmd_end) {
						res += *cmd_begin;
						res += ' ';
						++cmd_begin;
					}
					return res;
				}

			public:
				template <typename InputIterator>
				execute_failed_exception(const std::string & error, InputIterator cmd_begin, InputIterator cmd_end) :
						redis_exception(error + ", command: " + command_concatenate(cmd_begin, cmd_end))
				{
				}

			public:
				execute_failed_exception(const std::string & error, const std::string & command) :
						redis_exception(error + ", command: " + command)
				{
				}

				execute_failed_exception(const std::string & error, const char * command) :
						redis_exception(error + ", command: " + command)
				{
				}

#	if __cplusplus >= 201103L

				execute_failed_exception(const std::string & error, std::string && command) :
						redis_exception(error + ", command: " + command)
				{
				}

				execute_failed_exception(std::string && error, const std::string & command) :
						redis_exception(error + ", command: " + command)
				{
				}

				execute_failed_exception(std::string && error, std::string && command) :
						redis_exception(error + ", command: " + command)
				{
				}

				execute_failed_exception(std::string && error, const char * command) :
						redis_exception(error + ", command: " + command)
				{
				}
#	endif

		};

		class unexpected_case_exception: public redis_exception
		{
			private:
				template <typename InputIterator>
				std::string command_concatenate(InputIterator cmd_begin, InputIterator cmd_end)
				{
					std::string res;
					while (cmd_begin != cmd_end) {
						res += *cmd_begin;
						res += ' ';
						++cmd_begin;
					}
					return res;
				}

			public:
				template <typename InputIterator>
				unexpected_case_exception(reply_type unexpected_type, InputIterator cmd_begin, InputIterator cmd_end) :
						redis_exception("redis returns an unexpected type: " + reply_type_name<std::string>(unexpected_type) +
								" when execute command: " + command_concatenate(cmd_begin, cmd_end))
				{
				}

				template <size_t N>
				unexpected_case_exception(reply_type unexpected_type, const kerbal::utility::string_ref (&argv)[N]) :
						redis_exception("redis returns an unexpected type: " + reply_type_name<std::string>(unexpected_type) +
								" when execute command: " + command_concatenate(argv, argv + N))
				{
				}

				template <size_t N>
				unexpected_case_exception(reply_type unexpected_type, const std::string (&argv)[N]) :
						redis_exception("redis returns an unexpected type: " + reply_type_name<std::string>(unexpected_type) +
								" when execute command: " + command_concatenate(argv, argv + N))
				{
				}

				unexpected_case_exception(reply_type unexpected_type, const char * command) :
						redis_exception("redis returns an unexpected type: " + reply_type_name<std::string>(unexpected_type) +
								" when execute command: " + command)
				{
				}

				unexpected_case_exception(reply_type unexpected_type, const std::string & command) :
						redis_exception("redis returns an unexpected type: " + reply_type_name<std::string>(unexpected_type) +
								" when execute command: " + command)
				{
				}

#	if __cplusplus >= 201103L

				unexpected_case_exception(reply_type unexpected_type, std::string && command) :
						redis_exception("redis returns an unexpected type: " + reply_type_name<std::string>(unexpected_type) +
								" when execute command: " + command)
				{
				}
#	endif

		};

	} /* namespace redis_v2 */

} /* namespace kerbal */



#endif /* INCLUDE_KERBAL_REDIS_V2_EXCEPTION_HPP_ */
