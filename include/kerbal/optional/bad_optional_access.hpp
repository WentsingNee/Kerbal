/**
 * @file       bad_optional_access.hpp
 * @brief
 * @date       2018-10-28
 * @author     peter
 * @copyright
 *      peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OPTIONAL_BAD_OPTIONAL_ACCESS_
#define KERBAL_OPTIONAL_BAD_OPTIONAL_ACCESS_

#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/utility/throw_this_exception.hpp>
#include <exception>

namespace kerbal
{
	namespace optional
	{

		class bad_optional_access: public std::exception, public kerbal::utility::throw_this_exception_helper<bad_optional_access>
		{
			public:
				virtual const char* what() const KERBAL_NOEXCEPT
				{
					return "Attempted to access the value of an uninitialized optional object.";
				}
		};

	} /* namespace optional */

} /* namespace kerbal */


#endif /* KERBAL_OPTIONAL_BAD_OPTIONAL_ACCESS_ */
