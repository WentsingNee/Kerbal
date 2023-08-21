/**
 * @file       mt_generate_copy_n.sve.part.hpp
 * @brief
 * @date       2022-11-08
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_DETAIL_MT_GENERATE_COPY_N_MT_GENERATE_COPY_N_SVE_PART_HPP
#define KERBAL_RANDOM_DETAIL_MT_GENERATE_COPY_N_MT_GENERATE_COPY_N_SVE_PART_HPP

#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>

#include <arm_sve.h>


namespace kerbal
{

	namespace random
	{

		namespace detail
		{

			namespace sve
			{

				template <std::size_t U, kerbal::compatibility::uint32_t D, std::size_t S,
						kerbal::compatibility::uint32_t B, std::size_t T,
						kerbal::compatibility::uint32_t C, std::size_t L
				>
				void mt_generate_copy_n(const kerbal::compatibility::uint32_t mt_now[], kerbal::compatibility::uint32_t * out, std::size_t n) KERBAL_NOEXCEPT
				{
					const std::size_t STEP = svcntw();
					const svuint32_t sv_B = svdup_u32(B);
					const svuint32_t sv_C = svdup_u32(C);
					const svuint32_t sv_D = svdup_u32(D);
					svbool_t SVTRUE = svptrue_b32();

					std::size_t i = 0;
					svbool_t pg = svwhilelt_b32(i, n);
					do {
						svuint32_t sv_y = svld1(pg, &mt_now[i]);
						svuint32_t sv_shift, sv_and;

						sv_shift = svlsr_x(pg, sv_y, U);
						sv_and = svand_x(pg, sv_shift, sv_D);
						sv_y = sveor_x(pg, sv_y, sv_and);

						sv_shift = svlsl_x(pg, sv_y, S);
						sv_and = svand_x(pg, sv_shift, sv_B);
						sv_y = sveor_x(pg, sv_y, sv_and);

						sv_shift = svlsl_x(pg, sv_y, T);
						sv_and = svand_x(pg, sv_shift, sv_C);
						sv_y = sveor_x(pg, sv_y, sv_and);

						sv_shift = svlsr_x(pg, sv_y, L);
						sv_y = sveor_x(pg, sv_y, sv_shift);

						svst1(pg, &out[i], sv_y);

						i += STEP;
						pg = svwhilelt_b32(i, n);
					} while(svptest_any(SVTRUE, pg));
				}

				template <std::size_t U, kerbal::compatibility::uint64_t D, std::size_t S,
						kerbal::compatibility::uint64_t B, std::size_t T,
						kerbal::compatibility::uint64_t C, std::size_t L
				>
				void mt_generate_copy_n(const kerbal::compatibility::uint64_t mt_now[], kerbal::compatibility::uint64_t * out, std::size_t n) KERBAL_NOEXCEPT
				{
					const std::size_t STEP = svcntd();
					const svuint64_t sv_B = svdup_u64(B);
					const svuint64_t sv_C = svdup_u64(C);
					const svuint64_t sv_D = svdup_u64(D);
					svbool_t SVTRUE = svptrue_b64();

					std::size_t i = 0;
					svbool_t pg = svwhilelt_b64(i, n);
					do {
						svuint64_t sv_y = svld1(pg, &mt_now[i]);
						svuint64_t sv_shift, sv_and;

						sv_shift = svlsr_x(pg, sv_y, U);
						sv_and = svand_x(pg, sv_shift, sv_D);
						sv_y = sveor_x(pg, sv_y, sv_and);

						sv_shift = svlsl_x(pg, sv_y, S);
						sv_and = svand_x(pg, sv_shift, sv_B);
						sv_y = sveor_x(pg, sv_y, sv_and);

						sv_shift = svlsl_x(pg, sv_y, T);
						sv_and = svand_x(pg, sv_shift, sv_C);
						sv_y = sveor_x(pg, sv_y, sv_and);

						sv_shift = svlsr_x(pg, sv_y, L);
						sv_y = sveor_x(pg, sv_y, sv_shift);

						svst1(pg, &out[i], sv_y);

						i += STEP;
						pg = svwhilelt_b64(i, n);
					} while (svptest_any(SVTRUE, pg));

				}

			} // namespace sve

		} // namespace detail

	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_DETAIL_MT_GENERATE_COPY_N_MT_GENERATE_COPY_N_SVE_PART_HPP
