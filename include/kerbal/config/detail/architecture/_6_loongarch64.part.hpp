/**
 * @file       _6_loongarch64.part.hpp
 * @brief
 * @date       2024-04-19
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONFIG_DETAIL_ARCHITECTURE__6_LOONGARCH64_PART_HPP
#define KERBAL_CONFIG_DETAIL_ARCHITECTURE__6_LOONGARCH64_PART_HPP

#include <kerbal/config/compiler_id.hpp>


#if (KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU) || (KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_CLANG)

#	if defined(__loongarch64)
#		if defined(KERBAL_ARCHITECTURE) && KERBAL_ARCHITECTURE != KERBAL_ARCHITECTURE_LOONGARCH64
#			warning "Macro KERBAL_ARCHITECTURE has defined!"
#		else
#			define KERBAL_ARCHITECTURE KERBAL_ARCHITECTURE_LOONGARCH64
#		endif
#	endif

#endif


#endif // KERBAL_CONFIG_DETAIL_ARCHITECTURE__6_LOONGARCH64_PART_HPP
