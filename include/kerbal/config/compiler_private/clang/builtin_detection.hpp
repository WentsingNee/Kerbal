/**
 * @file       builtin_detection.hpp
 * @brief
 * @date       2020-07-19
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONFIG_COMPILER_PRIVATE_CLANG_BUILTIN_DETECTION_HPP
#define KERBAL_CONFIG_COMPILER_PRIVATE_CLANG_BUILTIN_DETECTION_HPP

#include <kerbal/config/compiler_id.hpp>

#if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_CLANG
#	include <kerbal/config/detail/unexpected_compiler_error.hpp>
#endif

// https://clang.llvm.org/docs/LanguageExtensions.html#feature-checking-macros

#if defined __has_builtin
#	define KERBAL_CLANG_PRIVATE_HAS_BUILTIN(x) __has_builtin(x)
#else
#	define KERBAL_CLANG_PRIVATE_HAS_BUILTIN(x) 0
#endif

#endif // KERBAL_CONFIG_COMPILER_PRIVATE_CLANG_BUILTIN_DETECTION_HPP
