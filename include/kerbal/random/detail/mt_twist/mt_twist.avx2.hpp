/**
 * @file       mt_twist.avx2.hpp
 * @brief
 * @date       2022-07-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_DETAIL_MT_TWIST_MT_TWIST_AVX2_HPP
#define KERBAL_RANDOM_DETAIL_MT_TWIST_MT_TWIST_AVX2_HPP

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

			namespace avx2
			{

				template <std::size_t N, std::size_t M, std::size_t R, kerbal::compatibility::uint32_t A>
				void mt_twist(kerbal::compatibility::uint32_t mt[]) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint32_t result_type;

					typedef kerbal::type_traits::integral_constant<result_type, (~static_cast<result_type>(0)) << R> UPPER_MASK; // most significant w-r bits
					typedef kerbal::type_traits::integral_constant<result_type, ~UPPER_MASK::value> LOWER_MASK; // least significant r bits
					KERBAL_STATIC_ASSERT(N >= M, "N should >= M");
					typedef kerbal::type_traits::integral_constant<std::size_t, N - M> NPM;

					typedef kerbal::type_traits::integral_constant<std::size_t, 256 / 32> STEP;
					const __m256i ymm_UPPER_MASK = _mm256_set1_epi32(static_cast<int>(UPPER_MASK::value)); // AVX
					const __m256i ymm_ZERO = _mm256_set1_epi32(0); // AVX
					const __m256i ymm_ONE = _mm256_set1_epi32(1); // AVX
					const __m256i ymm_A = _mm256_set1_epi32(static_cast<int>(A)); // AVX
					const __m256i ymm_iota = _mm256_setr_epi32(0, 1, 2, 3, 4, 5, 6, 7); // AVX

					std::size_t i = 0;
					for (; i + STEP::value <= NPM::value; i += STEP::value) {
						__m256i ymm_mti = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&mt[i])); // AVX
						__m256i ymm_mtip1 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&mt[i + 1])); // AVX
						__m256i ymm_y = _mm256_or_si256( // AVX2
								_mm256_and_si256(ymm_UPPER_MASK, ymm_mti), // AVX2
								_mm256_andnot_si256(ymm_UPPER_MASK, ymm_mtip1)); // AVX2
						__m256i ymm_mag_mask = _mm256_and_si256(ymm_y, ymm_ONE); // AVX2
						ymm_mag_mask = _mm256_sub_epi32(ymm_ZERO, ymm_mag_mask); // AVX2 <=> _mm256_cmpeq_epi32(ymm_mag_mask, ymm_ONE) AVX2
						ymm_mag_mask = _mm256_and_si256(ymm_mag_mask, ymm_A); // AVX2
						ymm_y = _mm256_srli_epi32(ymm_y, 1); // AVX2
						ymm_y = _mm256_xor_si256(ymm_y, ymm_mag_mask); // AVX2
						__m256i ymm_mtipm = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&mt[i + M])); // AVX
						ymm_mti = _mm256_xor_si256(ymm_y, ymm_mtipm); // AVX2
						_mm256_storeu_si256(reinterpret_cast<__m256i*>(&mt[i]), ymm_mti); // AVX
					}

					typedef kerbal::type_traits::integral_constant<int, NPM::value % STEP::value> FIRST_STEP_REMAIN;
					if (FIRST_STEP_REMAIN::value != 0) {
						__m256i ymm_mask = _mm256_cmpgt_epi32(_mm256_set1_epi32(FIRST_STEP_REMAIN::value), ymm_iota); // AVX2

						__m256i ymm_mti =
								(FIRST_STEP_REMAIN::value + M >= STEP::value) ?
								_mm256_loadu_si256(reinterpret_cast<const __m256i*>(&mt[i])) : // AVX
								_mm256_maskload_epi32(reinterpret_cast<const int*>(&mt[i]), ymm_mask); // AVX2
						__m256i ymm_mtip1 =
								(FIRST_STEP_REMAIN::value + M - 1 >= STEP::value) ?
								_mm256_loadu_si256(reinterpret_cast<const __m256i*>(&mt[i + 1])) : // AVX
								_mm256_maskload_epi32(reinterpret_cast<const int*>(&mt[i + 1]), ymm_mask); // AVX2
						__m256i ymm_y = _mm256_or_si256( // AVX2
								_mm256_and_si256(ymm_UPPER_MASK, ymm_mti), // AVX2
								_mm256_andnot_si256(ymm_UPPER_MASK, ymm_mtip1)); // AVX2
						__m256i ymm_mag_mask = _mm256_and_si256(ymm_y, ymm_ONE); // AVX2
						ymm_mag_mask = _mm256_sub_epi32(ymm_ZERO, ymm_mag_mask); // AVX2 <=> _mm256_cmpeq_epi32(ymm_mag_mask, ymm_ONE) AVX2
						ymm_mag_mask = _mm256_and_si256(ymm_mag_mask, ymm_A); // AVX2
						ymm_y = _mm256_srli_epi32(ymm_y, 1); // AVX2
						ymm_y = _mm256_xor_si256(ymm_y, ymm_mag_mask); // AVX2
						__m256i ymm_mtipm = _mm256_maskload_epi32(reinterpret_cast<const int*>(&mt[i + M]), ymm_mask); // AVX2
						ymm_mti = _mm256_xor_si256(ymm_y, ymm_mtipm); // AVX2
						_mm256_maskstore_epi32(reinterpret_cast<int*>(&mt[i]), ymm_mask, ymm_mti); // AVX2

						i = NPM::value;
					}

					for (; i + STEP::value <= N - 1; i += STEP::value) {
						__m256i ymm_mti = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&mt[i])); // AVX
						__m256i ymm_mtip1 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&mt[i + 1])); // AVX
						__m256i ymm_y = _mm256_or_si256( // AVX2
								_mm256_and_si256(ymm_UPPER_MASK, ymm_mti), // AVX2
								_mm256_andnot_si256(ymm_UPPER_MASK, ymm_mtip1)); // AVX2
						__m256i ymm_mag_mask = _mm256_and_si256(ymm_y, ymm_ONE); // AVX2
						ymm_mag_mask = _mm256_sub_epi32(ymm_ZERO, ymm_mag_mask); // AVX2 <=> _mm256_cmpeq_epi32(ymm_mag_mask, ymm_ONE) AVX2
						ymm_mag_mask = _mm256_and_si256(ymm_mag_mask, ymm_A); // AVX2
						ymm_y = _mm256_srli_epi32(ymm_y, 1); // AVX2
						ymm_y = _mm256_xor_si256(ymm_y, ymm_mag_mask); // AVX2
						__m256i ymm_mtipm = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&mt[i - NPM::value])); // AVX
						ymm_mti = _mm256_xor_si256(ymm_y, ymm_mtipm); // AVX2
						_mm256_storeu_si256(reinterpret_cast<__m256i*>(&mt[i]), ymm_mti); // AVX
					}

					typedef kerbal::type_traits::integral_constant<int, (M - 1) % STEP::value> SECOND_STEP_REMAIN;
					/*if (SECOND_STEP_REMAIN::value == 4) {
						__m128i xmm_mti = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&mt[i])); // SSE2
						__m128i xmm_mtip1 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&mt[i + 1])); // SSE2
						__m128i xmm_y = _mm_or_si128( // SSE2
								_mm_and_si128(_mm256_castsi256_si128(ymm_UPPER_MASK), xmm_mti), // SSE2, _mm256_castsi256_si128 AVX
								_mm_andnot_si128(_mm256_castsi256_si128(ymm_UPPER_MASK), xmm_mtip1)); // SSE2
						__m128i xmm_mag_mask = _mm_and_si128(xmm_y, _mm256_castsi256_si128(ymm_ONE)); // SSE2
						xmm_mag_mask = _mm_sub_epi32(_mm256_castsi256_si128(ymm_ZERO), xmm_mag_mask); // SSE2 <=> _mm_cmpeq_epi32(xmm_mag_mask, xmm_ONE) SSE2
						xmm_mag_mask = _mm_and_si128(xmm_mag_mask, _mm256_castsi256_si128(ymm_A)); // SSE2
						xmm_y = _mm_srli_epi32(xmm_y, 1); // SSE2
						xmm_y = _mm_xor_si128(xmm_y, xmm_mag_mask); // SSE2
						__m128i xmm_mtipm = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&mt[i - NPM::value])); // SSE2
						xmm_mti = _mm_xor_si128(xmm_y, xmm_mtipm); // SSE2
						_mm_storeu_si128(reinterpret_cast<__m128i*>(&mt[i]), xmm_mti); // SSE2
					} else*/ if (SECOND_STEP_REMAIN::value != 0) {
						__m256i ymm_mask = _mm256_cmpgt_epi32(_mm256_set1_epi32(SECOND_STEP_REMAIN::value), ymm_iota); // AVX2

						__m256i ymm_mti =
								(SECOND_STEP_REMAIN::value + 1 >= STEP::value) ?
								_mm256_loadu_si256(reinterpret_cast<const __m256i*>(&mt[i])) : // AVX
								_mm256_maskload_epi32(reinterpret_cast<const int*>(&mt[i]), ymm_mask); // AVX2
						__m256i ymm_mtip1 =
								(SECOND_STEP_REMAIN::value >= STEP::value) ?
								_mm256_loadu_si256(reinterpret_cast<const __m256i*>(&mt[i + 1])) : // AVX
								_mm256_maskload_epi32(reinterpret_cast<const int*>(&mt[i + 1]), ymm_mask); // AVX2
						__m256i ymm_y = _mm256_or_si256( // AVX2
								_mm256_and_si256(ymm_UPPER_MASK, ymm_mti), // AVX2
								_mm256_andnot_si256(ymm_UPPER_MASK, ymm_mtip1)); // AVX2
						__m256i ymm_mag_mask = _mm256_and_si256(ymm_y, ymm_ONE); // AVX2
						ymm_mag_mask = _mm256_sub_epi32(ymm_ZERO, ymm_mag_mask); // AVX2 <=> _mm256_cmpeq_epi32(ymm_mag_mask, ymm_ONE) AVX2
						ymm_mag_mask = _mm256_and_si256(ymm_mag_mask, ymm_A); // AVX2
						ymm_y = _mm256_srli_epi32(ymm_y, 1); // AVX2
						ymm_y = _mm256_xor_si256(ymm_y, ymm_mag_mask); // AVX2
						__m256i ymm_mtipm =
								(SECOND_STEP_REMAIN::value + NPM::value >= STEP::value) ?
								_mm256_loadu_si256(reinterpret_cast<const __m256i*>(&mt[i - NPM::value])) : // AVX
								_mm256_maskload_epi32(reinterpret_cast<const int*>(&mt[i - NPM::value]), ymm_mask); // AVX2
						ymm_mti = _mm256_xor_si256(ymm_y, ymm_mtipm); // AVX2
						_mm256_maskstore_epi32(reinterpret_cast<int*>(&mt[i]), ymm_mask, ymm_mti); // AVX2
					}

					// i = N - 1;

					result_type y = (mt[N - 1] & UPPER_MASK::value) | (mt[0] & LOWER_MASK::value);
					mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ ((y & 0x1UL) ? A : 0);

				}

				template <std::size_t N, std::size_t M, std::size_t R, kerbal::compatibility::uint64_t A>
				void mt_twist(kerbal::compatibility::uint64_t mt[]) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint64_t result_type;

					typedef kerbal::type_traits::integral_constant<result_type, (~static_cast<result_type>(0)) << R> UPPER_MASK; // most significant w-r bits
					typedef kerbal::type_traits::integral_constant<result_type, ~UPPER_MASK::value> LOWER_MASK; // least significant r bits
					KERBAL_STATIC_ASSERT(N >= M, "N should >= M");
					typedef kerbal::type_traits::integral_constant<std::size_t, N - M> NPM;

					typedef kerbal::type_traits::integral_constant<std::size_t, 256 / 64> STEP;
					const __m256i ymm_UPPER_MASK = _mm256_set1_epi64x(static_cast<long long>(UPPER_MASK::value)); // AVX
					const __m256i ymm_ZERO = _mm256_set1_epi64x(0); // AVX
					const __m256i ymm_ONE = _mm256_set1_epi64x(1); // AVX
					const __m256i ymm_A = _mm256_set1_epi64x(static_cast<long long>(A)); // AVX
					const __m256i ymm_iota = _mm256_setr_epi64x(0, 1, 2, 3); // AVX

					std::size_t i = 0;
					for (; i + STEP::value <= NPM::value; i += STEP::value) {
						__m256i ymm_mti = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&mt[i])); // AVX
						__m256i ymm_mtip1 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&mt[i + 1])); // AVX
						__m256i ymm_y = _mm256_or_si256( // AVX2
								_mm256_and_si256(ymm_UPPER_MASK, ymm_mti), // AVX2
								_mm256_andnot_si256(ymm_UPPER_MASK, ymm_mtip1)); // AVX2
						__m256i ymm_mag_mask = _mm256_and_si256(ymm_y, ymm_ONE); // AVX2
						ymm_mag_mask = _mm256_sub_epi64(ymm_ZERO, ymm_mag_mask); // AVX2 <=> _mm256_cmpeq_epi64(ymm_mag_mask, ymm_ONE) AVX2
						ymm_mag_mask = _mm256_and_si256(ymm_mag_mask, ymm_A); // AVX2
						ymm_y = _mm256_srli_epi64(ymm_y, 1); // AVX2
						ymm_y = _mm256_xor_si256(ymm_y, ymm_mag_mask); // AVX2
						__m256i ymm_mtipm = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&mt[i + M])); // AVX
						ymm_mti = _mm256_xor_si256(ymm_y, ymm_mtipm); // AVX2
						_mm256_storeu_si256(reinterpret_cast<__m256i*>(&mt[i]), ymm_mti); // AVX
					}

					typedef kerbal::type_traits::integral_constant<long long, NPM::value % STEP::value> FIRST_STEP_REMAIN;
					if (FIRST_STEP_REMAIN::value != 0) {
						__m256i ymm_mask = _mm256_cmpgt_epi64(_mm256_set1_epi64x(FIRST_STEP_REMAIN::value), ymm_iota); // AVX2

						__m256i ymm_mti =
								(FIRST_STEP_REMAIN::value + M >= STEP::value) ?
								_mm256_loadu_si256(reinterpret_cast<const __m256i*>(&mt[i])) : // AVX
								_mm256_maskload_epi64(reinterpret_cast<const long long*>(&mt[i]), ymm_mask); // AVX2
						__m256i ymm_mtip1 =
								(FIRST_STEP_REMAIN::value + M - 1 >= STEP::value) ?
								_mm256_loadu_si256(reinterpret_cast<const __m256i*>(&mt[i + 1])) : // AVX
								_mm256_maskload_epi64(reinterpret_cast<const long long*>(&mt[i + 1]), ymm_mask); // AVX2
						__m256i ymm_y = _mm256_or_si256( // AVX2
								_mm256_and_si256(ymm_UPPER_MASK, ymm_mti), // AVX2
								_mm256_andnot_si256(ymm_UPPER_MASK, ymm_mtip1)); // AVX2
						__m256i ymm_mag_mask = _mm256_and_si256(ymm_y, ymm_ONE); // AVX2
						ymm_mag_mask = _mm256_sub_epi64(ymm_ZERO, ymm_mag_mask); // AVX2 <=> _mm256_cmpeq_epi64(ymm_mag_mask, ymm_ONE) AVX2
						ymm_mag_mask = _mm256_and_si256(ymm_mag_mask, ymm_A); // AVX2
						ymm_y = _mm256_srli_epi64(ymm_y, 1); // AVX2
						ymm_y = _mm256_xor_si256(ymm_y, ymm_mag_mask); // AVX2
						__m256i ymm_mtipm = _mm256_maskload_epi64(reinterpret_cast<const long long*>(&mt[i + M]), ymm_mask); // AVX2
						ymm_mti = _mm256_xor_si256(ymm_y, ymm_mtipm); // AVX2
						_mm256_maskstore_epi64(reinterpret_cast<long long*>(&mt[i]), ymm_mask, ymm_mti); // AVX2

						i = NPM::value;
					}

					for (; i + STEP::value <= N - 1; i += STEP::value) {
						__m256i ymm_mti = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&mt[i])); // AVX
						__m256i ymm_mtip1 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&mt[i + 1])); // AVX
						__m256i ymm_y = _mm256_or_si256( // AVX2
								_mm256_and_si256(ymm_UPPER_MASK, ymm_mti), // AVX2
								_mm256_andnot_si256(ymm_UPPER_MASK, ymm_mtip1)); // AVX2
						__m256i ymm_mag_mask = _mm256_and_si256(ymm_y, ymm_ONE); // AVX2
						ymm_mag_mask = _mm256_sub_epi64(ymm_ZERO, ymm_mag_mask); // AVX2 <=> _mm256_cmpeq_epi64(ymm_mag_mask, ymm_ONE) AVX2
						ymm_mag_mask = _mm256_and_si256(ymm_mag_mask, ymm_A); // AVX2
						ymm_y = _mm256_srli_epi64(ymm_y, 1); // AVX2
						ymm_y = _mm256_xor_si256(ymm_y, ymm_mag_mask); // AVX2
						__m256i ymm_mtipm = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&mt[i - NPM::value])); // AVX
						ymm_mti = _mm256_xor_si256(ymm_y, ymm_mtipm); // AVX2
						_mm256_storeu_si256(reinterpret_cast<__m256i*>(&mt[i]), ymm_mti); // AVX
					}

					typedef kerbal::type_traits::integral_constant<long long, (M - 1) % STEP::value> SECOND_STEP_REMAIN;
					if (SECOND_STEP_REMAIN::value != 0) {
						__m256i ymm_mask = _mm256_cmpgt_epi64(_mm256_set1_epi64x(SECOND_STEP_REMAIN::value), ymm_iota); // AVX2

						__m256i ymm_mti =
								(SECOND_STEP_REMAIN::value + 1 >= STEP::value) ?
								_mm256_loadu_si256(reinterpret_cast<const __m256i*>(&mt[i])) : // AVX
								_mm256_maskload_epi64(reinterpret_cast<const long long*>(&mt[i]), ymm_mask); // AVX2
						__m256i ymm_mtip1 =
								(SECOND_STEP_REMAIN::value >= STEP::value) ?
								_mm256_loadu_si256(reinterpret_cast<const __m256i*>(&mt[i + 1])) : // AVX
								_mm256_maskload_epi64(reinterpret_cast<const long long*>(&mt[i + 1]), ymm_mask); // AVX2
						__m256i ymm_y = _mm256_or_si256( // AVX2
								_mm256_and_si256(ymm_UPPER_MASK, ymm_mti), // AVX2
								_mm256_andnot_si256(ymm_UPPER_MASK, ymm_mtip1)); // AVX2
						__m256i ymm_mag_mask = _mm256_and_si256(ymm_y, ymm_ONE); // AVX2
						ymm_mag_mask = _mm256_sub_epi64(ymm_ZERO, ymm_mag_mask); // AVX2 <=> _mm256_cmpeq_epi64(ymm_mag_mask, ymm_ONE) AVX2
						ymm_mag_mask = _mm256_and_si256(ymm_mag_mask, ymm_A); // AVX2
						ymm_y = _mm256_srli_epi64(ymm_y, 1); // AVX2
						ymm_y = _mm256_xor_si256(ymm_y, ymm_mag_mask); // AVX2
						__m256i ymm_mtipm =
								(SECOND_STEP_REMAIN::value + NPM::value >= STEP::value) ?
								_mm256_loadu_si256(reinterpret_cast<const __m256i*>(&mt[i - NPM::value])) : // AVX
								_mm256_maskload_epi64(reinterpret_cast<const long long*>(&mt[i - NPM::value]), ymm_mask); // AVX2
						ymm_mti = _mm256_xor_si256(ymm_y, ymm_mtipm); // AVX2
						_mm256_maskstore_epi64(reinterpret_cast<long long*>(&mt[i]), ymm_mask, ymm_mti); // AVX2
					}

					// i = N - 1;

					result_type y = (mt[N - 1] & UPPER_MASK::value) | (mt[0] & LOWER_MASK::value);
					mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ ((y & 0x1UL) ? A : 0);

				}

			} // namespace avx2

		} // namespace detail

	} // namespace random

} // namespace kerbal


#endif // KERBAL_RANDOM_DETAIL_MT_TWIST_MT_TWIST_AVX2_HPP
