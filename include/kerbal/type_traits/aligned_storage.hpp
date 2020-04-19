/**
 * @file       aligned_storage.hpp
 * @brief
 * @date       2019-4-19
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_ALIGNED_STORAGE_HPP
#define KERBAL_TYPE_TRAITS_ALIGNED_STORAGE_HPP

#include <cstddef>

#if __cplusplus >= 201103L
#	include <type_traits>
#endif

#ifndef KERBAL_ALIGNOF
#	if __cplusplus >= 201103L
#		define KERBAL_ALIGNOF(T) (alignof(T))
#	else
#		if defined __clang__ && !defined(__ibmxl__) //  Clang C++ emulates GCC, so it has to appear early.
#			define KERBAL_ALIGNOF(T) (__alignof__(T))
#		elif defined(__GNUC__) && !defined(__ibmxl__) //  GNU C++:
#			define KERBAL_ALIGNOF(T) (__alignof__(T))
#		elif defined _MSC_VER //  Microsoft Visual C++
			// Must remain the last #elif since some other vendors (Metrowerks, for
			// example) also #define _MSC_VER
#			define KERBAL_ALIGNOF(T) (__alignof(T))
#		endif
#	endif
#endif

namespace kerbal
{

	namespace type_traits
	{

#if __cplusplus >= 201103L

		template <size_t _Len, size_t _Align>
		struct aligned_storage: public std::aligned_storage<_Len, _Align>
		{
		};

#else

		template <size_t _Len, size_t _Align>
		struct aligned_storage
		{
			union type
			{
				unsigned char __data[_Len];
				struct __attribute__((__aligned__((_Align)))) {}__align;
			};
		};

#endif

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_ALIGNED_STORAGE_HPP
