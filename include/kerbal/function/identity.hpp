/**
 * @file       identity.hpp
 * @brief
 * @date       2021-11-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_FUNCTION_IDENTITY_HPP
#define KERBAL_FUNCTION_IDENTITY_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif


namespace kerbal
{

	namespace function
	{

		struct identity
		{

#		if __cplusplus >= 201103L

				template <typename T>
				KERBAL_CONSTEXPR
				T && operator()(T && s) const KERBAL_NOEXCEPT
				{
					return kerbal::utility::forward<T>(s);
				}

#		else

				template <typename T>
				T & operator()(T & s) const KERBAL_NOEXCEPT
				{
					return s;
				}

#		endif

		};

	} // namespace function

} // namespace kerbal

#endif // KERBAL_FUNCTION_IDENTITY_HPP
