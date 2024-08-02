/**
 * @file       mt_generate_copy_n.avx2.part.hpp
 * @brief
 * @date       2022-11-06
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_DETAIL_MT_GENERATE_COPY_N_MT_GENERATE_COPY_N_AVX2_PART_HPP
#define KERBAL_RANDOM_DETAIL_MT_GENERATE_COPY_N_MT_GENERATE_COPY_N_AVX2_PART_HPP

#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>

#include <immintrin.h>


namespace kerbal
{

	namespace random
	{

		namespace detail
		{

			namespace avx2
			{

				template <
					std::size_t U, kerbal::compatibility::uint32_t D,
					std::size_t S, kerbal::compatibility::uint32_t B,
					std::size_t T, kerbal::compatibility::uint32_t C,
					std::size_t L
				>
				void mt_generate_copy_n(
					const kerbal::compatibility::uint32_t mt_now[],
					kerbal::compatibility::uint32_t * out,
					std::size_t n
				) KERBAL_NOEXCEPT
				{
					typedef kerbal::type_traits::integral_constant<std::size_t, 256 / 32> STEP;
					const __m256i ymm_B = _mm256_set1_epi32(B); // AVX
					const __m256i ymm_C = _mm256_set1_epi32(C); // AVX
					const __m256i ymm_D = _mm256_set1_epi32(D); // AVX

					std::size_t i = 0;
					for (; i + STEP::value <= n; i += STEP::value) {
						__m256i ymm_y = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&mt_now[i])); // AVX
						__m256i ymm_shift, ymm_and;

						ymm_shift = _mm256_srli_epi32(ymm_y, U); // AVX2
						ymm_and = _mm256_and_si256(ymm_shift, ymm_D); // AVX2
						ymm_y = _mm256_xor_si256(ymm_y, ymm_and); // AVX2

						ymm_shift = _mm256_slli_epi32(ymm_y, S); // AVX2
						ymm_and = _mm256_and_si256(ymm_shift, ymm_B); // AVX2
						ymm_y = _mm256_xor_si256(ymm_y, ymm_and); // AVX2

						ymm_shift = _mm256_slli_epi32(ymm_y, T); // AVX2
						ymm_and = _mm256_and_si256(ymm_shift, ymm_C); // AVX2
						ymm_y = _mm256_xor_si256(ymm_y, ymm_and); // AVX2

						ymm_shift = _mm256_srli_epi32(ymm_y, L); // AVX2
						ymm_y = _mm256_xor_si256(ymm_y, ymm_shift); // AVX2

						_mm256_storeu_si256(reinterpret_cast<__m256i *>(&out[i]), ymm_y); // AVX
					}

					{
						__m256i ymm_iota = _mm256_setr_epi32(0, 1, 2, 3, 4, 5, 6, 7); // AVX
						__m256i ymm_mask = _mm256_cmpgt_epi32(_mm256_set1_epi32(static_cast<int>(n - i)), ymm_iota); // AVX2

						__m256i ymm_y = _mm256_maskload_epi32(reinterpret_cast<const int *>(&mt_now[i]), ymm_mask); // AVX2
						__m256i ymm_shift, ymm_and;

						ymm_shift = _mm256_srli_epi32(ymm_y, U); // AVX2
						ymm_and = _mm256_and_si256(ymm_shift, ymm_D); // AVX2
						ymm_y = _mm256_xor_si256(ymm_y, ymm_and); // AVX2

						ymm_shift = _mm256_slli_epi32(ymm_y, S); // AVX2
						ymm_and = _mm256_and_si256(ymm_shift, ymm_B); // AVX2
						ymm_y = _mm256_xor_si256(ymm_y, ymm_and); // AVX2

						ymm_shift = _mm256_slli_epi32(ymm_y, T); // AVX2
						ymm_and = _mm256_and_si256(ymm_shift, ymm_C); // AVX2
						ymm_y = _mm256_xor_si256(ymm_y, ymm_and); // AVX2

						ymm_shift = _mm256_srli_epi32(ymm_y, L); // AVX2
						ymm_y = _mm256_xor_si256(ymm_y, ymm_shift); // AVX2

						_mm256_maskstore_epi32(reinterpret_cast<int *>(&out[i]), ymm_mask, ymm_y); // AVX2
					}

				}

				template <
					std::size_t U, kerbal::compatibility::uint64_t D,
					std::size_t S, kerbal::compatibility::uint64_t B,
					std::size_t T, kerbal::compatibility::uint64_t C,
					std::size_t L
				>
				void mt_generate_copy_n(
					const kerbal::compatibility::uint64_t mt_now[],
					kerbal::compatibility::uint64_t * out,
					std::size_t n
				) KERBAL_NOEXCEPT
				{
					typedef kerbal::type_traits::integral_constant<std::size_t, 256 / 64> STEP;
					const __m256i ymm_B = _mm256_set1_epi64x(B); // AVX
					const __m256i ymm_C = _mm256_set1_epi64x(C); // AVX
					const __m256i ymm_D = _mm256_set1_epi64x(D); // AVX

					std::size_t i = 0;
					for (; i + STEP::value <= n; i += STEP::value) {
						__m256i ymm_y = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&mt_now[i])); // AVX
						__m256i ymm_shift, ymm_and;

						ymm_shift = _mm256_srli_epi64(ymm_y, U); // AVX2
						ymm_and = _mm256_and_si256(ymm_shift, ymm_D); // AVX2
						ymm_y = _mm256_xor_si256(ymm_y, ymm_and); // AVX2

						ymm_shift = _mm256_slli_epi64(ymm_y, S); // AVX2
						ymm_and = _mm256_and_si256(ymm_shift, ymm_B); // AVX2
						ymm_y = _mm256_xor_si256(ymm_y, ymm_and); // AVX2

						ymm_shift = _mm256_slli_epi64(ymm_y, T); // AVX2
						ymm_and = _mm256_and_si256(ymm_shift, ymm_C); // AVX2
						ymm_y = _mm256_xor_si256(ymm_y, ymm_and); // AVX2

						ymm_shift = _mm256_srli_epi64(ymm_y, L); // AVX2
						ymm_y = _mm256_xor_si256(ymm_y, ymm_shift); // AVX2

						_mm256_storeu_si256(reinterpret_cast<__m256i *>(&out[i]), ymm_y); // AVX
					}

					{
						__m256i ymm_iota = _mm256_setr_epi64x(0, 1, 2, 3); // AVX
						__m256i ymm_mask = _mm256_cmpgt_epi64(_mm256_set1_epi64x(static_cast<int>(n - i)), ymm_iota); // AVX2

						__m256i ymm_y = _mm256_maskload_epi64(reinterpret_cast<const long long int *>(&mt_now[i]), ymm_mask); // AVX2
						__m256i ymm_shift, ymm_and;

						ymm_shift = _mm256_srli_epi64(ymm_y, U); // AVX2
						ymm_and = _mm256_and_si256(ymm_shift, ymm_D); // AVX2
						ymm_y = _mm256_xor_si256(ymm_y, ymm_and); // AVX2

						ymm_shift = _mm256_slli_epi64(ymm_y, S); // AVX2
						ymm_and = _mm256_and_si256(ymm_shift, ymm_B); // AVX2
						ymm_y = _mm256_xor_si256(ymm_y, ymm_and); // AVX2

						ymm_shift = _mm256_slli_epi64(ymm_y, T); // AVX2
						ymm_and = _mm256_and_si256(ymm_shift, ymm_C); // AVX2
						ymm_y = _mm256_xor_si256(ymm_y, ymm_and); // AVX2

						ymm_shift = _mm256_srli_epi64(ymm_y, L); // AVX2
						ymm_y = _mm256_xor_si256(ymm_y, ymm_shift); // AVX2

						_mm256_maskstore_epi64(reinterpret_cast<long long int *>(&out[i]), ymm_mask, ymm_y); // AVX2
					}

				}

			} // namespace avx2

		} // namespace detail

	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_DETAIL_MT_GENERATE_COPY_N_MT_GENERATE_COPY_N_AVX2_PART_HPP
