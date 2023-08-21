/**
 * @file       _5_wasm.part.hpp
 * @brief
 * @date       2023-04-09
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONFIG_DETAIL_SYSTEM__5_WASM_PART_HPP
#define KERBAL_CONFIG_DETAIL_SYSTEM__5_WASM_PART_HPP

#include <kerbal/config/compiler_id.hpp>


#if (KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU) || (KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_CLANG)

#	if defined(__wasm__)
#		if defined(KERBAL_SYSTEM) && KERBAL_SYSTEM != KERBAL_SYSTEM_WASM
#			warning "Macro KERBAL_SYSTEM has defined!"
#		else
#			define KERBAL_SYSTEM KERBAL_SYSTEM_WASM
#		endif
#	endif

#endif


#endif // KERBAL_CONFIG_DETAIL_SYSTEM__5_WASM_PART_HPP
