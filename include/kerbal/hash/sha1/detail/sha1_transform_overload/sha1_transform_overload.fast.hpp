/**
 * @file       sha1_transform_overload.fast.hpp
 * @brief
 * @date       2024-10-06
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_HASH_SHA1_DETAIL_SHA1_TRANSFORM_OVERLOAD_SHA1_TRANSFORM_OVERLOAD_FAST_HPP
#define KERBAL_HASH_SHA1_DETAIL_SHA1_TRANSFORM_OVERLOAD_SHA1_TRANSFORM_OVERLOAD_FAST_HPP

#include <kerbal/hash/detail/char4tolong1.hpp>
#include <kerbal/hash/sha1/sha1.fwd.hpp>
#include <kerbal/hash/sha1/detail/sha1_context_base.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/numeric/bit.hpp>

#include <arm_neon.h>
#include <iostream>


namespace kerbal
{

	namespace hash
	{

		namespace detail
		{

			template <>
			class SHA1_transform_overload<kerbal::hash::SHA1_policy::fast> :
				protected kerbal::hash::detail::SHA1_context_base
			{
				protected:
					typedef kerbal::hash::detail::SHA1_context_base context_base;

#		if __cplusplus >= 201103L
					constexpr
					SHA1_transform_overload() = default;
#		endif

					// static
					// void update_w(uint32_t w[16]) KERBAL_NOEXCEPT;

					// KERBAL_CONSTEXPR14
					void transform(const uint8_t buffer[64]) KERBAL_NOEXCEPT;

			};

			inline
			void
			// SHA1_transform_overload<SHA1_policy::fast>::
			update_w(uint32x4_t & w0_3, uint32x4_t & w4_7, uint32x4_t & w8_11, uint32x4_t & w12_15) KERBAL_NOEXCEPT
			{
#if 0
				uint32x4_t w0_3 = vld1q_u32(w + 0);
				uint32x4_t w4_7 = vld1q_u32(w + 4);
				uint32x4_t w8_11 = vld1q_u32(w + 8);
				uint32x4_t w12_15 = vld1q_u32(w + 12);

				w0_3 = vsha1su1q_u32(vsha1su0q_u32(w0_3, w4_7, w8_11), w12_15);
				w4_7 = vsha1su1q_u32(vsha1su0q_u32(w4_7, w8_11, w12_15), w0_3);
				w8_11 = vsha1su1q_u32(vsha1su0q_u32(w8_11, w12_15, w0_3), w4_7);
				w12_15 = vsha1su1q_u32(vsha1su0q_u32(w12_15, w0_3, w4_7), w8_11);

				vst1q_u32(w + 0, w0_3);
				vst1q_u32(w + 4, w4_7);
				vst1q_u32(w + 8, w8_11);
				vst1q_u32(w + 12, w12_15);

#else

				// uint32x4x4_t vw = vld1q_u32_x4(w);
				//
				// uint32x4_t & w0_3 = vw.val[0];
				// uint32x4_t & w4_7 = vw.val[1];
				// uint32x4_t & w8_11 = vw.val[2];
				// uint32x4_t & w12_15 = vw.val[3];

				w0_3 = vsha1su1q_u32(vsha1su0q_u32(w0_3, w4_7, w8_11), w12_15);
				w4_7 = vsha1su1q_u32(vsha1su0q_u32(w4_7, w8_11, w12_15), w0_3);
				w8_11 = vsha1su1q_u32(vsha1su0q_u32(w8_11, w12_15, w0_3), w4_7);
				w12_15 = vsha1su1q_u32(vsha1su0q_u32(w12_15, w0_3, w4_7), w8_11);

				// vst1q_u32_x4(w, vw);

#endif

			}

			// KERBAL_CONSTEXPR14
			// inline
			void
			SHA1_transform_overload<SHA1_policy::fast>::
			transform(const uint8_t buffer[64]) KERBAL_NOEXCEPT
			{
				uint32_t w[16] = {};
				for (int i = 0; i < 16; ++i) {
					w[i] = char4tolong1<BYTE_ORDER>(buffer + 4 * i);
				}

				uint32x4x4_t vw = vld1q_u32_x4(w);

				uint32x4_t & w0_3 = vw.val[0];
				uint32x4_t & w4_7 = vw.val[1];
				uint32x4_t & w8_11 = vw.val[2];
				uint32x4_t & w12_15 = vw.val[3];

				/* Copy context->state[] to working vars */
				uint32_t cpy_state[4] = {
					this->state[0],
					this->state[1],
					this->state[2],
					this->state[3],
				};
				uint32_t e = this->state[4];

				uint32x4_t hash_abcd, wk;

				hash_abcd = vld1q_u32(cpy_state);

				// R1
				uint32x4_t const R1C = vdupq_n_u32(0x5A827999);

				wk = vaddq_u32(w0_3, R1C);
				hash_abcd = vsha1cq_u32(hash_abcd, e, wk);
				e = vsha1h_u32(cpy_state[0]);
				vst1q_u32(cpy_state, hash_abcd);

				wk = vaddq_u32(w4_7, R1C);
				hash_abcd = vsha1cq_u32(hash_abcd, e, wk);
				e = vsha1h_u32(cpy_state[0]);
				vst1q_u32(cpy_state, hash_abcd);

				wk = vaddq_u32(w8_11, R1C);
				hash_abcd = vsha1cq_u32(hash_abcd, e, wk);
				e = vsha1h_u32(cpy_state[0]);
				vst1q_u32(cpy_state, hash_abcd);

				wk = vaddq_u32(w12_15, R1C);
				hash_abcd = vsha1cq_u32(hash_abcd, e, wk);
				e = vsha1h_u32(cpy_state[0]);
				vst1q_u32(cpy_state, hash_abcd);

				update_w(w0_3, w4_7, w8_11, w12_15);

				wk = vaddq_u32(w0_3, R1C);
				hash_abcd = vsha1cq_u32(hash_abcd, e, wk);
				e = vsha1h_u32(cpy_state[0]);
				vst1q_u32(cpy_state, hash_abcd);

				// R2
				uint32x4_t const R2C = vdupq_n_u32(0x6ED9EBA1);

				wk = vaddq_u32(w4_7, R2C);
				hash_abcd = vsha1pq_u32(hash_abcd, e, wk);
				e = vsha1h_u32(cpy_state[0]);
				vst1q_u32(cpy_state, hash_abcd);

				wk = vaddq_u32(w8_11, R2C);
				hash_abcd = vsha1pq_u32(hash_abcd, e, wk);
				e = vsha1h_u32(cpy_state[0]);
				vst1q_u32(cpy_state, hash_abcd);

				wk = vaddq_u32(w12_15, R2C);
				hash_abcd = vsha1pq_u32(hash_abcd, e, wk);
				e = vsha1h_u32(cpy_state[0]);
				vst1q_u32(cpy_state, hash_abcd);

				update_w(w0_3, w4_7, w8_11, w12_15);

				wk = vaddq_u32(w0_3, R2C);
				hash_abcd = vsha1pq_u32(hash_abcd, e, wk);
				e = vsha1h_u32(cpy_state[0]);
				vst1q_u32(cpy_state, hash_abcd);

				wk = vaddq_u32(w4_7, R2C);
				hash_abcd = vsha1pq_u32(hash_abcd, e, wk);
				e = vsha1h_u32(cpy_state[0]);
				vst1q_u32(cpy_state, hash_abcd);

				// R3
				uint32x4_t const R3C = vdupq_n_u32(0x8F1BBCDC);

				wk = vaddq_u32(w8_11, R3C);
				hash_abcd = vsha1mq_u32(hash_abcd, e, wk);
				e = vsha1h_u32(cpy_state[0]);
				vst1q_u32(cpy_state, hash_abcd);

				wk = vaddq_u32(w12_15, R3C);
				hash_abcd = vsha1mq_u32(hash_abcd, e, wk);
				e = vsha1h_u32(cpy_state[0]);
				vst1q_u32(cpy_state, hash_abcd);

				update_w(w0_3, w4_7, w8_11, w12_15);

				wk = vaddq_u32(w0_3, R3C);
				hash_abcd = vsha1mq_u32(hash_abcd, e, wk);
				e = vsha1h_u32(cpy_state[0]);
				vst1q_u32(cpy_state, hash_abcd);

				wk = vaddq_u32(w4_7, R3C);
				hash_abcd = vsha1mq_u32(hash_abcd, e, wk);
				e = vsha1h_u32(cpy_state[0]);
				vst1q_u32(cpy_state, hash_abcd);

				wk = vaddq_u32(w8_11, R3C);
				hash_abcd = vsha1mq_u32(hash_abcd, e, wk);
				e = vsha1h_u32(cpy_state[0]);
				vst1q_u32(cpy_state, hash_abcd);

				// R4
				uint32x4_t const R4C = vdupq_n_u32(0xCA62C1D6);

				wk = vaddq_u32(w12_15, R4C);
				hash_abcd = vsha1pq_u32(hash_abcd, e, wk);
				e = vsha1h_u32(cpy_state[0]);
				vst1q_u32(cpy_state, hash_abcd);

				update_w(w0_3, w4_7, w8_11, w12_15);

				wk = vaddq_u32(w0_3, R4C);
				hash_abcd = vsha1pq_u32(hash_abcd, e, wk);
				e = vsha1h_u32(cpy_state[0]);
				vst1q_u32(cpy_state, hash_abcd);

				wk = vaddq_u32(w4_7, R4C);
				hash_abcd = vsha1pq_u32(hash_abcd, e, wk);
				e = vsha1h_u32(cpy_state[0]);
				vst1q_u32(cpy_state, hash_abcd);

				wk = vaddq_u32(w8_11, R4C);
				hash_abcd = vsha1pq_u32(hash_abcd, e, wk);
				e = vsha1h_u32(cpy_state[0]);
				vst1q_u32(cpy_state, hash_abcd);

				wk = vaddq_u32(w12_15, R4C);
				hash_abcd = vsha1pq_u32(hash_abcd, e, wk);
				e = vsha1h_u32(cpy_state[0]);
				vst1q_u32(cpy_state, hash_abcd);

				/* Add the working vars back into context.state[] */
				this->state[0] += cpy_state[0];
				this->state[1] += cpy_state[1];
				this->state[2] += cpy_state[2];
				this->state[3] += cpy_state[3];
				this->state[4] += e;
			}

		} // namespace detail

	} // namespace hash

} // namespace kerbal

#endif // KERBAL_HASH_SHA1_DETAIL_SHA1_TRANSFORM_OVERLOAD_SHA1_TRANSFORM_OVERLOAD_FAST_HPP
