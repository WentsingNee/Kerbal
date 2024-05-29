/**
 * @file       unreachable.hpp
 * @brief
 * @date       2022-03-30
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COMPATIBILITY_UNREACHABLE_HPP
#define KERBAL_COMPATIBILITY_UNREACHABLE_HPP

#include <kerbal/config/compiler_id.hpp>
#include <kerbal/config/compiler_private.hpp>

#include <kerbal/compatibility/noexcept.hpp>


#ifndef KERBAL_PRIVATE_HAS_BUILTIN_UNREACHABLE

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU

#		if KERBAL_GNU_PRIVATE_HAS_BUILTIN(__builtin_unreachable)
#			define KERBAL_PRIVATE_HAS_BUILTIN_UNREACHABLE 1
#			define KERBAL_BUILTIN_UNREACHABLE() __builtin_unreachable()
#		endif

#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_CLANG

#		if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__builtin_unreachable)
#			define KERBAL_PRIVATE_HAS_BUILTIN_UNREACHABLE 1
#			define KERBAL_BUILTIN_UNREACHABLE() __builtin_unreachable()
#		endif

#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC

#		if KERBAL_ICC_PRIVATE_HAS_BUILTIN(__builtin_unreachable)
#			define KERBAL_PRIVATE_HAS_BUILTIN_UNREACHABLE 1
#			define KERBAL_BUILTIN_UNREACHABLE() __builtin_unreachable()
#		endif

#	endif

#endif


#if !KERBAL_PRIVATE_HAS_BUILTIN_UNREACHABLE
#	if __cplusplus > 202002L
#		include <utility>
#	endif
#endif


namespace kerbal
{

	namespace compatibility
	{

#if KERBAL_PRIVATE_HAS_BUILTIN_UNREACHABLE

		inline
		void unreachable() KERBAL_NOEXCEPT
		{
			KERBAL_BUILTIN_UNREACHABLE();
		}

#else

#	if __cpp_lib_unreachable >= 202202L

		inline
		void unreachable()
		{
			std::unreachable();
		}

#	else

		inline
		void unreachable() KERBAL_NOEXCEPT
		{
		}

#	endif

#endif

	} // namespace compatibility

} // namespace kerbal

#endif // KERBAL_COMPATIBILITY_UNREACHABLE_HPP
