/**
 * @file       _0_libstdcxx.part.hpp
 * @brief
 * @date       2021-02-15
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONFIG_DETAIL_CXX_STDLIB__0_LIBSTDCXX_PART_HPP
#define KERBAL_CONFIG_DETAIL_CXX_STDLIB__0_LIBSTDCXX_PART_HPP

#include <cstddef>


#ifdef __GLIBCXX__
#	if defined(KERBAL_CXX_STDLIB) && KERBAL_CXX_STDLIB != KERBAL_CXX_STDLIB_LIBSTDCXX
#		warning "Macro KERBAL_CXX_STDLIB has defined!"
#	else
#		define KERBAL_CXX_STDLIB KERBAL_CXX_STDLIB_LIBSTDCXX
#	endif
#endif


#endif // KERBAL_CONFIG_DETAIL_CXX_STDLIB__0_LIBSTDCXX_PART_HPP
