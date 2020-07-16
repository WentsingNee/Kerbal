/**
 * @file       compiler_version.hpp
 * @brief
 * @date       2020-07-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONFIG_COMPILER_VERSION_HPP
#define KERBAL_CONFIG_COMPILER_VERSION_HPP

#include <kerbal/config/compiler_id.hpp>


#if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU

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

#elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_CLANG

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

#elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC

#ifndef KERBAL_MSVC_MAJOR
#	define KERBAL_MSVC_MAJOR        (_MSC_VER / 100)
#endif

#ifndef KERBAL_MSVC_MINOR
#	define KERBAL_MSVC_MINOR        (_MSC_VER % 100)
#endif

#ifndef KERBAL_MSVC_PATCHLEVEL
#	define KERBAL_MSVC_PATCHLEVEL   (_MSC_FULL_VER % 100000)
#endif

#ifndef KERBAL_MSVC_VERSION
#	define __KERBAL_MSVC_VERSION_HELPER(ver) #ver
#	define __KERBAL_MSVC_VERSION_HELPER2(ver) __KERBAL_MSVC_VERSION_HELPER(ver)
#	define KERBAL_MSVC_VERSION __KERBAL_MSVC_VERSION_HELPER2(_MSC_FULL_VER)
#endif

#ifndef KERBAL_MSVC_VERSION_MEETS
#define KERBAL_MSVC_VERSION_MEETS(major, minor, patchlevel) \
( \
	KERBAL_MSVC_MAJOR > (major) || \
	(KERBAL_MSVC_MAJOR == (major) && \
		(KERBAL_MSVC_MINOR > (minor) || \
		(KERBAL_MSVC_MINOR == (minor) && \
			KERBAL_MSVC_PATCHLEVEL >= (patchlevel) \
		) \
		) \
	)\
)
#endif // KERBAL_ICC_VERSION_MEETS

#elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC

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

#endif


#endif // KERBAL_CONFIG_COMPILER_VERSION_HPP
