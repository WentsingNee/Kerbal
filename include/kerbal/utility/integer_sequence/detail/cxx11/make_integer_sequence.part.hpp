/**
 * @file       make_integer_sequence.part.hpp
 * @brief
 * @date       2023-08-25
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_INTEGER_SEQUENCE_DETAIL_CXX11_MAKE_INTEGER_SEQUENCE_PART_HPP
#define KERBAL_UTILITY_INTEGER_SEQUENCE_DETAIL_CXX11_MAKE_INTEGER_SEQUENCE_PART_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

KERBAL_MODULE_GLOBAL


#include <kerbal/config/compiler_id.hpp>
#include <kerbal/config/compiler_private.hpp>

#include <cstddef>


KERBAL_EXPORT_MODULE_DECLARE(kerbal.utility.integer_sequence)


#if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU

//	https://gcc.gnu.org/onlinedocs/gcc-8.1.0/gcc/Type-Traits.html#Type-Traits
#	if KERBAL_GNU_VERSION_MEETS(8, 1, 0)
#		include <kerbal/utility/integer_sequence/detail/cxx11/make_integer_sequence/make_integer_sequence.integer_pack.part.hpp>
#	else
#		include <kerbal/utility/integer_sequence/detail/cxx11/make_integer_sequence/make_integer_sequence.default.part.hpp>
#	endif

#elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_CLANG

#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__make_integer_seq)
#		include <kerbal/utility/integer_sequence/detail/cxx11/make_integer_sequence/make_integer_sequence.make_integer_seq.part.hpp>
#	else
#		include <kerbal/utility/integer_sequence/detail/cxx11/make_integer_sequence/make_integer_sequence.default.part.hpp>
#	endif

#elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC

//	https://www.cnblogs.com/yamboo/p/14030418.html
#	if KERBAL_MSVC_VERSION_MEETS(19, 0, 0) // MSVC++ 14.0  _MSC_VER == 1900 (Visual Studio 2015 version 14.0)
#		include <kerbal/utility/integer_sequence/detail/cxx11/make_integer_sequence/make_integer_sequence.make_integer_seq.part.hpp>
#	else
#		include <kerbal/utility/integer_sequence/detail/cxx11/make_integer_sequence/make_integer_sequence.default.part.hpp>
#	endif


#elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC

#	if KERBAL_ICC_VERSION_MEETS(2021, 2, 0)
#		include <kerbal/utility/integer_sequence/detail/cxx11/make_integer_sequence/make_integer_sequence.integer_pack.part.hpp>
#	else
#		include <kerbal/utility/integer_sequence/detail/cxx11/make_integer_sequence/make_integer_sequence.default.part.hpp>
#	endif

#else

#	include <kerbal/utility/integer_sequence/detail/cxx11/make_integer_sequence/make_integer_sequence.default.part.hpp>

#endif

#endif // KERBAL_UTILITY_INTEGER_SEQUENCE_DETAIL_CXX11_MAKE_INTEGER_SEQUENCE_PART_HPP
