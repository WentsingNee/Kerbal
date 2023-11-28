/**
 * @file       mt_generate_copy_n.wasm_simd128.part.hpp
 * @brief
 * @date       2022-11-05
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_DETAIL_MT_GENERATE_COPY_N_MT_GENERATE_COPY_N_WASM_SIMD128_PART_HPP
#define KERBAL_RANDOM_DETAIL_MT_GENERATE_COPY_N_MT_GENERATE_COPY_N_WASM_SIMD128_PART_HPP

#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>

#include <wasm_simd128.h>

#include <kerbal/random/detail/mt_generate_copy_n/mt_generate_copy_n.plain.part.hpp>


namespace kerbal
{

	namespace random
	{

		namespace detail
		{

			namespace wasm_simd128
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
					typedef kerbal::compatibility::uint32_t result_type;

					typedef kerbal::type_traits::integral_constant<std::size_t, 128 / 32> STEP;
					const v128_t v128_B = wasm_u32x4_const_splat(B);
					const v128_t v128_C = wasm_u32x4_const_splat(C);
					const v128_t v128_D = wasm_u32x4_const_splat(D);

					std::size_t i = 0;
					for (; i + STEP::value <= n; i += STEP::value) {
						v128_t v128_y = wasm_v128_load(&mt_now[i]);
						v128_t v128_shift, v128_and;

						v128_shift = wasm_u32x4_shr(v128_y, U);
						v128_and = wasm_v128_and(v128_shift, v128_D);
						v128_y = wasm_v128_xor(v128_y, v128_and);

						v128_shift = wasm_i32x4_shl(v128_y, S);
						v128_and = wasm_v128_and(v128_shift, v128_B);
						v128_y = wasm_v128_xor(v128_y, v128_and);

						v128_shift = wasm_i32x4_shl(v128_y, T);
						v128_and = wasm_v128_and(v128_shift, v128_C);
						v128_y = wasm_v128_xor(v128_y, v128_and);

						v128_shift = wasm_u32x4_shr(v128_y, L);
						v128_y = wasm_v128_xor(v128_y, v128_shift);

						wasm_v128_store(&out[i], v128_y);
					}

					while (i < n) {
						EACH(i);
						++i;
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
					typedef kerbal::compatibility::uint64_t result_type;

					typedef kerbal::type_traits::integral_constant<std::size_t, 128 / 64> STEP;
					const v128_t v128_B = wasm_u64x2_const_splat(B);
					const v128_t v128_C = wasm_u64x2_const_splat(C);
					const v128_t v128_D = wasm_u64x2_const_splat(D);

					std::size_t i = 0;
					for (; i + STEP::value <= n; i += STEP::value) {
						v128_t v128_y = wasm_v128_load(&mt_now[i]);
						v128_t v128_shift, v128_and;

						v128_shift = wasm_u64x2_shr(v128_y, U);
						v128_and = wasm_v128_and(v128_shift, v128_D);
						v128_y = wasm_v128_xor(v128_y, v128_and);

						v128_shift = wasm_i64x2_shl(v128_y, S);
						v128_and = wasm_v128_and(v128_shift, v128_B);
						v128_y = wasm_v128_xor(v128_y, v128_and);

						v128_shift = wasm_i64x2_shl(v128_y, T);
						v128_and = wasm_v128_and(v128_shift, v128_C);
						v128_y = wasm_v128_xor(v128_y, v128_and);

						v128_shift = wasm_u64x2_shr(v128_y, L);
						v128_y = wasm_v128_xor(v128_y, v128_shift);

						wasm_v128_store(&out[i], v128_y);
					}

					while (i < n) {
						EACH(i);
						++i;
					}

				}

			} // namespace wasm_simd128

		} // namespace detail

	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_DETAIL_MT_GENERATE_COPY_N_MT_GENERATE_COPY_N_WASM_SIMD128_PART_HPP
