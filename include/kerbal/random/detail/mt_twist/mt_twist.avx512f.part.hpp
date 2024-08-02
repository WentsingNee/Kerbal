/**
 * @file       mt_twist.avx512f.part.hpp
 * @brief
 * @date       2022-07-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_DETAIL_MT_TWIST_MT_TWIST_AVX512F_PART_HPP
#define KERBAL_RANDOM_DETAIL_MT_TWIST_MT_TWIST_AVX512F_PART_HPP

#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
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

				template <std::size_t N, std::size_t M, std::size_t R, kerbal::compatibility::uint32_t A>
				void mt_twist(kerbal::compatibility::uint32_t mt[]) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint32_t result_type;

					typedef kerbal::type_traits::integral_constant<result_type, (~static_cast<result_type>(0)) << R> UPPER_MASK; // most significant w-r bits
					typedef kerbal::type_traits::integral_constant<result_type, ~UPPER_MASK::value> LOWER_MASK; // least significant r bits
					KERBAL_STATIC_ASSERT(N >= M, "N should >= M");
					typedef kerbal::type_traits::integral_constant<std::size_t, N - M> NPM;

					typedef kerbal::type_traits::integral_constant<std::size_t, 512 / 32> STEP;
					const __m512i zmm_UPPER_MASK = _mm512_set1_epi32(static_cast<int>(UPPER_MASK::value)); // AVX512F
					const __m512i zmm_ZERO = _mm512_set1_epi32(0); // AVX512F
					const __m512i zmm_ONE = _mm512_set1_epi32(1); // AVX512F
					const __m512i zmm_A = _mm512_set1_epi32(static_cast<int>(A)); // AVX512F

					std::size_t i = 0;
					for (; i + STEP::value <= NPM::value; i += STEP::value) {
						__m512i zmm_mti = _mm512_loadu_si512(&mt[i]); // AVX512F
						__m512i zmm_mtip1 = _mm512_loadu_si512(&mt[i + 1]); // AVX512F

					/*
						__m512i zmm_y = _mm512_or_si512( // AVX512F
							_mm512_and_si512(zmm_UPPER_MASK, zmm_mti), // AVX512F
							_mm512_andnot_si512(zmm_UPPER_MASK, zmm_mtip1)); // AVX512F

						can be optimised to ternarylogic operation as below:
					*/

						__m512i zmm_y = _mm512_ternarylogic_epi32(zmm_mti, zmm_UPPER_MASK, zmm_mtip1, 226); // AVX512F, 226 = 0b11100010

						__m512i zmm_mag_mask = _mm512_and_si512(zmm_y, zmm_ONE); // AVX512F
						zmm_mag_mask = _mm512_sub_epi32(zmm_ZERO, zmm_mag_mask); // AVX512F <=> _mm512_cmpeq_epi32(zmm_mag_mask, zmm_ONE) AVX512F
						zmm_mag_mask = _mm512_and_si512(zmm_mag_mask, zmm_A); // AVX512F
						zmm_y = _mm512_srli_epi32(zmm_y, 1); // AVX512F
						__m512i zmm_mtipm = _mm512_loadu_si512(&mt[i + M]); // AVX512F

					/*
						zmm_y = _mm512_xor_si512(zmm_y, zmm_mag_mask); // AVX512F
						zmm_mti = _mm512_xor_si512(zmm_y, zmm_mtipm); // AVX512F

						can be optimised to ternarylogic operation as below:
					*/

						zmm_mti = _mm512_ternarylogic_epi32(zmm_y, zmm_mag_mask, zmm_mtipm, 150); // AVX512F, 150 = 0b10010110

						_mm512_storeu_si512(&mt[i], zmm_mti); // AVX512F
					}

					typedef kerbal::type_traits::integral_constant<int, NPM::value % STEP::value> FIRST_STEP_REMAIN;
					if (FIRST_STEP_REMAIN::value != 0) {
						__mmask16 k_mask = _cvtu32_mask16(~(~0u << FIRST_STEP_REMAIN::value)); // AVX512F

						__m512i zmm_mti =
							(FIRST_STEP_REMAIN::value + M >= STEP::value) ?
							_mm512_loadu_si512(&mt[i]) : // AVX512F
							_mm512_maskz_loadu_epi32(k_mask, &mt[i]); // AVX512F
						__m512i zmm_mtip1 =
							(FIRST_STEP_REMAIN::value + M - 1 >= STEP::value) ?
							_mm512_loadu_si512(&mt[i + 1]) : // AVX512F
							_mm512_maskz_loadu_epi32(k_mask, &mt[i + 1]); // AVX512F
						__m512i zmm_y = _mm512_ternarylogic_epi32(zmm_mti, zmm_UPPER_MASK, zmm_mtip1, 226); // AVX512F, 226 = 0b11100010
						__m512i zmm_mag_mask = _mm512_and_si512(zmm_y, zmm_ONE); // AVX512F
						zmm_mag_mask = _mm512_sub_epi32(zmm_ZERO, zmm_mag_mask); // AVX512F <=> _mm512_cmpeq_epi32(zmm_mag_mask, zmm_ONE) AVX512F
						zmm_mag_mask = _mm512_and_si512(zmm_mag_mask, zmm_A); // AVX512F
						zmm_y = _mm512_srli_epi32(zmm_y, 1); // AVX512F
						__m512i zmm_mtipm = _mm512_maskz_loadu_epi32(k_mask, &mt[i + M]); // AVX512F
						zmm_mti = _mm512_ternarylogic_epi32(zmm_y, zmm_mag_mask, zmm_mtipm, 150); // AVX512F, 150 = 0b10010110
						_mm512_mask_storeu_epi32(&mt[i], k_mask, zmm_mti); // AVX512F

						i = NPM::value;
					}

					for (; i + STEP::value <= N - 1; i += STEP::value) {
						__m512i zmm_mti = _mm512_loadu_si512(&mt[i]); // AVX512F
						__m512i zmm_mtip1 = _mm512_loadu_si512(&mt[i + 1]); // AVX512F

					/*
						__m512i zmm_y = _mm512_or_si512( // AVX512F
							_mm512_and_si512(zmm_UPPER_MASK, zmm_mti), // AVX512F
							_mm512_andnot_si512(zmm_UPPER_MASK, zmm_mtip1)); // AVX512F

						can be optimised to ternarylogic operation as below:
					*/

						__m512i zmm_y = _mm512_ternarylogic_epi32(zmm_mti, zmm_UPPER_MASK, zmm_mtip1, 226); // AVX512F, 226 = 0b11100010

						__m512i zmm_mag_mask = _mm512_and_si512(zmm_y, zmm_ONE); // AVX512F
						zmm_mag_mask = _mm512_sub_epi32(zmm_ZERO, zmm_mag_mask); // AVX512F <=> _mm512_cmpeq_epi32(zmm_mag_mask, zmm_ONE) AVX512F
						zmm_mag_mask = _mm512_and_si512(zmm_mag_mask, zmm_A); // AVX512F
						zmm_y = _mm512_srli_epi32(zmm_y, 1); // AVX512F
						__m512i zmm_mtipm = _mm512_loadu_si512(&mt[i - NPM::value]); // AVX512F

					/*
						zmm_y = _mm512_xor_si512(zmm_y, zmm_mag_mask); // AVX512F
						zmm_mti = _mm512_xor_si512(zmm_y, zmm_mtipm); // AVX512F

						can be optimised to ternarylogic operation as below:
					*/

						zmm_mti = _mm512_ternarylogic_epi32(zmm_y, zmm_mag_mask, zmm_mtipm, 150); // AVX512F, 150 = 0b10010110

						_mm512_storeu_si512(&mt[i], zmm_mti); // AVX512F
					}

					typedef kerbal::type_traits::integral_constant<int, (M - 1) % STEP::value> SECOND_STEP_REMAIN;
					if (SECOND_STEP_REMAIN::value != 0) {
						__mmask16 k_mask = _cvtu32_mask16(~(~0u << SECOND_STEP_REMAIN::value)); // AVX512F
						__mmask16 k_maskp1 = _cvtu32_mask16(~(~0u << (SECOND_STEP_REMAIN::value + 1))); // AVX512F

						__m512i zmm_mti =
							(SECOND_STEP_REMAIN::value + 1 >= STEP::value) ?
							_mm512_loadu_si512(&mt[i]) : // AVX512F
							_mm512_maskz_loadu_epi32(k_maskp1, &mt[i]); // AVX512F
						__m512i zmm_mtip1 = _mm512_set1_epi32(static_cast<int>(mt[0])); // AVX512F
						zmm_mtip1 = _mm512_mask_loadu_epi32(zmm_mtip1, k_mask, &mt[i + 1]); // AVX512F
						// SECOND_STEP_REMAIN::value >= STEP::value always false
						__m512i zmm_y = _mm512_ternarylogic_epi32(zmm_mti, zmm_UPPER_MASK, zmm_mtip1, 226); // AVX512F, 226 = 0b11100010
						__m512i zmm_mag_mask = _mm512_and_si512(zmm_y, zmm_ONE); // AVX512F
						zmm_mag_mask = _mm512_sub_epi32(zmm_ZERO, zmm_mag_mask); // AVX512F <=> _mm512_cmpeq_epi32(zmm_mag_mask, zmm_ONE) AVX512F
						zmm_mag_mask = _mm512_and_si512(zmm_mag_mask, zmm_A); // AVX512F
						zmm_y = _mm512_srli_epi32(zmm_y, 1); // AVX512F
						__m512i zmm_mtipm =
							(SECOND_STEP_REMAIN::value + NPM::value + 1 >= STEP::value) ?
							_mm512_loadu_si512(&mt[i - NPM::value]) : // AVX512F
							_mm512_maskz_loadu_epi32(k_maskp1, &mt[i - NPM::value]); // AVX512F
						zmm_mti = _mm512_ternarylogic_epi32(zmm_y, zmm_mag_mask, zmm_mtipm, 150); // AVX512F, 150 = 0b10010110

						_mm512_mask_storeu_epi32(&mt[i], k_maskp1, zmm_mti); // AVX512F
					} else {

						// i = N - 1;

						result_type y = (mt[N - 1] & UPPER_MASK::value) | (mt[0] & LOWER_MASK::value);
						mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ ((y & 0x1UL) ? A : 0);
					}

				}

				template <std::size_t N, std::size_t M, std::size_t R, kerbal::compatibility::uint64_t A>
				void mt_twist(kerbal::compatibility::uint64_t mt[]) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint64_t result_type;

					typedef kerbal::type_traits::integral_constant<result_type, (~static_cast<result_type>(0)) << R> UPPER_MASK; // most significant w-r bits
					typedef kerbal::type_traits::integral_constant<result_type, ~UPPER_MASK::value> LOWER_MASK; // least significant r bits
					KERBAL_STATIC_ASSERT(N >= M, "N should >= M");
					typedef kerbal::type_traits::integral_constant<std::size_t, N - M> NPM;

					typedef kerbal::type_traits::integral_constant<std::size_t, 512 / 64> STEP;
					const __m512i zmm_UPPER_MASK = _mm512_set1_epi64(static_cast<long long>(UPPER_MASK::value)); // AVX512F
					const __m512i zmm_ZERO = _mm512_set1_epi64(0); // AVX512F
					const __m512i zmm_ONE = _mm512_set1_epi64(1); // AVX512F
					const __m512i zmm_A = _mm512_set1_epi64(static_cast<long long>(A)); // AVX512F
					const __m512i zmm_iota = _mm512_setr_epi64(0, 1, 2, 3, 4, 5, 6, 7); // AVX512F

					std::size_t i = 0;
					for (; i + STEP::value <= NPM::value; i += STEP::value) {
						__m512i zmm_mti = _mm512_loadu_si512(&mt[i]); // AVX512F
						__m512i zmm_mtip1 = _mm512_loadu_si512(&mt[i + 1]); // AVX512F

					/*
						__m512i zmm_y = _mm512_or_si512( // AVX512F
							_mm512_and_si512(zmm_UPPER_MASK, zmm_mti), // AVX512F
							_mm512_andnot_si512(zmm_UPPER_MASK, zmm_mtip1)); // AVX512F

						can be optimised to ternarylogic operation as below:
					*/

						__m512i zmm_y = _mm512_ternarylogic_epi64(zmm_mti, zmm_UPPER_MASK, zmm_mtip1, 226); // AVX512F, 226 = 0b11100010

						__m512i zmm_mag_mask = _mm512_and_si512(zmm_y, zmm_ONE); // AVX512F
						zmm_mag_mask = _mm512_sub_epi64(zmm_ZERO, zmm_mag_mask); // AVX512F <=> _mm512_cmpeq_epi64(zmm_mag_mask, zmm_ONE) AVX512F
						zmm_mag_mask = _mm512_and_si512(zmm_mag_mask, zmm_A); // AVX512F
						zmm_y = _mm512_srli_epi64(zmm_y, 1); // AVX512F
						__m512i zmm_mtipm = _mm512_loadu_si512(&mt[i + M]); // AVX512F

					/*
						zmm_y = _mm512_xor_si512(zmm_y, zmm_mag_mask); // AVX512F
						zmm_mti = _mm512_xor_si512(zmm_y, zmm_mtipm); // AVX512F

						can be optimised to ternarylogic operation as below:
					*/

						zmm_mti = _mm512_ternarylogic_epi64(zmm_y, zmm_mag_mask, zmm_mtipm, 150); // AVX512F, 150 = 0b10010110

						_mm512_storeu_si512(&mt[i], zmm_mti); // AVX512F
					}

					typedef kerbal::type_traits::integral_constant<int, NPM::value % STEP::value> FIRST_STEP_REMAIN;
					if (FIRST_STEP_REMAIN::value != 0) {
						__mmask8 k_mask = _mm512_cmpgt_epi64_mask(_mm512_set1_epi64(FIRST_STEP_REMAIN::value), zmm_iota); // AVX512F

						__m512i zmm_mti =
							(FIRST_STEP_REMAIN::value + M >= STEP::value) ?
							_mm512_loadu_si512(&mt[i]) : // AVX512F
							_mm512_maskz_loadu_epi64(k_mask, &mt[i]); // AVX512F
						__m512i zmm_mtip1 =
							(FIRST_STEP_REMAIN::value + M - 1 >= STEP::value) ?
							_mm512_loadu_si512(&mt[i + 1]) : // AVX512F
							_mm512_maskz_loadu_epi64(k_mask, &mt[i + 1]); // AVX512F
						__m512i zmm_y = _mm512_ternarylogic_epi64(zmm_mti, zmm_UPPER_MASK, zmm_mtip1, 226); // AVX512F, 226 = 0b11100010
						__m512i zmm_mag_mask = _mm512_and_si512(zmm_y, zmm_ONE); // AVX512F
						zmm_mag_mask = _mm512_sub_epi64(zmm_ZERO, zmm_mag_mask); // AVX512F <=> _mm512_cmpeq_epi64(zmm_mag_mask, zmm_ONE) AVX512F
						zmm_mag_mask = _mm512_and_si512(zmm_mag_mask, zmm_A); // AVX512F
						zmm_y = _mm512_srli_epi64(zmm_y, 1); // AVX512F
						__m512i zmm_mtipm = _mm512_loadu_si512(&mt[i + M]); // AVX512F
						zmm_mti = _mm512_ternarylogic_epi64(zmm_y, zmm_mag_mask, zmm_mtipm, 150); // AVX512F, 150 = 0b10010110
						_mm512_mask_storeu_epi64(&mt[i], k_mask, zmm_mti); // AVX512F

						i = NPM::value;
					}

					for (; i + STEP::value <= N - 1; i += STEP::value) {
						__m512i zmm_mti = _mm512_loadu_si512(&mt[i]); // AVX512F
						__m512i zmm_mtip1 = _mm512_loadu_si512(&mt[i + 1]); // AVX512F

					/*
						__m512i zmm_y = _mm512_or_si512( // AVX512F
							_mm512_and_si512(zmm_UPPER_MASK, zmm_mti), // AVX512F
							_mm512_andnot_si512(zmm_UPPER_MASK, zmm_mtip1)); // AVX512F

						can be optimised to ternarylogic operation as below:
					*/

						__m512i zmm_y = _mm512_ternarylogic_epi64(zmm_mti, zmm_UPPER_MASK, zmm_mtip1, 226); // AVX512F, 226 = 0b11100010

						__m512i zmm_mag_mask = _mm512_and_si512(zmm_y, zmm_ONE); // AVX512F
						zmm_mag_mask = _mm512_sub_epi64(zmm_ZERO, zmm_mag_mask); // AVX512F <=> _mm512_cmpeq_epi64(zmm_mag_mask, zmm_ONE) AVX512F
						zmm_mag_mask = _mm512_and_si512(zmm_mag_mask, zmm_A); // AVX512F
						zmm_y = _mm512_srli_epi64(zmm_y, 1); // AVX512F
						__m512i zmm_mtipm = _mm512_loadu_si512(&mt[i - NPM::value]); // AVX512F

					/*
						zmm_y = _mm512_xor_si512(zmm_y, zmm_mag_mask); // AVX512F
						zmm_mti = _mm512_xor_si512(zmm_y, zmm_mtipm); // AVX512F

						can be optimised to ternarylogic operation as below:
					*/

						zmm_mti = _mm512_ternarylogic_epi64(zmm_y, zmm_mag_mask, zmm_mtipm, 150); // AVX512F, 150 = 0b10010110

						_mm512_storeu_si512(&mt[i], zmm_mti); // AVX512F
					}

					typedef kerbal::type_traits::integral_constant<int, (M - 1) % STEP::value> SECOND_STEP_REMAIN;
					if (SECOND_STEP_REMAIN::value != 0) {
						__mmask8 k_mask = _mm512_cmpgt_epi64_mask(_mm512_set1_epi64(SECOND_STEP_REMAIN::value), zmm_iota); // AVX512F
						__mmask8 k_maskp1 = _mm512_cmpgt_epi64_mask(_mm512_set1_epi64(SECOND_STEP_REMAIN::value + 1), zmm_iota); // AVX512F

						__m512i zmm_mti =
							(SECOND_STEP_REMAIN::value + 1 >= STEP::value) ?
							_mm512_loadu_si512(&mt[i]) : // AVX512F
							_mm512_maskz_loadu_epi64(k_maskp1, &mt[i]); // AVX512F
						__m512i zmm_mtip1 = _mm512_set1_epi64(static_cast<long long>(mt[0])); // AVX512F
						zmm_mtip1 = _mm512_mask_loadu_epi64(zmm_mtip1, k_mask, &mt[i + 1]); // AVX512F
						// SECOND_STEP_REMAIN::value >= STEP::value always false
						__m512i zmm_y = _mm512_ternarylogic_epi64(zmm_mti, zmm_UPPER_MASK, zmm_mtip1, 226); // AVX512F, 226 = 0b11100010
						__m512i zmm_mag_mask = _mm512_and_si512(zmm_y, zmm_ONE); // AVX512F
						zmm_mag_mask = _mm512_sub_epi64(zmm_ZERO, zmm_mag_mask); // AVX512F <=> _mm512_cmpeq_epi64(zmm_mag_mask, zmm_ONE) AVX512F
						zmm_mag_mask = _mm512_and_si512(zmm_mag_mask, zmm_A); // AVX512F
						zmm_y = _mm512_srli_epi64(zmm_y, 1); // AVX512F
						__m512i zmm_mtipm =
							(SECOND_STEP_REMAIN::value + NPM::value + 1 >= STEP::value) ?
							_mm512_loadu_si512(&mt[i - NPM::value]) : // AVX512F
							_mm512_maskz_loadu_epi64(k_maskp1, &mt[i - NPM::value]); // AVX512F
						zmm_mti = _mm512_ternarylogic_epi64(zmm_y, zmm_mag_mask, zmm_mtipm, 150); // AVX512F, 150 = 0b10010110
						_mm512_mask_storeu_epi64(&mt[i], k_maskp1, zmm_mti); // AVX512F
					} else {

						// i = N - 1;

						result_type y = (mt[N - 1] & UPPER_MASK::value) | (mt[0] & LOWER_MASK::value);
						mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ ((y & 0x1UL) ? A : 0);
					}

				}

			} // namespace avx512f

		} // namespace detail

	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_DETAIL_MT_TWIST_MT_TWIST_AVX512F_PART_HPP
