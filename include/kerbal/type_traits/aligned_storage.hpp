/*
 * aligned_storage.hpp
 *
 *  Created on: 2019年4月19日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_TYPE_TRAITS_ALIGNED_STORAGE_HPP_
#define INCLUDE_KERBAL_TYPE_TRAITS_ALIGNED_STORAGE_HPP_

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

		template <std::size_t _Len, std::size_t _Align>
		struct aligned_storage: public std::aligned_storage<_Len, _Align>
		{
		};

#else

		template <std::size_t _Len, std::size_t _Align>
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

#endif /* INCLUDE_KERBAL_TYPE_TRAITS_ALIGNED_STORAGE_HPP_ */
