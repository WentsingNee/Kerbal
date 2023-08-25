/**
 * @file       sse.hpp
 * @brief
 * @date       sse.hpp
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_SIMD_SSE_HPP
#define KERBAL_SIMD_SSE_HPP

#include <emmintrin.h>

namespace kerbal
{

	namespace simd
	{

		namespace sse
		{

			template <typename T>
			struct m128_t;

			template <> struct m128_t<char>    { typedef __m128i type; };
			template <> struct m128_t<short>   { typedef __m128i type; };
			template <> struct m128_t<int>     { typedef __m128i type; };
			template <> struct m128_t<__int64> { typedef __m128i type; };
			template <> struct m128_t<float>   { typedef __m128 type; };
			template <> struct m128_t<double>  { typedef __m128d type; };


#	if __SSE2__

			inline m128_t<char>::type _mm_set1(char a)
			{
				return _mm_set1_epi8(a);
			}

			inline m128_t<short>::type _mm_set1(short a)
			{
				return _mm_set1_epi16(a);
			}

			inline m128_t<int>::type _mm_set1(int a)
			{
				return _mm_set1_epi32(a);
			}

			inline m128_t<__int64>::type _mm_set1(__int64 a)
			{
				return _mm_set1_epi64(a);
			}

			inline m128_t<double>::type _mm_set1(double a)
			{
				return _mm_set1_pd(a);
			}

#	endif // SSE2

			inline m128_t<float>::type _mm_set1(float a)
			{
				return _mm_set1_ps(a);
			}

		} // namespace sse

	} // namespace simd

} // namespace kerbal

#endif // KERBAL_SIMD_SSE_HPP
