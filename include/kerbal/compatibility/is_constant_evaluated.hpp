/**
 * @file       is_constant_evaluated.hpp
 * @brief
 * @date       2021-1-1
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COMPATIBILITY_IS_CONSTANT_EVALUATED_HPP
#define KERBAL_COMPATIBILITY_IS_CONSTANT_EVALUATED_HPP

#include <kerbal/config/compiler_id.hpp>
#include <kerbal/config/compiler_private.hpp>


#ifndef KERBAL_SUPPORTS_IS_CONSTANT_EVALUATED

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU

#		if KERBAL_GNU_PRIVATE_HAS_BUILTIN(__builtin_is_constant_evaluated)
#			define KERBAL_SUPPORTS_IS_CONSTANT_EVALUATED 1
#			define KERBAL_IS_CONSTANT_EVALUATED() (__builtin_is_constant_evaluated())
#		endif

#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_CLANG

#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__builtin_is_constant_evaluated)
#			define KERBAL_SUPPORTS_IS_CONSTANT_EVALUATED 1
#			define KERBAL_IS_CONSTANT_EVALUATED() (__builtin_is_constant_evaluated())
#		endif

#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC

#		if KERBAL_MSVC_VERSION_MEETS(19, 25, 0) // vs2019
#			define KERBAL_SUPPORTS_IS_CONSTANT_EVALUATED 1
#			define KERBAL_IS_CONSTANT_EVALUATED() (__builtin_is_constant_evaluated())
#		endif

#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC

#		if KERBAL_ICC_PRIVATE_HAS_BUILTIN(__builtin_is_constant_evaluated)
#			define KERBAL_SUPPORTS_IS_CONSTANT_EVALUATED 1
#			define KERBAL_IS_CONSTANT_EVALUATED() (__builtin_is_constant_evaluated())
#		endif

#	endif


#	ifndef KERBAL_SUPPORTS_IS_CONSTANT_EVALUATED
#		if __cplusplus > 201703L
#			include <type_traits>
#			if __cpp_lib_is_constant_evaluated >= 201811L
#				define KERBAL_SUPPORTS_IS_CONSTANT_EVALUATED 1
#				define KERBAL_IS_CONSTANT_EVALUATED() (std::is_constant_evaluated())
#			endif
#		endif
#	endif


#	ifndef KERBAL_SUPPORTS_IS_CONSTANT_EVALUATED
#		define KERBAL_SUPPORTS_IS_CONSTANT_EVALUATED 0
#	endif

#else // ifdef KERBAL_SUPPORTS_IS_CONSTANT_EVALUATED

#	if KERBAL_SUPPORTS_IS_CONSTANT_EVALUATED

#		ifndef KERBAL_IS_CONSTANT_EVALUATED
#			error "Macro KERBAL_IS_CONSTANT_EVALUATED has not been defined yet!"
#		endif

#	endif

#endif


#endif // KERBAL_COMPATIBILITY_IS_CONSTANT_EVALUATED_HPP
