/**
 * @file       mt_twist.riscv_v.part.hpp
 * @brief
 * @date       2023-12-16
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_ENGINE_DETAIL_MT_TWIST_MT_TWIST_RISCV_V_PART_HPP
#define KERBAL_RANDOM_ENGINE_DETAIL_MT_TWIST_MT_TWIST_RISCV_V_PART_HPP

#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>

#include <riscv_vector.h>


namespace kerbal
{

	namespace random
	{

		namespace detail
		{

			namespace riscv_v
			{

				template <std::size_t N, std::size_t M, std::size_t R, kerbal::compatibility::uint32_t A>
				void mt_twist(kerbal::compatibility::uint32_t mt[]) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint32_t result_type;

					typedef kerbal::type_traits::integral_constant<result_type, (~static_cast<result_type>(0)) << R> UPPER_MASK; // most significant w-r bits
					typedef kerbal::type_traits::integral_constant<result_type, ~UPPER_MASK::value> LOWER_MASK; // least significant r bits
					KERBAL_STATIC_ASSERT(N >= M, "N should >= M");
					typedef kerbal::type_traits::integral_constant<std::size_t, N - M> NPM;

					std::size_t i = 0;
					for (std::size_t vl, n = NPM::value; n > 0; n -= vl, i += vl) {
						vl = __riscv_vsetvl_e32m1(n);
						vuint32m1_t v_mti = __riscv_vle32_v_u32m1(&mt[i], vl);
						vuint32m1_t v_mtip1 = __riscv_vle32_v_u32m1(&mt[i + 1], vl);
						__riscv_vor_vv_u32m1(v_mti, v_mtip1, vl);
						vuint32m1_t v_y = __riscv_vor_vv_u32m1(
							__riscv_vand_vx_u32m1(v_mti, UPPER_MASK::value, vl),
							__riscv_vand_vx_u32m1(v_mtip1, LOWER_MASK::value, vl),
							vl
						);
						vuint32m1_t v_mag_mask = __riscv_vand_vx_u32m1(v_y, 1, vl);
						v_mag_mask = __riscv_vrsub_vx_u32m1(v_mag_mask, 0, vl);
						v_mag_mask = __riscv_vand_vx_u32m1(v_mag_mask, A, vl);
						v_y = __riscv_vsrl_vx_u32m1(v_y, 1u, vl);
						v_mti = __riscv_vxor_vv_u32m1(v_y, v_mag_mask, vl);
						vuint32m1_t v_mtipm = __riscv_vle32_v_u32m1(&mt[i + M], vl);
						v_mti = __riscv_vxor_vv_u32m1(v_mti, v_mtipm, vl);
						__riscv_vse32_v_u32m1(&mt[i], v_mti, vl);
					}

					i = NPM::value;
					for (std::size_t vl, n = M - 1; n > 0; n -= vl, i += vl) {
						vl = __riscv_vsetvl_e32m1(n);
						vuint32m1_t v_mti = __riscv_vle32_v_u32m1(&mt[i], vl);
						vuint32m1_t v_mtip1 = __riscv_vle32_v_u32m1(&mt[i + 1], vl);
						vuint32m1_t v_y = __riscv_vor_vv_u32m1(
							__riscv_vand_vx_u32m1(v_mti, UPPER_MASK::value, vl),
							__riscv_vand_vx_u32m1(v_mtip1, LOWER_MASK::value, vl),
							vl
						);
						vuint32m1_t v_mag_mask = __riscv_vand_vx_u32m1(v_y, 1, vl);
						v_mag_mask = __riscv_vrsub_vx_u32m1(v_mag_mask, 0, vl);
						v_mag_mask = __riscv_vand_vx_u32m1(v_mag_mask, A, vl);
						v_y = __riscv_vsrl_vx_u32m1(v_y, 1u, vl);
						v_mti = __riscv_vxor_vv_u32m1(v_y, v_mag_mask, vl);
						vuint32m1_t v_mtipm = __riscv_vle32_v_u32m1(&mt[i - (NPM::value)], vl);
						v_mti = __riscv_vxor_vv_u32m1(v_mti, v_mtipm, vl);
						__riscv_vse32_v_u32m1(&mt[i], v_mti, vl);
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

					std::size_t i = 0;
					for (std::size_t vl, n = NPM::value; n > 0; n -= vl, i += vl) {
						vl = __riscv_vsetvl_e64m1(n);
						vuint64m1_t v_mti = __riscv_vle64_v_u64m1(&mt[i], vl);
						vuint64m1_t v_mtip1 = __riscv_vle64_v_u64m1(&mt[i + 1], vl);
						vuint64m1_t v_y = __riscv_vor_vv_u64m1(
							__riscv_vand_vx_u64m1(v_mti, UPPER_MASK::value, vl),
							__riscv_vand_vx_u64m1(v_mtip1, LOWER_MASK::value, vl),
							vl
						);
						vuint64m1_t v_mag_mask = __riscv_vand_vx_u64m1(v_y, 1, vl);
						v_mag_mask = __riscv_vrsub_vx_u64m1(v_mag_mask, 0, vl);
						v_mag_mask = __riscv_vand_vx_u64m1(v_mag_mask, A, vl);
						v_y = __riscv_vsrl_vx_u64m1(v_y, 1u, vl);
						v_mti = __riscv_vxor_vv_u64m1(v_y, v_mag_mask, vl);
						vuint64m1_t v_mtipm = __riscv_vle64_v_u64m1(&mt[i + M], vl);
						v_mti = __riscv_vxor_vv_u64m1(v_mti, v_mtipm, vl);
						__riscv_vse64_v_u64m1(&mt[i], v_mti, vl);
					}

					i = NPM::value;
					for (std::size_t vl, n = M - 1; n > 0; n -= vl, i += vl) {
						vl = __riscv_vsetvl_e64m1(n);
						vuint64m1_t v_mti = __riscv_vle64_v_u64m1(&mt[i], vl);
						vuint64m1_t v_mtip1 = __riscv_vle64_v_u64m1(&mt[i + 1], vl);
						vuint64m1_t v_y = __riscv_vor_vv_u64m1(
							__riscv_vand_vx_u64m1(v_mti, UPPER_MASK::value, vl),
							__riscv_vand_vx_u64m1(v_mtip1, LOWER_MASK::value, vl),
							vl
						);
						vuint64m1_t v_mag_mask = __riscv_vand_vx_u64m1(v_y, 1, vl);
						v_mag_mask = __riscv_vrsub_vx_u64m1(v_mag_mask, 0, vl);
						v_mag_mask = __riscv_vand_vx_u64m1(v_mag_mask, A, vl);
						v_y = __riscv_vsrl_vx_u64m1(v_y, 1u, vl);
						v_mti = __riscv_vxor_vv_u64m1(v_y, v_mag_mask, vl);
						vuint64m1_t v_mtipm = __riscv_vle64_v_u64m1(&mt[i - (NPM::value)], vl);
						v_mti = __riscv_vxor_vv_u64m1(v_mti, v_mtipm, vl);
						__riscv_vse64_v_u64m1(&mt[i], v_mti, vl);
					}

					result_type y = (mt[N - 1] & UPPER_MASK::value) | (mt[0] & LOWER_MASK::value);
					mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ ((y & 0x1UL) ? A : 0);
				}

			} // namespace riscv_v

		} // namespace detail

	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_ENGINE_DETAIL_MT_TWIST_MT_TWIST_RISCV_V_PART_HPP
