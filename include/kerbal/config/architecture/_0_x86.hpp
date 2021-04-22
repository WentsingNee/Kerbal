/**
 * @file       _0_x86.hpp
 * @brief
 * @date       2021-02-08
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONFIG_ARCHITECTURE__0_X86_HPP
#define KERBAL_CONFIG_ARCHITECTURE__0_X86_HPP

#include <kerbal/config/compiler_id.hpp>


#if (KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU) || (KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_CLANG)

#	if defined(__x86__)
#		if defined(KERBAL_ARCHITECTURE) && KERBAL_ARCHITECTURE != KERBAL_ARCHITECTURE_X86
#			warning "Macro KERBAL_ARCHITECTURE has defined!"
#		else
#			define KERBAL_ARCHITECTURE KERBAL_ARCHITECTURE_AMD64
#		endif
#	endif

#elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC

#	if defined(_M_IX86)
#		if defined(KERBAL_ARCHITECTURE) && KERBAL_ARCHITECTURE != KERBAL_ARCHITECTURE_X86
#			pragma message ("Kerbal Warning: " "Macro KERBAL_ARCHITECTURE has defined!")
#		else
#			define KERBAL_ARCHITECTURE KERBAL_ARCHITECTURE_X86
#		endif
#	endif

#elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC

#	if defined(_M_IX86)
#		if defined(KERBAL_ARCHITECTURE) && KERBAL_ARCHITECTURE != KERBAL_ARCHITECTURE_X86
#			warning "Macro KERBAL_ARCHITECTURE has defined!"
#		else
#			define KERBAL_ARCHITECTURE KERBAL_ARCHITECTURE_X86
#		endif
#	endif

#endif


#endif // KERBAL_CONFIG_ARCHITECTURE__0_X86_HPP
