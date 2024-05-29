/**
 * @file       unused.hpp
 * @brief
 * @date       2022-01-21
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ATTRIBUTE_UNUSED_HPP
#define KERBAL_ATTRIBUTE_UNUSED_HPP

#if __cplusplus >= 201703L
#	define KERBAL_ATTRIBUTE_UNUSED [[maybe_unused]]
#else

#	include <kerbal/config/compiler_id.hpp>
#	include <kerbal/config/compiler_private.hpp>

#		if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU
#			if KERBAL_GNU_VERSION_MEETS(2, 95, 3) // https://gcc.gnu.org/onlinedocs/gcc-2.95.3/gcc_4.html#SEC90]
#				define KERBAL_ATTRIBUTE_UNUSED __attribute__((unused))
#			endif
#		endif

#		if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_CLANG

#			ifdef __has_cpp_attribute
#				if __has_cpp_attribute(gnu::unused) // https://clang.llvm.org/docs/LanguageExtensions.html#has-cpp-attribute
#					define KERBAL_ATTRIBUTE_UNUSED [[gnu::unused]]
#				endif
#			endif

#			ifndef KERBAL_ATTRIBUTE_UNUSED
#				ifdef __has_attribute
#					if __has_attribute(unused) // https://clang.llvm.org/docs/LanguageExtensions.html#has-cpp-attribute
#						define KERBAL_ATTRIBUTE_UNUSED __attribute__((unused))
#					endif
#				endif
#			endif

#		endif

#		if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC
#			define KERBAL_ATTRIBUTE_UNUSED __attribute__((unused))
#		endif

#endif


#	ifdef KERBAL_ATTRIBUTE_UNUSED
#		define KERBAL_HAS_ATTRIBUTE_UNUSED_SUPPORT 1
#	else
#		define KERBAL_ATTRIBUTE_UNUSED
#		define KERBAL_HAS_ATTRIBUTE_UNUSED_SUPPORT 0

#		if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_MSVC
#			warning "KERBAL_ATTRIBUTE_UNUSED is not supported"
#		endif

#	endif


#endif // KERBAL_ATTRIBUTE_UNUSED_HPP
