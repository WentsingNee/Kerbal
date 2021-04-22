/**
 * @file       _2_msvc.hpp
 * @brief
 * @date       2021-02-08
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONFIG_COMPILER_ID__2_MSVC_HPP
#define KERBAL_CONFIG_COMPILER_ID__2_MSVC_HPP


#if defined(_MSC_VER)
#	if defined(KERBAL_COMPILER_ID) && KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_MSVC
#		pragma message ("Kerbal Warning: " "Macro KERBAL_COMPILER_ID has defined!")
#	else
#		define KERBAL_COMPILER_ID KERBAL_COMPILER_ID_MSVC
#	endif
#endif


#endif // KERBAL_CONFIG_COMPILER_ID__2_MSVC_HPP
