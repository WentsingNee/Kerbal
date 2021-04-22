/**
 * @file       _1_clang.hpp
 * @brief
 * @date       2021-02-08
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONFIG_COMPILER_ID__1_CLANG_HPP
#define KERBAL_CONFIG_COMPILER_ID__1_CLANG_HPP


#if defined(__clang__)
#	if defined(KERBAL_COMPILER_ID) && KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_CLANG
#		warning "Macro KERBAL_COMPILER_ID has defined!"
#	else
#		define KERBAL_COMPILER_ID KERBAL_COMPILER_ID_CLANG
#	endif
#endif


#endif // KERBAL_CONFIG_COMPILER_ID__1_CLANG_HPP
