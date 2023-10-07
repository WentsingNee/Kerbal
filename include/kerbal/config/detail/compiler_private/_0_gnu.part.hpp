/**
 * @file       _0_gnu.part.hpp
 * @brief
 * @date       2021-04-23
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONFIG_DETAIL_COMPILER_PRIVATE__0_GNU_PART_HPP
#define KERBAL_CONFIG_DETAIL_COMPILER_PRIVATE__0_GNU_PART_HPP

#include <kerbal/config/compiler_id.hpp>

#if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_GNU
#	include <kerbal/config/detail/unexpected_compiler_error.part.hpp>
#endif



//===============
// Compiler Version

#ifndef KERBAL_GNU_MAJOR
#	define KERBAL_GNU_MAJOR        __GNUC__
#endif

#ifndef KERBAL_GNU_MINOR
#	define KERBAL_GNU_MINOR        __GNUC_MINOR__
#endif

#ifndef KERBAL_GNU_PATCHLEVEL
#	define KERBAL_GNU_PATCHLEVEL   __GNUC_PATCHLEVEL__
#endif

#ifndef KERBAL_GNU_VERSION
#	define KERBAL_GNU_VERSION      __VERSION__
#endif

#ifndef KERBAL_GNU_VERSION_MEETS
#define KERBAL_GNU_VERSION_MEETS(major, minor, patchlevel) \
( \
	KERBAL_GNU_MAJOR > (major) || \
	(KERBAL_GNU_MAJOR == (major) && \
		(KERBAL_GNU_MINOR > (minor) || \
		(KERBAL_GNU_MINOR == (minor) && \
			KERBAL_GNU_PATCHLEVEL >= (patchlevel) \
		) \
		) \
	) \
)
#endif // KERBAL_GNU_VERSION_MEETS



//===============
// has_builtin (since gcc10)
//
// https://gcc.gnu.org/onlinedocs/gcc-10.1.0/cpp/_005f_005fhas_005fbuiltin.html#g_t_005f_005fhas_005fbuiltin

#ifdef __has_builtin
#	define KERBAL_GNU_PRIVATE_HAS_BUILTIN(x) __has_builtin(x)
#else
#	define KERBAL_GNU_PRIVATE_HAS_BUILTIN(x) 0
#endif


#endif // KERBAL_CONFIG_DETAIL_COMPILER_PRIVATE__0_GNU_PART_HPP
