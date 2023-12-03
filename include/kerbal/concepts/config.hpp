/**
 * @file       config.hpp
 * @brief
 * @date       2020-02-29
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONCEPTS_CONFIG_HPP
#define KERBAL_CONCEPTS_CONFIG_HPP

#ifndef KERBAL_HAS_CONCEPTS_SUPPORT

#	if __cpp_concepts
#		define KERBAL_HAS_CONCEPTS_SUPPORT 1
#	endif

#	ifndef KERBAL_HAS_CONCEPTS_SUPPORT
#		define KERBAL_HAS_CONCEPTS_SUPPORT 0
#	endif

#endif


#ifndef KERBAL_CONCEPT
#	if KERBAL_HAS_CONCEPTS_SUPPORT
#		define KERBAL_CONCEPT concept
#	else
#		define KERBAL_CONCEPT
#	endif
#endif


#ifndef KERBAL_CONSTRAINT
#	if KERBAL_HAS_CONCEPTS_SUPPORT
#		define KERBAL_CONSTRAINT(C) C
#	else
#		define KERBAL_CONSTRAINT(C) typename
#	endif
#endif


#ifndef KERBAL_REQUIRES
#	if KERBAL_HAS_CONCEPTS_SUPPORT
#		define KERBAL_REQUIRES(C) requires C
#	else
#		define KERBAL_REQUIRES(C)
#	endif
#endif

#endif // KERBAL_CONCEPTS_CONFIG_HPP
