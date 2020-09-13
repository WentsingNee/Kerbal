/**
 * @file       architecture.hpp
 * @brief
 * @date       2020-07-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONFIG_ARCHITECTURE_HPP
#define KERBAL_CONFIG_ARCHITECTURE_HPP

#include <kerbal/config/compiler_id.hpp>


#ifndef KERBAL_ARCHITECTURE_UNKNOWN
#	define KERBAL_ARCHITECTURE_UNKNOWN -1
#endif

#ifndef KERBAL_ARCHITECTURE_X86
#	define KERBAL_ARCHITECTURE_X86 0
#endif

#ifndef KERBAL_ARCHITECTURE_AMD64
#	define KERBAL_ARCHITECTURE_AMD64 1
#endif

#ifndef KERBAL_ARCHITECTURE_ARM
#	define KERBAL_ARCHITECTURE_ARM 2
#endif

#ifndef KERBAL_ARCHITECTURE_AARCH64
#	define KERBAL_ARCHITECTURE_AARCH64 3
#endif

#ifndef KERBAL_ARCHITECTURE

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU

#		if defined(__amd64__)
#			if defined(KERBAL_ARCHITECTURE) && KERBAL_ARCHITECTURE != KERBAL_ARCHITECTURE_AMD64
#				warning "Macro KERBAL_ARCHITECTURE has defined!"
#			else
#				define KERBAL_ARCHITECTURE KERBAL_ARCHITECTURE_AMD64
#			endif
#		endif

#		if defined(__arm__)
#			if defined(KERBAL_ARCHITECTURE) && KERBAL_ARCHITECTURE != KERBAL_ARCHITECTURE_ARM
#				warning "Macro KERBAL_ARCHITECTURE has defined!"
#			else
#				define KERBAL_ARCHITECTURE KERBAL_ARCHITECTURE_ARM
#			endif
#		endif

#		if defined(__aarch64__)
#			if defined(KERBAL_ARCHITECTURE) && KERBAL_ARCHITECTURE != KERBAL_ARCHITECTURE_AARCH64
#				warning "Macro KERBAL_ARCHITECTURE has defined!"
#			else
#				define KERBAL_ARCHITECTURE KERBAL_ARCHITECTURE_AARCH64
#			endif
#		endif

#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_CLANG

#		if defined(__amd64__)
#			if defined(KERBAL_ARCHITECTURE) && KERBAL_ARCHITECTURE != KERBAL_ARCHITECTURE_AMD64
#				warning "Macro KERBAL_ARCHITECTURE has defined!"
#			else
#				define KERBAL_ARCHITECTURE KERBAL_ARCHITECTURE_AMD64
#			endif
#		endif

#		if defined(__arm__)
#			if defined(KERBAL_ARCHITECTURE) && KERBAL_ARCHITECTURE != KERBAL_ARCHITECTURE_ARM
#				warning "Macro KERBAL_ARCHITECTURE has defined!"
#			else
#				define KERBAL_ARCHITECTURE KERBAL_ARCHITECTURE_ARM
#			endif
#		endif

#		if defined(__aarch64__)
#			if defined(KERBAL_ARCHITECTURE) && KERBAL_ARCHITECTURE != KERBAL_ARCHITECTURE_AARCH64
#				warning "Macro KERBAL_ARCHITECTURE has defined!"
#			else
#				define KERBAL_ARCHITECTURE KERBAL_ARCHITECTURE_AARCH64
#			endif
#		endif

#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC

#		if defined(_M_IX86)
#			if defined(KERBAL_ARCHITECTURE) && KERBAL_ARCHITECTURE != KERBAL_ARCHITECTURE_X86
#				warning "Macro KERBAL_ARCHITECTURE has defined!"
#			else
#				define KERBAL_ARCHITECTURE KERBAL_ARCHITECTURE_X86
#			endif
#		endif

#		if defined(_M_AMD64)
#			if defined(KERBAL_ARCHITECTURE) && KERBAL_ARCHITECTURE != KERBAL_ARCHITECTURE_AMD64
#				warning "Macro KERBAL_ARCHITECTURE has defined!"
#			else
#				define KERBAL_ARCHITECTURE KERBAL_ARCHITECTURE_AMD64
#			endif
#		endif

#		if defined(_M_ARM)
#			if defined(KERBAL_ARCHITECTURE) && KERBAL_ARCHITECTURE != KERBAL_ARCHITECTURE_ARM
#				warning "Macro KERBAL_ARCHITECTURE has defined!"
#			else
#				define KERBAL_ARCHITECTURE KERBAL_ARCHITECTURE_ARM
#			endif
#		endif

#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC

#		if defined(__LP64__) || defined(__LP64) || defined(_M_AMD64)
#			if defined(KERBAL_ARCHITECTURE) && KERBAL_ARCHITECTURE != KERBAL_ARCHITECTURE_AMD64
#				warning "Macro KERBAL_ARCHITECTURE has defined!"
#			else
#				define KERBAL_ARCHITECTURE KERBAL_ARCHITECTURE_AMD64
#			endif
#		endif

#		if defined(_M_IX86)
#			if defined(KERBAL_ARCHITECTURE) && KERBAL_ARCHITECTURE != KERBAL_ARCHITECTURE_X86
#				warning "Macro KERBAL_ARCHITECTURE has defined!"
#			else
#				define KERBAL_ARCHITECTURE KERBAL_ARCHITECTURE_X86
#			endif
#		endif

#	endif

#	ifndef KERBAL_ARCHITECTURE
#		define KERBAL_ARCHITECTURE KERBAL_ARCHITECTURE_UNKNOWN
#		warning "Unknown architecture"
#	endif

#endif // ifndef KERBAL_ARCHITECTURE


#endif // KERBAL_CONFIG_ARCHITECTURE_HPP
