/**
 * @file       bad_function_call.hpp
 * @brief
 * @date       2022-06-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_FUNCTION_FUNCTION_BAD_FUNCTION_CALL_HPP
#define KERBAL_FUNCTION_FUNCTION_BAD_FUNCTION_CALL_HPP

#include <kerbal/compatibility/noexcept.hpp>

#include <stdexcept>


namespace kerbal
{

	namespace function
	{

		class bad_function_call : public std::exception
		{
			public:
				virtual const char * what() const KERBAL_NOEXCEPT
				{
					return "bad function call";
				}
		};

	} // namespace function

} // namespace kerbal

#endif // KERBAL_FUNCTION_FUNCTION_BAD_FUNCTION_CALL_HPP
