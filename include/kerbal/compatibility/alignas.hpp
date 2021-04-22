/**
 * @file       alignas.hpp
 * @brief
 * @date       2020-07-15
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COMPATIBILITY_ALIGNAS_HPP
#define KERBAL_COMPATIBILITY_ALIGNAS_HPP

#include <kerbal/config/compiler_id.hpp>
#include <kerbal/config/compiler_private.hpp>


#ifndef KERBAL_ALIGNAS

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU

#		if __cplusplus >= 201103L && KERBAL_GNU_VERSION_MEETS(4, 8, 0) // https://gcc.gnu.org/projects/cxx-status.html#cxx11
#			define KERBAL_ALIGNAS(alignment) alignas(alignment)
#		elif KERBAL_GNU_VERSION_MEETS(3, 0, 4) // https://gcc.gnu.org/onlinedocs/gcc-3.0.4/gcc/Variable-Attributes.html#Variable%20Attributes
#			define KERBAL_ALIGNAS(alignment) __attribute__((aligned(alignment)))
#		endif

#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_CLANG

// https://clang.llvm.org/docs/LanguageExtensions.html#c-11-alignment-specifiers

#		if __cplusplus >= 201103L && KERBAL_CLANG_PRIVATE_HAS_FEATURE(cxx_alignas)
#			define KERBAL_ALIGNAS(alignment) alignas(alignment)
#		elif KERBAL_CLANG_PRIVATE_HAS_EXTENSION(cxx_alignas)
#			define KERBAL_ALIGNAS(alignment) alignas(alignment)
#		elif defined(__GNUC__)
#			define KERBAL_ALIGNAS(alignment) __attribute__((aligned(alignment)))
#		endif

#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC

// https://docs.microsoft.com/zh-cn/cpp/preprocessor/predefined-macros?view=vs-2019
// https://docs.microsoft.com/en-us/previous-versions/visualstudio/

#		if __cplusplus >= 201103L && KERBAL_MSVC_VERSION_MEETS(19, 0, 0) // VS2015
#			define KERBAL_ALIGNAS(alignment) alignas(alignment)
#		elif KERBAL_MSVC_VERSION_MEETS(13, 10, 0) // VS2003
#			define KERBAL_ALIGNAS(alignment) __declspec(align(alignment))
#		endif

#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC

// https://software.intel.com/content/www/us/en/develop/articles/c0x-features-supported-by-intel-c-compiler.html

#		if __cplusplus >= 201103L && KERBAL_ICC_VERSION_MEETS(15, 0, 0)
#			define KERBAL_ALIGNAS(alignment) alignas(alignment)
#		elif KERBAL_ICC_VERSION_MEETS(19, 0, 0) && defined(__GNUC__)
#			define KERBAL_ALIGNAS(alignment) __attribute__((aligned (alignment)))
#		endif

#	endif

#endif

#undef KERBAL_ALIGNAS_SUPPORTED
#ifdef KERBAL_ALIGNAS
#	define KERBAL_ALIGNAS_SUPPORTED 1
#else

#	define KERBAL_ALIGNAS_SUPPORTED 0

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC
#		pragma message ("Kerbal Warning: " "KERBAL_ALIGNAS is not supported")
#	else
#		warning "Kerbal Warning: " "KERBAL_ALIGNAS is not supported"
#	endif

#endif

#endif // KERBAL_COMPATIBILITY_ALIGNAS_HPP
