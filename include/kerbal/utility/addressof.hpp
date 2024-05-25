/**
 * @file       addressof.hpp
 * @brief      
 * @date       2019-7-13
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_ADDRESSOF_HPP
#define KERBAL_UTILITY_ADDRESSOF_HPP

#include <kerbal/config/compiler_id.hpp>
#include <kerbal/config/compiler_private.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>


#ifndef KERBAL_HAS_BUILTIN_ADDRESSOF_SUPPORT

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU

#		if KERBAL_GNU_PRIVATE_HAS_BUILTIN(__builtin_addressof)
#			define KERBAL_HAS_BUILTIN_ADDRESSOF_SUPPORT 1
#			define KERBAL_BUILTIN_ADDRESSOF(x) __builtin_addressof(x)
#		endif

#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_CLANG

#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__builtin_addressof)
#			define KERBAL_HAS_BUILTIN_ADDRESSOF_SUPPORT 1
#			define KERBAL_BUILTIN_ADDRESSOF(x) __builtin_addressof(x)
#		endif

#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC

#		if KERBAL_ICC_PRIVATE_HAS_BUILTIN(__builtin_addressof)
#			define KERBAL_HAS_BUILTIN_ADDRESSOF_SUPPORT 1
#			define KERBAL_BUILTIN_ADDRESSOF(x) __builtin_addressof(x)
#		endif

#	endif

#endif


#if !KERBAL_HAS_BUILTIN_ADDRESSOF_SUPPORT
#	if __cplusplus >= 201103L
#		include <memory>
#	endif
#endif


namespace kerbal
{

	namespace utility
	{

#	if KERBAL_HAS_BUILTIN_ADDRESSOF_SUPPORT

		template <typename T>
		KERBAL_CONSTEXPR
		T * addressof(T & arg) KERBAL_NOEXCEPT
		{
			return KERBAL_BUILTIN_ADDRESSOF(arg);
		}

#	else

		template <typename T>
#	if __cpp_lib_addressof_constexpr >= 201603L
		KERBAL_CONSTEXPR17
#	endif
		T * addressof(T & arg) KERBAL_NOEXCEPT
		{

#		if __cplusplus >= 201103L
			return std::addressof(arg);
#		else
			return
				static_cast<T *>(
					static_cast<void *>(
						&const_cast<char &>(
							(const volatile char &)(arg)
						)
					)
				);
#		endif

		}

#	endif


#	if __cplusplus >= 201103L

		template <typename T>
		const T * addressof(const T &&) = delete;

#	endif

	} // namespace utility

} // namespace kerbal

#endif // KERBAL_UTILITY_ADDRESSOF_HPP
