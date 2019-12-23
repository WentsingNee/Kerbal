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

#ifndef KERBAL_HASH_IMPL_SHA1_IMPL_HPP_
#define KERBAL_HASH_IMPL_SHA1_IMPL_HPP_

#include <kerbal/algorithm/querier.hpp>
#include <kerbal/algorithm/modifier.hpp>
#include <kerbal/iterator/iterator.hpp>

namespace kerbal
{
	namespace hash
	{

		template <>
		KERBAL_CONSTEXPR
		uint32_t __SHA1_context_base::blk0<LITTLE_ENDIAN>(const uint32_t l[16], int i) KERBAL_NOEXCEPT
		{
			return (__roll_uint32(l[i], 24) & 0xFF00FF00) |
					(__roll_uint32(l[i], 8) & 0x00FF00FF);
		}

		template <>
		KERBAL_CONSTEXPR
		uint32_t __SHA1_context_base::blk0<BIG_ENDIAN>(const uint32_t l[16], int i) KERBAL_NOEXCEPT
		{
			return l[i];
		}

		KERBAL_CONSTEXPR14
		uint32_t __SHA1_context_base::blk(uint32_t block_l[16], int i) KERBAL_NOEXCEPT
		{
			return block_l[i & 15] = __roll_uint32(
					block_l[(i + 13) & 15] ^ block_l[(i + 8) & 15]
							^ block_l[(i + 2) & 15] ^ block_l[i & 15], 1);
		}

		KERBAL_CONSTEXPR14
		void __SHA1_context_base::R0(uint32_t block_l[16], uint32_t v, uint32_t & w, uint32_t x, uint32_t y, uint32_t & z, int i) KERBAL_NOEXCEPT
		{
			z += (block_l[i] = blk0<BYTE_ORDER>(block_l, i));
			z += __roll_uint32(v, 5);
			z += ((w & (x ^ y)) ^ y) + 0x5A827999;
			w = __roll_uint32(w, 30);
		}

		KERBAL_CONSTEXPR14
		void __SHA1_context_base::R1(uint32_t block_l[16], uint32_t v, uint32_t & w, uint32_t x, uint32_t y, uint32_t & z, int i) KERBAL_NOEXCEPT
		{
			z += (block_l[i & 15] = blk(block_l, i));
			z += __roll_uint32(v, 5);
			z += ((w & (x ^ y)) ^ y) + 0x5A827999;
			w = __roll_uint32(w, 30);
		}

		KERBAL_CONSTEXPR14
		void __SHA1_context_base::R2(uint32_t block_l[16], uint32_t v, uint32_t & w, uint32_t x, uint32_t y, uint32_t & z, int i) KERBAL_NOEXCEPT
		{
			z += (block_l[i & 15] = blk(block_l, i));
			z += __roll_uint32(v, 5);
			z += (w ^ x ^ y) + 0x6ED9EBA1;
			w = __roll_uint32(w, 30);
		}

		KERBAL_CONSTEXPR14
		void __SHA1_context_base::R3(uint32_t block_l[16], uint32_t v, uint32_t & w, uint32_t x, uint32_t y, uint32_t & z, int i) KERBAL_NOEXCEPT
		{
			z += (block_l[i & 15] = blk(block_l, i));
			z += __roll_uint32(v, 5);
			z += (((w | x) & y) | (w & x)) + 0x8F1BBCDC;
			w = __roll_uint32(w, 30);
		}

		KERBAL_CONSTEXPR14
		void __SHA1_context_base::R4(uint32_t block_l[16], uint32_t v, uint32_t & w, uint32_t x, uint32_t y, uint32_t & z, int i) KERBAL_NOEXCEPT
		{
			z += (block_l[i & 15] = blk(block_l, i));
			z += __roll_uint32(v, 5);
			z += (w ^ x ^ y) + 0xCA62C1D6;
			w = __roll_uint32(w, 30);
		}

#	if __cplusplus >= 201103L

		constexpr __SHA1_context_base::__SHA1_context_base() noexcept :
				state { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0 },
				count { 0, 0 }, buffer { }
		{
		}

#	else

		__SHA1_context_base::__SHA1_context_base() KERBAL_NOEXCEPT
		{
			this->state[0] = 0x67452301;
			this->state[1] = 0xEFCDAB89;
			this->state[2] = 0x98BADCFE;
			this->state[3] = 0x10325476;
			this->state[4] = 0xC3D2E1F0;

			this->count[0] = this->count[1] = 0;

			kerbal::algorithm::fill(this->buffer, this->buffer + 64, static_cast<unsigned char>(0));
		}

#	endif

		KERBAL_CONSTEXPR14
		void SHA1_context<SHA1_policy::size>::__transform(const uint32_t block[16]) KERBAL_NOEXCEPT
		{
			uint32_t l[16] = {};
			kerbal::algorithm::copy(block, block + 16, l);

			/* Copy context->state[] to working vars */
			uint32_t a = this->state[0];
			uint32_t b = this->state[1];
			uint32_t c = this->state[2];
			uint32_t d = this->state[3];
			uint32_t e = this->state[4];

			for (int i = 0; i < 15; i += 5) {
				R0(l, a, b, c, d, e, i + 0); R0(l, e, a, b, c, d, i + 1); R0(l, d, e, a, b, c, i + 2); R0(l, c, d, e, a, b, i + 3); R0(l, b, c, d, e, a, i + 4);
			}
			R0(l, a, b, c, d, e, 15);

			R1(l, e, a, b, c, d, 16); R1(l, d, e, a, b, c, 17); R1(l, c, d, e, a, b, 18); R1(l, b, c, d, e, a, 19);

			for (int i = 20; i < 40; i += 5) {
				R2(l, a, b, c, d, e, i + 0); R2(l, e, a, b, c, d, i + 1); R2(l, d, e, a, b, c, i + 2); R2(l, c, d, e, a, b, i + 3); R2(l, b, c, d, e, a, i + 4);
			}

			for (int i = 40; i < 60; i += 5) {
				R3(l, a, b, c, d, e, i + 0); R3(l, e, a, b, c, d, i + 1); R3(l, d, e, a, b, c, i + 2); R3(l, c, d, e, a, b, i + 3); R3(l, b, c, d, e, a, i + 4);
			}

			for (int i = 60; i < 80; i += 5) {
				R4(l, a, b, c, d, e, i + 0); R4(l, e, a, b, c, d, i + 1); R4(l, d, e, a, b, c, i + 2); R4(l, c, d, e, a, b, i + 3); R4(l, b, c, d, e, a, i + 4);
			}

			/* Add the working vars back into context.state[] */
			this->state[0] += a;
			this->state[1] += b;
			this->state[2] += c;
			this->state[3] += d;
			this->state[4] += e;
		}

		KERBAL_CONSTEXPR14
		void SHA1_context<SHA1_policy::fast>::__transform(const uint32_t block[16]) KERBAL_NOEXCEPT
		{
			uint32_t l[16] = {};
			kerbal::algorithm::copy(block, block + 16, l);

			/* Copy context->state[] to working vars */
			uint32_t a = this->state[0];
			uint32_t b = this->state[1];
			uint32_t c = this->state[2];
			uint32_t d = this->state[3];
			uint32_t e = this->state[4];

			R0(l, a, b, c, d, e,  0); R0(l, e, a, b, c, d,  1); R0(l, d, e, a, b, c,  2); R0(l, c, d, e, a, b,  3); R0(l, b, c, d, e, a,  4);
			R0(l, a, b, c, d, e,  5); R0(l, e, a, b, c, d,  6); R0(l, d, e, a, b, c,  7); R0(l, c, d, e, a, b,  8); R0(l, b, c, d, e, a,  9);
			R0(l, a, b, c, d, e, 10); R0(l, e, a, b, c, d, 11); R0(l, d, e, a, b, c, 12); R0(l, c, d, e, a, b, 13); R0(l, b, c, d, e, a, 14);
			R0(l, a, b, c, d, e, 15);

			R1(l, e, a, b, c, d, 16); R1(l, d, e, a, b, c, 17); R1(l, c, d, e, a, b, 18); R1(l, b, c, d, e, a, 19);

			R2(l, a, b, c, d, e, 20); R2(l, e, a, b, c, d, 21); R2(l, d, e, a, b, c, 22); R2(l, c, d, e, a, b, 23); R2(l, b, c, d, e, a, 24);
			R2(l, a, b, c, d, e, 25); R2(l, e, a, b, c, d, 26); R2(l, d, e, a, b, c, 27); R2(l, c, d, e, a, b, 28); R2(l, b, c, d, e, a, 29);
			R2(l, a, b, c, d, e, 30); R2(l, e, a, b, c, d, 31); R2(l, d, e, a, b, c, 32); R2(l, c, d, e, a, b, 33); R2(l, b, c, d, e, a, 34);
			R2(l, a, b, c, d, e, 35); R2(l, e, a, b, c, d, 36); R2(l, d, e, a, b, c, 37); R2(l, c, d, e, a, b, 38); R2(l, b, c, d, e, a, 39);

			R3(l, a, b, c, d, e, 40); R3(l, e, a, b, c, d, 41); R3(l, d, e, a, b, c, 42); R3(l, c, d, e, a, b, 43); R3(l, b, c, d, e, a, 44);
			R3(l, a, b, c, d, e, 45); R3(l, e, a, b, c, d, 46); R3(l, d, e, a, b, c, 47); R3(l, c, d, e, a, b, 48); R3(l, b, c, d, e, a, 49);
			R3(l, a, b, c, d, e, 50); R3(l, e, a, b, c, d, 51); R3(l, d, e, a, b, c, 52); R3(l, c, d, e, a, b, 53); R3(l, b, c, d, e, a, 54);
			R3(l, a, b, c, d, e, 55); R3(l, e, a, b, c, d, 56); R3(l, d, e, a, b, c, 57); R3(l, c, d, e, a, b, 58); R3(l, b, c, d, e, a, 59);

			R4(l, a, b, c, d, e, 60); R4(l, e, a, b, c, d, 61); R4(l, d, e, a, b, c, 62); R4(l, c, d, e, a, b, 63); R4(l, b, c, d, e, a, 64);
			R4(l, a, b, c, d, e, 65); R4(l, e, a, b, c, d, 66); R4(l, d, e, a, b, c, 67); R4(l, c, d, e, a, b, 68); R4(l, b, c, d, e, a, 69);
			R4(l, a, b, c, d, e, 70); R4(l, e, a, b, c, d, 71); R4(l, d, e, a, b, c, 72); R4(l, c, d, e, a, b, 73); R4(l, b, c, d, e, a, 74);
			R4(l, a, b, c, d, e, 75); R4(l, e, a, b, c, d, 76); R4(l, d, e, a, b, c, 77); R4(l, c, d, e, a, b, 78); R4(l, b, c, d, e, a, 79);

			/* Add the working vars back into context.state[] */
			this->state[0] += a;
			this->state[1] += b;
			this->state[2] += c;
			this->state[3] += d;
			this->state[4] += e;
		}

		KERBAL_CONSTEXPR
		inline uint32_t char4tolong1(unsigned char c[4])
		{
			return (c[3] << 24) + (c[2] << 16) + (c[1] << 8) + c[0];
		}

		template <typename Son>
		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void __SHA1_context_base2<Son>::update(ForwardIterator first, ForwardIterator last) KERBAL_NOEXCEPT
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

			difference_type len(kerbal::iterator::distance(first, last));

			uint32_t j = (static_cast<uint32_t>(this->count[0]) >> 3) & 63;

			iterator adv(first);
			difference_type d(kerbal::iterator::advance_at_most(adv, 64 - j, last));
			kerbal::algorithm::copy(first, adv, this->buffer + j);
			first = adv;

			if (d == 64 - j) {

				uint32_t l[16] = {};

				{
					for (int i = 0; i < 16; ++i) {
						l[i] = char4tolong1(this->buffer + 4 * i);
					}
					this->__transform__redistribute(l);
				}

				while (kerbal::iterator::advance_at_most(adv, 64, last) == 64) {

					for (int i = 0; i < 16; ++i) {
						unsigned char c[4] = {}; {
							c[0] = *first; ++first;
							c[1] = *first; ++first;
							c[2] = *first; ++first;
							c[3] = *first; ++first;
						}
						l[i] = char4tolong1(c);
					}

					this->__transform__redistribute(l);
				}
				kerbal::algorithm::copy(first, last, this->buffer);

			}

			j = this->count[0];
			this->count[0] += len << 3;
			if (this->count[0] < j) {
				++this->count[1];
			}
			this->count[1] += (len >> 29);

		}
//		{
//			uint32_t i, j;
//
//			j = context->count[0];
//			if ((context->count[0] += len << 3) < j)
//				context->count[1]++;
//			context->count[1] += (len >> 29);
//			j = (j >> 3) & 63;
//			if ((j + len) > 63) {
//				memcpy(&context->buffer[j], data, (i = 64 - j));
//				SHA1Transform(context->state, context->buffer);
//				for (; i + 63 < len; i += 64) {
//					SHA1Transform(context->state, &data[i]);
//				}
//				j = 0;
//			} else
//				i = 0;
//			memcpy(&context->buffer[j], &data[i], len - i);
//		}

		template <typename Son>
		KERBAL_CONSTEXPR14
		typename __SHA1_context_base2<Son>::result
		__SHA1_context_base2<Son>::digest() KERBAL_NOEXCEPT
		{
			const unsigned char finalcount[8] = {
					static_cast<unsigned char>(this->count[1] >> 24),
					static_cast<unsigned char>(this->count[1] >> 16),
					static_cast<unsigned char>(this->count[1] >> 8),
					static_cast<unsigned char>(this->count[1] >> 0),
					static_cast<unsigned char>(this->count[0] >> 24),
					static_cast<unsigned char>(this->count[0] >> 16),
					static_cast<unsigned char>(this->count[0] >> 8),
					static_cast<unsigned char>(this->count[0] >> 0),
			}; /* Endian independent */

			{
				unsigned char c = 0200;
				const unsigned char * p = &c;
				this->update(p, p + 1);
				while ((this->count[0] & 504) != 448) {
					c = 0000;
					this->update(p, p + 1);
				}
			}

			this->update(finalcount, finalcount + 8); /* Should cause a SHA1Transform() */

			return result(this->state);
		}

	} // namespace hash

} // namespace kerbal

#endif /* KERBAL_HASH_IMPL_SHA1_IMPL_HPP_ */
