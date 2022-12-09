/**
 * @file       bitarray.sse2.hpp
 * @brief
 * @date       2022-11-12
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_NUMERIC_BIT_BITARRAY_BITARRAY_SSE2_HPP
#define KERBAL_NUMERIC_BIT_BITARRAY_BITARRAY_SSE2_HPP

#include <kerbal/compatibility/alignof.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/smath/max_sa_sb.hpp>
#include <kerbal/type_traits/aligned_storage.hpp>

#include <kerbal/numeric/bit/bitarray/bitarray.plain.hpp>

#include <emmintrin.h> // SSE2
//#include <immintrin.h> // SSE2, _mm_storeu_si64, _mm_loadu_si64


namespace kerbal
{

	namespace numeric
	{

		namespace detail
		{

			namespace sse2
			{

				inline
				kerbal::numeric::bitarray_result<kerbal::compatibility::uint8_t>::type
				bitarray(kerbal::compatibility::uint8_t x)
				{
					typedef kerbal::compatibility::uint8_t T;
					typedef kerbal::compatibility::uint64_t uint64_t;
					typedef typename kerbal::numeric::bitarray_result<T>::type bitarray_result_t;

					uint64_t u = x * 0x0101010101010101ull;
					u &= 0x0102040810204080ull;
					__m128i xmm_x = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(&u)); // SSE2
					xmm_x = _mm_min_epu8(xmm_x, _mm_set1_epi8(1)); // SSE2
					_mm_storel_epi64(reinterpret_cast<__m128i *>(&u), xmm_x); // SSE2

					kerbal::type_traits::aligned_storage<
							sizeof(bitarray_result_t),
							kerbal::smath::max_sa_sb<std::size_t, KERBAL_ALIGNOF(bitarray_result_t), KERBAL_ALIGNOF(uint64_t)>::value
					>::type as;
					reinterpret_cast<uint64_t &>(as) = u;
					return reinterpret_cast<const bitarray_result_t &>(as);
				}

				inline
				kerbal::numeric::bitarray_result<kerbal::compatibility::uint8_t>::type
				bitarray_old(kerbal::compatibility::uint8_t x)
				{
					typedef kerbal::compatibility::uint8_t T;
					typedef kerbal::compatibility::uint64_t uint64_t;
					typedef typename kerbal::numeric::bitarray_result<T>::type bitarray_result_t;

					__m128i const xmm_andmask = _mm_setr_epi8(
							static_cast<char>(1u << 7), 1u << 6, 1u << 5, 1u << 4,
							1u << 3, 1u << 2, 1u << 1, 1u << 0,
							0, 0, 0, 0, 0, 0, 0, 0
					); // SSE2
					__m128i const xmm_ALL_ONE = _mm_set1_epi8(1);

//					__m128i xmm_x = _mm_set1_epi8(static_cast<char>(x)); // SSE2

					__m128i xmm_x = _mm_cvtsi32_si128(x * 0x0101);
					xmm_x = _mm_shufflelo_epi16(xmm_x, 0);

					xmm_x = _mm_and_si128(xmm_x, xmm_andmask); // SSE2
					xmm_x = _mm_min_epu8(xmm_x, xmm_ALL_ONE); // SSE2

					kerbal::type_traits::aligned_storage<
							sizeof(bitarray_result_t),
							kerbal::smath::max_sa_sb<std::size_t, KERBAL_ALIGNOF(bitarray_result_t), KERBAL_ALIGNOF(uint64_t)>::value
					>::type as;
					_mm_storel_epi64(reinterpret_cast<__m128i *>(&as), xmm_x); // SSE2
					return reinterpret_cast<const bitarray_result_t &>(as);
				}

				inline
				kerbal::numeric::bitarray_result<kerbal::compatibility::uint16_t>::type
				bitarray(kerbal::compatibility::uint16_t x)
				{
					typedef kerbal::compatibility::uint16_t T;
					typedef kerbal::compatibility::uint64_t uint64_t;
					typedef typename kerbal::numeric::bitarray_result<T>::type bitarray_result_t;

					__m128i const xmm_andmask = _mm_setr_epi8(
							static_cast<char>(1u << 7), 1u << 6, 1u << 5, 1u << 4,
							1u << 3, 1u << 2, 1u << 1, 1u << 0,
							static_cast<char>(1u << 7), 1u << 6, 1u << 5, 1u << 4,
							1u << 3, 1u << 2, 1u << 1, 1u << 0
					); // SSE2
					__m128i const xmm_ALL_ONE = _mm_set1_epi8(1);

					kerbal::type_traits::aligned_storage<
							sizeof(bitarray_result_t),
							kerbal::smath::max_sa_sb<std::size_t, KERBAL_ALIGNOF(bitarray_result_t), KERBAL_ALIGNOF(uint64_t)>::value
					>::type as;

					uint64_t u = ((static_cast<uint64_t>(x & 0xFF00) << 24) | (x & 0xFF)) * 0x01010101u;
					__m128i xmm_x = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(&u)); // SSE2
					xmm_x = _mm_shuffle_epi32(xmm_x, 0x05); // SSE2, 0x5 = [00, 00, 01, 01]
					xmm_x = _mm_and_si128(xmm_x, xmm_andmask); // SSE2
					xmm_x = _mm_min_epu8(xmm_x, xmm_ALL_ONE); // SSE2
					_mm_storeu_si128(reinterpret_cast<__m128i *>(&as), xmm_x); // SSE2
					return reinterpret_cast<const bitarray_result_t &>(as);
				}

				inline
				kerbal::numeric::bitarray_result<kerbal::compatibility::uint32_t>::type
				bitarray(kerbal::compatibility::uint32_t x)
				{
					typedef kerbal::compatibility::uint32_t T;
					typedef kerbal::compatibility::uint64_t uint64_t;
					typedef typename kerbal::numeric::bitarray_result<T>::type bitarray_result_t;

					__m128i const xmm_andmask = _mm_setr_epi8(
							static_cast<char>(1u << 7), 1u << 6, 1u << 5, 1u << 4,
							1u << 3, 1u << 2, 1u << 1, 1u << 0,
							static_cast<char>(1u << 7), 1u << 6, 1u << 5, 1u << 4,
							1u << 3, 1u << 2, 1u << 1, 1u << 0
					); // SSE2
					__m128i const xmm_ALL_ONE = _mm_set1_epi8(1);

					kerbal::type_traits::aligned_storage<
							sizeof(bitarray_result_t),
							kerbal::smath::max_sa_sb<std::size_t, KERBAL_ALIGNOF(bitarray_result_t), KERBAL_ALIGNOF(uint64_t)>::value
					>::type as;

					uint64_t u = ((static_cast<uint64_t>(x & 0xFF00) << 24) | (x & 0xFF)) * 0x01010101u;
					__m128i xmm_x = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(&u)); // SSE2
					xmm_x = _mm_shuffle_epi32(xmm_x, 0x05); // SSE2, 0x5 = [00, 00, 01, 01]
					xmm_x = _mm_and_si128(xmm_x, xmm_andmask); // SSE2
					xmm_x = _mm_min_epu8(xmm_x, xmm_ALL_ONE); // SSE2
					_mm_storeu_si128(reinterpret_cast<__m128i *>(&as) + 1, xmm_x); // SSE2

					x >>= 16;
					u = ((static_cast<uint64_t>(x & 0xFF00) << 24) | (x & 0xFF)) * 0x01010101u;
					xmm_x = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(&u)); // SSE2
					xmm_x = _mm_shuffle_epi32(xmm_x, 0x05); // SSE2, 0x5 = [00, 00, 01, 01]
					xmm_x = _mm_and_si128(xmm_x, xmm_andmask); // SSE2
					xmm_x = _mm_min_epu8(xmm_x, xmm_ALL_ONE); // SSE2
					_mm_storeu_si128(reinterpret_cast<__m128i *>(&as) + 0, xmm_x); // SSE2

					return reinterpret_cast<const bitarray_result_t &>(as);
				}


			} // namespace sse2

		} // namespace detail

	} // namespace numeric

} // namespace kerbal


#endif // KERBAL_NUMERIC_BIT_BITARRAY_BITARRAY_SSE2_HPP
