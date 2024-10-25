/**
 * @file       mt_twist.sve.part.hpp
 * @brief
 * @date       2022-11-4
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_ENGINE_DETAIL_MT_TWIST_MT_TWIST_SVE_PART_HPP
#define KERBAL_RANDOM_ENGINE_DETAIL_MT_TWIST_MT_TWIST_SVE_PART_HPP

#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/type_traits/conditional.hpp>
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

				template <std::size_t N, std::size_t M, std::size_t R, kerbal::compatibility::uint32_t A>
				void mt_twist(kerbal::compatibility::uint32_t mto[]) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint32_t result_type;
					typedef typename kerbal::type_traits::conditional<
						sizeof(std::size_t) == 4,
						::uint32_t,
						::uint64_t
					>::type index_t;

					typedef kerbal::type_traits::integral_constant<result_type, (~static_cast<result_type>(0)) << R> UPPER_MASK; // most significant w-r bits
					typedef kerbal::type_traits::integral_constant<result_type, ~UPPER_MASK::value> LOWER_MASK; // least significant r bits
					KERBAL_STATIC_ASSERT(N >= M, "N should >= M");
					typedef kerbal::type_traits::integral_constant<std::size_t, N - M> NPM;

					::uint32_t * mt = reinterpret_cast< ::uint32_t *>(mto);
					const std::size_t STEP = svcntw();
					const svuint32_t sv_UPPER_MASK = svdup_u32(UPPER_MASK::value);
					const svuint32_t sv_ZERO = svdup_u32(0);
					const svuint32_t sv_ONE = svdup_u32(1);
					const svuint32_t sv_A = svdup_u32(A);
					svbool_t SVTRUE = svptrue_b32();

					index_t i = 0;
					svbool_t pg = svwhilelt_b32(i, NPM::value);
					do {
						svuint32_t sv_mti = svld1(pg, &mt[i]);
						svuint32_t sv_mtip1 = svld1(pg, &mt[i + 1]);
						svuint32_t sv_y = svorr_x(pg,
							svand_x(pg, sv_mti, sv_UPPER_MASK),
							svbic_x(pg, sv_mtip1, sv_UPPER_MASK));
						svuint32_t sv_mag_mask = svand_x(pg, sv_y, sv_ONE);
						sv_mag_mask = svsub_x(pg, sv_ZERO, sv_mag_mask);
						sv_mag_mask = svand_x(pg, sv_mag_mask, sv_A);
						sv_y = svlsr_x(pg, sv_y, 1u);
						sv_mti = sveor_x(pg, sv_y, sv_mag_mask);
						svuint32_t sv_mtipm = svld1(pg, &mt[i + M]);
						sv_mti = sveor_x(pg, sv_mti, sv_mtipm);
						svst1(pg, &mt[i], sv_mti);

						i += STEP;
						pg = svwhilelt_b32(i, NPM::value);
					} while(svptest_any(SVTRUE, pg));

					i = NPM::value;
					pg = svwhilelt_b32(i, N - 1);
					do {
						svuint32_t sv_mti = svld1(pg, &mt[i]);
						svuint32_t sv_mtip1 = svld1(pg, &mt[i + 1]);
						svuint32_t sv_y = svorr_x(pg,
							svand_x(pg, sv_mti, sv_UPPER_MASK),
							svbic_x(pg, sv_mtip1, sv_UPPER_MASK));
						svuint32_t sv_mag_mask = svand_x(pg, sv_y, sv_ONE);
						sv_mag_mask = svsub_x(pg, sv_ZERO, sv_mag_mask);
						sv_mag_mask = svand_x(pg, sv_mag_mask, sv_A);
						sv_y = svlsr_x(pg, sv_y, 1u);
						sv_mti = sveor_x(pg, sv_y, sv_mag_mask);
						svuint32_t sv_mtipm = svld1(pg, &mt[i - (NPM::value)]);
						sv_mti = sveor_x(pg, sv_mti, sv_mtipm);
						svst1(pg, &mt[i], sv_mti);

						i += STEP;
						pg = svwhilelt_b32(i, N - 1);
					} while (svptest_any(SVTRUE, pg));

					result_type y = (mt[N - 1] & UPPER_MASK::value) | (mt[0] & LOWER_MASK::value);
					mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ ((y & 0x1UL) ? A : 0);
				}

				template <std::size_t N, std::size_t M, std::size_t R, kerbal::compatibility::uint64_t A>
				void mt_twist(kerbal::compatibility::uint64_t mto[]) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint64_t result_type;
					typedef typename kerbal::type_traits::conditional<
						sizeof(std::size_t) == 4,
						::uint32_t,
						::uint64_t
					>::type index_t;

					typedef kerbal::type_traits::integral_constant<result_type, (~static_cast<result_type>(0)) << R> UPPER_MASK; // most significant w-r bits
					typedef kerbal::type_traits::integral_constant<result_type, ~UPPER_MASK::value> LOWER_MASK; // least significant r bits
					KERBAL_STATIC_ASSERT(N >= M, "N should >= M");
					typedef kerbal::type_traits::integral_constant<index_t, N - M> NPM;

					::uint64_t * mt = reinterpret_cast< ::uint64_t *>(mto);
					const std::size_t STEP = svcntd();
					const svuint64_t sv_UPPER_MASK = svdup_u64(UPPER_MASK::value);
					const svuint64_t sv_ZERO = svdup_u64(0);
					const svuint64_t sv_ONE = svdup_u64(1);
					const svuint64_t sv_A = svdup_u64(A);
					svbool_t SVTRUE = svptrue_b64();

					index_t i = 0;
					svbool_t pg = svwhilelt_b64(i, NPM::value);
					do {
						svuint64_t sv_mti = svld1(pg, &mt[i]);
						svuint64_t sv_mtip1 = svld1(pg, &mt[i + 1]);
						svuint64_t sv_y = svorr_x(pg,
							svand_x(pg, sv_mti, sv_UPPER_MASK),
							svbic_x(pg, sv_mtip1, sv_UPPER_MASK));
						svuint64_t sv_mag_mask = svand_x(pg, sv_y, sv_ONE);
						sv_mag_mask = svsub_x(pg, sv_ZERO, sv_mag_mask);
						sv_mag_mask = svand_x(pg, sv_mag_mask, sv_A);
						sv_y = svlsr_x(pg, sv_y, 1u);
						sv_mti = sveor_x(pg, sv_y, sv_mag_mask);
						svuint64_t sv_mtipm = svld1(pg, &mt[i + M]);
						sv_mti = sveor_x(pg, sv_mti, sv_mtipm);
						svst1(pg, &mt[i], sv_mti);

						i += STEP;
						pg = svwhilelt_b64(i, NPM::value);
					} while (svptest_any(SVTRUE, pg));

					i = NPM::value;
					pg = svwhilelt_b64(i, N - 1);
					do {
						svuint64_t sv_mti = svld1(pg, &mt[i]);
						svuint64_t sv_mtip1 = svld1(pg, &mt[i + 1]);
						svuint64_t sv_y = svorr_x(pg,
							svand_x(pg, sv_mti, sv_UPPER_MASK),
							svbic_x(pg, sv_mtip1, sv_UPPER_MASK));
						svuint64_t sv_mag_mask = svand_x(pg, sv_y, sv_ONE);
						sv_mag_mask = svsub_x(pg, sv_ZERO, sv_mag_mask);
						sv_mag_mask = svand_x(pg, sv_mag_mask, sv_A);
						sv_y = svlsr_x(pg, sv_y, 1u);
						sv_mti = sveor_x(pg, sv_y, sv_mag_mask);
						svuint64_t sv_mtipm = svld1(pg, &mt[i - (NPM::value)]);
						sv_mti = sveor_x(pg, sv_mti, sv_mtipm);
						svst1(pg, &mt[i], sv_mti);

						i += STEP;
						pg = svwhilelt_b64(i, N - 1);
					} while (svptest_any(SVTRUE, pg));

					result_type y = (mt[N - 1] & UPPER_MASK::value) | (mt[0] & LOWER_MASK::value);
					mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ ((y & 0x1UL) ? A : 0);
				}

			} // namespace sve

		} // namespace detail

	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_ENGINE_DETAIL_MT_TWIST_MT_TWIST_SVE_PART_HPP
