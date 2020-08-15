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

#ifndef KERBAL_CONFIG_COMPILER_PRIVATE_GNU_BUILTIN_DETECTION_HPP
#define KERBAL_CONFIG_COMPILER_PRIVATE_GNU_BUILTIN_DETECTION_HPP

#include <kerbal/config/compiler_id.hpp>

#if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_GNU
#	error "KERBAL_COMPILER_ID doesn't match requirement!"
#endif

// https://gcc.gnu.org/onlinedocs/cpp/_005f_005fhas_005fbuiltin.html#g_t_005f_005fhas_005fbuiltin

#if defined __has_builtin
#	define KERBAL_GNU_PRIVATE_HAS_BUILTIN(x) __has_builtin(x)
#else
#	define KERBAL_GNU_PRIVATE_HAS_BUILTIN(x) 0
#endif

#endif // KERBAL_CONFIG_COMPILER_PRIVATE_GNU_BUILTIN_DETECTION_HPP
