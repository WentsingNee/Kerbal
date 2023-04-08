/**
 * @file       _4_wasm.hpp
 * @brief
 * @date       2023-04-09
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONFIG_ARCHITECTURE__4_WASM_HPP
#define KERBAL_CONFIG_ARCHITECTURE__4_WASM_HPP

#include <kerbal/config/compiler_id.hpp>


#if (KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU) || (KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_CLANG)

#	if defined(__wasm__)
#		if defined(KERBAL_ARCHITECTURE) && KERBAL_ARCHITECTURE != KERBAL_ARCHITECTURE_WASM
#			warning "Macro KERBAL_ARCHITECTURE has defined!"
#		else
#			define KERBAL_ARCHITECTURE KERBAL_ARCHITECTURE_WASM
#		endif
#	endif

#endif


#endif // KERBAL_CONFIG_ARCHITECTURE__4_WASM_HPP
