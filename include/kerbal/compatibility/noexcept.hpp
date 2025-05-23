/**
 * @file       noexcept.hpp
 * @brief
 * @date       2019-5-11
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COMPATIBILITY_NOEXCEPT_HPP
#define KERBAL_COMPATIBILITY_NOEXCEPT_HPP

#include <kerbal/config/exceptions.hpp>


#ifndef KERBAL_NOEXCEPT
#	if __cplusplus >= 201103L
#		define KERBAL_NOEXCEPT noexcept
#	else
#		define KERBAL_NOEXCEPT throw()
#	endif
#endif


#ifndef KERBAL_NOEXCEPT17
#	if __cplusplus >= 201703L
#		define KERBAL_NOEXCEPT17 noexcept
#	else
#		define KERBAL_NOEXCEPT17
#	endif
#endif


#ifndef KERBAL_CONDITIONAL_NOEXCEPT
#	if KERBAL_SUPPORTS_EXCEPTIONS
#		if __cplusplus >= 201103L
#			define KERBAL_CONDITIONAL_NOEXCEPT(cond) noexcept(cond)
#		else
#			define KERBAL_CONDITIONAL_NOEXCEPT(cond)
#		endif
#	else
#		define KERBAL_CONDITIONAL_NOEXCEPT(cond) KERBAL_NOEXCEPT
#	endif
#endif

#endif // KERBAL_COMPATIBILITY_NOEXCEPT_HPP
