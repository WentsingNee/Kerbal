/**
 * @file       _2_msvc.part.hpp
 * @brief
 * @date       2021-02-20
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONFIG_DETAIL_CXX_STDLIB__2_MSVC_PART_HPP
#define KERBAL_CONFIG_DETAIL_CXX_STDLIB__2_MSVC_PART_HPP

#include <cstddef>


#ifdef _MSVC_STL_VERSION
#	if defined(KERBAL_CXX_STDLIB) && KERBAL_CXX_STDLIB != KERBAL_CXX_STDLIB_MSVC
#		pragma message ("Kerbal Warning: " "Macro KERBAL_CXX_STDLIB has defined!")
#	else
#		define KERBAL_CXX_STDLIB KERBAL_CXX_STDLIB_MSVC
#	endif
#endif


#endif // KERBAL_CONFIG_DETAIL_CXX_STDLIB__2_MSVC_PART_HPP
