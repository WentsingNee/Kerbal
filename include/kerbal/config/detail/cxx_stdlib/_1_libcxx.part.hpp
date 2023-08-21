/**
 * @file       _1_libcxx.part.hpp
 * @brief
 * @date       2021-02-20
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONFIG_DETAIL_CXX_STDLIB__1_LIBCXX_PART_HPP
#define KERBAL_CONFIG_DETAIL_CXX_STDLIB__1_LIBCXX_PART_HPP

#include <cstddef>


#ifdef _LIBCPP_VERSION
#	if defined(KERBAL_CXX_STDLIB) && KERBAL_CXX_STDLIB != KERBAL_CXX_STDLIB_LIBCXX
#		warning "Macro KERBAL_CXX_STDLIB has defined!"
#	else
#		define KERBAL_CXX_STDLIB KERBAL_CXX_STDLIB_LIBCXX
#	endif
#endif


#endif // KERBAL_CONFIG_DETAIL_CXX_STDLIB__1_LIBCXX_PART_HPP
