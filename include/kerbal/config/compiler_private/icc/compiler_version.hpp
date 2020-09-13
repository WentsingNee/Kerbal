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

#ifndef KERBAL_CONFIG_COMPILER_PRIVATE_ICC_COMPILER_VERSION_HPP
#define KERBAL_CONFIG_COMPILER_PRIVATE_ICC_COMPILER_VERSION_HPP

#include <kerbal/config/compiler_id.hpp>

#if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_ICC
#	include <kerbal/config/detail/unexpected_compiler_error.hpp>
#endif


#ifndef KERBAL_ICC_MAJOR
#	define KERBAL_ICC_MAJOR        (__INTEL_COMPILER / 100)
#endif

#ifndef KERBAL_ICC_MINOR
#	define KERBAL_ICC_MINOR        (__INTEL_COMPILER % 100)
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
	)\
)
#endif // KERBAL_ICC_VERSION_MEETS


#endif // KERBAL_CONFIG_COMPILER_PRIVATE_ICC_COMPILER_VERSION_HPP
