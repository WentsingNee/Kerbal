/**
 * @file       mt_twist.lsx.part.hpp
 * @brief
 * @date       2025-02-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_ENGINE_DETAIL_MT_TWIST_MT_TWIST_LSX_PART_HPP
#define KERBAL_RANDOM_ENGINE_DETAIL_MT_TWIST_MT_TWIST_LSX_PART_HPP

#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>

#include <lsxintrin.h>

#include <kerbal/random/engine/detail/mt_twist/mt_twist.plain.part.hpp>


namespace kerbal
{

	namespace random
	{

		namespace detail
		{

			namespace lsx
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
					const __m128i vr_UPPER_MASK = __lsx_vreplgr2vr_w(UPPER_MASK::value); // LSX
					const __m128i vr_ZERO = __lsx_vreplgr2vr_w(0); // LSX
					const __m128i vr_ONE = __lsx_vreplgr2vr_w(1); // LSX
					const __m128i vr_A = __lsx_vreplgr2vr_w(static_cast<result_type>(A)); // LSX

					std::size_t i = 0;
					for (; i + STEP::value <= NPM::value; i += STEP::value) {
						__m128i vr_mti = __lsx_vld(&mt[i], 0); // LSX
						__m128i vr_mtip1 = __lsx_vld(&mt[i], 1 * sizeof(result_type)); // LSX
						__m128i vr_y = __lsx_vor_v( // LSX
							__lsx_vand_v(vr_UPPER_MASK, vr_mti), // LSX
							__lsx_vandn_v(vr_UPPER_MASK, vr_mtip1)); // LSX
						__m128i vr_mag_mask = __lsx_vand_v(vr_y, vr_ONE); // LSX
						vr_mag_mask = __lsx_vsub_w(vr_ZERO, vr_mag_mask); // LSX <=> _mm_cmpeq_epi32(vr_mag_mask, vr_ONE) LSX
						vr_mag_mask = __lsx_vand_v(vr_mag_mask, vr_A); // LSX
						vr_y = __lsx_vsrli_w(vr_y, 1); // LSX
						vr_y = __lsx_vxor_v(vr_y, vr_mag_mask); // LSX
						__m128i vr_mtipm = __lsx_vld(&mt[i], M * sizeof(result_type)); // LSX
						vr_mti = __lsx_vxor_v(vr_y, vr_mtipm); // LSX
						__lsx_vst(vr_mti, &mt[i], 0); // LSX
					}

					typedef kerbal::type_traits::integral_constant<std::size_t, NPM::value % STEP::value> FIRST_STEP_REMAIN;
					if (FIRST_STEP_REMAIN::value == 3) {
						EACH1(i);
						EACH1(i + 1);
						EACH1(i + 2);
					} else if (FIRST_STEP_REMAIN::value == 2) {
						EACH1(i);
						EACH1(i + 1);
					} else if (FIRST_STEP_REMAIN::value == 1) {
						EACH1(i);
					}

					i = NPM::value;

					for (; i + STEP::value <= N - 1; i += STEP::value) {
						__m128i vr_mti = __lsx_vld(&mt[i], 0); // LSX
						__m128i vr_mtip1 = __lsx_vld(&mt[i], 1 * sizeof(result_type)); // LSX
						__m128i vr_y = __lsx_vor_v( // LSX
							__lsx_vand_v(vr_UPPER_MASK, vr_mti), // LSX
							__lsx_vandn_v(vr_UPPER_MASK, vr_mtip1)); // LSX
						__m128i vr_mag_mask = __lsx_vand_v(vr_y, vr_ONE); // LSX
						vr_mag_mask = __lsx_vsub_w(vr_ZERO, vr_mag_mask); // LSX <=> _mm_cmpeq_epi32(vr_mag_mask, vr_ONE) LSX
						vr_mag_mask = __lsx_vand_v(vr_mag_mask, vr_A); // LSX
						vr_y = __lsx_vsrli_w(vr_y, 1); // LSX
						vr_y = __lsx_vxor_v(vr_y, vr_mag_mask); // LSX
						__m128i vr_mtipm = __lsx_vld(&mt[i - (NPM::value)], 0); // LSX
						vr_mti = __lsx_vxor_v(vr_y, vr_mtipm); // LSX
						__lsx_vst(vr_mti, &mt[i], 0); // LSX
					}

					typedef kerbal::type_traits::integral_constant<std::size_t, (M - 1) % STEP::value> SECOND_STEP_REMAIN;
					if (SECOND_STEP_REMAIN::value == 3) {
						EACH2(i);
						EACH2(i + 1);
						EACH2(i + 2);
					} else if (SECOND_STEP_REMAIN::value == 2) {
						EACH2(i);
						EACH2(i + 1);
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
					const __m128i vr_UPPER_MASK = __lsx_vreplgr2vr_d(UPPER_MASK::value); // LSX
					const __m128i vr_ZERO = __lsx_vreplgr2vr_d(0); // LSX
					const __m128i vr_ONE = __lsx_vreplgr2vr_d(1); // LSX
					const __m128i vr_A = __lsx_vreplgr2vr_d(static_cast<result_type>(A)); // LSX

					std::size_t i = 0;
					for (; i + STEP::value <= NPM::value; i += STEP::value) {
						__m128i vr_mti = __lsx_vld(&mt[i], 0); // LSX
						__m128i vr_mtip1 = __lsx_vld(&mt[i], M * sizeof(result_type)); // LSX
						__m128i vr_y = __lsx_vor_v( // LSX
							__lsx_vand_v(vr_UPPER_MASK, vr_mti), // LSX
							__lsx_vandn_v(vr_UPPER_MASK, vr_mtip1)); // LSX
						__m128i vr_mag_mask = __lsx_vand_v(vr_y, vr_ONE); // LSX
						vr_mag_mask = __lsx_vsub_d(vr_ZERO, vr_mag_mask); // LSX <=> _mm_cmpeq_epi64(vr_mag_mask, vr_ONE) SSE4.1
						vr_mag_mask = __lsx_vand_v(vr_mag_mask, vr_A); // LSX
						vr_y = __lsx_vsrli_d(vr_y, 1); // LSX
						vr_y = __lsx_vxor_v(vr_y, vr_mag_mask); // LSX
						__m128i vr_mtipm = __lsx_vld(&mt[i], M * sizeof(result_type)); // LSX
						vr_mti = __lsx_vxor_v(vr_y, vr_mtipm); // LSX
						__lsx_vst(vr_mti, &mt[i], 0); // LSX
					}

					typedef kerbal::type_traits::integral_constant<std::size_t, NPM::value % STEP::value> FIRST_STEP_REMAIN;
					if (FIRST_STEP_REMAIN::value != 0) {
						EACH1(i);
					}

					i = NPM::value;

					for (; i + STEP::value <= N - 1; i += STEP::value) {
						__m128i vr_mti = __lsx_vld(&mt[i], 0); // LSX
						__m128i vr_mtip1 = __lsx_vld(&mt[i], 1 * sizeof(result_type)); // LSX
						__m128i vr_y = __lsx_vor_v( // LSX
							__lsx_vand_v(vr_UPPER_MASK, vr_mti), // LSX
							__lsx_vandn_v(vr_UPPER_MASK, vr_mtip1)); // LSX
						__m128i vr_mag_mask = __lsx_vand_v(vr_y, vr_ONE); // LSX
						vr_mag_mask = __lsx_vsub_d(vr_ZERO, vr_mag_mask); // LSX <=> _mm_cmpeq_epi64(vr_mag_mask, vr_ONE) SSE4.1
						vr_mag_mask = __lsx_vand_v(vr_mag_mask, vr_A); // LSX
						vr_y = __lsx_vsrli_d(vr_y, 1); // LSX
						vr_y = __lsx_vxor_v(vr_y, vr_mag_mask); // LSX
						__m128i vr_mtipm = __lsx_vld(&mt[i - (NPM::value)], 0); // LSX
						vr_mti = __lsx_vxor_v(vr_y, vr_mtipm); // LSX
						__lsx_vst(vr_mti, &mt[i], 0); // LSX
					}

					typedef kerbal::type_traits::integral_constant<std::size_t, (M - 1) % STEP::value> SECOND_STEP_REMAIN;
					if (SECOND_STEP_REMAIN::value != 0) {
						EACH2(i);
					}

					// i = N - 1

					result_type y = (mt[N - 1] & UPPER_MASK::value) | (mt[0] & LOWER_MASK::value);
					mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ ((y & 0x1UL) ? A : 0);

				}

			} // namespace lsx

		} // namespace detail

	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_ENGINE_DETAIL_MT_TWIST_MT_TWIST_LSX_PART_HPP
