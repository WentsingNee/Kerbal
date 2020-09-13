/**
 * @file       compiler_version.hpp
 * @brief
 * @date       2020-09-10
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONFIG_COMPILER_PRIVATE_CLANG_COMPILER_VERSION_HPP
#define KERBAL_CONFIG_COMPILER_PRIVATE_CLANG_COMPILER_VERSION_HPP

#include <kerbal/config/compiler_id.hpp>

#if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_CLANG
#	include <kerbal/config/detail/unexpected_compiler_error.hpp>
#endif


#ifndef KERBAL_CLANG_MAJOR
#	define KERBAL_CLANG_MAJOR        __clang_major__
#endif

#ifndef KERBAL_CLANG_MINOR
#	define KERBAL_CLANG_MINOR        __clang_minor__
#endif

#ifndef KERBAL_CLANG_PATCHLEVEL
#	define KERBAL_CLANG_PATCHLEVEL   __clang_patchlevel__
#endif

#ifndef KERBAL_CLANG_VERSION
#	define KERBAL_CLANG_VERSION      __clang_version__
#endif

#ifndef KERBAL_CLANG_VERSION_MEETS
#define KERBAL_CLANG_VERSION_MEETS(major, minor, patchlevel) \
( \
	KERBAL_CLANG_MAJOR > (major) || \
	(KERBAL_CLANG_MAJOR == (major) && \
		(KERBAL_CLANG_MINOR > (minor) || \
		(KERBAL_CLANG_MINOR == (minor) && \
			KERBAL_CLANG_PATCHLEVEL >= (patchlevel) \
		) \
		) \
	)\
)
#endif // KERBAL_CLANG_VERSION_MEETS


#endif // KERBAL_CONFIG_COMPILER_PRIVATE_CLANG_COMPILER_VERSION_HPP
