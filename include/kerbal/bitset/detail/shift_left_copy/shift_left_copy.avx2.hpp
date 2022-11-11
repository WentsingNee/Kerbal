/**
 * @file       shift_left_copy.avx2.hpp
 * @brief
 * @date       2022-11-10
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_BITSET_DETAIL_SHIFT_LEFT_COPY_SHIFT_LEFT_COPY_AVX2_HPP
#define KERBAL_BITSET_DETAIL_SHIFT_LEFT_COPY_SHIFT_LEFT_COPY_AVX2_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>
#include <climits>

#include <immintrin.h>

#include <kerbal/bitset/detail/shift_left_copy/shift_left_copy.plain.hpp>


namespace kerbal
{

	namespace bitset
	{

		namespace detail
		{

			namespace avx2
			{

				inline
				void shift_left_copy(const kerbal::compatibility::uint64_t block[], std::size_t n, std::size_t inner_ofs, kerbal::compatibility::uint64_t out[]) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint64_t Block;
					typedef kerbal::type_traits::integral_constant<std::size_t, CHAR_BIT * sizeof(Block)> BITS_PER_BLOCK;

					typedef kerbal::type_traits::integral_constant<std::size_t, 256 / 64> STEP;

					const std::size_t ano_ofs = (BITS_PER_BLOCK::value - inner_ofs);
					--n;

					std::size_t i = 0;
					for (; i + STEP::value <= n; i += STEP::value) {
						__m256i ymm_block = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&block[i])); // AVX
						__m256i ymm_blockp1 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&block[i + 1])); // AVX

						ymm_block = _mm256_srli_epi64(ymm_block, inner_ofs); // AVX2
						ymm_blockp1 = _mm256_slli_epi64(ymm_blockp1, ano_ofs); // AVX2
						ymm_block = _mm256_or_si256(ymm_block, ymm_blockp1); // AVX2

						_mm256_storeu_si256(reinterpret_cast<__m256i*>(&out[i]), ymm_block); // AVX
					}

					{
						__m256i ymm_iota = _mm256_setr_epi64x(0, 1, 2, 3); // AVX
						__m256i ymm_mask = _mm256_cmpgt_epi64(_mm256_set1_epi64x(static_cast<int>(n - i)), ymm_iota); // AVX2

						__m256i ymm_block = _mm256_maskload_epi64(reinterpret_cast<const long long int *>(&block[i]), ymm_mask); // AVX2
						__m256i ymm_blockp1 = _mm256_maskload_epi64(reinterpret_cast<const long long int *>(&block[i + 1]), ymm_mask); // AVX2

						ymm_block = _mm256_srli_epi64(ymm_block, inner_ofs); // AVX2
						ymm_blockp1 = _mm256_slli_epi64(ymm_blockp1, ano_ofs); // AVX2
						ymm_block = _mm256_or_si256(ymm_block, ymm_blockp1); // AVX2

						_mm256_maskstore_epi64(reinterpret_cast<long long int *>(&out[i]), ymm_mask, ymm_block); // AVX2
					}
				}

			} // namespace avx2

		} // namespace detail

	} // namespace bitset

} // namespace kerbal


#endif // KERBAL_BITSET_DETAIL_SHIFT_LEFT_COPY_SHIFT_LEFT_COPY_AVX2_HPP
