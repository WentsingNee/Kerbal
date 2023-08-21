/**
 * @file       _1_clang.part.hpp
 * @brief
 * @date       2021-04-23
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONFIG_DETAIL_COMPILER_PRIVATE__1_CLANG_PART_HPP
#define KERBAL_CONFIG_DETAIL_COMPILER_PRIVATE__1_CLANG_PART_HPP

#include <kerbal/config/compiler_id.hpp>

#if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_CLANG
#	include <kerbal/config/detail/unexpected_compiler_error.part.hpp>
#endif



//===============
// Compiler Version

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
	) \
)
#endif // KERBAL_CLANG_VERSION_MEETS



//===============
// has_builtin
//
// https://clang.llvm.org/docs/LanguageExtensions.html#feature-checking-macros

#ifdef __has_builtin
#	define KERBAL_CLANG_PRIVATE_HAS_BUILTIN(x) __has_builtin(x)
#else
#	define KERBAL_CLANG_PRIVATE_HAS_BUILTIN(x) 0
#endif



//===============
// has_feature
//
// https://clang.llvm.org/docs/LanguageExtensions.html#has-feature-and-has-extension

#ifdef __has_feature                             // Optional of course.
#	define KERBAL_CLANG_PRIVATE_HAS_FEATURE(x)   __has_feature(x)
#else
#	define KERBAL_CLANG_PRIVATE_HAS_FEATURE(x)   0
#endif



//===============
// has_extension
//
// https://clang.llvm.org/docs/LanguageExtensions.html#has-feature-and-has-extension

#ifdef __has_extension
#	define KERBAL_CLANG_PRIVATE_HAS_EXTENSION(x) __has_extension(x)
#else
#	define KERBAL_CLANG_PRIVATE_HAS_EXTENSION(x) __has_feature(x) // Compatibility with pre-3.0 compilers.
#endif


#endif // KERBAL_CONFIG_DETAIL_COMPILER_PRIVATE__1_CLANG_PART_HPP
