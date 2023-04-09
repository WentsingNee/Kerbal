/**
 * @file       mt_twist.wasm_simd128.hpp
 * @brief
 * @date       2023-04-09
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_DETAIL_MT_TWIST_MT_TWIST_WASM_SIMD128_HPP
#define KERBAL_RANDOM_DETAIL_MT_TWIST_MT_TWIST_WASM_SIMD128_HPP

#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>

#include <wasm_simd128.h>

#include <kerbal/random/detail/mt_twist/mt_twist.plain.hpp>


namespace kerbal
{

	namespace random
	{

		namespace detail
		{

			namespace wasm_simd128
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
					const v128_t v128_UPPER_MASK = wasm_u32x4_const_splat(static_cast<int>(UPPER_MASK::value));
					const v128_t v128_ONE = wasm_u32x4_const_splat(1);
					const v128_t v128_A = wasm_u32x4_const_splat(static_cast<int>(A));

					unsigned int i = 0; // Note: gcc unreasonable warning: iteration 4611686018427387903 invokes undefined behavior [-Waggressive-loop-optimizations]
					for (; i + STEP::value <= NPM::value; i += STEP::value) {
						v128_t v128_mti = wasm_v128_load(&mt[i]);
						v128_t v128_mtip1 = wasm_v128_load(&mt[i + 1]);
						v128_t v128_y = wasm_v128_bitselect(v128_mti, v128_mtip1, v128_UPPER_MASK);
						v128_t v128_mag_mask = wasm_v128_and(v128_y, v128_ONE);
						v128_mag_mask = wasm_i32x4_eq(v128_mag_mask, v128_ONE);
						v128_mag_mask = wasm_v128_and(v128_mag_mask, v128_A);
						v128_y = wasm_u32x4_shr(v128_y, 1);
						v128_y = wasm_v128_xor(v128_y, v128_mag_mask);
						v128_t v128_mtipm = wasm_v128_load(&mt[i + M]);
						v128_mti = wasm_v128_xor(v128_y, v128_mtipm);
						wasm_v128_store(&mt[i], v128_mti);
					}

					typedef kerbal::type_traits::integral_constant<int, NPM::value % STEP::value> FIRST_STEP_REMAIN;
					if (FIRST_STEP_REMAIN::value == 3) {
//						v128_t v128_mti = wasm_v128_load(&mt[i]); // FIRST_STEP_REMAIN::value (3) + M >= STEP::value always true
//
//						v128_t v128_mtip1;
//						if (FIRST_STEP_REMAIN::value + M - 1 >= STEP::value) {
//							v128_mtip1 = wasm_v128_load(&mt[i + 1]);
//						} else {
//							v128_mtip1 = wasm_v128_load32_lane(&mt[i + 1], v128_mtip1, 0);
//							v128_mtip1 = wasm_v128_load32_lane(&mt[i + 2], v128_mtip1, 1);
//							v128_mtip1 = wasm_v128_load32_lane(&mt[i + 3], v128_mtip1, 2);
//						}
//
//
//
//						v128_t v128_y = wasm_v128_bitselect(v128_mti, v128_mtip1, v128_UPPER_MASK);
//						v128_t v128_mag_mask = wasm_v128_and(v128_y, v128_ONE);
//						v128_mag_mask = wasm_i32x4_eq(v128_mag_mask, v128_ONE);
//						v128_mag_mask = wasm_v128_and(v128_mag_mask, v128_A);
//						v128_y = wasm_u32x4_shr(v128_y, 1);
//						v128_y = wasm_v128_xor(v128_y, v128_mag_mask);
//						v128_t v128_mtipm; {
//							v128_mtipm = wasm_v128_load32_lane(&mt[i + M + 0], v128_mtipm, 0);
//							v128_mtipm = wasm_v128_load32_lane(&mt[i + M + 1], v128_mtipm, 1);
//							v128_mtipm = wasm_v128_load32_lane(&mt[i + M + 2], v128_mtipm, 2);
//						}
//						v128_mti = wasm_v128_xor(v128_y, v128_mtipm);
//
//						if (true) {
//							kerbal::compatibility::uint32_t t = mt[i + 3];
//							wasm_v128_store(&mt[i], v128_mti);
//							// FIRST_STEP_REMAIN::value (3) + M >= STEP::value always true
//							mt[i + 3] = t;
//						} else {
//							wasm_v128_store32_lane(&mt[i + 0], v128_mti, 0);
//							wasm_v128_store32_lane(&mt[i + 1], v128_mti, 1);
//							wasm_v128_store32_lane(&mt[i + 2], v128_mti, 2);
//						}

						EACH1(i);
						EACH1(i+1);
						EACH1(i+2);
					} else if (FIRST_STEP_REMAIN::value == 2) {
//						v128_t v128_mti = _mm_loadl_epi64(&mt[i]);
//						v128_t v128_mtip1 = _mm_loadl_epi64(&mt[i + 1]);
//						v128_t v128_y = wasm_v128_bitselect(v128_mti, v128_mtip1, v128_UPPER_MASK);
//						v128_t v128_mag_mask = wasm_v128_and(v128_y, v128_ONE);
//						v128_mag_mask = wasm_i32x4_sub(v128_ZERO, v128_mag_mask); // <=> wasm_i32x4_eq(v128_mag_mask, v128_ONE)
//						v128_mag_mask = wasm_v128_and(v128_mag_mask, v128_A);
//						v128_y = wasm_u32x4_shr(v128_y, 1);
//						v128_y = wasm_v128_xor(v128_y, v128_mag_mask);
//						v128_t v128_mtipm = _mm_loadl_epi64(&mt[i + M]));
//						v128_mti = wasm_v128_xor(v128_y, v128_mtipm);
//						_mm_storel_epi64(&mt[i]), v128_mti);
						EACH1(i);
					} else if (FIRST_STEP_REMAIN::value == 1) {
						EACH1(i);
					}

					i = NPM::value;

					for (; i + STEP::value <= N - 1; i += STEP::value) {
						v128_t v128_mti = wasm_v128_load(&mt[i]);
						v128_t v128_mtip1 = wasm_v128_load(&mt[i + 1]);
						v128_t v128_y = wasm_v128_bitselect(v128_mti, v128_mtip1, v128_UPPER_MASK);
						v128_t v128_mag_mask = wasm_v128_and(v128_y, v128_ONE);
						v128_mag_mask = wasm_i32x4_eq(v128_mag_mask, v128_ONE);
						v128_mag_mask = wasm_v128_and(v128_mag_mask, v128_A);
						v128_y = wasm_u32x4_shr(v128_y, 1);
						v128_y = wasm_v128_xor(v128_y, v128_mag_mask);
						v128_t v128_mtipm = wasm_v128_load(&mt[i - (NPM::value)]);
						v128_mti = wasm_v128_xor(v128_y, v128_mtipm);
						wasm_v128_store(&mt[i], v128_mti);
					}

					typedef kerbal::type_traits::integral_constant<int, (M - 1) % STEP::value> SECOND_STEP_REMAIN;
					if (SECOND_STEP_REMAIN::value == 3) {
//						v128_t v128_mti = _mm_loadl_epi64(&mt[i]);
//						v128_t v128_mtip1 = _mm_loadl_epi64(&mt[i + 1]);
//						v128_t v128_y = wasm_v128_bitselect(v128_mti, v128_mtip1, v128_UPPER_MASK);
//						v128_t v128_mag_mask = wasm_v128_and(v128_y, v128_ONE);
//						v128_mag_mask = wasm_i32x4_sub(v128_ZERO, v128_mag_mask); // <=> wasm_i32x4_eq(v128_mag_mask, v128_ONE)
//						v128_mag_mask = wasm_v128_and(v128_mag_mask, v128_A);
//						v128_y = wasm_u32x4_shr(v128_y, 1);
//						v128_y = wasm_v128_xor(v128_y, v128_mag_mask);
//						v128_t v128_mtipm = _mm_loadl_epi64(&mt[i - (NPM::value)]));
//						v128_mti = wasm_v128_xor(v128_y, v128_mtipm);
//						_mm_storel_epi64(&mt[i]), v128_mti);
						EACH2(i);
						EACH2(i+1);

						i += 2;
						EACH2(i);
					} else if (SECOND_STEP_REMAIN::value == 2) {
//						v128_t v128_mti = _mm_loadl_epi64(&mt[i]);
//						v128_t v128_mtip1 = _mm_loadl_epi64(&mt[i + 1]);
//						v128_t v128_y = wasm_v128_bitselect(v128_mti, v128_mtip1, v128_UPPER_MASK);
//						v128_t v128_mag_mask = wasm_v128_and(v128_y, v128_ONE);
//						v128_mag_mask = wasm_i32x4_sub(v128_ZERO, v128_mag_mask); // <=> wasm_i32x4_eq(v128_mag_mask, v128_ONE)
//						v128_mag_mask = wasm_v128_and(v128_mag_mask, v128_A);
//						v128_y = wasm_u32x4_shr(v128_y, 1);
//						v128_y = wasm_v128_xor(v128_y, v128_mag_mask);
//						v128_t v128_mtipm = _mm_loadl_epi64(&mt[i - (NPM::value)]));
//						v128_mti = wasm_v128_xor(v128_y, v128_mtipm);
//						_mm_storel_epi64(&mt[i]), v128_mti);

						EACH2(i);
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
					const v128_t v128_UPPER_MASK = wasm_u64x2_const_splat(static_cast<long long>(UPPER_MASK::value));
					const v128_t v128_ZERO = wasm_u64x2_const_splat(0);
					const v128_t v128_ONE = wasm_u64x2_const_splat(1);
					const v128_t v128_A = wasm_u64x2_const_splat(static_cast<long long>(A));

					std::size_t i = 0;
					for (; i + STEP::value <= NPM::value; i += STEP::value) {
						v128_t v128_mti = wasm_v128_load(&mt[i]);
						v128_t v128_mtip1 = wasm_v128_load(&mt[i + 1]);
						v128_t v128_y = wasm_v128_bitselect(v128_mti, v128_mtip1, v128_UPPER_MASK);
						v128_t v128_mag_mask = wasm_v128_and(v128_y, v128_ONE);
						v128_mag_mask = wasm_i64x2_sub(v128_ZERO, v128_mag_mask); // <=> wasm_i64x2_eq(v128_mag_mask, v128_ONE)SSE4.1
						v128_mag_mask = wasm_v128_and(v128_mag_mask, v128_A);
						v128_y = wasm_u64x2_shr(v128_y, 1);
						v128_y = wasm_v128_xor(v128_y, v128_mag_mask);
						v128_t v128_mtipm = wasm_v128_load(&mt[i + M]);
						v128_mti = wasm_v128_xor(v128_y, v128_mtipm);
						wasm_v128_store(&mt[i], v128_mti);
					}

					typedef kerbal::type_traits::integral_constant<long long, NPM::value % STEP::value> FIRST_STEP_REMAIN;
					if (FIRST_STEP_REMAIN::value != 0) {
						EACH1(i);
					}

					i = NPM::value;

					for (; i + STEP::value <= N - 1; i += STEP::value) {
						v128_t v128_mti = wasm_v128_load(&mt[i]);
						v128_t v128_mtip1 = wasm_v128_load(&mt[i + 1]);
						v128_t v128_y = wasm_v128_bitselect(v128_mti, v128_mtip1, v128_UPPER_MASK);
						v128_t v128_mag_mask = wasm_v128_and(v128_y, v128_ONE);
						v128_mag_mask = wasm_i64x2_sub(v128_ZERO, v128_mag_mask); // <=> wasm_i64x2_eq(v128_mag_mask, v128_ONE)SSE4.1
						v128_mag_mask = wasm_v128_and(v128_mag_mask, v128_A);
						v128_y = wasm_u64x2_shr(v128_y, 1);
						v128_y = wasm_v128_xor(v128_y, v128_mag_mask);
						v128_t v128_mtipm = wasm_v128_load(&mt[i - (NPM::value)]);
						v128_mti = wasm_v128_xor(v128_y, v128_mtipm);
						wasm_v128_store(&mt[i], v128_mti);
					}

					typedef kerbal::type_traits::integral_constant<long long, (M - 1) % STEP::value> SECOND_STEP_REMAIN;
					if (SECOND_STEP_REMAIN::value != 0) {
						EACH2(i);
					}

					// i = N - 1

					result_type y = (mt[N - 1] & UPPER_MASK::value) | (mt[0] & LOWER_MASK::value);
					mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ ((y & 0x1UL) ? A : 0);

				}

			} // namespace wasm_simd128

		} // namespace detail

	} // namespace random

} // namespace kerbal


#endif // KERBAL_RANDOM_DETAIL_MT_TWIST_MT_TWIST_WASM_SIMD128_HPP
