/**
 * @file       _3_icc.hpp
 * @brief
 * @date       2021-04-23
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONFIG_COMPILER_PRIVATE__3_ICC_HPP
#define KERBAL_CONFIG_COMPILER_PRIVATE__3_ICC_HPP

#include <kerbal/config/compiler_id.hpp>

#if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_ICC
#	include <kerbal/config/detail/unexpected_compiler_error.hpp>
#endif



//===============
// Compiler Version

// https://software.intel.com/content/www/us/en/develop/documentation/cpp-compiler-developer-guide-and-reference/top/compiler-reference/macros/additional-predefined-macros.html

#ifndef KERBAL_ICC_MAJOR
#	define KERBAL_ICC_MAJOR        (__INTEL_COMPILER)
#endif

#ifndef KERBAL_ICC_MINOR
#	define KERBAL_ICC_MINOR        (__INTEL_COMPILER_UPDATE)
#endif

#ifndef KERBAL_ICC_PATCHLEVEL
#	define KERBAL_ICC_PATCHLEVEL   0
#endif

#ifndef KERBAL_ICC_VERSION
#	define KERBAL_ICC_VERSION      __VERSION__
#endif

#ifndef KERBAL_ICC_VERSION_MEETS
#define KERBAL_ICC_VERSION_MEETS(major, minor, patchlevel) \
( \
	KERBAL_ICC_MAJOR > (major) || \
	(KERBAL_ICC_MAJOR == (major) && \
		(KERBAL_ICC_MINOR > (minor) || \
		(KERBAL_ICC_MINOR == (minor) && \
			KERBAL_ICC_PATCHLEVEL >= (patchlevel) \
		) \
		) \
	) \
)
#endif // KERBAL_ICC_VERSION_MEETS



//===============
// has_builtin

#ifdef __has_builtin
#	define KERBAL_ICC_PRIVATE_HAS_BUILTIN(x) __has_builtin(x)
#else
#	define KERBAL_ICC_PRIVATE_HAS_BUILTIN(x) 0
#endif



//===============
// has_feature

#ifdef __has_feature                             // Optional of course.
#	define KERBAL_ICC_PRIVATE_HAS_FEATURE(x)   __has_feature(x)
#else
#	define KERBAL_ICC_PRIVATE_HAS_FEATURE(x)   0
#endif


#endif // KERBAL_CONFIG_COMPILER_PRIVATE__3_ICC_HPP
