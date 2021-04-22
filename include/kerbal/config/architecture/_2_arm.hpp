/**
 * @file       _2_arm.hpp
 * @brief
 * @date       2021-02-08
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONFIG_ARCHITECTURE__2_ARM_HPP
#define KERBAL_CONFIG_ARCHITECTURE__2_ARM_HPP

#include <kerbal/config/compiler_id.hpp>


#if (KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU) || (KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_CLANG)

#	if defined(__arm__)
#		if defined(KERBAL_ARCHITECTURE) && KERBAL_ARCHITECTURE != KERBAL_ARCHITECTURE_ARM
#			warning "Macro KERBAL_ARCHITECTURE has defined!"
#		else
#			define KERBAL_ARCHITECTURE KERBAL_ARCHITECTURE_ARM
#		endif
#	endif

#elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC

#	if defined(_M_ARM)
#		if defined(KERBAL_ARCHITECTURE) && KERBAL_ARCHITECTURE != KERBAL_ARCHITECTURE_ARM
#			pragma message ("Kerbal Warning: " "Macro KERBAL_ARCHITECTURE has defined!")
#		else
#			define KERBAL_ARCHITECTURE KERBAL_ARCHITECTURE_ARM
#		endif
#	endif

#endif


#endif // KERBAL_CONFIG_ARCHITECTURE__2_ARM_HPP
