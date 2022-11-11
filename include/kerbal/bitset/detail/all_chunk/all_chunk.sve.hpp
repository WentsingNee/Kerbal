/**
 * @file       all_chunk.sve.hpp
 * @brief
 * @date       2022-11-11
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_BITSET_DETAIL_ALL_CHUNK_ALL_CHUNK_SVE_HPP
#define KERBAL_BITSET_DETAIL_ALL_CHUNK_ALL_CHUNK_SVE_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>

#include <arm_sve.h>

#include <kerbal/bitset/detail/all_chunk/all_chunk.plain.hpp>


namespace kerbal
{

	namespace bitset
	{

		namespace detail
		{

			namespace sve
			{

				inline bool all_chunk(const kerbal::compatibility::uint32_t block[], std::size_t trunk_size) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint32_t Block;
					typedef kerbal::type_traits::integral_constant<Block, static_cast<Block>(~static_cast<Block>(0))> ALL_ONE;

					const std::size_t STEP = svcntw();
					svuint32_t sv_ALL_ONE = svdup_u32(ALL_ONE::value);
					svbool_t SVTRUE = svptrue_b32();

					std::size_t i = 0;
					svbool_t pg = svwhilelt_b32(i, trunk_size);
					do {
						svuint32_t sv_block = svld1(pg, &block[i]);
						svbool_t sv_noteq = svcmpne(pg, sv_block, sv_ALL_ONE);

						if (svptest_any(pg, sv_noteq)) {
							return false;
						}

						i += STEP;
						pg = svwhilelt_b32(i, trunk_size);
					} while(svptest_any(SVTRUE, pg));

					return true;
				}

//				inline bool all_chunk4(const kerbal::compatibility::uint32_t block[], std::size_t trunk_size) KERBAL_NOEXCEPT
//				{
//					typedef kerbal::compatibility::uint32_t Block;
//					typedef kerbal::type_traits::integral_constant<Block, static_cast<Block>(~static_cast<Block>(0))> ALL_ONE;
//
//					typedef kerbal::type_traits::integral_constant<std::size_t, 128 / 32> STEP;
//					const uint32x4_t sv_ALL_ONE = vdupsv_n_u32(ALL_ONE::value);
//
//					std::size_t i = 0;
//					for (; i + 4 * STEP::value <= trunk_size; i += 4 * STEP::value) {
//						uint32x4x4_t qx4_block = vld4sv_u32(&block[i]);
//
//						qx4_block.val[0] = vandsv_u32(qx4_block.val[0], qx4_block.val[1]);
//						qx4_block.val[0] = vandsv_u32(qx4_block.val[0], qx4_block.val[2]);
//						qx4_block.val[0] = vandsv_u32(qx4_block.val[0], qx4_block.val[3]);
//
//						if (!test_all_ones(vreinterpretsv_u64_u32(qx4_block.val[0]))) {
//							return false;
//						}
//					}
//
//					while (i < trunk_size) {
//						EACH(i);
//						++i;
//					}
//
//					return true;
//				}

				inline bool all_chunk8(const kerbal::compatibility::uint32_t block[], std::size_t trunk_size) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint32_t Block;
					typedef kerbal::type_traits::integral_constant<Block, static_cast<Block>(~static_cast<Block>(0))> ALL_ONE;

					const std::size_t STEP = svcntw();
					svuint32_t sv_ALL_ONE = svdup_u32(ALL_ONE::value);
					svbool_t SVTRUE = svptrue_b32();

					std::size_t i = 0;
					for (; i + 8 * STEP <= trunk_size; i += 8 * STEP) {
						svuint32x4_t svx4_block0 = svld4(SVTRUE, &block[i + 0 * STEP]);
						svuint32x4_t svx4_block1 = svld4(SVTRUE, &block[i + 4 * STEP]);

						svuint32_t sv_blockp0 = svget4(svx4_block0, 0);
						svuint32_t sv_blockp1 = svget4(svx4_block0, 1);
						svuint32_t sv_blockp2 = svget4(svx4_block0, 2);
						svuint32_t sv_blockp3 = svget4(svx4_block0, 3);
						svuint32_t sv_blockp4 = svget4(svx4_block1, 0);
						svuint32_t sv_blockp5 = svget4(svx4_block1, 1);
						svuint32_t sv_blockp6 = svget4(svx4_block1, 2);
						svuint32_t sv_blockp7 = svget4(svx4_block1, 3);

						sv_blockp0 = svand_x(SVTRUE, sv_blockp0, sv_blockp1);
						sv_blockp0 = svand_x(SVTRUE, sv_blockp0, sv_blockp2);
						sv_blockp0 = svand_x(SVTRUE, sv_blockp0, sv_blockp3);
						sv_blockp0 = svand_x(SVTRUE, sv_blockp0, sv_blockp4);
						sv_blockp0 = svand_x(SVTRUE, sv_blockp0, sv_blockp5);
						sv_blockp0 = svand_x(SVTRUE, sv_blockp0, sv_blockp6);
						sv_blockp0 = svand_x(SVTRUE, sv_blockp0, sv_blockp7);

						svbool_t sv_noteq = svcmpne(SVTRUE, sv_blockp0, sv_ALL_ONE);

						if (svptest_any(SVTRUE, sv_noteq)) {
							return false;
						}
					}

					svbool_t pg = svwhilelt_b32(i, trunk_size);
					{
						svuint32_t sv_block = svld1(pg, &block[i]);
						svbool_t sv_noteq = svcmpne(pg, sv_block, sv_ALL_ONE);

						if (svptest_any(pg, sv_noteq)) {
							return false;
						}
					}

					return true;
				}

			} // namespace sve

		} // namespace detail

	} // namespace bitset

} // namespace kerbal


#endif // KERBAL_BITSET_DETAIL_ALL_CHUNK_ALL_CHUNK_SVE_HPP
