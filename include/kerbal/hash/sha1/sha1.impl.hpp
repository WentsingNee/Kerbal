/**
 * @file       sha1.impl.hpp
 * @brief
 * @date       2019-9-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_HASH_SHA1_SHA1_IMPL_HPP
#define KERBAL_HASH_SHA1_SHA1_IMPL_HPP

#include <kerbal/algorithm/modifier/copy.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/numeric/bit.hpp>
#include <kerbal/type_traits/is_same.hpp>

#include <cstddef>

#include <kerbal/hash/sha1.hpp>

#if KERBAL_ENABLE_SHA1_INSTRUCT
#	include <immintrin.h>
#endif


namespace kerbal
{

	namespace hash
	{

		KERBAL_CONSTEXPR14
		inline
		void SHA1_context_base::R1(const uint32_t * w, uint32_t a, uint32_t & b, uint32_t c, uint32_t d, uint32_t & e, std::size_t i) KERBAL_NOEXCEPT
		{
			e += w[i];
			e += kerbal::numeric::rotl(a, 5);
			e += ((b & (c ^ d)) ^ d) + 0x5A827999;
			b = kerbal::numeric::rotl(b, 30);
		}

		KERBAL_CONSTEXPR14
		inline
		void SHA1_context_base::R2(const uint32_t * w, uint32_t a, uint32_t & b, uint32_t c, uint32_t d, uint32_t & e, std::size_t i) KERBAL_NOEXCEPT
		{
			e += w[i];
			e += kerbal::numeric::rotl(a, 5);
			e += (b ^ c ^ d) + 0x6ED9EBA1;
			b = kerbal::numeric::rotl(b, 30);
		}

		KERBAL_CONSTEXPR14
		inline
		void SHA1_context_base::R3(const uint32_t * w, uint32_t a, uint32_t & b, uint32_t c, uint32_t d, uint32_t & e, std::size_t i) KERBAL_NOEXCEPT
		{
			e += w[i];
			e += kerbal::numeric::rotl(a, 5);
			e += (((b | c) & d) | (b & c)) + 0x8F1BBCDC;
			b = kerbal::numeric::rotl(b, 30);
		}

		KERBAL_CONSTEXPR14
		inline
		void SHA1_context_base::R4(const uint32_t * w, uint32_t a, uint32_t & b, uint32_t c, uint32_t d, uint32_t & e, std::size_t i) KERBAL_NOEXCEPT
		{
			e += w[i];
			e += kerbal::numeric::rotl(a, 5);
			e += (b ^ c ^ d) + 0xCA62C1D6;
			b = kerbal::numeric::rotl(b, 30);
		}

#	if __cplusplus >= 201103L

		constexpr
		SHA1_context_base::SHA1_context_base() noexcept :
				state { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0 },
				count { 0, 0 }, buffer { }
		{
		}

#	else

		SHA1_context_base::SHA1_context_base() KERBAL_NOEXCEPT
		{
			this->state[0] = 0x67452301;
			this->state[1] = 0xEFCDAB89;
			this->state[2] = 0x98BADCFE;
			this->state[3] = 0x10325476;
			this->state[4] = 0xC3D2E1F0;

			this->count[0] = this->count[1] = 0;

			// buffer doesn't need init
		}

#	endif

		template <int byte_order>
		KERBAL_CONSTEXPR
		uint32_t char4tolong1(const uint8_t c[4]) KERBAL_NOEXCEPT;

		template <>
		KERBAL_CONSTEXPR
		inline
		uint32_t char4tolong1<LITTLE_ENDIAN>(const uint8_t c[4]) KERBAL_NOEXCEPT
		{
			return (c[0] << 24u) | (c[1] << 16u) | (c[2] << 8u) | c[3];
		}

		template <>
		KERBAL_CONSTEXPR
		inline
		uint32_t char4tolong1<BIG_ENDIAN>(const uint8_t c[4]) KERBAL_NOEXCEPT
		{
			return (c[3] << 24u) | (c[2] << 16u) | (c[1] << 8u) | c[0];
		}

		KERBAL_CONSTEXPR14
		inline
		void k_rotate5(uint32_t & a, uint32_t & b, uint32_t & c, uint32_t & d, uint32_t & e)
		{
			uint32_t t = a;
			a = b;
			b = c;
			c = d;
			d = e;
			e = t;
		}

		KERBAL_CONSTEXPR14
		inline
		void update_w_size(uint32_t w[20]) KERBAL_NOEXCEPT
		{
			w[0] = kerbal::numeric::rotl(w[17] ^ w[12] ^ w[6] ^ w[4] , 1);
			w[1] = kerbal::numeric::rotl(w[18] ^ w[13] ^ w[7] ^ w[5] , 1);
			w[2] = kerbal::numeric::rotl(w[19] ^ w[14] ^ w[8] ^ w[6] , 1);
			w[3] = kerbal::numeric::rotl(w[0] ^ w[15] ^ w[9] ^ w[7] , 1);
			w[4] = kerbal::numeric::rotl(w[1] ^ w[16] ^ w[10] ^ w[8] , 1);
			w[5] = kerbal::numeric::rotl(w[2] ^ w[17] ^ w[11] ^ w[9] , 1);
			w[6] = kerbal::numeric::rotl(w[3] ^ w[18] ^ w[12] ^ w[10] , 1);
			w[7] = kerbal::numeric::rotl(w[4] ^ w[19] ^ w[13] ^ w[11] , 1);
			w[8] = kerbal::numeric::rotl(w[5] ^ w[0] ^ w[14] ^ w[12] , 1);
			w[9] = kerbal::numeric::rotl(w[6] ^ w[1] ^ w[15] ^ w[13] , 1);
			w[10] = kerbal::numeric::rotl(w[7] ^ w[2] ^ w[16] ^ w[14] , 1);
			w[11] = kerbal::numeric::rotl(w[8] ^ w[3] ^ w[17] ^ w[15] , 1);
			w[12] = kerbal::numeric::rotl(w[9] ^ w[4] ^ w[18] ^ w[16] , 1);
			w[13] = kerbal::numeric::rotl(w[10] ^ w[5] ^ w[19] ^ w[17] , 1);
			w[14] = kerbal::numeric::rotl(w[11] ^ w[6] ^ w[0] ^ w[18] , 1);
			w[15] = kerbal::numeric::rotl(w[12] ^ w[7] ^ w[1] ^ w[19] , 1);
			w[16] = kerbal::numeric::rotl(w[13] ^ w[8] ^ w[2] ^ w[0] , 1);
			w[17] = kerbal::numeric::rotl(w[14] ^ w[9] ^ w[3] ^ w[1] , 1);
			w[18] = kerbal::numeric::rotl(w[15] ^ w[10] ^ w[4] ^ w[2] , 1);
			w[19] = kerbal::numeric::rotl(w[16] ^ w[11] ^ w[5] ^ w[3] , 1);
		}

		KERBAL_CONSTEXPR14
		inline
		void SHA1_transform_overload<SHA1_policy::size>::transform(const uint8_t buffer[64]) KERBAL_NOEXCEPT
		{
			uint32_t w[20] = {};
			for (int i = 0; i < 16; ++i) {
				w[i] = char4tolong1<BYTE_ORDER>(buffer + 4 * i);
			}
			for (int i = 16; i < 20; ++i) {
				w[i] = kerbal::numeric::rotl(w[i - 16] ^ w[i - 14] ^ w[i - 8] ^ w[i - 3], 1);
			}

			/* Copy context->state[] to working vars */
			uint32_t a = this->state[0];
			uint32_t b = this->state[1];
			uint32_t c = this->state[2];
			uint32_t d = this->state[3];
			uint32_t e = this->state[4];

			uint32_t * ww = w;
			for (int i = 0; i < 4; ++i) {
				R1(ww, a, b, c, d, e, 0);
				R1(ww, e, a, b, c, d, 1);
				R1(ww, d, e, a, b, c, 2);
				R1(ww, c, d, e, a, b, 3);
				R1(ww, b, c, d, e, a, 4);
				ww += 5;
			}

			update_w_size(w);

			ww = w;
			for (int i = 0; i < 4; ++i) {
				R2(ww, a, b, c, d, e, 0);
				R2(ww, e, a, b, c, d, 1);
				R2(ww, d, e, a, b, c, 2);
				R2(ww, c, d, e, a, b, 3);
				R2(ww, b, c, d, e, a, 4);
				ww += 5;
			}

			update_w_size(w);

			ww = w;
			for (int i = 0; i < 4; ++i) {
				R3(ww, a, b, c, d, e, 0);
				R3(ww, e, a, b, c, d, 1);
				R3(ww, d, e, a, b, c, 2);
				R3(ww, c, d, e, a, b, 3);
				R3(ww, b, c, d, e, a, 4);
				ww += 5;
			}

			update_w_size(w);

			ww = w;
			for (int i = 0; i < 4; ++i) {
				R4(ww, a, b, c, d, e, 0);
				R4(ww, e, a, b, c, d, 1);
				R4(ww, d, e, a, b, c, 2);
				R4(ww, c, d, e, a, b, 3);
				R4(ww, b, c, d, e, a, 4);
				ww += 5;
			}

			/* Add the working vars back into context.state[] */
			this->state[0] += a;
			this->state[1] += b;
			this->state[2] += c;
			this->state[3] += d;
			this->state[4] += e;
		}

		KERBAL_CONSTEXPR14
		inline
		void update_w_fast(uint32_t w[16]) KERBAL_NOEXCEPT
		{
			w[0] = kerbal::numeric::rotl(w[0] ^ w[2] ^ w[8] ^ w[13], 1);
			w[1] = kerbal::numeric::rotl(w[1] ^ w[3] ^ w[9] ^ w[14], 1);
			w[2] = kerbal::numeric::rotl(w[2] ^ w[4] ^ w[10] ^ w[15], 1);
			w[3] = kerbal::numeric::rotl(w[3] ^ w[5] ^ w[11] ^ w[0], 1);
			w[4] = kerbal::numeric::rotl(w[4] ^ w[6] ^ w[12] ^ w[1], 1);
			w[5] = kerbal::numeric::rotl(w[5] ^ w[7] ^ w[13] ^ w[2], 1);
			w[6] = kerbal::numeric::rotl(w[6] ^ w[8] ^ w[14] ^ w[3], 1);
			w[7] = kerbal::numeric::rotl(w[7] ^ w[9] ^ w[15] ^ w[4], 1);
			w[8] = kerbal::numeric::rotl(w[8] ^ w[10] ^ w[0] ^ w[5], 1);
			w[9] = kerbal::numeric::rotl(w[9] ^ w[11] ^ w[1] ^ w[6], 1);
			w[10] = kerbal::numeric::rotl(w[10] ^ w[12] ^ w[2] ^ w[7], 1);
			w[11] = kerbal::numeric::rotl(w[11] ^ w[13] ^ w[3] ^ w[8], 1);
			w[12] = kerbal::numeric::rotl(w[12] ^ w[14] ^ w[4] ^ w[9], 1);
			w[13] = kerbal::numeric::rotl(w[13] ^ w[15] ^ w[5] ^ w[10], 1);
			w[14] = kerbal::numeric::rotl(w[14] ^ w[0] ^ w[6] ^ w[11], 1);
			w[15] = kerbal::numeric::rotl(w[15] ^ w[1] ^ w[7] ^ w[12], 1);
		}

		KERBAL_CONSTEXPR14
		inline
		void SHA1_transform_overload<SHA1_policy::fast>::transform(const uint8_t buffer[64]) KERBAL_NOEXCEPT
		{
			uint32_t w[16] = {};
			for (int i = 0; i < 16; ++i) {
				w[i] = char4tolong1<BYTE_ORDER>(buffer + 4 * i);
			}

			/* Copy context->state[] to working vars */
			uint32_t a = this->state[0];
			uint32_t b = this->state[1];
			uint32_t c = this->state[2];
			uint32_t d = this->state[3];
			uint32_t e = this->state[4];

			R1(w, a, b, c, d, e,  0); R1(w, e, a, b, c, d,  1); R1(w, d, e, a, b, c,  2); R1(w, c, d, e, a, b,  3); k_rotate5(b, c, d, e, a);
			R1(w, a, b, c, d, e,  4); R1(w, e, a, b, c, d,  5); R1(w, d, e, a, b, c,  6); R1(w, c, d, e, a, b,  7); k_rotate5(b, c, d, e, a);
			R1(w, a, b, c, d, e,  8); R1(w, e, a, b, c, d,  9); R1(w, d, e, a, b, c, 10); R1(w, c, d, e, a, b, 11); k_rotate5(b, c, d, e, a);
			R1(w, a, b, c, d, e, 12); R1(w, e, a, b, c, d, 13); R1(w, d, e, a, b, c, 14); R1(w, c, d, e, a, b, 15); k_rotate5(b, c, d, e, a);

			update_w_fast(w);

			R1(w, a, b, c, d, e,  0); R1(w, e, a, b, c, d,  1); R1(w, d, e, a, b, c,  2); R1(w, c, d, e, a, b,  3); k_rotate5(b, c, d, e, a);
			R2(w, a, b, c, d, e,  4); R2(w, e, a, b, c, d,  5); R2(w, d, e, a, b, c,  6); R2(w, c, d, e, a, b,  7); k_rotate5(b, c, d, e, a);
			R2(w, a, b, c, d, e,  8); R2(w, e, a, b, c, d,  9); R2(w, d, e, a, b, c, 10); R2(w, c, d, e, a, b, 11); k_rotate5(b, c, d, e, a);
			R2(w, a, b, c, d, e, 12); R2(w, e, a, b, c, d, 13); R2(w, d, e, a, b, c, 14); R2(w, c, d, e, a, b, 15); k_rotate5(b, c, d, e, a);

			update_w_fast(w);

			R2(w, a, b, c, d, e,  0); R2(w, e, a, b, c, d,  1); R2(w, d, e, a, b, c,  2); R2(w, c, d, e, a, b,  3); k_rotate5(b, c, d, e, a);
			R2(w, a, b, c, d, e,  4); R2(w, e, a, b, c, d,  5); R2(w, d, e, a, b, c,  6); R2(w, c, d, e, a, b,  7); k_rotate5(b, c, d, e, a);
			R3(w, a, b, c, d, e,  8); R3(w, e, a, b, c, d,  9); R3(w, d, e, a, b, c, 10); R3(w, c, d, e, a, b, 11); k_rotate5(b, c, d, e, a);
			R3(w, a, b, c, d, e, 12); R3(w, e, a, b, c, d, 13); R3(w, d, e, a, b, c, 14); R3(w, c, d, e, a, b, 15); k_rotate5(b, c, d, e, a);

			update_w_fast(w);

			R3(w, a, b, c, d, e,  0); R3(w, e, a, b, c, d,  1); R3(w, d, e, a, b, c,  2); R3(w, c, d, e, a, b,  3); k_rotate5(b, c, d, e, a);
			R3(w, a, b, c, d, e,  4); R3(w, e, a, b, c, d,  5); R3(w, d, e, a, b, c,  6); R3(w, c, d, e, a, b,  7); k_rotate5(b, c, d, e, a);
			R3(w, a, b, c, d, e,  8); R3(w, e, a, b, c, d,  9); R3(w, d, e, a, b, c, 10); R3(w, c, d, e, a, b, 11); k_rotate5(b, c, d, e, a);
			R4(w, a, b, c, d, e, 12); R4(w, e, a, b, c, d, 13); R4(w, d, e, a, b, c, 14); R4(w, c, d, e, a, b, 15); k_rotate5(b, c, d, e, a);

			update_w_fast(w);

			R4(w, a, b, c, d, e,  0); R4(w, e, a, b, c, d,  1); R4(w, d, e, a, b, c,  2); R4(w, c, d, e, a, b,  3); k_rotate5(b, c, d, e, a);
			R4(w, a, b, c, d, e,  4); R4(w, e, a, b, c, d,  5); R4(w, d, e, a, b, c,  6); R4(w, c, d, e, a, b,  7); k_rotate5(b, c, d, e, a);
			R4(w, a, b, c, d, e,  8); R4(w, e, a, b, c, d,  9); R4(w, d, e, a, b, c, 10); R4(w, c, d, e, a, b, 11); k_rotate5(b, c, d, e, a);
			R4(w, a, b, c, d, e, 12); R4(w, e, a, b, c, d, 13); R4(w, d, e, a, b, c, 14); R4(w, c, d, e, a, b, 15); k_rotate5(b, c, d, e, a);

			/* Add the working vars back into context.state[] */
			this->state[0] += a;
			this->state[1] += b;
			this->state[2] += c;
			this->state[3] += d;
			this->state[4] += e;
		}


#	if KERBAL_ENABLE_SHA1_INSTRUCT

		inline
		__m128i mm_reverse32(__m128i a)
		{
			return _mm_shuffle_epi32(a, 27); // bswap; 27 == 0b 00 01 10 11
		}

		inline
		void update_w_sha1_instruct(__m128i xmm_w[4]) KERBAL_NOEXCEPT
		{
			//w[0] = kerbal::numeric::rotl(w[0] ^ w[2] ^ w[8] ^ w[13] , 1);
			//w[1] = kerbal::numeric::rotl(w[1] ^ w[3] ^ w[9] ^ w[14] , 1);
			//w[2] = kerbal::numeric::rotl(w[2] ^ w[4] ^ w[10] ^ w[15] , 1);
			//w[3] = kerbal::numeric::rotl(w[3] ^ w[5] ^ w[11] ^ w[0] , 1);
			{
				__m128i xmm_sha1msg1 = _mm_sha1msg1_epu32(xmm_w[0], xmm_w[1]);
				xmm_sha1msg1 = _mm_xor_si128(xmm_sha1msg1, xmm_w[2]);
				xmm_w[0] = _mm_sha1msg2_epu32(xmm_sha1msg1, xmm_w[3]);
			}

			//w[4] = kerbal::numeric::rotl(w[4] ^ w[6] ^ w[12] ^ w[1] , 1);
			//w[5] = kerbal::numeric::rotl(w[5] ^ w[7] ^ w[13] ^ w[2] , 1);
			//w[6] = kerbal::numeric::rotl(w[6] ^ w[8] ^ w[14] ^ w[3] , 1);
			//w[7] = kerbal::numeric::rotl(w[7] ^ w[9] ^ w[15] ^ w[4] , 1);
			{
				__m128i xmm_sha1msg1 = _mm_sha1msg1_epu32(xmm_w[1], xmm_w[2]);
				xmm_sha1msg1 = _mm_xor_si128(xmm_sha1msg1, xmm_w[3]);
				xmm_w[1] = _mm_sha1msg2_epu32(xmm_sha1msg1, xmm_w[0]);
			}

			//w[8] = kerbal::numeric::rotl(w[8] ^ w[10] ^ w[0] ^ w[5] , 1);
			//w[9] = kerbal::numeric::rotl(w[9] ^ w[11] ^ w[1] ^ w[6] , 1);
			//w[10] = kerbal::numeric::rotl(w[10] ^ w[12] ^ w[2] ^ w[7] , 1);
			//w[11] = kerbal::numeric::rotl(w[11] ^ w[13] ^ w[3] ^ w[8] , 1);
			{
				__m128i xmm_sha1msg1 = _mm_sha1msg1_epu32(xmm_w[2], xmm_w[3]);
				xmm_sha1msg1 = _mm_xor_si128(xmm_sha1msg1, xmm_w[0]);
				xmm_w[2] = _mm_sha1msg2_epu32(xmm_sha1msg1, xmm_w[1]);
			}

			//w[12] = kerbal::numeric::rotl(w[12] ^ w[14] ^ w[4] ^ w[9] , 1);
			//w[13] = kerbal::numeric::rotl(w[13] ^ w[15] ^ w[5] ^ w[10] , 1);
			//w[14] = kerbal::numeric::rotl(w[14] ^ w[0] ^ w[6] ^ w[11] , 1);
			//w[15] = kerbal::numeric::rotl(w[15] ^ w[1] ^ w[7] ^ w[12] , 1);
			{
				__m128i xmm_sha1msg1 = _mm_sha1msg1_epu32(xmm_w[3], xmm_w[0]);
				xmm_sha1msg1 = _mm_xor_si128(xmm_sha1msg1, xmm_w[1]);
				xmm_w[3] = _mm_sha1msg2_epu32(xmm_sha1msg1, xmm_w[2]);
			}

		}

		inline
		void SHA1_transform_overload<SHA1_policy::sha1_instruct>::transform(const uint8_t buffer[64]) KERBAL_NOEXCEPT
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

				update_w_sha1_instruct(xmm_w);
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

				update_w_sha1_instruct(xmm_w);
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

				update_w_sha1_instruct(xmm_w);
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

				update_w_sha1_instruct(xmm_w);
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

#	endif

		template <typename Policy>
		template <typename RandomAccessIterator>
		KERBAL_CONSTEXPR14
		void SHA1_context<Policy>::update_helper(RandomAccessIterator first, RandomAccessIterator last,
													std::random_access_iterator_tag) KERBAL_NOEXCEPT
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

			difference_type const len(last - first);

			uint32_t j = (this->count[0] / 8) % 64;

			if (len >= static_cast<uint32_t>(64 - j)) {
				iterator next = first + static_cast<uint32_t>(64 - j);
				kerbal::algorithm::copy(first, next, this->buffer + j);
				first = next;
				this->transform(this->buffer);

				difference_type loop = (last - first) / 64;
				for (difference_type i = 0; i < loop; ++i) {
					next = first + 64;
					kerbal::algorithm::copy(first, next, this->buffer);
					first = next;
					this->transform(this->buffer);
				}
				j = 0;
			}

			kerbal::algorithm::copy(first, last, this->buffer + j);

			j = this->count[0];
			this->count[0] += static_cast<kerbal::compatibility::uint32_t>(len << 3);
			if (this->count[0] < j) {
				++this->count[1];
			}
			this->count[1] += static_cast<kerbal::compatibility::uint32_t>(len >> 29);

		}

		template <typename Policy>
		KERBAL_CONSTEXPR14
		void SHA1_context<Policy>::update(const uint8_t * first, const uint8_t * last) KERBAL_NOEXCEPT
		{
			typedef const uint8_t * iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

			difference_type const len(last - first);

			uint32_t j = (this->count[0] / 8) % 64;

			if (len >= static_cast<uint32_t>(64 - j)) {
				if (j != 0) {
					iterator next = first + static_cast<uint32_t>(64 - j);
					kerbal::algorithm::copy(first, next, this->buffer + j);
					first = next;
					this->transform(this->buffer);
				}

				difference_type loop = (last - first) / 64;
				for (difference_type i = 0; i < loop; ++i) {
					this->transform(first);
					first += 64;
				}
				j = 0;
			}

			kerbal::algorithm::copy(first, last, this->buffer + j);

			j = this->count[0];
			this->count[0] += static_cast<kerbal::compatibility::uint32_t>(len << 3);
			if (this->count[0] < j) {
				++this->count[1];
			}
			this->count[1] += static_cast<kerbal::compatibility::uint32_t>(len >> 29);

		}

		template <typename Policy>
		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void SHA1_context<Policy>::update(ForwardIterator first, ForwardIterator last) KERBAL_NOEXCEPT
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			KERBAL_STATIC_ASSERT((kerbal::type_traits::is_same<value_type, uint8_t>::value), "Iterator must refers to uint8_t");

			this->update_helper(first, last, kerbal::iterator::iterator_category(first));
		}

		template <typename Policy>
		KERBAL_CONSTEXPR14
		typename SHA1_context<Policy>::result
		SHA1_context<Policy>::digest() KERBAL_NOEXCEPT
		{
			const uint8_t final_count[8] = {
					static_cast<uint8_t>(this->count[1] >> 24),
					static_cast<uint8_t>(this->count[1] >> 16),
					static_cast<uint8_t>(this->count[1] >> 8),
					static_cast<uint8_t>(this->count[1] >> 0),
					static_cast<uint8_t>(this->count[0] >> 24),
					static_cast<uint8_t>(this->count[0] >> 16),
					static_cast<uint8_t>(this->count[0] >> 8),
					static_cast<uint8_t>(this->count[0] >> 0),
			}; /* Endian independent */

			{
				uint8_t p[1] = {0200};
				this->update(p, p + 1);
				while ((this->count[0] & 504) != 448) {
					// 504 = 0b111111000
					// 448 = 0b111000000
					p[0] = 0000;
					this->update(p, p + 1);
				}
			}

			this->update(final_count, final_count + 8); /* Should cause a SHA1Transform() */

			return result(this->state);
		}

	} // namespace hash

} // namespace kerbal

#endif // KERBAL_HASH_SHA1_SHA1_IMPL_HPP
