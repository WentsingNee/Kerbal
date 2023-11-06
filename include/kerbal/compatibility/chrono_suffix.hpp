/**
 * @file       chrono_suffix.hpp
 * @brief
 * @date       2018-7-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COMPATIBILITY_CHRONO_SUFFIX_HPP
#define KERBAL_COMPATIBILITY_CHRONO_SUFFIX_HPP

#if __cplusplus >= 201103L

#include <kerbal/config/compiler_id.hpp>

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU
#		include <kerbal/config/compiler_private.hpp>
#		if KERBAL_GNU_VERSION_MEETS(5, 0, 0)
#			define KERBAL_HAS_COMPATIBILITY_CHRONO_SUFFIX_SUPPORT 1
#		endif
#	else
#		define KERBAL_HAS_COMPATIBILITY_CHRONO_SUFFIX_SUPPORT 1
#	endif

#endif

#if KERBAL_HAS_COMPATIBILITY_CHRONO_SUFFIX_SUPPORT
#	include <kerbal/compatibility/chrono_suffix/detail/chrono_suffix.cxx11.part.hpp>
#endif

#endif // KERBAL_COMPATIBILITY_CHRONO_SUFFIX_HPP
