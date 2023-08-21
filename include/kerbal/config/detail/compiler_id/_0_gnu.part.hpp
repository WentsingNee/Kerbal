/**
 * @file       _0_gnu.part.hpp
 * @brief
 * @date       2021-02-08
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONFIG_DETAIL_COMPILER_ID__0_GNU_PART_HPP
#define KERBAL_CONFIG_DETAIL_COMPILER_ID__0_GNU_PART_HPP


#if defined(__GNUC__) && !defined(__clang__) && !defined(__ICC) && !defined(__ICL)
#	if defined(KERBAL_COMPILER_ID) && KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_GNU
#		warning "Macro KERBAL_COMPILER_ID has defined!"
#	else
#		define KERBAL_COMPILER_ID KERBAL_COMPILER_ID_GNU
#	endif
#endif


#endif // KERBAL_CONFIG_DETAIL_COMPILER_ID__0_GNU_PART_HPP
