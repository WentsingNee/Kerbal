/**
 * @file       _3_apple.hpp
 * @brief
 * @date       2021-05-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONFIG_SYSTEM__3_APPLE_HPP
#define KERBAL_CONFIG_SYSTEM__3_APPLE_HPP

#include <kerbal/config/compiler_id.hpp>


#if (KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU) || \
	(KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_CLANG) || \
	(KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC)

#	if defined(__APPLE__)
#		if defined(KERBAL_SYSTEM) && KERBAL_SYSTEM != KERBAL_SYSTEM_APPLE
#			warning "Macro KERBAL_SYSTEM has defined!"
#		else
#			define KERBAL_SYSTEM KERBAL_SYSTEM_APPLE
#		endif
#	endif

#endif


#endif // KERBAL_CONFIG_SYSTEM__3_APPLE_HPP
