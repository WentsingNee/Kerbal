/**
 * @file       mt_generate_copy_n.neon.part.hpp
 * @brief
 * @date       2022-11-05
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_DETAIL_MT_GENERATE_COPY_N_MT_GENERATE_COPY_N_NEON_PART_HPP
#define KERBAL_RANDOM_DETAIL_MT_GENERATE_COPY_N_MT_GENERATE_COPY_N_NEON_PART_HPP

#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>

#include <arm_neon.h>

#include <kerbal/random/detail/mt_generate_copy_n/mt_generate_copy_n.plain.part.hpp>


namespace kerbal
{

	namespace random
	{

		namespace detail
		{

			namespace neon
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
					const uint32x4_t q_B = vdupq_n_u32(B);
					const uint32x4_t q_C = vdupq_n_u32(C);
					const uint32x4_t q_D = vdupq_n_u32(D);

					std::size_t i = 0;
					for (; i + STEP::value <= n; i += STEP::value) {
						uint32x4_t q_mti = vld1q_u32(reinterpret_cast< ::uint32_t const *>(&mt_now[i]));
						uint32x4_t q_shift, q_and;

						q_shift = vshrq_n_u32(q_mti, U);
						q_and = vandq_u32(q_shift, q_D);
						q_mti = veorq_u32(q_mti, q_and);

						q_shift = vshlq_n_u32(q_mti, S);
						q_and = vandq_u32(q_shift, q_B);
						q_mti = veorq_u32(q_mti, q_and);

						q_shift = vshlq_n_u32(q_mti, T);
						q_and = vandq_u32(q_shift, q_C);
						q_mti = veorq_u32(q_mti, q_and);

						q_shift = vshrq_n_u32(q_mti, L);
						q_mti = veorq_u32(q_mti, q_shift);

						vst1q_u32(reinterpret_cast< ::uint32_t *>(out), q_mti);
						out += STEP::value;
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
					const uint64x2_t q_B = vdupq_n_u64(B);
					const uint64x2_t q_C = vdupq_n_u64(C);
					const uint64x2_t q_D = vdupq_n_u64(D);

					std::size_t i = 0;
					for (; i + STEP::value <= n; i += STEP::value) {
						uint64x2_t q_mti = vld1q_u64(reinterpret_cast< ::uint64_t const *>(&mt_now[i]));
						uint64x2_t q_shift, q_and;

						q_shift = vshrq_n_u64(q_mti, U);
						q_and = vandq_u64(q_shift, q_D);
						q_mti = veorq_u64(q_mti, q_and);

						q_shift = vshlq_n_u64(q_mti, S);
						q_and = vandq_u64(q_shift, q_B);
						q_mti = veorq_u64(q_mti, q_and);

						q_shift = vshlq_n_u64(q_mti, T);
						q_and = vandq_u64(q_shift, q_C);
						q_mti = veorq_u64(q_mti, q_and);

						q_shift = vshrq_n_u64(q_mti, L);
						q_mti = veorq_u64(q_mti, q_shift);

						vst1q_u64(reinterpret_cast< ::uint64_t *>(out), q_mti);
						out += STEP::value;
					}

					while (i < n) {
						EACH(i);
						++i;
					}

				}

			} // namespace neon

		} // namespace detail

	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_DETAIL_MT_GENERATE_COPY_N_MT_GENERATE_COPY_N_NEON_PART_HPP
