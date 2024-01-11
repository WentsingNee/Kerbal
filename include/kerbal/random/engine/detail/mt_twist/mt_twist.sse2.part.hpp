/**
 * @file       mt_twist.sse2.part.hpp
 * @brief
 * @date       2022-07-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_ENGINE_DETAIL_MT_TWIST_MT_TWIST_SSE2_PART_HPP
#define KERBAL_RANDOM_ENGINE_DETAIL_MT_TWIST_MT_TWIST_SSE2_PART_HPP

#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>

#include <emmintrin.h>

#include <kerbal/random/engine/detail/mt_twist/mt_twist.plain.part.hpp>


namespace kerbal
{

	namespace random
	{

		namespace detail
		{

			namespace sse2
			{

				template <std::size_t N, std::size_t M, std::size_t R, kerbal::compatibility::uint32_t A>
				void mt_twist(kerbal::compatibility::uint32_t mt[]) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint32_t result_type;

					typedef kerbal::type_traits::integral_constant<result_type, (~static_cast<result_type>(0)) << R> UPPER_MASK; // most significant w-r bits
					typedef kerbal::type_traits::integral_constant<result_type, ~UPPER_MASK::value> LOWER_MASK; // least significant r bits
					KERBAL_STATIC_ASSERT(N >= M, "N should >= M");
					typedef kerbal::type_traits::integral_constant<std::size_t, N - M> NPM;

					typedef kerbal::type_traits::integral_constant<std::size_t, 128 / 32> STEP;
					const __m128i xmm_UPPER_MASK = _mm_set1_epi32(static_cast<int>(UPPER_MASK::value)); // SSE2
					const __m128i xmm_ZERO = _mm_set1_epi32(0); // SSE2
					const __m128i xmm_ONE = _mm_set1_epi32(1); // SSE2
					const __m128i xmm_A = _mm_set1_epi32(static_cast<int>(A)); // SSE2

					unsigned int i = 0; // Note: gcc unreasonable warning: iteration 4611686018427387903 invokes undefined behavior [-Waggressive-loop-optimizations]
					for (; i + STEP::value <= NPM::value; i += STEP::value) {
						__m128i xmm_mti = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&mt[i])); // SSE2
						__m128i xmm_mtip1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&mt[i + 1])); // SSE2
						__m128i xmm_y = _mm_or_si128( // SSE2
							_mm_and_si128(xmm_UPPER_MASK, xmm_mti), // SSE2
							_mm_andnot_si128(xmm_UPPER_MASK, xmm_mtip1)); // SSE2
						__m128i xmm_mag_mask = _mm_and_si128(xmm_y, xmm_ONE); // SSE2
						xmm_mag_mask = _mm_sub_epi32(xmm_ZERO, xmm_mag_mask); // SSE2 <=> _mm_cmpeq_epi32(xmm_mag_mask, xmm_ONE) SSE2
						xmm_mag_mask = _mm_and_si128(xmm_mag_mask, xmm_A); // SSE2
						xmm_y = _mm_srli_epi32(xmm_y, 1); // SSE2
						xmm_y = _mm_xor_si128(xmm_y, xmm_mag_mask); // SSE2
						__m128i xmm_mtipm = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&mt[i + M])); // SSE2
						xmm_mti = _mm_xor_si128(xmm_y, xmm_mtipm); // SSE2
						_mm_storeu_si128(reinterpret_cast<__m128i *>(&mt[i]), xmm_mti); // SSE2
					}

					typedef kerbal::type_traits::integral_constant<int, NPM::value % STEP::value> FIRST_STEP_REMAIN;
					if (FIRST_STEP_REMAIN::value == 3) {
						__m128i xmm_mti = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(&mt[i])); // SSE2
						__m128i xmm_mtip1 = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(&mt[i + 1])); // SSE2
						__m128i xmm_y = _mm_or_si128( // SSE2
							_mm_and_si128(xmm_UPPER_MASK, xmm_mti), // SSE2
							_mm_andnot_si128(xmm_UPPER_MASK, xmm_mtip1)); // SSE2
						__m128i xmm_mag_mask = _mm_and_si128(xmm_y, xmm_ONE); // SSE2
						xmm_mag_mask = _mm_sub_epi32(xmm_ZERO, xmm_mag_mask); // SSE2 <=> _mm_cmpeq_epi32(xmm_mag_mask, xmm_ONE) SSE2
						xmm_mag_mask = _mm_and_si128(xmm_mag_mask, xmm_A); // SSE2
						xmm_y = _mm_srli_epi32(xmm_y, 1); // SSE2
						xmm_y = _mm_xor_si128(xmm_y, xmm_mag_mask); // SSE2
						__m128i xmm_mtipm = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(&mt[i + M])); // SSE2
						xmm_mti = _mm_xor_si128(xmm_y, xmm_mtipm); // SSE2
						_mm_storel_epi64(reinterpret_cast<__m128i *>(&mt[i]), xmm_mti); // SSE2

						i += 2;
						EACH1(i);
					} else if (FIRST_STEP_REMAIN::value == 2) {
						__m128i xmm_mti = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(&mt[i])); // SSE2
						__m128i xmm_mtip1 = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(&mt[i + 1])); // SSE2
						__m128i xmm_y = _mm_or_si128( // SSE2
							_mm_and_si128(xmm_UPPER_MASK, xmm_mti), // SSE2
							_mm_andnot_si128(xmm_UPPER_MASK, xmm_mtip1)); // SSE2
						__m128i xmm_mag_mask = _mm_and_si128(xmm_y, xmm_ONE); // SSE2
						xmm_mag_mask = _mm_sub_epi32(xmm_ZERO, xmm_mag_mask); // SSE2 <=> _mm_cmpeq_epi32(xmm_mag_mask, xmm_ONE) SSE2
						xmm_mag_mask = _mm_and_si128(xmm_mag_mask, xmm_A); // SSE2
						xmm_y = _mm_srli_epi32(xmm_y, 1); // SSE2
						xmm_y = _mm_xor_si128(xmm_y, xmm_mag_mask); // SSE2
						__m128i xmm_mtipm = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(&mt[i + M])); // SSE2
						xmm_mti = _mm_xor_si128(xmm_y, xmm_mtipm); // SSE2
						_mm_storel_epi64(reinterpret_cast<__m128i *>(&mt[i]), xmm_mti); // SSE2
					} else if (FIRST_STEP_REMAIN::value == 1) {
						EACH1(i);
					}

					i = NPM::value;

#if 0 // mtsimd

					if (FIRST_STEP_REMAIN::value != 0) {
						__m128i xmm_mti = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&mt[i])); // SSE2
						__m128i xmm_mtip1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&mt[i + 1])); // SSE2
						__m128i xmm_y = _mm_or_si128( // SSE2
							_mm_and_si128(xmm_UPPER_MASK, xmm_mti), // SSE2
							_mm_andnot_si128(xmm_UPPER_MASK, xmm_mtip1) // SSE2
						);
						__m128i xmm_mag_mask = _mm_and_si128(xmm_y, xmm_ONE); // SSE2
						xmm_mag_mask = _mm_sub_epi32(xmm_ZERO, xmm_mag_mask); // SSE2 <=> _mm_cmpeq_epi32(xmm_mag_mask, xmm_ONE) SSE2
						xmm_mag_mask = _mm_and_si128(xmm_mag_mask, xmm_A); // SSE2
						xmm_y = _mm_srli_epi32(xmm_y, 1); // SSE2
						xmm_mti = _mm_xor_si128(xmm_y, xmm_mag_mask); // SSE2
						_mm_storeu_si128(reinterpret_cast<__m128i *>(&mt[i]), xmm_mti); // SSE2

						unsigned int j = 0;
						for (; j < FIRST_STEP_REMAIN::value; ++j) {
							mt[i] ^= mt[i + M];
							++i;
						}
						for (; j < STEP::value; ++j) {
							mt[i] ^= mt[i - NPM::value];
							++i;
						}
					}

#endif

					for (; i + STEP::value <= N - 1; i += STEP::value) {
						__m128i xmm_mti = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&mt[i])); // SSE2
						__m128i xmm_mtip1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&mt[i + 1])); // SSE2
						__m128i xmm_y = _mm_or_si128( // SSE2
							_mm_and_si128(xmm_UPPER_MASK, xmm_mti), // SSE2
							_mm_andnot_si128(xmm_UPPER_MASK, xmm_mtip1)); // SSE2
						__m128i xmm_mag_mask = _mm_and_si128(xmm_y, xmm_ONE); // SSE2
						xmm_mag_mask = _mm_sub_epi32(xmm_ZERO, xmm_mag_mask); // SSE2 <=> _mm_cmpeq_epi32(xmm_mag_mask, xmm_ONE) SSE2
						xmm_mag_mask = _mm_and_si128(xmm_mag_mask, xmm_A); // SSE2
						xmm_y = _mm_srli_epi32(xmm_y, 1); // SSE2
						xmm_y = _mm_xor_si128(xmm_y, xmm_mag_mask); // SSE2
						__m128i xmm_mtipm = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&mt[i - (NPM::value)])); // SSE2
						xmm_mti = _mm_xor_si128(xmm_y, xmm_mtipm); // SSE2
						_mm_storeu_si128(reinterpret_cast<__m128i *>(&mt[i]), xmm_mti); // SSE2
					}

					typedef kerbal::type_traits::integral_constant<int, (M - 1) % STEP::value> SECOND_STEP_REMAIN;
					if (SECOND_STEP_REMAIN::value == 3) {
						__m128i xmm_mti = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(&mt[i])); // SSE2
						__m128i xmm_mtip1 = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(&mt[i + 1])); // SSE2
						__m128i xmm_y = _mm_or_si128( // SSE2
							_mm_and_si128(xmm_UPPER_MASK, xmm_mti), // SSE2
							_mm_andnot_si128(xmm_UPPER_MASK, xmm_mtip1)); // SSE2
						__m128i xmm_mag_mask = _mm_and_si128(xmm_y, xmm_ONE); // SSE2
						xmm_mag_mask = _mm_sub_epi32(xmm_ZERO, xmm_mag_mask); // SSE2 <=> _mm_cmpeq_epi32(xmm_mag_mask, xmm_ONE) SSE2
						xmm_mag_mask = _mm_and_si128(xmm_mag_mask, xmm_A); // SSE2
						xmm_y = _mm_srli_epi32(xmm_y, 1); // SSE2
						xmm_y = _mm_xor_si128(xmm_y, xmm_mag_mask); // SSE2
						__m128i xmm_mtipm = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(&mt[i - (NPM::value)])); // SSE2
						xmm_mti = _mm_xor_si128(xmm_y, xmm_mtipm); // SSE2
						_mm_storel_epi64(reinterpret_cast<__m128i *>(&mt[i]), xmm_mti); // SSE2

						i += 2;
						EACH2(i);
					} else if (SECOND_STEP_REMAIN::value == 2) {
						__m128i xmm_mti = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(&mt[i])); // SSE2
						__m128i xmm_mtip1 = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(&mt[i + 1])); // SSE2
						__m128i xmm_y = _mm_or_si128( // SSE2
							_mm_and_si128(xmm_UPPER_MASK, xmm_mti), // SSE2
							_mm_andnot_si128(xmm_UPPER_MASK, xmm_mtip1)); // SSE2
						__m128i xmm_mag_mask = _mm_and_si128(xmm_y, xmm_ONE); // SSE2
						xmm_mag_mask = _mm_sub_epi32(xmm_ZERO, xmm_mag_mask); // SSE2 <=> _mm_cmpeq_epi32(xmm_mag_mask, xmm_ONE) SSE2
						xmm_mag_mask = _mm_and_si128(xmm_mag_mask, xmm_A); // SSE2
						xmm_y = _mm_srli_epi32(xmm_y, 1); // SSE2
						xmm_y = _mm_xor_si128(xmm_y, xmm_mag_mask); // SSE2
						__m128i xmm_mtipm = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(&mt[i - (NPM::value)])); // SSE2
						xmm_mti = _mm_xor_si128(xmm_y, xmm_mtipm); // SSE2
						_mm_storel_epi64(reinterpret_cast<__m128i *>(&mt[i]), xmm_mti); // SSE2
					} else if (SECOND_STEP_REMAIN::value == 1) {
						EACH2(i);
						++i;
					}

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

					typedef kerbal::type_traits::integral_constant<std::size_t, 128 / 64> STEP;
					const __m128i xmm_UPPER_MASK = _mm_set1_epi64x(static_cast<long long>(UPPER_MASK::value)); // SSE2
					const __m128i xmm_ZERO = _mm_set1_epi64x(0); // SSE2
					const __m128i xmm_ONE = _mm_set1_epi64x(1); // SSE2
					const __m128i xmm_A = _mm_set1_epi64x(static_cast<long long>(A)); // SSE2

					std::size_t i = 0;
					for (; i + STEP::value <= NPM::value; i += STEP::value) {
						__m128i xmm_mti = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&mt[i])); // SSE2
						__m128i xmm_mtip1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&mt[i + 1])); // SSE2
						__m128i xmm_y = _mm_or_si128( // SSE2
							_mm_and_si128(xmm_UPPER_MASK, xmm_mti), // SSE2
							_mm_andnot_si128(xmm_UPPER_MASK, xmm_mtip1)); // SSE2
						__m128i xmm_mag_mask = _mm_and_si128(xmm_y, xmm_ONE); // SSE2
						xmm_mag_mask = _mm_sub_epi64(xmm_ZERO, xmm_mag_mask); // SSE2 <=> _mm_cmpeq_epi64(xmm_mag_mask, xmm_ONE) SSE4.1
						xmm_mag_mask = _mm_and_si128(xmm_mag_mask, xmm_A); // SSE2
						xmm_y = _mm_srli_epi64(xmm_y, 1); // SSE2
						xmm_y = _mm_xor_si128(xmm_y, xmm_mag_mask); // SSE2
						__m128i xmm_mtipm = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&mt[i + M])); // SSE2
						xmm_mti = _mm_xor_si128(xmm_y, xmm_mtipm); // SSE2
						_mm_storeu_si128(reinterpret_cast<__m128i *>(&mt[i]), xmm_mti); // SSE2
					}

					typedef kerbal::type_traits::integral_constant<long long, NPM::value % STEP::value> FIRST_STEP_REMAIN;
					if (FIRST_STEP_REMAIN::value != 0) {
						EACH1(i);
					}

					i = NPM::value;

					for (; i + STEP::value <= N - 1; i += STEP::value) {
						__m128i xmm_mti = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&mt[i])); // SSE2
						__m128i xmm_mtip1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&mt[i + 1])); // SSE2
						__m128i xmm_y = _mm_or_si128( // SSE2
							_mm_and_si128(xmm_UPPER_MASK, xmm_mti), // SSE2
							_mm_andnot_si128(xmm_UPPER_MASK, xmm_mtip1)); // SSE2
						__m128i xmm_mag_mask = _mm_and_si128(xmm_y, xmm_ONE); // SSE2
						xmm_mag_mask = _mm_sub_epi64(xmm_ZERO, xmm_mag_mask); // SSE2 <=> _mm_cmpeq_epi64(xmm_mag_mask, xmm_ONE) SSE4.1
						xmm_mag_mask = _mm_and_si128(xmm_mag_mask, xmm_A); // SSE2
						xmm_y = _mm_srli_epi64(xmm_y, 1); // SSE2
						xmm_y = _mm_xor_si128(xmm_y, xmm_mag_mask); // SSE2
						__m128i xmm_mtipm = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&mt[i - (NPM::value)])); // SSE2
						xmm_mti = _mm_xor_si128(xmm_y, xmm_mtipm); // SSE2
						_mm_storeu_si128(reinterpret_cast<__m128i *>(&mt[i]), xmm_mti); // SSE2
					}

					typedef kerbal::type_traits::integral_constant<long long, (M - 1) % STEP::value> SECOND_STEP_REMAIN;
					if (SECOND_STEP_REMAIN::value != 0) {
						EACH2(i);
					}

					// i = N - 1

					result_type y = (mt[N - 1] & UPPER_MASK::value) | (mt[0] & LOWER_MASK::value);
					mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ ((y & 0x1UL) ? A : 0);

				}

			} // namespace sse2

		} // namespace detail

	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_ENGINE_DETAIL_MT_TWIST_MT_TWIST_SSE2_PART_HPP
