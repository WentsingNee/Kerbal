/**
 * @file       bitarray.neon.hpp
 * @brief
 * @date       2022-11-12
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_NUMERIC_BIT_BITARRAY_BITARRAY_NEON_HPP
#define KERBAL_NUMERIC_BIT_BITARRAY_BITARRAY_NEON_HPP

#include <kerbal/compatibility/alignof.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/smath/max_sa_sb.hpp>
#include <kerbal/type_traits/aligned_storage.hpp>

#include <kerbal/numeric/bit/bitarray/bitarray.plain.hpp>

#include <arm_neon.h>


namespace kerbal
{

	namespace numeric
	{

		namespace detail
		{

			namespace neon
			{

				inline
				kerbal::numeric::bitarray_result<kerbal::compatibility::uint8_t>::type
				bitarray(kerbal::compatibility::uint8_t x)
				{
					typedef kerbal::compatibility::uint8_t T;
					typedef kerbal::compatibility::uint64_t uint64_t;
					typedef typename kerbal::numeric::bitarray_result<T>::type bitarray_result_t;

					uint64_t u = x * 0x0101010101010101ull;
					u &= 0x0102040810204080ull;
					uint8x8_t d_x = vreinterpret_u8_u64(vld1_u64(&u));
					d_x = vmin_u8(d_x, vdup_n_u8(1));

					kerbal::type_traits::aligned_storage<
							kerbal::smath::max_sa_sb<std::size_t, sizeof(bitarray_result_t), sizeof(uint64_t)>::value,
							kerbal::smath::max_sa_sb<std::size_t, KERBAL_ALIGNOF(bitarray_result_t), KERBAL_ALIGNOF(uint64_t)>::value
					>::type as;
					vst1_u64(reinterpret_cast<uint64_t *>(&as), vreinterpret_u64_u8(d_x));
					return reinterpret_cast<const bitarray_result_t &>(as);
				}

				inline
				kerbal::numeric::bitarray_result<kerbal::compatibility::uint8_t>::type
				bitarray_old(kerbal::compatibility::uint8_t x)
				{
					typedef kerbal::compatibility::uint8_t T;
					typedef typename kerbal::numeric::bitarray_result<T>::type bitarray_result_t;

#if 0
					const uint8_t mask[8] = {
							1u << 7, 1u << 6, 1u << 5, 1u << 4,
							1u << 3, 1u << 2, 1u << 1, 1u << 0
					};
					uint8x8_t const d_andmask = vld1_u8(mask);
#else
					uint8x8_t const d_andmask = vcreate_u8(0x0102040810204080ull);
#endif

					uint8x8_t d_x = vdup_n_u8(x);
					d_x = vand_u8(d_x, d_andmask);
					d_x = vmin_u8(d_x, vdup_n_u8(1));

					kerbal::type_traits::aligned_storage<
							kerbal::smath::max_sa_sb<std::size_t, sizeof(bitarray_result_t), sizeof(uint64_t)>::value,
							kerbal::smath::max_sa_sb<std::size_t, KERBAL_ALIGNOF(bitarray_result_t), KERBAL_ALIGNOF(uint64_t)>::value
					>::type as;
					vst1_u64(reinterpret_cast<uint64_t *>(&as), vreinterpret_u64_u8(d_x));
					return reinterpret_cast<const bitarray_result_t &>(as);
				}

//				inline
//				kerbal::numeric::bitarray_result<kerbal::compatibility::uint16_t>::type
//				bitarray(kerbal::compatibility::uint16_t x)
//				{
//					typedef kerbal::compatibility::uint16_t T;
//					typedef kerbal::compatibility::uint8_t uint8_t;
//					typedef kerbal::compatibility::uint64_t uint64_t;
//					typedef typename kerbal::numeric::bitarray_result<T>::type bitarray_result_t;
//
//					uint8x8_t const d_andmask = vcreate_u8(0x0102040810204080ull);
//					uint8x16_t const q_andmask = vcombine_u8(d_andmask, d_andmask);
//
//					uint64_t u = ((static_cast<uint64_t>(x & 0xff00) << 24) | x & 0xff) * 0x01010101u;
//
//					uint8x16_t q_x = vld1_u64(&u);
//					q_x = _mm_shuffle_epi32(q_x, 0x05);
//					q_x = vand_u8(q_x, q_andmask);
//					q_x = vmin_u8(q_x, vdup_n_u8(1));
//
//					kerbal::numeric::bitarray_result<T>::type r;
//					vst1q_u8(reinterpret_cast<uint8_t*>(&r[0]), q_x);
//
//					return r;
//				}

				inline
				kerbal::numeric::bitarray_result<kerbal::compatibility::uint16_t>::type
				bitarray(kerbal::compatibility::uint16_t x)
				{
					typedef kerbal::compatibility::uint16_t T;
					typedef kerbal::compatibility::uint64_t uint64_t;
					typedef kerbal::compatibility::uint8_t uint8_t;
					typedef typename kerbal::numeric::bitarray_result<T>::type bitarray_result_t;

#define XX 2
#if XX == 0
					const uint8_t mask[16] = {
							1u << 7, 1u << 6, 1u << 5, 1u << 4,
							1u << 3, 1u << 2, 1u << 1, 1u << 0,
							1u << 7, 1u << 6, 1u << 5, 1u << 4,
							1u << 3, 1u << 2, 1u << 1, 1u << 0
					};
					uint8x16_t const q_andmask = vld1q_u8(mask);
#elif XX == 1
					const uint8_t mask[8] = {
							1u << 7, 1u << 6, 1u << 5, 1u << 4,
							1u << 3, 1u << 2, 1u << 1, 1u << 0
					};
					uint8x8_t const d_andmask = vld1_u8(mask);
					uint8x16_t const q_andmask = vcombine_u8(d_andmask, d_andmask);
#else
					uint8x8_t const d_andmask = vcreate_u8(0x0102040810204080ull);
					uint8x16_t const q_andmask = vcombine_u8(d_andmask, d_andmask);
#endif

					uint8_t high = x >> 8, low = x & 0xff;
					uint8x8_t d_high = vdup_n_u8(high);
					uint8x8_t d_low = vdup_n_u8(low);
					uint8x16_t q_x = vcombine_u8(d_high, d_low);
					q_x = vandq_u8(q_x, q_andmask);
					q_x = vminq_u8(q_x, vdupq_n_u8(1));

					kerbal::type_traits::aligned_storage<
							kerbal::smath::max_sa_sb<std::size_t, sizeof(bitarray_result_t), sizeof(uint64_t)>::value,
							kerbal::smath::max_sa_sb<std::size_t, KERBAL_ALIGNOF(bitarray_result_t), KERBAL_ALIGNOF(uint64_t)>::value
					>::type as;
					vst1q_u8(reinterpret_cast<uint8_t *>(&as), q_x);
					return reinterpret_cast<const bitarray_result_t &>(as);
				}


			} // namespace neon

		} // namespace detail

	} // namespace numeric

} // namespace kerbal


#endif // KERBAL_NUMERIC_BIT_BITARRAY_BITARRAY_NEON_HPP
