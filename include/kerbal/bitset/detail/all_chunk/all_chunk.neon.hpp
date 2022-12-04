/**
 * @file       all_chunk.neon.hpp
 * @brief
 * @date       2022-11-09
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_BITSET_DETAIL_ALL_CHUNK_ALL_CHUNK_NEON_HPP
#define KERBAL_BITSET_DETAIL_ALL_CHUNK_ALL_CHUNK_NEON_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>

#include <arm_neon.h>

#include <kerbal/bitset/detail/all_chunk/all_chunk.plain.hpp>


namespace kerbal
{

	namespace bitset
	{

		namespace detail
		{

			namespace neon
			{

				inline bool test_all_ones(uint64x2_t a)
				{
					typedef kerbal::compatibility::uint64_t Block;
					typedef kerbal::type_traits::integral_constant<Block, static_cast<Block>(~static_cast<Block>(0))> ALL_ONE;

					return (vgetq_lane_u64(a, 0) & vgetq_lane_u64(a, 1)) == ALL_ONE::value;
				}

				inline bool all_chunk(const kerbal::compatibility::uint32_t block[], std::size_t chunk_size) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint32_t Block;
					typedef kerbal::type_traits::integral_constant<Block, static_cast<Block>(~static_cast<Block>(0))> ALL_ONE;

					typedef kerbal::type_traits::integral_constant<std::size_t, 128 / 32> STEP;

					std::size_t i = 0;
					for (; i + 8 * STEP::value <= chunk_size; i += 8 * STEP::value) {
//						uint64x2_t q_blockp0 = vreinterpretq_u64_u32(vld1q_u32(&block[i + 0 * STEP::value]));
//						uint64x2_t q_blockp1 = vreinterpretq_u64_u32(vld1q_u32(&block[i + 1 * STEP::value]));
//						uint64x2_t q_blockp2 = vreinterpretq_u64_u32(vld1q_u32(&block[i + 2 * STEP::value]));
//						uint64x2_t q_blockp3 = vreinterpretq_u64_u32(vld1q_u32(&block[i + 3 * STEP::value]));
//						uint64x2_t q_blockp4 = vreinterpretq_u64_u32(vld1q_u32(&block[i + 4 * STEP::value]));
//						uint64x2_t q_blockp5 = vreinterpretq_u64_u32(vld1q_u32(&block[i + 5 * STEP::value]));
//						uint64x2_t q_blockp6 = vreinterpretq_u64_u32(vld1q_u32(&block[i + 6 * STEP::value]));
//						uint64x2_t q_blockp7 = vreinterpretq_u64_u32(vld1q_u32(&block[i + 7 * STEP::value]));
//
//						q_blockp0 = vandq_u64(q_blockp0, q_blockp1);
//						q_blockp0 = vandq_u64(q_blockp0, q_blockp2);
//						q_blockp0 = vandq_u64(q_blockp0, q_blockp3);
//						q_blockp0 = vandq_u64(q_blockp0, q_blockp4);
//						q_blockp0 = vandq_u64(q_blockp0, q_blockp5);
//						q_blockp0 = vandq_u64(q_blockp0, q_blockp6);
//						q_blockp0 = vandq_u64(q_blockp0, q_blockp7);
//
//
//						if (!test_all_ones(q_blockp0)) {
//							return false;
//						}


						uint32x4x4_t qx4_block0 = vld4q_u32(&block[i]);
						uint32x4x4_t qx4_block1 = vld4q_u32(&block[i + 4 * STEP::value]);

						qx4_block0.val[0] = vandq_u32(qx4_block0.val[0], qx4_block0.val[1]);
						qx4_block0.val[0] = vandq_u32(qx4_block0.val[0], qx4_block0.val[2]);
						qx4_block0.val[0] = vandq_u32(qx4_block0.val[0], qx4_block0.val[3]);

						qx4_block0.val[0] = vandq_u32(qx4_block0.val[0], qx4_block1.val[0]);
						qx4_block0.val[0] = vandq_u32(qx4_block0.val[0], qx4_block1.val[1]);
						qx4_block0.val[0] = vandq_u32(qx4_block0.val[0], qx4_block1.val[2]);
						qx4_block0.val[0] = vandq_u32(qx4_block0.val[0], qx4_block1.val[3]);

						if (!test_all_ones(vreinterpretq_u64_u32(qx4_block0.val[0]))) {
							return false;
						}
					}

					while (i < chunk_size) {
						EACH(i);
						++i;
					}

					return true;
				}

				inline bool all_chunk(const kerbal::compatibility::uint64_t block[], std::size_t chunk_size) KERBAL_NOEXCEPT
				{
					typedef kerbal::compatibility::uint64_t Block;
					typedef kerbal::type_traits::integral_constant<Block, static_cast<Block>(~static_cast<Block>(0))> ALL_ONE;

					typedef kerbal::type_traits::integral_constant<std::size_t, 128 / 64> STEP;

					std::size_t i = 0;
					for (; i + 8 * STEP::value <= chunk_size; i += 8 * STEP::value) {

						uint32x4x4_t qx4_block0 = vld4q_u32(reinterpret_cast<const uint32_t *>(&block[i])); // arm g++ doesn't support vld4q_u64
						uint32x4x4_t qx4_block1 = vld4q_u32(reinterpret_cast<const uint32_t *>(&block[i + 4 * STEP::value]));

						uint64x2_t q_blockp0 = vreinterpretq_u64_u32(qx4_block0.val[0]);
						uint64x2_t q_blockp1 = vreinterpretq_u64_u32(qx4_block0.val[1]);
						uint64x2_t q_blockp2 = vreinterpretq_u64_u32(qx4_block0.val[2]);
						uint64x2_t q_blockp3 = vreinterpretq_u64_u32(qx4_block0.val[3]);
						uint64x2_t q_blockp4 = vreinterpretq_u64_u32(qx4_block1.val[0]);
						uint64x2_t q_blockp5 = vreinterpretq_u64_u32(qx4_block1.val[1]);
						uint64x2_t q_blockp6 = vreinterpretq_u64_u32(qx4_block1.val[2]);
						uint64x2_t q_blockp7 = vreinterpretq_u64_u32(qx4_block1.val[3]);

						q_blockp0 = vandq_u64(q_blockp0, q_blockp1);
						q_blockp0 = vandq_u64(q_blockp0, q_blockp2);
						q_blockp0 = vandq_u64(q_blockp0, q_blockp3);

						q_blockp0 = vandq_u64(q_blockp0, q_blockp4);
						q_blockp0 = vandq_u64(q_blockp0, q_blockp5);
						q_blockp0 = vandq_u64(q_blockp0, q_blockp6);
						q_blockp0 = vandq_u64(q_blockp0, q_blockp7);

						if (!test_all_ones(q_blockp0)) {
							return false;
						}
					}

					while (i < chunk_size) {
						EACH(i);
						++i;
					}

					return true;
				}

			} // namespace neon

		} // namespace detail

	} // namespace bitset

} // namespace kerbal


#endif // KERBAL_BITSET_DETAIL_ALL_CHUNK_ALL_CHUNK_NEON_HPP
