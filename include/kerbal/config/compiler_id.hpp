/**
 * @file       compiler_id.hpp
 * @brief
 * @date       2020-07-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONFIG_COMPILER_ID_HPP
#define KERBAL_CONFIG_COMPILER_ID_HPP


#ifndef KERBAL_COMPILER_ID_UNKNOWN
#	define KERBAL_COMPILER_ID_UNKNOWN -1
#endif

#ifndef KERBAL_COMPILER_ID_GNU
#	define KERBAL_COMPILER_ID_GNU 0
#endif

#ifndef KERBAL_COMPILER_ID_CLANG
#	define KERBAL_COMPILER_ID_CLANG 1
#endif

#ifndef KERBAL_COMPILER_ID_MSVC
#	define KERBAL_COMPILER_ID_MSVC 2
#endif

#ifndef KERBAL_COMPILER_ID_ICC
#	define KERBAL_COMPILER_ID_ICC 3
#endif



#ifndef KERBAL_COMPILER_ID

#	if defined(__GNUC__) && !defined(__clang__) && !defined(__ICC) && !defined(__ICL)
#		if defined(KERBAL_COMPILER_ID) && KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_GNU
#			warning "Macro KERBAL_COMPILER_ID has defined!"
#		else
#			define KERBAL_COMPILER_ID KERBAL_COMPILER_ID_GNU
#		endif
#	endif

#	if defined(__clang__)
#		if defined(KERBAL_COMPILER_ID) && KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_CLANG
#			warning "Macro KERBAL_COMPILER_ID has defined!"
#		else
#			define KERBAL_COMPILER_ID KERBAL_COMPILER_ID_CLANG
#		endif
#	endif

#	if defined(_MSC_VER)
#		if defined(KERBAL_COMPILER_ID) && KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_MSVC
#			warning "Macro KERBAL_COMPILER_ID has defined!"
#		else
#			define KERBAL_COMPILER_ID KERBAL_COMPILER_ID_MSVC
#		endif
#	endif

#	if defined(__ICC) || defined(__ICL) // __ICC (Linux , macOS* ), __ICL (Windows)
#		if defined(KERBAL_COMPILER_ID) && KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_ICC
#			warning "Macro KERBAL_COMPILER_ID has defined!"
#		else
#			define KERBAL_COMPILER_ID KERBAL_COMPILER_ID_ICC
#		endif
#	endif

#	ifndef KERBAL_COMPILER_ID
#		define KERBAL_COMPILER_ID KERBAL_COMPILER_ID_UNKNOWN
#	endif

#endif


#endif // KERBAL_CONFIG_COMPILER_ID_HPP
