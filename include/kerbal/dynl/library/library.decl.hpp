/**
 * @file       library.decl.hpp
 * @brief
 * @date       2024-09-15
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_DYNL_LIBRARY_LIBRARY_DECL_HPP
#define KERBAL_DYNL_LIBRARY_LIBRARY_DECL_HPP

#include <kerbal/dynl/library/library.fwd.hpp>

#include <kerbal/config/system.hpp>

#if ( \
	KERBAL_SYSTEM == KERBAL_SYSTEM_LINUX || \
	KERBAL_SYSTEM == KERBAL_SYSTEM_APPLE || \
	KERBAL_SYSTEM == KERBAL_SYSTEM_ANDROID \
)
#	include <kerbal/dynl/library/detail/unix/library.decl.unix.part.hpp>
#endif

#endif // KERBAL_DYNL_LIBRARY_LIBRARY_DECL_HPP
