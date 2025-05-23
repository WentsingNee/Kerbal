/**
 * @file       compiler_id.hpp
 * @brief
 * @date       2020-07-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONFIG_COMPILER_ID_HPP
#define KERBAL_CONFIG_COMPILER_ID_HPP


#ifndef KERBAL_COMPILER_ID_UNKNOWN
#	define KERBAL_COMPILER_ID_UNKNOWN -1
#endif

#ifndef KERBAL_COMPILER_ID_GNU
#	define KERBAL_COMPILER_ID_GNU 0
#endif

#ifndef KERBAL_COMPILER_ID_CLANG
#	define KERBAL_COMPILER_ID_CLANG 1
#endif

#ifndef KERBAL_COMPILER_ID_MSVC
#	define KERBAL_COMPILER_ID_MSVC 2
#endif

#ifndef KERBAL_COMPILER_ID_ICC
#	define KERBAL_COMPILER_ID_ICC 3
#endif

#ifndef KERBAL_COMPILER_ID_NVCC
#	define KERBAL_COMPILER_ID_NVCC 4
#endif



#ifndef KERBAL_COMPILER_ID

#	include <kerbal/config/detail/compiler_id/_0_gnu.part.hpp>
#	include <kerbal/config/detail/compiler_id/_1_clang.part.hpp>
#	include <kerbal/config/detail/compiler_id/_2_msvc.part.hpp>
#	include <kerbal/config/detail/compiler_id/_3_icc.part.hpp>
#	include <kerbal/config/detail/compiler_id/_4_nvcc.part.hpp>


#	ifndef KERBAL_COMPILER_ID

#		define KERBAL_COMPILER_ID KERBAL_COMPILER_ID_UNKNOWN

#		pragma message ("Kerbal Warning: " "Unknown compiler")
#		warning "Kerbal Warning: " "Unknown compiler"

#	endif

#endif


#endif // KERBAL_CONFIG_COMPILER_ID_HPP
