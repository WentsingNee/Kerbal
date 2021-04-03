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


#if !defined(KERBAL_ENABLE_CONCEPTS)

#	if __cpp_concepts >= 201507L
#		define KERBAL_ENABLE_CONCEPTS __cpp_concepts
#	endif

#endif

#ifndef KERBAL_CONCEPT
#	define KERBAL_CONCEPT concept
#endif

#endif // KERBAL_CONCEPTS_CONFIG_HPP
