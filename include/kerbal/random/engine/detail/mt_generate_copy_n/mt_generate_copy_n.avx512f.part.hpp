/**
 * @file       mt_generate_copy_n.avx512f.part.hpp
 * @brief
 * @date       2022-11-07
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_ENGINE_DETAIL_MT_GENERATE_COPY_N_MT_GENERATE_COPY_N_AVX512F_PART_HPP
#define KERBAL_RANDOM_ENGINE_DETAIL_MT_GENERATE_COPY_N_MT_GENERATE_COPY_N_AVX512F_PART_HPP

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

			namespace avx512f
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
					typedef kerbal::type_traits::integral_constant<std::size_t, 512 / 32> STEP;
					const __m512i zmm_B = _mm512_set1_epi32(B); // AVX512F
					const __m512i zmm_C = _mm512_set1_epi32(C); // AVX512F
					const __m512i zmm_D = _mm512_set1_epi32(D); // AVX512F

					std::size_t i = 0;
					for (; i + STEP::value <= n; i += STEP::value) {
						__m512i zmm_y = _mm512_loadu_si512(&mt_now[i]); // AVX512F
						__m512i zmm_shift;

						zmm_shift = _mm512_srli_epi32(zmm_y, U); // AVX512F
						zmm_y = _mm512_ternarylogic_epi32(zmm_shift, zmm_D, zmm_y, 106); // AVX512F, 106 = 0b01101010, (a & b) ^ c

						zmm_shift = _mm512_slli_epi32(zmm_y, S); // AVX512F
						zmm_y = _mm512_ternarylogic_epi32(zmm_shift, zmm_B, zmm_y, 106); // AVX512F, 106 = 0b01101010, (a & b) ^ c

						zmm_shift = _mm512_slli_epi32(zmm_y, T); // AVX512F
						zmm_y = _mm512_ternarylogic_epi32(zmm_shift, zmm_C, zmm_y, 106); // AVX512F, 106 = 0b01101010, (a & b) ^ c

						zmm_shift = _mm512_srli_epi32(zmm_y, L); // AVX512F
						zmm_y = _mm512_xor_si512(zmm_y, zmm_shift); // AVX512F

						_mm512_storeu_si512(&out[i], zmm_y); // AVX512F
					}

					{
						__mmask16 k_mask = _cvtu32_mask16(~(~0u << (n - i))); // AVX512F

						__m512i zmm_y = _mm512_maskz_loadu_epi32(k_mask, &mt_now[i]); // AVX512F
						__m512i zmm_shift;

						zmm_shift = _mm512_srli_epi32(zmm_y, U); // AVX512F
						zmm_y = _mm512_ternarylogic_epi32(zmm_shift, zmm_D, zmm_y, 106); // AVX512F, 106 = 0b01101010, (a & b) ^ c

						zmm_shift = _mm512_slli_epi32(zmm_y, S); // AVX512F
						zmm_y = _mm512_ternarylogic_epi32(zmm_shift, zmm_B, zmm_y, 106); // AVX512F, 106 = 0b01101010, (a & b) ^ c

						zmm_shift = _mm512_slli_epi32(zmm_y, T); // AVX512F
						zmm_y = _mm512_ternarylogic_epi32(zmm_shift, zmm_C, zmm_y, 106); // AVX512F, 106 = 0b01101010, (a & b) ^ c

						zmm_shift = _mm512_srli_epi32(zmm_y, L); // AVX512F
						zmm_y = _mm512_xor_si512(zmm_y, zmm_shift); // AVX512F

						_mm512_mask_storeu_epi32(&out[i], k_mask, zmm_y); // AVX512F
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
					typedef kerbal::type_traits::integral_constant<std::size_t, 512 / 64> STEP;
					const __m512i zmm_B = _mm512_set1_epi64(B); // AVX512F
					const __m512i zmm_C = _mm512_set1_epi64(C); // AVX512F
					const __m512i zmm_D = _mm512_set1_epi64(D); // AVX512F

					std::size_t i = 0;
					for (; i + STEP::value <= n; i += STEP::value) {
						__m512i zmm_y = _mm512_loadu_si512(&mt_now[i]); // AVX512F
						__m512i zmm_shift;

						zmm_shift = _mm512_srli_epi64(zmm_y, U); // AVX512F
						zmm_y = _mm512_ternarylogic_epi64(zmm_shift, zmm_D, zmm_y, 106); // AVX512F, 106 = 0b01101010, (a & b) ^ c

						zmm_shift = _mm512_slli_epi64(zmm_y, S); // AVX512F
						zmm_y = _mm512_ternarylogic_epi64(zmm_shift, zmm_B, zmm_y, 106); // AVX512F, 106 = 0b01101010, (a & b) ^ c

						zmm_shift = _mm512_slli_epi64(zmm_y, T); // AVX512F
						zmm_y = _mm512_ternarylogic_epi64(zmm_shift, zmm_C, zmm_y, 106); // AVX512F, 106 = 0b01101010, (a & b) ^ c

						zmm_shift = _mm512_srli_epi64(zmm_y, L); // AVX512F
						zmm_y = _mm512_xor_si512(zmm_y, zmm_shift); // AVX512F

						_mm512_storeu_si512(&out[i], zmm_y); // AVX512F
					}

					{
						__m512i zmm_iota = _mm512_setr_epi64(0, 1, 2, 3, 4, 5, 6, 7); // AVX512F
						__mmask8 k_mask = _mm512_cmpgt_epi64_mask(_mm512_set1_epi64(static_cast<int>(n - i)), zmm_iota); // AVX512F

//						__mmask8 k_mask = _cvtu32_mask8(~0u << (STEP::value - (n - i))); // AVX512DQ

						__m512i zmm_y = _mm512_maskz_loadu_epi64(k_mask, &mt_now[i]); // AVX512F
						__m512i zmm_shift;

						zmm_shift = _mm512_srli_epi64(zmm_y, U); // AVX512F
						zmm_y = _mm512_ternarylogic_epi64(zmm_shift, zmm_D, zmm_y, 106); // AVX512F, 106 = 0b01101010, (a & b) ^ c

						zmm_shift = _mm512_slli_epi64(zmm_y, S); // AVX512F
						zmm_y = _mm512_ternarylogic_epi64(zmm_shift, zmm_B, zmm_y, 106); // AVX512F, 106 = 0b01101010, (a & b) ^ c

						zmm_shift = _mm512_slli_epi64(zmm_y, T); // AVX512F
						zmm_y = _mm512_ternarylogic_epi64(zmm_shift, zmm_C, zmm_y, 106); // AVX512F, 106 = 0b01101010, (a & b) ^ c

						zmm_shift = _mm512_srli_epi64(zmm_y, L); // AVX512F
						zmm_y = _mm512_xor_si512(zmm_y, zmm_shift); // AVX512F

						_mm512_mask_storeu_epi64(&out[i], k_mask, zmm_y); // AVX512F
					}

				}

			} // namespace avx512f

		} // namespace detail

	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_ENGINE_DETAIL_MT_GENERATE_COPY_N_MT_GENERATE_COPY_N_AVX512F_PART_HPP
