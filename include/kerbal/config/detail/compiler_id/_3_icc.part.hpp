/**
 * @file       _3_icc.part.hpp
 * @brief
 * @date       2021-02-08
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONFIG_DETAIL_COMPILER_ID__3_ICC_PART_HPP
#define KERBAL_CONFIG_DETAIL_COMPILER_ID__3_ICC_PART_HPP


#if defined(__ICC) || defined(__ICL) // __ICC (Linux , macOS* ), __ICL (Windows)
#	if defined(KERBAL_COMPILER_ID) && KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_ICC
#		warning "Macro KERBAL_COMPILER_ID has defined!"
#	else
#		define KERBAL_COMPILER_ID KERBAL_COMPILER_ID_ICC
#	endif
#endif


#endif // KERBAL_CONFIG_DETAIL_COMPILER_ID__3_ICC_PART_HPP
