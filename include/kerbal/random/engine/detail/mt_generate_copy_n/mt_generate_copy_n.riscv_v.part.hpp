/**
 * @file       mt_generate_copy_n.riscv_v.part.hpp
 * @brief
 * @date       2023-12-16
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_ENGINE_DETAIL_MT_GENERATE_COPY_N_MT_GENERATE_COPY_N_RISCV_V_PART_HPP
#define KERBAL_RANDOM_ENGINE_DETAIL_MT_GENERATE_COPY_N_MT_GENERATE_COPY_N_RISCV_V_PART_HPP

#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/noexcept.hpp>

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
					std::size_t i = 0;
					for (std::size_t vl; n > 0; n -= vl, i += vl) {
						vl = __riscv_vsetvl_e32m1(n);
						vuint32m1_t v_y = __riscv_vle32_v_u32m1(&mt_now[i], vl);
						vuint32m1_t v_shift, v_and;

						v_shift = __riscv_vsrl_vx_u32m1(v_y, U, vl);
						v_and = __riscv_vand_vx_u32m1(v_shift, D, vl);
						v_y = __riscv_vxor_vv_u32m1(v_y, v_and, vl);

						v_shift = __riscv_vsll_vx_u32m1(v_y, S, vl);
						v_and = __riscv_vand_vx_u32m1(v_shift, B, vl);
						v_y = __riscv_vxor_vv_u32m1(v_y, v_and, vl);

						v_shift = __riscv_vsll_vx_u32m1(v_y, T, vl);
						v_and = __riscv_vand_vx_u32m1(v_shift, C, vl);
						v_y = __riscv_vxor_vv_u32m1(v_y, v_and, vl);

						v_shift = __riscv_vsrl_vx_u32m1(v_y, L, vl);
						v_y = __riscv_vxor_vv_u32m1(v_y, v_shift, vl);

						__riscv_vse32_v_u32m1(&out[i], v_y, vl);
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
					std::size_t i = 0;
					for (std::size_t vl; n > 0; n -= vl, i += vl) {
						vl = __riscv_vsetvl_e64m1(n);
						vuint64m1_t v_y = __riscv_vle64_v_u64m1(&mt_now[i], vl);
						vuint64m1_t v_shift, v_and;

						v_shift = __riscv_vsrl_vx_u64m1(v_y, U, vl);
						v_and = __riscv_vand_vx_u64m1(v_shift, D, vl);
						v_y = __riscv_vxor_vv_u64m1(v_y, v_and, vl);

						v_shift = __riscv_vsll_vx_u64m1(v_y, S, vl);
						v_and = __riscv_vand_vx_u64m1(v_shift, B, vl);
						v_y = __riscv_vxor_vv_u64m1(v_y, v_and, vl);

						v_shift = __riscv_vsll_vx_u64m1(v_y, T, vl);
						v_and = __riscv_vand_vx_u64m1(v_shift, C, vl);
						v_y = __riscv_vxor_vv_u64m1(v_y, v_and, vl);

						v_shift = __riscv_vsrl_vx_u64m1(v_y, L, vl);
						v_y = __riscv_vxor_vv_u64m1(v_y, v_shift, vl);

						__riscv_vse64_v_u64m1(&out[i], v_y, vl);
					}

				}

			} // namespace sve

		} // namespace detail

	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_ENGINE_DETAIL_MT_GENERATE_COPY_N_MT_GENERATE_COPY_N_RISCV_V_PART_HPP
