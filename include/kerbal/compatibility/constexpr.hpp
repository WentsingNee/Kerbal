/**
 * @file       constexpr.hpp
 * @brief
 * @date       2019-5-11
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COMPATIBILITY_CONSTEXPR_HPP
#define KERBAL_COMPATIBILITY_CONSTEXPR_HPP


#ifndef KERBAL_ENABLE_CONSTEXPR
#	if __cplusplus >= 201103L
#		define KERBAL_ENABLE_CONSTEXPR 1
#	else
#		define KERBAL_ENABLE_CONSTEXPR 0
#	endif
#endif

#ifndef KERBAL_CONSTEXPR
#	if KERBAL_ENABLE_CONSTEXPR
#		define KERBAL_CONSTEXPR constexpr
#	else
#		define KERBAL_CONSTEXPR
#	endif
#endif



#ifndef KERBAL_ENABLE_CONSTEXPR14
#	if __cplusplus >= 201402L
#		define KERBAL_ENABLE_CONSTEXPR14 1
#	else
#		define KERBAL_ENABLE_CONSTEXPR14 0
#	endif
#endif

#ifndef KERBAL_CONSTEXPR14
#	if KERBAL_ENABLE_CONSTEXPR14
#		define KERBAL_CONSTEXPR14 constexpr
#	else
#		define KERBAL_CONSTEXPR14
#	endif
#endif



#ifndef KERBAL_ENABLE_CONSTEXPR17
#	if __cplusplus >= 201703L
#		if __cpp_constexpr >= 201402L
#			define KERBAL_ENABLE_CONSTEXPR17 1
#		else
#			define KERBAL_ENABLE_CONSTEXPR17 0
#		endif
#	else
#		define KERBAL_ENABLE_CONSTEXPR17 0
#	endif
#endif

#ifndef KERBAL_CONSTEXPR17
#	if KERBAL_ENABLE_CONSTEXPR17
#		define KERBAL_CONSTEXPR17 constexpr
#	else
#		define KERBAL_CONSTEXPR17
#	endif
#endif



#ifndef KERBAL_ENABLE_CONSTEXPR20
#	if __cplusplus > 201703L
#		if __cpp_constexpr >= 201907L
#			define KERBAL_ENABLE_CONSTEXPR20 1
#		else
#			define KERBAL_ENABLE_CONSTEXPR20 0
#		endif
#	else
#		define KERBAL_ENABLE_CONSTEXPR20 0
#	endif
#endif

#ifndef KERBAL_CONSTEXPR20
#	if KERBAL_ENABLE_CONSTEXPR20
#		define KERBAL_CONSTEXPR20 constexpr
#	else
#		define KERBAL_CONSTEXPR20
#	endif
#endif

#endif // KERBAL_COMPATIBILITY_CONSTEXPR_HPP
