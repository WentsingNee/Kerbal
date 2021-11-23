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


#endif // KERBAL_COMPATIBILITY_METHOD_OVERLOAD_TAG_HPP
