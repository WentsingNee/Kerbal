/**
 * @file       storage.hpp
 * @brief
 * @date       2018-6-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_STORAGE_HPP
#define KERBAL_UTILITY_STORAGE_HPP

#if __cplusplus >= 201103L

#include <kerbal/config/compiler_id.hpp>

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU
#		include <kerbal/config/compiler_private.hpp>
#		if KERBAL_GNU_VERSION_MEETS(5, 0, 0)
#			define KERBAL_SUPPORTS_UTILITY_STORAGE 1
#		endif
#	else
#		define KERBAL_SUPPORTS_UTILITY_STORAGE 1
#	endif

#endif

#if KERBAL_SUPPORTS_UTILITY_STORAGE
#	include <kerbal/utility/storage/detail/storage.cxx11.part.hpp>
#endif

#endif // KERBAL_UTILITY_STORAGE_HPP
