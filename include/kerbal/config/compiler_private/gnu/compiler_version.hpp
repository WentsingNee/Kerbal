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

#ifndef KERBAL_CONFIG_COMPILER_PRIVATE_GNU_COMPILER_VERSION_HPP
#define KERBAL_CONFIG_COMPILER_PRIVATE_GNU_COMPILER_VERSION_HPP

#include <kerbal/config/compiler_id.hpp>

#if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_GNU
#	include <kerbal/config/detail/unexpected_compiler_error.hpp>
#endif


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
	)\
)
#endif // KERBAL_GNU_VERSION_MEETS


#endif // KERBAL_CONFIG_COMPILER_PRIVATE_GNU_COMPILER_VERSION_HPP
