/**
 * @file       all_chunk.avx512f.hpp
 * @brief
 * @date       2022-11-11
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_BITSET_DETAIL_ALL_CHUNK_ALL_CHUNK_AVX512F_HPP
#define KERBAL_BITSET_DETAIL_ALL_CHUNK_ALL_CHUNK_AVX512F_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>

#include <immintrin.h>

#include <kerbal/bitset/detail/all_chunk/all_chunk.plain.hpp>


namespace kerbal
{

	namespace bitset
	{

		namespace detail
		{

			namespace avx512f
			{

				inline bool all_chunk(const kerbal::compatibility::uint32_t block[], std::size_t chunk_size) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint32_t Block;
					typedef kerbal::type_traits::integral_constant<Block, static_cast<Block>(~static_cast<Block>(0))> ALL_ONE;
					typedef kerbal::type_traits::integral_constant<std::size_t, 512 / 32> STEP;
					const __m512i zmm_ALL_ONE = _mm512_set1_epi32(static_cast<int>(ALL_ONE::value)); // AVX512F

					std::size_t i = 0;
					for (; i + 8 * STEP::value <= chunk_size; i += 8 * STEP::value) {
						__m512i zmm_blockp0 = _mm512_loadu_si512(&block[i + 0 * STEP::value]); // AVX512F
						__m512i zmm_blockp1 = _mm512_loadu_si512(&block[i + 1 * STEP::value]); // AVX512F
						__m512i zmm_blockp2 = _mm512_loadu_si512(&block[i + 2 * STEP::value]); // AVX512F
						__m512i zmm_blockp3 = _mm512_loadu_si512(&block[i + 3 * STEP::value]); // AVX512F
						__m512i zmm_blockp4 = _mm512_loadu_si512(&block[i + 4 * STEP::value]); // AVX512F
						__m512i zmm_blockp5 = _mm512_loadu_si512(&block[i + 5 * STEP::value]); // AVX512F
						__m512i zmm_blockp6 = _mm512_loadu_si512(&block[i + 6 * STEP::value]); // AVX512F
						__m512i zmm_blockp7 = _mm512_loadu_si512(&block[i + 7 * STEP::value]); // AVX512F

						zmm_blockp0 = _mm512_ternarylogic_epi32(zmm_blockp0, zmm_blockp1, zmm_blockp2, 128); // AVX512F, 128 = 0b10000000, a & b & c
						zmm_blockp0 = _mm512_ternarylogic_epi32(zmm_blockp0, zmm_blockp3, zmm_blockp4, 128); // AVX512F
						zmm_blockp0 = _mm512_ternarylogic_epi32(zmm_blockp0, zmm_blockp5, zmm_blockp6, 128); // AVX512F
						zmm_blockp0 = _mm512_and_si512(zmm_blockp0, zmm_blockp7); // AVX512F

						__mmask16 k_eq = _mm512_cmpeq_epi32_mask(zmm_blockp0, zmm_ALL_ONE); // AVX512F
						if (!_mm512_kortestc(k_eq, k_eq)) { // AVX512F
							return false;
						}
					}

					for (; i + STEP::value <= chunk_size; i += STEP::value) {
						__m512i zmm_block = _mm512_loadu_si512(&block[i]); // AVX512F
						__mmask16 k_eq = _mm512_cmpeq_epi32_mask(zmm_block, zmm_ALL_ONE); // AVX512F
						if (!_mm512_kortestc(k_eq, k_eq)) { // AVX512F
							return false;
						}
					}

					{
						__mmask16 k_mask = _cvtu32_mask16(~(~0u << (chunk_size - i))); // AVX512F

						__m512i zmm_block = _mm512_mask_loadu_epi32(zmm_ALL_ONE, k_mask, &block[i]); // AVX2
						__mmask16 k_eq = _mm512_cmpeq_epi32_mask(zmm_block, zmm_ALL_ONE); // AVX512F
						if (!_mm512_kortestc(k_eq, k_eq)) { // AVX512F
							return false;
						}
					}

					return true;
				}


				inline bool all_chunk(const kerbal::compatibility::uint64_t block[], std::size_t chunk_size) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint64_t Block;
					typedef kerbal::type_traits::integral_constant<Block, static_cast<Block>(~static_cast<Block>(0))> ALL_ONE;
					typedef kerbal::type_traits::integral_constant<std::size_t, 512 / 64> STEP;
					const __m512i zmm_ALL_ONE = _mm512_set1_epi64(static_cast<long long>(ALL_ONE::value)); // AVX512F

					std::size_t i = 0;
					for (; i + 8 * STEP::value <= chunk_size; i += 8 * STEP::value) {
						__m512i zmm_blockp0 = _mm512_loadu_si512(&block[i + 0 * STEP::value]); // AVX512F
						__m512i zmm_blockp1 = _mm512_loadu_si512(&block[i + 1 * STEP::value]); // AVX512F
						__m512i zmm_blockp2 = _mm512_loadu_si512(&block[i + 2 * STEP::value]); // AVX512F
						__m512i zmm_blockp3 = _mm512_loadu_si512(&block[i + 3 * STEP::value]); // AVX512F
						__m512i zmm_blockp4 = _mm512_loadu_si512(&block[i + 4 * STEP::value]); // AVX512F
						__m512i zmm_blockp5 = _mm512_loadu_si512(&block[i + 5 * STEP::value]); // AVX512F
						__m512i zmm_blockp6 = _mm512_loadu_si512(&block[i + 6 * STEP::value]); // AVX512F
						__m512i zmm_blockp7 = _mm512_loadu_si512(&block[i + 7 * STEP::value]); // AVX512F

						zmm_blockp0 = _mm512_ternarylogic_epi64(zmm_blockp0, zmm_blockp1, zmm_blockp2, 128); // AVX512F, 128 = 0b10000000, a & b & c
						zmm_blockp0 = _mm512_ternarylogic_epi64(zmm_blockp0, zmm_blockp3, zmm_blockp4, 128); // AVX512F
						zmm_blockp0 = _mm512_ternarylogic_epi64(zmm_blockp0, zmm_blockp5, zmm_blockp6, 128); // AVX512F
						zmm_blockp0 = _mm512_and_si512(zmm_blockp0, zmm_blockp7); // AVX512F

						__mmask16 k_eq = _mm512_cmpeq_epi32_mask(zmm_blockp0, zmm_ALL_ONE); // AVX512F
						if (!_mm512_kortestc(k_eq, k_eq)) { // AVX512F
							return false;
						}
					}

					for (; i + STEP::value <= chunk_size; i += STEP::value) {
						__m512i zmm_block = _mm512_loadu_si512(&block[i]); // AVX512F
						__mmask16 k_eq = _mm512_cmpeq_epi32_mask(zmm_block, zmm_ALL_ONE); // AVX512F
						if (!_mm512_kortestc(k_eq, k_eq)) { // AVX512F
							return false;
						}
					}

					{
						__m512i zmm_iota = _mm512_setr_epi64(0, 1, 2, 3, 4, 5, 6, 7); // AVX512F
						__mmask8 k_mask = _mm512_cmpgt_epi64_mask(_mm512_set1_epi64(static_cast<int>(chunk_size - i)), zmm_iota); // AVX512F

						__m512i zmm_block = _mm512_mask_loadu_epi64(zmm_ALL_ONE, k_mask, &block[i]); // AVX2
						__mmask16 k_eq = _mm512_cmpeq_epi32_mask(zmm_block, zmm_ALL_ONE); // AVX512F
						if (!_mm512_kortestc(k_eq, k_eq)) { // AVX512F
							return false;
						}
					}

					return true;
				}

			} // namespace avx512f

		} // namespace detail

	} // namespace bitset

} // namespace kerbal


#endif // KERBAL_BITSET_DETAIL_ALL_CHUNK_ALL_CHUNK_AVX512F_HPP
