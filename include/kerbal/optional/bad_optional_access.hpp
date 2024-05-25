/**
 * @file       bad_optional_access.hpp
 * @brief
 * @date       2018-10-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OPTIONAL_BAD_OPTIONAL_ACCESS_HPP
#define KERBAL_OPTIONAL_BAD_OPTIONAL_ACCESS_HPP

#include <kerbal/compatibility/noexcept.hpp>

#include <exception>


namespace kerbal
{

	namespace optional
	{

		class bad_optional_access:
			public std::exception
		{
			public:
				virtual
				const char * what() const KERBAL_NOEXCEPT
				{
					return "Attempted to access the value of an uninitialized optional object.";
				}
		};

	} // namespace optional

} // namespace kerbal

#endif // KERBAL_OPTIONAL_BAD_OPTIONAL_ACCESS_HPP
