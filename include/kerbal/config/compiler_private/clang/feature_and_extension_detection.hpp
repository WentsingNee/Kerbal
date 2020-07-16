/**
 * @file       feature_and_extension_detection.hpp
 * @brief
 * @date       2020-07-15
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONFIG_COMPILER_PRIVATE_CLANG_FEATURE_AND_EXTENSION_DETECTION_HPP
#define KERBAL_CONFIG_COMPILER_PRIVATE_CLANG_FEATURE_AND_EXTENSION_DETECTION_HPP

#include <kerbal/config/compiler_id.hpp>

#if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_CLANG
#	error "KERBAL_COMPILER_ID doesn't match requirement!"
#endif

// https://clang.llvm.org/docs/LanguageExtensions.html#has-feature-and-has-extension

#ifdef __has_feature                             // Optional of course.
#	define KERBAL_CLANG_PRIVATE_HAS_FEATURE(x)   __has_feature(x)
#else
#	define KERBAL_CLANG_PRIVATE_HAS_FEATURE(x)   0
#endif

#ifdef __has_extension
#	define KERBAL_CLANG_PRIVATE_HAS_EXTENSION(x) __has_extension(x)
#else
#	define KERBAL_CLANG_PRIVATE_HAS_EXTENSION(x) __has_feature(x) // Compatibility with pre-3.0 compilers.
#endif

#endif // KERBAL_CONFIG_COMPILER_PRIVATE_CLANG_FEATURE_AND_EXTENSION_DETECTION_HPP
