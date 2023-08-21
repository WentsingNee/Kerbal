/**
 * @file       _1_windows.part.hpp
 * @brief
 * @date       2021-05-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONFIG_DETAIL_SYSTEM__1_WINDOWS_PART_HPP
#define KERBAL_CONFIG_DETAIL_SYSTEM__1_WINDOWS_PART_HPP

#include <kerbal/config/compiler_id.hpp>


#if (KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU) || \
	(KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_CLANG) || \
	(KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC)

#	if defined(_WIN32) || defined(_WIN64)
#		if defined(KERBAL_SYSTEM) && KERBAL_SYSTEM != KERBAL_SYSTEM_WINDOWS
#			warning "Macro KERBAL_SYSTEM has defined!"
#		else
#			define KERBAL_SYSTEM KERBAL_SYSTEM_WINDOWS
#		endif
#	endif

#elif (KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC)

#	if defined(_WIN32) || defined(_WIN64)
#		if defined(KERBAL_SYSTEM) && KERBAL_SYSTEM != KERBAL_SYSTEM_WINDOWS
#			pragma message "Macro KERBAL_SYSTEM has defined!"
#		else
#			define KERBAL_SYSTEM KERBAL_SYSTEM_WINDOWS
#		endif
#	endif

#endif


#endif // KERBAL_CONFIG_DETAIL_SYSTEM__1_WINDOWS_PART_HPP
