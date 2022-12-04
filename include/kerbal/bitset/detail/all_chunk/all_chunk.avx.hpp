/**
 * @file       all_chunk.avx.hpp
 * @brief
 * @date       2022-11-09
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_BITSET_DETAIL_ALL_CHUNK_ALL_CHUNK_AVX_HPP
#define KERBAL_BITSET_DETAIL_ALL_CHUNK_ALL_CHUNK_AVX_HPP

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

			namespace avx
			{

				inline bool all_chunk(const kerbal::compatibility::uint32_t block[], std::size_t chunk_size) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint32_t Block;
					typedef kerbal::type_traits::integral_constant<Block, static_cast<Block>(~static_cast<Block>(0))> ALL_ONE;
					typedef kerbal::type_traits::integral_constant<std::size_t, 256 / 32> STEP;
					const __m256i ymm_ALL_ONE = _mm256_set1_epi32(static_cast<int>(ALL_ONE::value)); // AVX

					std::size_t i = 0;
					for (; i + 8 * STEP::value <= chunk_size; i += 8 * STEP::value) {
						{
							__m256i ymm_blockp0 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&block[i + 0 * STEP::value])); // AVX
							__m256i ymm_blockp1 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&block[i + 1 * STEP::value])); // AVX
							__m256i ymm_blockp2 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&block[i + 2 * STEP::value])); // AVX
							__m256i ymm_blockp3 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&block[i + 3 * STEP::value])); // AVX
							__m256i ymm_blockp4 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&block[i + 4 * STEP::value])); // AVX
							__m256i ymm_blockp5 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&block[i + 5 * STEP::value])); // AVX
							__m256i ymm_blockp6 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&block[i + 6 * STEP::value])); // AVX
							__m256i ymm_blockp7 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&block[i + 7 * STEP::value])); // AVX

							if (
									!_mm256_testc_si256(ymm_blockp0, ymm_ALL_ONE) ||
									!_mm256_testc_si256(ymm_blockp1, ymm_ALL_ONE) ||
									!_mm256_testc_si256(ymm_blockp2, ymm_ALL_ONE) ||
									!_mm256_testc_si256(ymm_blockp3, ymm_ALL_ONE) ||
									!_mm256_testc_si256(ymm_blockp4, ymm_ALL_ONE) ||
									!_mm256_testc_si256(ymm_blockp5, ymm_ALL_ONE) ||
									!_mm256_testc_si256(ymm_blockp6, ymm_ALL_ONE) ||
									!_mm256_testc_si256(ymm_blockp7, ymm_ALL_ONE)
							) { // AVX
								return false;
							}
						}
					}

					for (; i + STEP::value <= chunk_size; i += STEP::value) {
						__m256i ymm_block = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&block[i])); // AVX
						if (!_mm256_testc_si256(ymm_block, ymm_ALL_ONE)) { // AVX
							return false;
						}
					}

					while (i < chunk_size) {
						EACH(i);
						++i;
					}

					return true;
				}

				inline bool all_chunk(const kerbal::compatibility::uint64_t block[], std::size_t chunk_size) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint64_t Block;
					typedef kerbal::type_traits::integral_constant<Block, static_cast<Block>(~static_cast<Block>(0))> ALL_ONE;
					typedef kerbal::type_traits::integral_constant<std::size_t, 256 / 64> STEP;
					const __m256i ymm_ALL_ONE = _mm256_set1_epi64x(static_cast<long long>(ALL_ONE::value)); // AVX

					std::size_t i = 0;
					for (; i + 8 * STEP::value <= chunk_size; i += 8 * STEP::value) {
						{
							__m256i ymm_blockp0 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&block[i + 0 * STEP::value])); // AVX
							__m256i ymm_blockp1 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&block[i + 1 * STEP::value])); // AVX
							__m256i ymm_blockp2 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&block[i + 2 * STEP::value])); // AVX
							__m256i ymm_blockp3 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&block[i + 3 * STEP::value])); // AVX
							__m256i ymm_blockp4 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&block[i + 4 * STEP::value])); // AVX
							__m256i ymm_blockp5 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&block[i + 5 * STEP::value])); // AVX
							__m256i ymm_blockp6 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&block[i + 6 * STEP::value])); // AVX
							__m256i ymm_blockp7 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&block[i + 7 * STEP::value])); // AVX

							if (
									!_mm256_testc_si256(ymm_blockp0, ymm_ALL_ONE) ||
									!_mm256_testc_si256(ymm_blockp1, ymm_ALL_ONE) ||
									!_mm256_testc_si256(ymm_blockp2, ymm_ALL_ONE) ||
									!_mm256_testc_si256(ymm_blockp3, ymm_ALL_ONE) ||
									!_mm256_testc_si256(ymm_blockp4, ymm_ALL_ONE) ||
									!_mm256_testc_si256(ymm_blockp5, ymm_ALL_ONE) ||
									!_mm256_testc_si256(ymm_blockp6, ymm_ALL_ONE) ||
									!_mm256_testc_si256(ymm_blockp7, ymm_ALL_ONE)
							) { // AVX
								return false;
							}
						}
					}

					for (; i + STEP::value <= chunk_size; i += STEP::value) {
						__m256i ymm_block = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&block[i])); // AVX
						if (!_mm256_testc_si256(ymm_block, ymm_ALL_ONE)) { // AVX
							return false;
						}
					}

					while (i < chunk_size) {
						EACH(i);
						++i;
					}

					return true;
				}

			} // namespace avx

		} // namespace detail

	} // namespace bitset

} // namespace kerbal


#endif // KERBAL_BITSET_DETAIL_ALL_CHUNK_ALL_CHUNK_AVX_HPP
