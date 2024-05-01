/**
 * @file       mt_twist_and_generate.avx2.part.hpp
 * @brief
 * @date       2024-05-01
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_DETAIL_MT_TWIST_AND_GENERATE_MT_TWIST_AND_GENERATE_AVX2_PART_HPP
#define KERBAL_RANDOM_DETAIL_MT_TWIST_AND_GENERATE_MT_TWIST_AND_GENERATE_AVX2_PART_HPP

#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/config/architecture.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>

#include <immintrin.h>

#include <kerbal/random/detail/mt_twist_and_generate/mt_twist_and_generate.plain.part.hpp>


namespace kerbal
{

	namespace random
	{

		namespace detail
		{

			namespace avx2
			{

#			define TWIST_AVX2_U32() do { \
						ymm_y = _mm256_or_si256( /* AVX2 */ \
							_mm256_and_si256(ymm_UPPER_MASK, ymm_mti), /* AVX2 */ \
							_mm256_andnot_si256(ymm_UPPER_MASK, ymm_mtip1)); /* AVX2 */ \
						__m256i ymm_mag_mask = _mm256_and_si256(ymm_y, ymm_ONE); /* AVX2 */ \
						ymm_mag_mask = _mm256_sub_epi32(ymm_ZERO, ymm_mag_mask); /* AVX2 <=> _mm256_cmpeq_epi32(ymm_mag_mask, ymm_ONE) AVX2 */ \
						ymm_mag_mask = _mm256_and_si256(ymm_mag_mask, ymm_A); /* AVX2 */ \
						ymm_y = _mm256_srli_epi32(ymm_y, 1); /* AVX2 */ \
						ymm_y = _mm256_xor_si256(ymm_y, ymm_mag_mask); /* AVX2 */ \
					} while (false)

#			define GENERATE_AVX2_U32() do { \
						ymm_shift = _mm256_srli_epi32(ymm_mti, U); /* AVX2 */ \
						ymm_and = _mm256_and_si256(ymm_shift, ymm_D); /* AVX2 */ \
						ymm_mti = _mm256_xor_si256(ymm_mti, ymm_and); /* AVX2 */ \
 \
						ymm_shift = _mm256_slli_epi32(ymm_mti, S); /* AVX2 */ \
						ymm_and = _mm256_and_si256(ymm_shift, ymm_B); /* AVX2 */ \
						ymm_mti = _mm256_xor_si256(ymm_mti, ymm_and); /* AVX2 */ \
 \
						ymm_shift = _mm256_slli_epi32(ymm_mti, T); /* AVX2 */ \
						ymm_and = _mm256_and_si256(ymm_shift, ymm_C); /* AVX2 */ \
						ymm_mti = _mm256_xor_si256(ymm_mti, ymm_and); /* AVX2 */ \
 \
						ymm_shift = _mm256_srli_epi32(ymm_mti, L); /* AVX2 */ \
						ymm_mti = _mm256_xor_si256(ymm_mti, ymm_shift); /* AVX2 */ \
					} while (false)

				template <
					std::size_t N, std::size_t M, std::size_t R, kerbal::compatibility::uint32_t A,
					std::size_t U, kerbal::compatibility::uint32_t D,
					std::size_t S, kerbal::compatibility::uint32_t B,
					std::size_t T, kerbal::compatibility::uint32_t C,
					std::size_t L
				>
				void mt_twist_and_generate(
					kerbal::compatibility::uint32_t mt[],
					kerbal::compatibility::uint32_t out[]
				) KERBAL_NOEXCEPT
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
					const __m256i ymm_B = _mm256_set1_epi32(B); // AVX
					const __m256i ymm_C = _mm256_set1_epi32(C); // AVX
					const __m256i ymm_D = _mm256_set1_epi32(D); // AVX

					std::size_t i = 0;
					for (; i + STEP::value <= NPM::value; i += STEP::value) {
						__m256i ymm_mti = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&mt[i])); // AVX
						__m256i ymm_mtip1 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&mt[i + 1])); // AVX
						__m256i ymm_y;
						TWIST_AVX2_U32();
						__m256i ymm_mtipm = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&mt[i + M])); // AVX
						ymm_mti = _mm256_xor_si256(ymm_y, ymm_mtipm); // AVX2
						_mm256_storeu_si256(reinterpret_cast<__m256i *>(&mt[i]), ymm_mti); // AVX

						__m256i ymm_shift, ymm_and;
						GENERATE_AVX2_U32();
						_mm256_storeu_si256(reinterpret_cast<__m256i *>(&out[i]), ymm_mti); // AVX
					}

					typedef kerbal::type_traits::integral_constant<int, NPM::value % STEP::value> FIRST_STEP_REMAIN;
					if (FIRST_STEP_REMAIN::value != 0) {
						__m256i ymm_mask = _mm256_cmpgt_epi32(_mm256_set1_epi32(FIRST_STEP_REMAIN::value), ymm_iota); // AVX2

						__m256i ymm_mti =
							(FIRST_STEP_REMAIN::value + M >= STEP::value) ?
							_mm256_loadu_si256(reinterpret_cast<const __m256i *>(&mt[i])) : // AVX
							_mm256_maskload_epi32(reinterpret_cast<const int *>(&mt[i]), ymm_mask); // AVX2
						__m256i ymm_mtip1 =
							(FIRST_STEP_REMAIN::value + M - 1 >= STEP::value) ?
							_mm256_loadu_si256(reinterpret_cast<const __m256i *>(&mt[i + 1])) : // AVX
							_mm256_maskload_epi32(reinterpret_cast<const int *>(&mt[i + 1]), ymm_mask); // AVX2
						__m256i ymm_y;
						TWIST_AVX2_U32();
						__m256i ymm_mtipm = _mm256_maskload_epi32(reinterpret_cast<const int *>(&mt[i + M]), ymm_mask); // AVX2
						ymm_mti = _mm256_xor_si256(ymm_y, ymm_mtipm); // AVX2
						_mm256_maskstore_epi32(reinterpret_cast<int *>(&mt[i]), ymm_mask, ymm_mti); // AVX2

						__m256i ymm_shift, ymm_and;
						GENERATE_AVX2_U32();
						_mm256_maskstore_epi32(reinterpret_cast<int *>(&out[i]), ymm_mask, ymm_mti); // AVX

						i = NPM::value;
					}

					for (; i + STEP::value <= N - 1; i += STEP::value) {
						__m256i ymm_mti = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&mt[i])); // AVX
						__m256i ymm_mtip1 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&mt[i + 1])); // AVX
						__m256i ymm_y;
						TWIST_AVX2_U32();
						__m256i ymm_mtipm = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&mt[i - NPM::value])); // AVX
						ymm_mti = _mm256_xor_si256(ymm_y, ymm_mtipm); // AVX2
						_mm256_storeu_si256(reinterpret_cast<__m256i *>(&mt[i]), ymm_mti); // AVX

						__m256i ymm_shift, ymm_and;
						GENERATE_AVX2_U32();
						_mm256_storeu_si256(reinterpret_cast<__m256i *>(&out[i]), ymm_mti); // AVX
					}

					typedef kerbal::type_traits::integral_constant<int, (M - 1) % STEP::value> SECOND_STEP_REMAIN;
					if (SECOND_STEP_REMAIN::value != 0) {
						__m256i ymm_mask = _mm256_cmpgt_epi32(_mm256_set1_epi32(SECOND_STEP_REMAIN::value), ymm_iota); // AVX2
						__m256i ymm_maskp1 = _mm256_cmpgt_epi32(_mm256_set1_epi32(SECOND_STEP_REMAIN::value + 1), ymm_iota); // AVX2

						__m256i ymm_mti =
							(SECOND_STEP_REMAIN::value + 1 >= STEP::value) ?
							_mm256_loadu_si256(reinterpret_cast<const __m256i *>(&mt[i])) : // AVX
							_mm256_maskload_epi32(reinterpret_cast<const int *>(&mt[i]), ymm_maskp1); // AVX2
						__m256i ymm_mtip1 = _mm256_maskload_epi32(reinterpret_cast<const int *>(&mt[i + 1]), ymm_mask); // AVX2
						// SECOND_STEP_REMAIN::value >= STEP::value always false

#	if 0
						ymm_mtip1 = _mm256_insert_epi32(ymm_mtip1, mt[0], SECOND_STEP_REMAIN::value); // AVX
#	else
						// support of _mm256_insert_epi32 are too bad

						typedef kerbal::type_traits::integral_constant<std::size_t, 128 / 32> HALF_STEP;
						__m128i xmm_insert_tmp = _mm256_extracti128_si256(ymm_mtip1, SECOND_STEP_REMAIN::value / HALF_STEP::value);
						xmm_insert_tmp = _mm_insert_epi32(xmm_insert_tmp, mt[0], SECOND_STEP_REMAIN::value % HALF_STEP::value);
						ymm_mtip1 = _mm256_inserti128_si256(ymm_mtip1, xmm_insert_tmp, SECOND_STEP_REMAIN::value / HALF_STEP::value);
#	endif

						__m256i ymm_y;
						TWIST_AVX2_U32();
						__m256i ymm_mtipm =
							(SECOND_STEP_REMAIN::value + NPM::value + 1 >= STEP::value) ?
							_mm256_loadu_si256(reinterpret_cast<const __m256i *>(&mt[i - NPM::value])) : // AVX
							_mm256_maskload_epi32(reinterpret_cast<const int *>(&mt[i - NPM::value]), ymm_maskp1); // AVX2
						ymm_mti = _mm256_xor_si256(ymm_y, ymm_mtipm); // AVX2
						_mm256_maskstore_epi32(reinterpret_cast<int *>(&mt[i]), ymm_maskp1, ymm_mti); // AVX2

						__m256i ymm_shift, ymm_and;
						GENERATE_AVX2_U32();
						_mm256_maskstore_epi32(reinterpret_cast<int *>(&out[i]), ymm_maskp1, ymm_mti); // AVX2
					} else {

						// i = N - 1;
						EACH3();
					}

				}

				template <
					std::size_t N, std::size_t M, std::size_t R, kerbal::compatibility::uint64_t A,
					std::size_t U, kerbal::compatibility::uint64_t D,
					std::size_t S, kerbal::compatibility::uint64_t B,
					std::size_t T, kerbal::compatibility::uint64_t C,
					std::size_t L
				>
				void mt_twist_and_generate(
					kerbal::compatibility::uint64_t mt[],
					kerbal::compatibility::uint64_t out[]
				) KERBAL_NOEXCEPT
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
						__m256i ymm_mti = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&mt[i])); // AVX
						__m256i ymm_mtip1 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&mt[i + 1])); // AVX
						__m256i ymm_y = _mm256_or_si256( // AVX2
							_mm256_and_si256(ymm_UPPER_MASK, ymm_mti), // AVX2
							_mm256_andnot_si256(ymm_UPPER_MASK, ymm_mtip1)); // AVX2
						__m256i ymm_mag_mask = _mm256_and_si256(ymm_y, ymm_ONE); // AVX2
						ymm_mag_mask = _mm256_sub_epi64(ymm_ZERO, ymm_mag_mask); // AVX2 <=> _mm256_cmpeq_epi64(ymm_mag_mask, ymm_ONE) AVX2
						ymm_mag_mask = _mm256_and_si256(ymm_mag_mask, ymm_A); // AVX2
						ymm_y = _mm256_srli_epi64(ymm_y, 1); // AVX2
						ymm_y = _mm256_xor_si256(ymm_y, ymm_mag_mask); // AVX2
						__m256i ymm_mtipm = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&mt[i + M])); // AVX
						ymm_mti = _mm256_xor_si256(ymm_y, ymm_mtipm); // AVX2
						_mm256_storeu_si256(reinterpret_cast<__m256i *>(&mt[i]), ymm_mti); // AVX
					}

					typedef kerbal::type_traits::integral_constant<long long, NPM::value % STEP::value> FIRST_STEP_REMAIN;
					if (FIRST_STEP_REMAIN::value != 0) {
						__m256i ymm_mask = _mm256_cmpgt_epi64(_mm256_set1_epi64x(FIRST_STEP_REMAIN::value), ymm_iota); // AVX2

						__m256i ymm_mti =
							(FIRST_STEP_REMAIN::value + M >= STEP::value) ?
							_mm256_loadu_si256(reinterpret_cast<const __m256i *>(&mt[i])) : // AVX
							_mm256_maskload_epi64(reinterpret_cast<const long long *>(&mt[i]), ymm_mask); // AVX2
						__m256i ymm_mtip1 =
							(FIRST_STEP_REMAIN::value + M - 1 >= STEP::value) ?
							_mm256_loadu_si256(reinterpret_cast<const __m256i *>(&mt[i + 1])) : // AVX
							_mm256_maskload_epi64(reinterpret_cast<const long long *>(&mt[i + 1]), ymm_mask); // AVX2
						__m256i ymm_y = _mm256_or_si256( // AVX2
							_mm256_and_si256(ymm_UPPER_MASK, ymm_mti), // AVX2
							_mm256_andnot_si256(ymm_UPPER_MASK, ymm_mtip1)); // AVX2
						__m256i ymm_mag_mask = _mm256_and_si256(ymm_y, ymm_ONE); // AVX2
						ymm_mag_mask = _mm256_sub_epi64(ymm_ZERO, ymm_mag_mask); // AVX2 <=> _mm256_cmpeq_epi64(ymm_mag_mask, ymm_ONE) AVX2
						ymm_mag_mask = _mm256_and_si256(ymm_mag_mask, ymm_A); // AVX2
						ymm_y = _mm256_srli_epi64(ymm_y, 1); // AVX2
						ymm_y = _mm256_xor_si256(ymm_y, ymm_mag_mask); // AVX2
						__m256i ymm_mtipm = _mm256_maskload_epi64(reinterpret_cast<const long long *>(&mt[i + M]), ymm_mask); // AVX2
						ymm_mti = _mm256_xor_si256(ymm_y, ymm_mtipm); // AVX2
						_mm256_maskstore_epi64(reinterpret_cast<long long *>(&mt[i]), ymm_mask, ymm_mti); // AVX2

						i = NPM::value;
					}

					for (; i + STEP::value <= N - 1; i += STEP::value) {
						__m256i ymm_mti = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&mt[i])); // AVX
						__m256i ymm_mtip1 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&mt[i + 1])); // AVX
						__m256i ymm_y = _mm256_or_si256( // AVX2
							_mm256_and_si256(ymm_UPPER_MASK, ymm_mti), // AVX2
							_mm256_andnot_si256(ymm_UPPER_MASK, ymm_mtip1)); // AVX2
						__m256i ymm_mag_mask = _mm256_and_si256(ymm_y, ymm_ONE); // AVX2
						ymm_mag_mask = _mm256_sub_epi64(ymm_ZERO, ymm_mag_mask); // AVX2 <=> _mm256_cmpeq_epi64(ymm_mag_mask, ymm_ONE) AVX2
						ymm_mag_mask = _mm256_and_si256(ymm_mag_mask, ymm_A); // AVX2
						ymm_y = _mm256_srli_epi64(ymm_y, 1); // AVX2
						ymm_y = _mm256_xor_si256(ymm_y, ymm_mag_mask); // AVX2
						__m256i ymm_mtipm = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&mt[i - NPM::value])); // AVX
						ymm_mti = _mm256_xor_si256(ymm_y, ymm_mtipm); // AVX2
						_mm256_storeu_si256(reinterpret_cast<__m256i *>(&mt[i]), ymm_mti); // AVX
					}

					typedef kerbal::type_traits::integral_constant<long long, (M - 1) % STEP::value> SECOND_STEP_REMAIN;
					if (SECOND_STEP_REMAIN::value != 0) {
						__m256i ymm_mask = _mm256_cmpgt_epi64(_mm256_set1_epi64x(SECOND_STEP_REMAIN::value), ymm_iota); // AVX2
						__m256i ymm_maskp1 = _mm256_cmpgt_epi64(_mm256_set1_epi64x(SECOND_STEP_REMAIN::value + 1), ymm_iota); // AVX2

						__m256i ymm_mti =
							(SECOND_STEP_REMAIN::value + 1 >= STEP::value) ?
							_mm256_loadu_si256(reinterpret_cast<const __m256i *>(&mt[i])) : // AVX
							_mm256_maskload_epi64(reinterpret_cast<const long long *>(&mt[i]), ymm_maskp1); // AVX2
						__m256i ymm_mtip1 = _mm256_maskload_epi64(reinterpret_cast<const long long *>(&mt[i + 1]), ymm_mask); // AVX2
						// SECOND_STEP_REMAIN::value >= STEP::value always false

#	if 0
						ymm_mtip1 = _mm256_insert_epi64(ymm_mtip1, mt[0], SECOND_STEP_REMAIN::value); // AVX
#	else
						// support of _mm256_insert_epi64 are too bad

						typedef kerbal::type_traits::integral_constant<std::size_t, 128 / 64> HALF_STEP;
						__m128i xmm_insert_tmp = _mm256_extracti128_si256(ymm_mtip1, SECOND_STEP_REMAIN::value / HALF_STEP::value);
#		if KERBAL_ARCHITECTURE == KERBAL_ARCHITECTURE_X86
						xmm_insert_tmp = _mm_insert_epi32(xmm_insert_tmp, mt[0] >> 32, SECOND_STEP_REMAIN::value % HALF_STEP::value * 2 + 1);
						xmm_insert_tmp = _mm_insert_epi32(xmm_insert_tmp, mt[0] & 0xffffffff, SECOND_STEP_REMAIN::value % HALF_STEP::value * 2);
#		else
						xmm_insert_tmp = _mm_insert_epi64(xmm_insert_tmp, mt[0], SECOND_STEP_REMAIN::value % HALF_STEP::value);
#		endif
						ymm_mtip1 = _mm256_inserti128_si256(ymm_mtip1, xmm_insert_tmp, SECOND_STEP_REMAIN::value / HALF_STEP::value);
#	endif

						__m256i ymm_y = _mm256_or_si256( // AVX2
							_mm256_and_si256(ymm_UPPER_MASK, ymm_mti), // AVX2
							_mm256_andnot_si256(ymm_UPPER_MASK, ymm_mtip1)); // AVX2
						__m256i ymm_mag_mask = _mm256_and_si256(ymm_y, ymm_ONE); // AVX2
						ymm_mag_mask = _mm256_sub_epi64(ymm_ZERO, ymm_mag_mask); // AVX2 <=> _mm256_cmpeq_epi64(ymm_mag_mask, ymm_ONE) AVX2
						ymm_mag_mask = _mm256_and_si256(ymm_mag_mask, ymm_A); // AVX2
						ymm_y = _mm256_srli_epi64(ymm_y, 1); // AVX2
						ymm_y = _mm256_xor_si256(ymm_y, ymm_mag_mask); // AVX2
						__m256i ymm_mtipm =
							(SECOND_STEP_REMAIN::value + NPM::value + 1 >= STEP::value) ?
							_mm256_loadu_si256(reinterpret_cast<const __m256i *>(&mt[i - NPM::value])) : // AVX
							_mm256_maskload_epi64(reinterpret_cast<const long long *>(&mt[i - NPM::value]), ymm_maskp1); // AVX2
						ymm_mti = _mm256_xor_si256(ymm_y, ymm_mtipm); // AVX2
						_mm256_maskstore_epi64(reinterpret_cast<long long *>(&mt[i]), ymm_maskp1, ymm_mti); // AVX2
					} else {

						// i = N - 1;
						EACH3();
					}

				}

			} // namespace avx2

		} // namespace detail

	} // namespace random

} // namespace kerbal


#endif // KERBAL_RANDOM_DETAIL_MT_TWIST_AND_GENERATE_MT_TWIST_AND_GENERATE_AVX2_PART_HPP
