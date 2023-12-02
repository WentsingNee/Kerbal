/**
 * @file       exceptions.hpp
 * @brief
 * @date       2023-12-02
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONFIG_EXCEPTIONS_HPP
#define KERBAL_CONFIG_EXCEPTIONS_HPP

#ifndef KERBAL_HAS_EXCEPTIONS_SUPPORT

#	ifdef __cpp_exceptions

#		if __cpp_exceptions
#			define KERBAL_HAS_EXCEPTIONS_SUPPORT 1
#		endif

#	else // ifdef __cpp_exceptions

#		include <kerbal/config/compiler_id.hpp>
#		include <kerbal/config/compiler_private.hpp>

#		if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU // g++4.8 doesn't define __cpp_exceptions in global
#			if !KERBAL_GNU_VERSION_MEETS(5, 0, 0)
#				ifdef __EXCEPTIONS
#					define KERBAL_HAS_EXCEPTIONS_SUPPORT 1
#				endif
#			endif
#		endif

#	endif // ifdef __cpp_exceptions

#	ifndef KERBAL_HAS_EXCEPTIONS_SUPPORT
#		define KERBAL_HAS_EXCEPTIONS_SUPPORT 0
#	endif

#endif // ifndef KERBAL_HAS_EXCEPTIONS_SUPPORT

#endif // KERBAL_CONFIG_EXCEPTIONS_HPP
