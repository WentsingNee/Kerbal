/**
 * @file       sha1_transform_overload.sha1_instruct.hpp
 * @brief
 * @date       2024-10-07
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_HASH_SHA1_DETAIL_SHA1_TRANSFORM_OVERLOAD_SHA1_TRANSFORM_OVERLOAD_SHA1_INSTRUCT_HPP
#define KERBAL_HASH_SHA1_DETAIL_SHA1_TRANSFORM_OVERLOAD_SHA1_TRANSFORM_OVERLOAD_SHA1_INSTRUCT_HPP

#include <kerbal/hash/sha1/sha1.fwd.hpp>

#if KERBAL_ENABLE_SHA1_INSTRUCT

#	include <kerbal/hash/sha1/detail/sha1_context_base.hpp>

#	include <kerbal/compatibility/noexcept.hpp>

#	include <immintrin.h>


namespace kerbal
{

	namespace hash
	{

		namespace detail
		{

			template <>
			class SHA1_transform_overload<SHA1_policy::sha1_instruct> :
				protected SHA1_context_base
			{
				protected:

#		if __cplusplus >= 201103L
					constexpr
					SHA1_transform_overload() = default;
#		endif

					static
					__m128i mm_reverse32(__m128i a) KERBAL_NOEXCEPT;

					static
					void update_w(__m128i xmm_w[4]) KERBAL_NOEXCEPT;

					void transform(const uint8_t buffer[64]) KERBAL_NOEXCEPT;

			};

			inline
			__m128i
			SHA1_transform_overload<SHA1_policy::sha1_instruct>::
			mm_reverse32(__m128i a) KERBAL_NOEXCEPT
			{
				return _mm_shuffle_epi32(a, 27); // bswap; 27 == 0b 00 01 10 11
			}

			inline
			void
			SHA1_transform_overload<SHA1_policy::sha1_instruct>::
			update_w(__m128i xmm_w[4]) KERBAL_NOEXCEPT
			{
				//w[0] = kerbal::numeric::rotl(w[0] ^ w[2] ^ w[8] ^ w[13], 1);
				//w[1] = kerbal::numeric::rotl(w[1] ^ w[3] ^ w[9] ^ w[14], 1);
				//w[2] = kerbal::numeric::rotl(w[2] ^ w[4] ^ w[10] ^ w[15], 1);
				//w[3] = kerbal::numeric::rotl(w[3] ^ w[5] ^ w[11] ^ w[0], 1);
				{
					__m128i xmm_sha1msg1 = _mm_sha1msg1_epu32(xmm_w[0], xmm_w[1]);
					xmm_sha1msg1 = _mm_xor_si128(xmm_sha1msg1, xmm_w[2]);
					xmm_w[0] = _mm_sha1msg2_epu32(xmm_sha1msg1, xmm_w[3]);
				}

				//w[4] = kerbal::numeric::rotl(w[4] ^ w[6] ^ w[12] ^ w[1], 1);
				//w[5] = kerbal::numeric::rotl(w[5] ^ w[7] ^ w[13] ^ w[2], 1);
				//w[6] = kerbal::numeric::rotl(w[6] ^ w[8] ^ w[14] ^ w[3], 1);
				//w[7] = kerbal::numeric::rotl(w[7] ^ w[9] ^ w[15] ^ w[4], 1);
				{
					__m128i xmm_sha1msg1 = _mm_sha1msg1_epu32(xmm_w[1], xmm_w[2]);
					xmm_sha1msg1 = _mm_xor_si128(xmm_sha1msg1, xmm_w[3]);
					xmm_w[1] = _mm_sha1msg2_epu32(xmm_sha1msg1, xmm_w[0]);
				}

				//w[8] = kerbal::numeric::rotl(w[8] ^ w[10] ^ w[0] ^ w[5], 1);
				//w[9] = kerbal::numeric::rotl(w[9] ^ w[11] ^ w[1] ^ w[6], 1);
				//w[10] = kerbal::numeric::rotl(w[10] ^ w[12] ^ w[2] ^ w[7], 1);
				//w[11] = kerbal::numeric::rotl(w[11] ^ w[13] ^ w[3] ^ w[8], 1);
				{
					__m128i xmm_sha1msg1 = _mm_sha1msg1_epu32(xmm_w[2], xmm_w[3]);
					xmm_sha1msg1 = _mm_xor_si128(xmm_sha1msg1, xmm_w[0]);
					xmm_w[2] = _mm_sha1msg2_epu32(xmm_sha1msg1, xmm_w[1]);
				}

				//w[12] = kerbal::numeric::rotl(w[12] ^ w[14] ^ w[4] ^ w[9], 1);
				//w[13] = kerbal::numeric::rotl(w[13] ^ w[15] ^ w[5] ^ w[10], 1);
				//w[14] = kerbal::numeric::rotl(w[14] ^ w[0] ^ w[6] ^ w[11], 1);
				//w[15] = kerbal::numeric::rotl(w[15] ^ w[1] ^ w[7] ^ w[12], 1);
				{
					__m128i xmm_sha1msg1 = _mm_sha1msg1_epu32(xmm_w[3], xmm_w[0]);
					xmm_sha1msg1 = _mm_xor_si128(xmm_sha1msg1, xmm_w[1]);
					xmm_w[3] = _mm_sha1msg2_epu32(xmm_sha1msg1, xmm_w[2]);
				}

			}

			inline
			void
			SHA1_transform_overload<SHA1_policy::sha1_instruct>::
			transform(const uint8_t buffer[64]) KERBAL_NOEXCEPT
			{
				__m128i const xmm_emask = _mm_set_epi8(
					0, 1, 2, 3,
					4, 5, 6, 7,
					8, 9, 10, 11,
					12, 13, 14, 15
				);

				__m128i xmm_w[4] = {
					_mm_shuffle_epi8(_mm_loadu_si128(reinterpret_cast<const __m128i*>(buffer + 16 * 0)), xmm_emask),
					_mm_shuffle_epi8(_mm_loadu_si128(reinterpret_cast<const __m128i*>(buffer + 16 * 1)), xmm_emask),
					_mm_shuffle_epi8(_mm_loadu_si128(reinterpret_cast<const __m128i*>(buffer + 16 * 2)), xmm_emask),
					_mm_shuffle_epi8(_mm_loadu_si128(reinterpret_cast<const __m128i*>(buffer + 16 * 3)), xmm_emask),
				};

				__m128i xmm_abcd_ori = mm_reverse32(_mm_loadu_si128(reinterpret_cast<const __m128i*>(this->state + 0)));
				__m128i xmm_e = _mm_set_epi32(this->state[4], 0, 0, 0);
				__m128i xmm_abcd = xmm_abcd_ori;
				__m128i xmm_abcd2;
				__m128i xmm_t;

				{
					// round 0-3
					xmm_t = _mm_add_epi32(xmm_e, xmm_w[0]);
					xmm_abcd2 = _mm_sha1rnds4_epu32(xmm_abcd, xmm_t, 0);

					// round 4-7
					xmm_t = _mm_sha1nexte_epu32(xmm_abcd, xmm_w[1]);
					xmm_abcd = _mm_sha1rnds4_epu32(xmm_abcd2, xmm_t, 0);

					// round 8-11
					xmm_t = _mm_sha1nexte_epu32(xmm_abcd2, xmm_w[2]);
					xmm_abcd2 = _mm_sha1rnds4_epu32(xmm_abcd, xmm_t, 0);

					// round 12-15
					xmm_t = _mm_sha1nexte_epu32(xmm_abcd, xmm_w[3]);
					xmm_abcd = _mm_sha1rnds4_epu32(xmm_abcd2, xmm_t, 0);

					update_w(xmm_w);
				}

				{
					// round 16-19
					xmm_t = _mm_sha1nexte_epu32(xmm_abcd2, xmm_w[0]);
					xmm_abcd2 = _mm_sha1rnds4_epu32(xmm_abcd, xmm_t, 0);

					// round 20-23
					xmm_t = _mm_sha1nexte_epu32(xmm_abcd, xmm_w[1]);
					xmm_abcd = _mm_sha1rnds4_epu32(xmm_abcd2, xmm_t, 1);

					// round 24-27
					xmm_t = _mm_sha1nexte_epu32(xmm_abcd2, xmm_w[2]);
					xmm_abcd2 = _mm_sha1rnds4_epu32(xmm_abcd, xmm_t, 1);

					// round 28-31
					xmm_t = _mm_sha1nexte_epu32(xmm_abcd, xmm_w[3]);
					xmm_abcd = _mm_sha1rnds4_epu32(xmm_abcd2, xmm_t, 1);

					update_w(xmm_w);
				}

				{
					// round 32-35
					xmm_t = _mm_sha1nexte_epu32(xmm_abcd2, xmm_w[0]);
					xmm_abcd2 = _mm_sha1rnds4_epu32(xmm_abcd, xmm_t, 1);

					// round 36-39
					xmm_t = _mm_sha1nexte_epu32(xmm_abcd, xmm_w[1]);
					xmm_abcd = _mm_sha1rnds4_epu32(xmm_abcd2, xmm_t, 1);

					// round 40-43
					xmm_t = _mm_sha1nexte_epu32(xmm_abcd2, xmm_w[2]);
					xmm_abcd2 = _mm_sha1rnds4_epu32(xmm_abcd, xmm_t, 2);

					// round 44-47
					xmm_t = _mm_sha1nexte_epu32(xmm_abcd, xmm_w[3]);
					xmm_abcd = _mm_sha1rnds4_epu32(xmm_abcd2, xmm_t, 2);

					update_w(xmm_w);
				}

				{
					// round 48-51
					xmm_t = _mm_sha1nexte_epu32(xmm_abcd2, xmm_w[0]);
					xmm_abcd2 = _mm_sha1rnds4_epu32(xmm_abcd, xmm_t, 2);

					// round 52-55
					xmm_t = _mm_sha1nexte_epu32(xmm_abcd, xmm_w[1]);
					xmm_abcd = _mm_sha1rnds4_epu32(xmm_abcd2, xmm_t, 2);

					// round 56-59
					xmm_t = _mm_sha1nexte_epu32(xmm_abcd2, xmm_w[2]);
					xmm_abcd2 = _mm_sha1rnds4_epu32(xmm_abcd, xmm_t, 2);

					// round 60-63
					xmm_t = _mm_sha1nexte_epu32(xmm_abcd, xmm_w[3]);
					xmm_abcd = _mm_sha1rnds4_epu32(xmm_abcd2, xmm_t, 3);

					update_w(xmm_w);
				}

				{
					// round 64-67
					xmm_t = _mm_sha1nexte_epu32(xmm_abcd2, xmm_w[0]);
					xmm_abcd2 = _mm_sha1rnds4_epu32(xmm_abcd, xmm_t, 3);

					// round 68-71
					xmm_t = _mm_sha1nexte_epu32(xmm_abcd, xmm_w[1]);
					xmm_abcd = _mm_sha1rnds4_epu32(xmm_abcd2, xmm_t, 3);

					// round 72-75
					xmm_t = _mm_sha1nexte_epu32(xmm_abcd2, xmm_w[2]);
					xmm_abcd2 = _mm_sha1rnds4_epu32(xmm_abcd, xmm_t, 3);

					// round 76-79
					xmm_t = _mm_sha1nexte_epu32(xmm_abcd, xmm_w[3]);
					xmm_abcd = _mm_sha1rnds4_epu32(xmm_abcd2, xmm_t, 3);
				}

				/* Add the working vars back into context.state[] */
				xmm_abcd_ori = _mm_add_epi32(xmm_abcd_ori, xmm_abcd);
				xmm_abcd_ori = mm_reverse32(xmm_abcd_ori);
				_mm_storeu_si128(reinterpret_cast<__m128i*>(this->state), xmm_abcd_ori);

				__m128i const xmm_ZERO = _mm_set1_epi32(0);
				xmm_e = _mm_sha1nexte_epu32(xmm_abcd2, xmm_ZERO);
				this->state[4] += _mm_extract_epi32(xmm_e, 3);
			}

		} // namespace detail

	} // namespace hash

} // namespace kerbal

#endif

#endif // KERBAL_HASH_SHA1_DETAIL_SHA1_TRANSFORM_OVERLOAD_SHA1_TRANSFORM_OVERLOAD_SHA1_INSTRUCT_HPP
