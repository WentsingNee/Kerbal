/**
 * @file       bad_any_cast.hpp
 * @brief      
 * @date       2019-7-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ANY_BAD_ANY_CAST_HPP
#define KERBAL_ANY_BAD_ANY_CAST_HPP

#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/utility/throw_this_exception.hpp>

#include <stdexcept>

namespace kerbal
{

	namespace any
	{

		class bad_any_cast:
					public kerbal::utility::throw_this_exception_helper<bad_any_cast>,
					public std::logic_error
		{
			public:
				virtual const char* what() const KERBAL_NOEXCEPT
				{
					return "bad any_cast";
				}
		};

	} // namespace any

} // namespace kerbal


#endif // KERBAL_ANY_BAD_ANY_CAST_HPP
