/**
 * @file       _2_msvc.part.hpp
 * @brief
 * @date       2021-04-23
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONFIG_DETAIL_COMPILER_PRIVATE__2_MSVC_PART_HPP
#define KERBAL_CONFIG_DETAIL_COMPILER_PRIVATE__2_MSVC_PART_HPP

#include <kerbal/config/compiler_id.hpp>

#if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_MSVC
#	include <kerbal/config/detail/unexpected_compiler_error.part.hpp>
#endif



//===============
// Compiler Version

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
	( \
		KERBAL_MSVC_MAJOR == (major) && \
		( \
			KERBAL_MSVC_MINOR > (minor) || \
			( \
				KERBAL_MSVC_MINOR == (minor) && \
				KERBAL_MSVC_PATCHLEVEL >= (patchlevel) \
			) \
		) \
	) \
)
#endif // KERBAL_MSVC_VERSION_MEETS


#endif // KERBAL_CONFIG_DETAIL_COMPILER_PRIVATE__2_MSVC_PART_HPP
