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

#ifndef KERBAL_ARCHITECTURE_WASM
#	define KERBAL_ARCHITECTURE_WASM 4
#endif



#ifndef KERBAL_ARCHITECTURE

#	include <kerbal/config/detail/architecture/_0_x86.part.hpp>
#	include <kerbal/config/detail/architecture/_1_amd64.part.hpp>
#	include <kerbal/config/detail/architecture/_2_arm.part.hpp>
#	include <kerbal/config/detail/architecture/_3_aarch64.part.hpp>
#	include <kerbal/config/detail/architecture/_4_wasm.part.hpp>


#	ifndef KERBAL_ARCHITECTURE

#		define KERBAL_ARCHITECTURE KERBAL_ARCHITECTURE_UNKNOWN

#		if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC
#			pragma message ("Kerbal Warning: " "Unknown architecture")
#		else
#			warning "Kerbal Warning: " "Unknown architecture"
#		endif

#	endif

#endif // ifndef KERBAL_ARCHITECTURE


#endif // KERBAL_CONFIG_ARCHITECTURE_HPP
