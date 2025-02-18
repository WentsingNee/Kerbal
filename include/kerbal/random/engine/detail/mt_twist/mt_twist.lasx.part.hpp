/**
 * @file       mt_twist.lasx.part.hpp
 * @brief
 * @date       2025-02-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_ENGINE_DETAIL_MT_TWIST_MT_TWIST_LASX_PART_HPP
#define KERBAL_RANDOM_ENGINE_DETAIL_MT_TWIST_MT_TWIST_LASX_PART_HPP

#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>

#include <lasxintrin.h>

#include <kerbal/random/engine/detail/mt_twist/mt_twist.plain.part.hpp>


namespace kerbal
{

	namespace random
	{

		namespace detail
		{

			namespace lasx
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
					const __m256i vr_UPPER_MASK = __lasx_xvreplgr2vr_w(UPPER_MASK::value); // LASX
					const __m256i vr_ZERO = __lasx_xvreplgr2vr_w(0); // LASX
					const __m256i vr_ONE = __lasx_xvreplgr2vr_w(1); // LASX
					const __m256i vr_A = __lasx_xvreplgr2vr_w(static_cast<result_type>(A)); // LASX

					std::size_t i = 0;
					for (; i + STEP::value <= NPM::value; i += STEP::value) {
						__m256i vr_mti = __lasx_xvld(&mt[i], 0); // LASX
						__m256i vr_mtip1 = __lasx_xvld(&mt[i], 1 * sizeof(result_type)); // LASX
						__m256i vr_y = __lasx_xvor_v( // LASX
							__lasx_xvand_v(vr_UPPER_MASK, vr_mti), // LASX
							__lasx_xvandn_v(vr_UPPER_MASK, vr_mtip1)); // LASX
						__m256i vr_mag_mask = __lasx_xvand_v(vr_y, vr_ONE); // LASX
						vr_mag_mask = __lasx_xvsub_w(vr_ZERO, vr_mag_mask); // LASX <=> _mm_cmpeq_epi32(vr_mag_mask, vr_ONE) LASX
						vr_mag_mask = __lasx_xvand_v(vr_mag_mask, vr_A); // LASX
						vr_y = __lasx_xvsrli_w(vr_y, 1); // LASX
						vr_y = __lasx_xvxor_v(vr_y, vr_mag_mask); // LASX
						__m256i vr_mtipm = __lasx_xvld(&mt[i], M * sizeof(result_type)); // LASX
						vr_mti = __lasx_xvxor_v(vr_y, vr_mtipm); // LASX
						__lasx_xvst(vr_mti, &mt[i], 0); // LASX
					}

					typedef kerbal::type_traits::integral_constant<std::size_t, NPM::value % STEP::value> FIRST_STEP_REMAIN;
					while (i < NPM::value) {
						EACH1(i);
						++i;
					}

					for (; i + STEP::value <= N - 1; i += STEP::value) {
						__m256i vr_mti = __lasx_xvld(&mt[i], 0); // LASX
						__m256i vr_mtip1 = __lasx_xvld(&mt[i], 1 * sizeof(result_type)); // LASX
						__m256i vr_y = __lasx_xvor_v( // LASX
							__lasx_xvand_v(vr_UPPER_MASK, vr_mti), // LASX
							__lasx_xvandn_v(vr_UPPER_MASK, vr_mtip1)); // LASX
						__m256i vr_mag_mask = __lasx_xvand_v(vr_y, vr_ONE); // LASX
						vr_mag_mask = __lasx_xvsub_w(vr_ZERO, vr_mag_mask); // LASX <=> _mm_cmpeq_epi32(vr_mag_mask, vr_ONE) LASX
						vr_mag_mask = __lasx_xvand_v(vr_mag_mask, vr_A); // LASX
						vr_y = __lasx_xvsrli_w(vr_y, 1); // LASX
						vr_y = __lasx_xvxor_v(vr_y, vr_mag_mask); // LASX
						__m256i vr_mtipm = __lasx_xvld(&mt[i - (NPM::value)], 0); // LASX
						vr_mti = __lasx_xvxor_v(vr_y, vr_mtipm); // LASX
						__lasx_xvst(vr_mti, &mt[i], 0); // LASX
					}

					typedef kerbal::type_traits::integral_constant<std::size_t, (M - 1) % STEP::value> SECOND_STEP_REMAIN;
					// while (i < N - 1) {
					// 	EACH2(i);
					// 	++i;
					// }
					// ERROR: ICE

					i = (N - 1);

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
					const __m256i vr_UPPER_MASK = __lasx_xvreplgr2vr_d(UPPER_MASK::value); // LASX
					const __m256i vr_ZERO = __lasx_xvreplgr2vr_d(0); // LASX
					const __m256i vr_ONE = __lasx_xvreplgr2vr_d(1); // LASX
					const __m256i vr_A = __lasx_xvreplgr2vr_d(static_cast<result_type>(A)); // LASX

					std::size_t i = 0;
					for (; i + STEP::value <= NPM::value; i += STEP::value) {
						__m256i vr_mti = __lasx_xvld(&mt[i], 0); // LASX
						__m256i vr_mtip1 = __lasx_xvld(&mt[i], M * sizeof(result_type)); // LASX
						__m256i vr_y = __lasx_xvor_v( // LASX
							__lasx_xvand_v(vr_UPPER_MASK, vr_mti), // LASX
							__lasx_xvandn_v(vr_UPPER_MASK, vr_mtip1)); // LASX
						__m256i vr_mag_mask = __lasx_xvand_v(vr_y, vr_ONE); // LASX
						vr_mag_mask = __lasx_xvsub_d(vr_ZERO, vr_mag_mask); // LASX <=> _mm_cmpeq_epi64(vr_mag_mask, vr_ONE) SSE4.1
						vr_mag_mask = __lasx_xvand_v(vr_mag_mask, vr_A); // LASX
						vr_y = __lasx_xvsrli_d(vr_y, 1); // LASX
						vr_y = __lasx_xvxor_v(vr_y, vr_mag_mask); // LASX
						__m256i vr_mtipm = __lasx_xvld(&mt[i], M * sizeof(result_type)); // LASX
						vr_mti = __lasx_xvxor_v(vr_y, vr_mtipm); // LASX
						__lasx_xvst(vr_mti, &mt[i], 0); // LASX
					}

					typedef kerbal::type_traits::integral_constant<std::size_t, NPM::value % STEP::value> FIRST_STEP_REMAIN;
					while (i < NPM::value) {
						EACH1(i);
						++i;
					}

					for (; i + STEP::value <= N - 1; i += STEP::value) {
						__m256i vr_mti = __lasx_xvld(&mt[i], 0); // LASX
						__m256i vr_mtip1 = __lasx_xvld(&mt[i], 1 * sizeof(result_type)); // LASX
						__m256i vr_y = __lasx_xvor_v( // LASX
							__lasx_xvand_v(vr_UPPER_MASK, vr_mti), // LASX
							__lasx_xvandn_v(vr_UPPER_MASK, vr_mtip1)); // LASX
						__m256i vr_mag_mask = __lasx_xvand_v(vr_y, vr_ONE); // LASX
						vr_mag_mask = __lasx_xvsub_d(vr_ZERO, vr_mag_mask); // LASX <=> _mm_cmpeq_epi64(vr_mag_mask, vr_ONE) SSE4.1
						vr_mag_mask = __lasx_xvand_v(vr_mag_mask, vr_A); // LASX
						vr_y = __lasx_xvsrli_d(vr_y, 1); // LASX
						vr_y = __lasx_xvxor_v(vr_y, vr_mag_mask); // LASX
						__m256i vr_mtipm = __lasx_xvld(&mt[i - (NPM::value)], 0); // LASX
						vr_mti = __lasx_xvxor_v(vr_y, vr_mtipm); // LASX
						__lasx_xvst(vr_mti, &mt[i], 0); // LASX
					}

					typedef kerbal::type_traits::integral_constant<std::size_t, (M - 1) % STEP::value> SECOND_STEP_REMAIN;
					// while (i < N - 1) {
					// 	EACH2(i);
					// 	++i;
					// }
					// ERROR: ICE

					i = N - 1;

					result_type y = (mt[N - 1] & UPPER_MASK::value) | (mt[0] & LOWER_MASK::value);
					mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ ((y & 0x1UL) ? A : 0);

				}

			} // namespace lasx

		} // namespace detail

	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_ENGINE_DETAIL_MT_TWIST_MT_TWIST_LASX_PART_HPP
