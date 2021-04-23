/**
 * @file       _4_nvcc.hpp
 * @brief
 * @date       2021-02-08
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONFIG_DETAIL_COMPILER_ID__4_NVCC_HPP
#define KERBAL_CONFIG_DETAIL_COMPILER_ID__4_NVCC_HPP


#if defined(__NVCC__)
#	if defined(KERBAL_COMPILER_ID) && KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_NVCC
#		warning "Macro KERBAL_COMPILER_ID has defined!"
#	else
#		define KERBAL_COMPILER_ID KERBAL_COMPILER_ID_NVCC
#	endif
#endif


#endif // KERBAL_CONFIG_DETAIL_COMPILER_ID__4_NVCC_HPP
