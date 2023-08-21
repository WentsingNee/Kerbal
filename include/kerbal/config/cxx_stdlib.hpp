/**
 * @file       cxx_stdlib.hpp
 * @brief
 * @date       2021-04-22
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONFIG_CXX_STDLIB_HPP
#define KERBAL_CONFIG_CXX_STDLIB_HPP


#ifndef KERBAL_CXX_STDLIB_UNKNOWN
#	define KERBAL_CXX_STDLIB_UNKNOWN -1
#endif

#ifndef KERBAL_CXX_STDLIB_LIBSTDCXX
#	define KERBAL_CXX_STDLIB_LIBSTDCXX 0
#endif

#ifndef KERBAL_CXX_STDLIB_LIBCXX
#	define KERBAL_CXX_STDLIB_LIBCXX 1
#endif

#ifndef KERBAL_CXX_STDLIB_MSVC
#	define KERBAL_CXX_STDLIB_MSVC 2
#endif



#ifndef KERBAL_CXX_STDLIB

#	include <kerbal/config/detail/cxx_stdlib/_0_libstdcxx.part.hpp>
#	include <kerbal/config/detail/cxx_stdlib/_1_libcxx.part.hpp>
#	include <kerbal/config/detail/cxx_stdlib/_2_msvc.part.hpp>


#	ifndef KERBAL_CXX_STDLIB

#		define KERBAL_CXX_STDLIB KERBAL_CXX_STDLIB_UNKNOWN

#		if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC
#			pragma message ("Kerbal Warning: " "Unknown C++ stdlib")
#		else
#			warning "Kerbal Warning: " "Unknown C++ stdlib"
#		endif

#	endif

#endif


#endif // KERBAL_CONFIG_CXX_STDLIB_HPP
