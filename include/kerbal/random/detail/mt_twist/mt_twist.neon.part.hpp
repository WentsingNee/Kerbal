/**
 * @file       mt_twist.neon.part.hpp
 * @brief
 * @date       2022-05-21
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_DETAIL_MT_TWIST_MT_TWIST_NEON_PART_HPP
#define KERBAL_RANDOM_DETAIL_MT_TWIST_MT_TWIST_NEON_PART_HPP

#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>

#include <arm_neon.h>

#include <kerbal/random/detail/mt_twist/mt_twist.plain.part.hpp>


namespace kerbal
{

	namespace random
	{

		namespace detail
		{

			namespace neon
			{

				template <std::size_t N, std::size_t M, std::size_t R, kerbal::compatibility::uint32_t A>
				void mt_twist(kerbal::compatibility::uint32_t mto[]) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint32_t result_type;

					typedef kerbal::type_traits::integral_constant<result_type, (~static_cast<result_type>(0)) << R> UPPER_MASK; // most significant w-r bits
					typedef kerbal::type_traits::integral_constant<result_type, ~UPPER_MASK::value> LOWER_MASK; // least significant r bits
					KERBAL_STATIC_ASSERT(N >= M, "N should >= M");
					typedef kerbal::type_traits::integral_constant<std::size_t, N - M> NPM;

					::uint32_t * mt = reinterpret_cast< ::uint32_t *>(mto);
					typedef kerbal::type_traits::integral_constant<std::size_t, 128 / 32> STEP;
					const uint32x4_t q_UPPER_MASK = vdupq_n_u32(UPPER_MASK::value);
					const uint32x4_t q_ONE = vdupq_n_u32(1);
					const uint32x4_t q_A = vdupq_n_u32(A);

					unsigned int i = 0; // Note: gcc unreasonable warning: iteration 4611686018427387903 invokes undefined behavior [-Waggressive-loop-optimizations]
					for (; i + STEP::value <= NPM::value; i += STEP::value) {
						uint32x4_t q_mti = vld1q_u32(&mt[i]);
						uint32x4_t q_mtip1 = vld1q_u32(&mt[i + 1]);
						uint32x4_t q_y = vbslq_u32(q_UPPER_MASK, q_mti, q_mtip1);
						uint32x4_t q_mag_mask = vandq_u32(q_y, q_ONE);
						q_mag_mask = vceqq_u32(q_mag_mask, q_ONE);
						q_mag_mask = vandq_u32(q_mag_mask, q_A);
						q_y = vshrq_n_u32(q_y, 1);
						q_mti = veorq_u32(q_y, q_mag_mask);
						uint32x4_t q_mtipm = vld1q_u32(&mt[i + M]);
						q_mti = veorq_u32(q_mti, q_mtipm);
						vst1q_u32(&mt[i], q_mti);
					}

					typedef kerbal::type_traits::integral_constant<int, NPM::value % STEP::value> FIRST_STEP_REMAIN;
					if (FIRST_STEP_REMAIN::value == 3) {
						uint32x4_t q_mti = vld1q_u32(&mt[i]); // FIRST_STEP_REMAIN::value (3) + M >= STEP::value always true

						uint32x4_t q_mtip1;
						if (FIRST_STEP_REMAIN::value + M - 1 >= STEP::value) {
							q_mtip1 = vld1q_u32(&mt[i + 1]);
						} else {
							uint32x2_t d_un;
							q_mtip1 = vcombine_u32(
								vld1_u32(&mt[i + 1]),
								vld1_lane_u32(&mt[i + 3], d_un, 0)
							);
						}

						uint32x4_t q_y = vbslq_u32(q_UPPER_MASK, q_mti, q_mtip1);
						uint32x4_t q_mag_mask = vandq_u32(q_y, q_ONE);
						q_mag_mask = vceqq_u32(q_mag_mask, q_ONE);
						q_mag_mask = vandq_u32(q_mag_mask, q_A);
						q_y = vshrq_n_u32(q_y, 1);
						q_mti = veorq_u32(q_y, q_mag_mask);

						uint32x4_t q_mtipm; {
							uint32x2_t d_un;
							q_mtipm = vcombine_u32(
								vld1_u32(&mt[i + 0 + M]),
								vld1_lane_u32(&mt[i + 2 + M], d_un, 0)
							);
						}

						q_mti = veorq_u32(q_mti, q_mtipm);

						vst1_u32(&mt[i + 0], vget_low_u32(q_mti));
						vst1q_lane_u32(&mt[i + 2], q_mti, 2);
					} else if (FIRST_STEP_REMAIN::value == 2) {
						uint32x2_t d_mti = vld1_u32(&mt[i]);
						uint32x2_t d_mtip1 = vld1_u32(&mt[i + 1]);
						uint32x2_t d_y = vbsl_u32(vget_low_u32(q_UPPER_MASK), d_mti, d_mtip1);
						uint32x2_t d_mag_mask = vand_u32(d_y, vget_low_u32(q_ONE));
						d_mag_mask = vceq_u32(d_mag_mask, vget_low_u32(q_ONE));
						d_mag_mask = vand_u32(d_mag_mask, vget_low_u32(q_A));
						d_y = vshr_n_u32(d_y, 1);
						d_mti = veor_u32(d_y, d_mag_mask);
						uint32x2_t d_mtipm = vld1_u32(&mt[i + 0 + M]);
						d_mti = veor_u32(d_mti, d_mtipm);

						vst1_u32(&mt[i + 0], d_mti);
					} else if (FIRST_STEP_REMAIN::value == 1) {
						EACH1(i);
					}

					i = NPM::value;

					for (; i + STEP::value <= N - 1; i += STEP::value) {
						uint32x4_t q_mti = vld1q_u32(&mt[i]);
						uint32x4_t q_mtip1 = vld1q_u32(&mt[i + 1]);
						uint32x4_t q_y = vbslq_u32(q_UPPER_MASK, q_mti, q_mtip1);
						uint32x4_t q_mag_mask = vandq_u32(q_y, q_ONE);
						q_mag_mask = vceqq_u32(q_mag_mask, q_ONE);
						q_mag_mask = vandq_u32(q_mag_mask, q_A);
						q_y = vshrq_n_u32(q_y, 1);
						q_mti = veorq_u32(q_y, q_mag_mask);
						uint32x4_t q_mtipm = vld1q_u32(&mt[i - (NPM::value)]);
						q_mti = veorq_u32(q_mti, q_mtipm);
						vst1q_u32(&mt[i], q_mti);
					}

					while (i < N - 1) {
						EACH2(i);
						++i;
					}

					result_type y = (mt[N - 1] & UPPER_MASK::value) | (mt[0] & LOWER_MASK::value);
					mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ ((y & 0x1UL) ? A : 0);

				}

				template <std::size_t N, std::size_t M, std::size_t R, kerbal::compatibility::uint64_t A>
				void mt_twist(kerbal::compatibility::uint64_t mto[]) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint64_t result_type;

					typedef kerbal::type_traits::integral_constant<result_type, (~static_cast<result_type>(0)) << R> UPPER_MASK; // most significant w-r bits
					typedef kerbal::type_traits::integral_constant<result_type, ~UPPER_MASK::value> LOWER_MASK; // least significant r bits
					KERBAL_STATIC_ASSERT(N >= M, "N should >= M");
					typedef kerbal::type_traits::integral_constant<std::size_t, N - M> NPM;

					::uint64_t * mt = reinterpret_cast< ::uint64_t *>(mto);
					typedef kerbal::type_traits::integral_constant<std::size_t, 128 / 64> STEP;
					const uint64x2_t q_UPPER_MASK = vdupq_n_u64(UPPER_MASK::value);
					const uint64x2_t q_ZERO = vdupq_n_u64(0);
					const uint64x2_t q_ONE = vdupq_n_u64(1);
					const uint64x2_t q_A = vdupq_n_u64(A);

					unsigned int i = 0; // Note: gcc unreasonable warning: iteration 4611686018427387903 invokes undefined behavior [-Waggressive-loop-optimizations]
					for (; i + STEP::value <= NPM::value; i += STEP::value) {
						uint64x2_t q_mti = vld1q_u64(&mt[i]);
						uint64x2_t q_mtip1 = vld1q_u64(&mt[i + 1]);
						uint64x2_t q_y = vbslq_u64(q_UPPER_MASK, q_mti, q_mtip1);
						uint64x2_t q_mag_mask = vandq_u64(q_y, q_ONE);
						q_mag_mask = vsubq_u64(q_ZERO, q_mag_mask); // <=> vceqq_u64(q_mag_mask, q_ONE) neon // arm neon does not support `vceqq_u64` offically
						q_mag_mask = vandq_u64(q_mag_mask, q_A);
						q_y = vshrq_n_u64(q_y, 1);
						q_mti = veorq_u64(q_y, q_mag_mask);
						uint64x2_t q_mtipm = vld1q_u64(&mt[i + M]);
						q_mti = veorq_u64(q_mti, q_mtipm);
						vst1q_u64(&mt[i], q_mti);
					}

					typedef kerbal::type_traits::integral_constant<int, NPM::value % STEP::value> FIRST_STEP_REMAIN;
					if (FIRST_STEP_REMAIN::value != 0) {
						EACH1(i);
						++i;
					}

					for (; i + STEP::value <= N - 1; i += STEP::value) {
						uint64x2_t q_mti = vld1q_u64(&mt[i]);
						uint64x2_t q_mtip1 = vld1q_u64(&mt[i + 1]);
						uint64x2_t q_y = vbslq_u64(q_UPPER_MASK, q_mti, q_mtip1);
						uint64x2_t q_mag_mask = vandq_u64(q_y, q_ONE);
						q_mag_mask = vsubq_u64(q_ZERO, q_mag_mask); // neon <=> vceqq_u64(q_mag_mask, q_ONE) neon // arm neon does not support `vceqq_u64` offically
						q_mag_mask = vandq_u64(q_mag_mask, q_A);
						q_y = vshrq_n_u64(q_y, 1);
						q_mti = veorq_u64(q_y, q_mag_mask);
						uint64x2_t q_mtipm = vld1q_u64(&mt[i - (NPM::value)]);
						q_mti = veorq_u64(q_mti, q_mtipm);
						vst1q_u64(&mt[i], q_mti);
					}

					typedef kerbal::type_traits::integral_constant<int, (M - 1) % STEP::value> SECOND_STEP_REMAIN;
					if (SECOND_STEP_REMAIN::value != 0) {
						EACH2(i);
						++i;
					}

					result_type y = (mt[N - 1] & UPPER_MASK::value) | (mt[0] & LOWER_MASK::value);
					mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ ((y & 0x1UL) ? A : 0);
				}

			} // namespace neon

		} // namespace detail

	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_DETAIL_MT_TWIST_MT_TWIST_NEON_PART_HPP
