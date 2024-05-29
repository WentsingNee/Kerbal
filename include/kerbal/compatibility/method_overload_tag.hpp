/**
 * @file       method_overload_tag.hpp
 * @brief
 * @date       2019-5-11
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COMPATIBILITY_METHOD_OVERLOAD_TAG_HPP
#define KERBAL_COMPATIBILITY_METHOD_OVERLOAD_TAG_HPP

#ifndef KERBAL_REFERENCE_OVERLOAD_TAG
#	if __cplusplus < 201103L
#		define KERBAL_REFERENCE_OVERLOAD_TAG
#	else
#		define KERBAL_REFERENCE_OVERLOAD_TAG &
#	endif
#endif

#ifndef KERBAL_CONST_REFERENCE_OVERLOAD_TAG
#	if __cplusplus < 201103L
#		define KERBAL_CONST_REFERENCE_OVERLOAD_TAG const
#	else
#		define KERBAL_CONST_REFERENCE_OVERLOAD_TAG const &
#	endif
#endif


#ifndef KERBAL_SUPPORTS_CONST_RVALUE_REFERENCE_MEMBER

#include <kerbal/config/compiler_id.hpp>

#if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU
#	include <kerbal/config/compiler_private.hpp>
#	if KERBAL_GNU_VERSION_MEETS(5, 0, 0)
#		define KERBAL_SUPPORTS_CONST_RVALUE_REFERENCE_MEMBER 1
#	endif
#else
#	define KERBAL_SUPPORTS_CONST_RVALUE_REFERENCE_MEMBER 1
#endif

#	ifndef KERBAL_SUPPORTS_CONST_RVALUE_REFERENCE_MEMBER
#		define KERBAL_SUPPORTS_CONST_RVALUE_REFERENCE_MEMBER 0
#	endif

#endif

#endif // KERBAL_COMPATIBILITY_METHOD_OVERLOAD_TAG_HPP
