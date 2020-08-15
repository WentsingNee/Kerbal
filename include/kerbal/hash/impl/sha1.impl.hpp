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

#ifndef KERBAL_HASH_IMPL_SHA1_IMPL_HPP
#define KERBAL_HASH_IMPL_SHA1_IMPL_HPP

#include <kerbal/algorithm/modifier.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/numeric/bit.hpp>
#include <kerbal/type_traits/is_same.hpp>

#include <kerbal/hash/sha1.hpp>

namespace kerbal
{

	namespace hash
	{

		template <>
		KERBAL_CONSTEXPR14
		uint32_t SHA1_context_base::blk0<LITTLE_ENDIAN>(uint32_t l[16], size_t i) KERBAL_NOEXCEPT
		{
			return l[i] = (kerbal::numeric::rotl(l[i], 24) & 0xFF00FF00u) |
					(kerbal::numeric::rotl(l[i], 8) & 0x00FF00FFu);
		}

		template <>
		KERBAL_CONSTEXPR14
		uint32_t SHA1_context_base::blk0<BIG_ENDIAN>(uint32_t l[16], size_t i) KERBAL_NOEXCEPT
		{
			return l[i];
		}

		KERBAL_CONSTEXPR
		inline
		uint32_t SHA1_context_base::blk(const uint32_t l[16], size_t i) KERBAL_NOEXCEPT
		{
			return kerbal::numeric::rotl(
					l[(i + 13) & 15u] ^ l[(i + 8) & 15u] ^ l[(i + 2) & 15u] ^ l[i & 15u]
					, 1);
		}

		KERBAL_CONSTEXPR14
		inline
		void SHA1_context_base::R0(uint32_t block_l[16], uint32_t v, uint32_t & w, uint32_t x, uint32_t y, uint32_t & z, size_t i) KERBAL_NOEXCEPT
		{
			z += blk0<BYTE_ORDER>(block_l, i);
			z += kerbal::numeric::rotl(v, 5);
			z += ((w & (x ^ y)) ^ y) + 0x5A827999;
			w = kerbal::numeric::rotl(w, 30);
		}

		KERBAL_CONSTEXPR14
		inline
		void SHA1_context_base::R1(uint32_t block_l[16], uint32_t v, uint32_t & w, uint32_t x, uint32_t y, uint32_t & z, size_t i) KERBAL_NOEXCEPT
		{
			z += (block_l[i & 15u] = blk(block_l, i));
			z += kerbal::numeric::rotl(v, 5);
			z += ((w & (x ^ y)) ^ y) + 0x5A827999;
			w = kerbal::numeric::rotl(w, 30);
		}

		KERBAL_CONSTEXPR14
		inline
		void SHA1_context_base::R2(uint32_t block_l[16], uint32_t v, uint32_t & w, uint32_t x, uint32_t y, uint32_t & z, size_t i) KERBAL_NOEXCEPT
		{
			z += (block_l[i & 15u] = blk(block_l, i));
			z += kerbal::numeric::rotl(v, 5);
			z += (w ^ x ^ y) + 0x6ED9EBA1;
			w = kerbal::numeric::rotl(w, 30);
		}

		KERBAL_CONSTEXPR14
		inline
		void SHA1_context_base::R3(uint32_t block_l[16], uint32_t v, uint32_t & w, uint32_t x, uint32_t y, uint32_t & z, size_t i) KERBAL_NOEXCEPT
		{
			z += (block_l[i & 15u] = blk(block_l, i));
			z += kerbal::numeric::rotl(v, 5);
			z += (((w | x) & y) | (w & x)) + 0x8F1BBCDC;
			w = kerbal::numeric::rotl(w, 30);
		}

		KERBAL_CONSTEXPR14
		inline
		void SHA1_context_base::R4(uint32_t block_l[16], uint32_t v, uint32_t & w, uint32_t x, uint32_t y, uint32_t & z, size_t i) KERBAL_NOEXCEPT
		{
			z += (block_l[i & 15u] = blk(block_l, i));
			z += kerbal::numeric::rotl(v, 5);
			z += (w ^ x ^ y) + 0xCA62C1D6;
			w = kerbal::numeric::rotl(w, 30);
		}

//#if BYTE_ORDER == LITTLE_ENDIAN
//#define blk0(l, i) l[(i)]=((kerbal::numeric::rotl(l[i],24)&0xFF00FF00u) \
//    |(kerbal::numeric::rotl(l[i],8)&0x00FF00FFu))
//#elif BYTE_ORDER == BIG_ENDIAN
//#define blk0(l, i) l[i]
//#else
//#error "Endianness not defined!"
//#endif
//
//#define blk(l, i) l[(i)&15u]=(kerbal::numeric::rotl(l[(i+13)&15u]^l[(i+8)&15u] \
//    ^l[(i+2)&15u]^l[i&15u],1))
//
//
//#define R0(l,v,w,x,y,z,i) z+=((w&(x^y))^y)+(blk0(l, i))+0x5A827999+kerbal::numeric::rotl(v,5);w=kerbal::numeric::rotl(w,30);
//#define R1(l,v,w,x,y,z,i) z+=((w&(x^y))^y)+(blk(l, i))+0x5A827999+kerbal::numeric::rotl(v,5);w=kerbal::numeric::rotl(w,30);
//#define R2(l,v,w,x,y,z,i) z+=(w^x^y)+(blk(l, i))+0x6ED9EBA1+kerbal::numeric::rotl(v,5);w=kerbal::numeric::rotl(w,30);
//#define R3(l,v,w,x,y,z,i) z+=(((w|x)&y)|(w&x))+(blk(l, i))+0x8F1BBCDC+kerbal::numeric::rotl(v,5);w=kerbal::numeric::rotl(w,30);
//#define R4(l,v,w,x,y,z,i) z+=(w^x^y)+(blk(l, i))+0xCA62C1D6+kerbal::numeric::rotl(v,5);w=kerbal::numeric::rotl(w,30);

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

			kerbal::algorithm::fill(this->buffer, this->buffer + 64, static_cast<unsigned char>(0));
		}

#	endif

		KERBAL_CONSTEXPR
		inline uint32_t char4tolong1(const unsigned char c[4])
		{
			return (c[3] << 24u) + (c[2] << 16u) + (c[1] << 8u) + c[0];
		}

		KERBAL_CONSTEXPR14
		inline
		void SHA1_transform_overload<SHA1_policy::size>::transform(const unsigned char buffer[64]) KERBAL_NOEXCEPT
		{
			uint32_t l[16] = {};
			for (int i = 0; i < 16; ++i) {
				l[i] = char4tolong1(buffer + 4 * i);
			}

			/* Copy context->state[] to working vars */
			uint32_t a = this->state[0];
			uint32_t b = this->state[1];
			uint32_t c = this->state[2];
			uint32_t d = this->state[3];
			uint32_t e = this->state[4];

			for (size_t i = 0; i < 15; i += 5) {
				R0(l, a, b, c, d, e, i + 0); R0(l, e, a, b, c, d, i + 1); R0(l, d, e, a, b, c, i + 2); R0(l, c, d, e, a, b, i + 3); R0(l, b, c, d, e, a, i + 4);
			}
			R0(l, a, b, c, d, e, 15u);

			R1(l, e, a, b, c, d, 16u); R1(l, d, e, a, b, c, 17u); R1(l, c, d, e, a, b, 18u); R1(l, b, c, d, e, a, 19u);

			for (size_t i = 20; i < 40; i += 5) {
				R2(l, a, b, c, d, e, i + 0); R2(l, e, a, b, c, d, i + 1); R2(l, d, e, a, b, c, i + 2); R2(l, c, d, e, a, b, i + 3); R2(l, b, c, d, e, a, i + 4);
			}

			for (size_t i = 40; i < 60; i += 5) {
				R3(l, a, b, c, d, e, i + 0); R3(l, e, a, b, c, d, i + 1); R3(l, d, e, a, b, c, i + 2); R3(l, c, d, e, a, b, i + 3); R3(l, b, c, d, e, a, i + 4);
			}

			for (size_t i = 60; i < 80; i += 5) {
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
		inline
		void SHA1_transform_overload<SHA1_policy::fast>::transform(const unsigned char buffer[64]) KERBAL_NOEXCEPT
		{
			uint32_t l[16] = {};
			for (int i = 0; i < 16; ++i) {
				l[i] = char4tolong1(buffer + 4 * i);
			}

			/* Copy context->state[] to working vars */
			uint32_t a = this->state[0];
			uint32_t b = this->state[1];
			uint32_t c = this->state[2];
			uint32_t d = this->state[3];
			uint32_t e = this->state[4];

			R0(l, a, b, c, d, e,  0u); R0(l, e, a, b, c, d,  1u); R0(l, d, e, a, b, c,  2u); R0(l, c, d, e, a, b,  3u); R0(l, b, c, d, e, a,  4u);
			R0(l, a, b, c, d, e,  5u); R0(l, e, a, b, c, d,  6u); R0(l, d, e, a, b, c,  7u); R0(l, c, d, e, a, b,  8u); R0(l, b, c, d, e, a,  9u);
			R0(l, a, b, c, d, e, 10u); R0(l, e, a, b, c, d, 11u); R0(l, d, e, a, b, c, 12u); R0(l, c, d, e, a, b, 13u); R0(l, b, c, d, e, a, 14u);
			R0(l, a, b, c, d, e, 15u);

			R1(l, e, a, b, c, d, 16u); R1(l, d, e, a, b, c, 17u); R1(l, c, d, e, a, b, 18u); R1(l, b, c, d, e, a, 19u);

			R2(l, a, b, c, d, e, 20u); R2(l, e, a, b, c, d, 21u); R2(l, d, e, a, b, c, 22u); R2(l, c, d, e, a, b, 23u); R2(l, b, c, d, e, a, 24u);
			R2(l, a, b, c, d, e, 25u); R2(l, e, a, b, c, d, 26u); R2(l, d, e, a, b, c, 27u); R2(l, c, d, e, a, b, 28u); R2(l, b, c, d, e, a, 29u);
			R2(l, a, b, c, d, e, 30u); R2(l, e, a, b, c, d, 31u); R2(l, d, e, a, b, c, 32u); R2(l, c, d, e, a, b, 33u); R2(l, b, c, d, e, a, 34u);
			R2(l, a, b, c, d, e, 35u); R2(l, e, a, b, c, d, 36u); R2(l, d, e, a, b, c, 37u); R2(l, c, d, e, a, b, 38u); R2(l, b, c, d, e, a, 39u);

			R3(l, a, b, c, d, e, 40u); R3(l, e, a, b, c, d, 41u); R3(l, d, e, a, b, c, 42u); R3(l, c, d, e, a, b, 43u); R3(l, b, c, d, e, a, 44u);
			R3(l, a, b, c, d, e, 45u); R3(l, e, a, b, c, d, 46u); R3(l, d, e, a, b, c, 47u); R3(l, c, d, e, a, b, 48u); R3(l, b, c, d, e, a, 49u);
			R3(l, a, b, c, d, e, 50u); R3(l, e, a, b, c, d, 51u); R3(l, d, e, a, b, c, 52u); R3(l, c, d, e, a, b, 53u); R3(l, b, c, d, e, a, 54u);
			R3(l, a, b, c, d, e, 55u); R3(l, e, a, b, c, d, 56u); R3(l, d, e, a, b, c, 57u); R3(l, c, d, e, a, b, 58u); R3(l, b, c, d, e, a, 59u);

			R4(l, a, b, c, d, e, 60u); R4(l, e, a, b, c, d, 61u); R4(l, d, e, a, b, c, 62u); R4(l, c, d, e, a, b, 63u); R4(l, b, c, d, e, a, 64u);
			R4(l, a, b, c, d, e, 65u); R4(l, e, a, b, c, d, 66u); R4(l, d, e, a, b, c, 67u); R4(l, c, d, e, a, b, 68u); R4(l, b, c, d, e, a, 69u);
			R4(l, a, b, c, d, e, 70u); R4(l, e, a, b, c, d, 71u); R4(l, d, e, a, b, c, 72u); R4(l, c, d, e, a, b, 73u); R4(l, b, c, d, e, a, 74u);
			R4(l, a, b, c, d, e, 75u); R4(l, e, a, b, c, d, 76u); R4(l, d, e, a, b, c, 77u); R4(l, c, d, e, a, b, 78u); R4(l, b, c, d, e, a, 79u);

			/* Add the working vars back into context.state[] */
			this->state[0] += a;
			this->state[1] += b;
			this->state[2] += c;
			this->state[3] += d;
			this->state[4] += e;
		}

		template <typename Policy>
		template <typename RandomAccessIterator>
		KERBAL_CONSTEXPR14
		void SHA1_context<Policy>::update_helper(RandomAccessIterator first, RandomAccessIterator last,
													std::random_access_iterator_tag) KERBAL_NOEXCEPT
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

			difference_type len(last - first);

			uint32_t j = (this->count[0] / 8) % 64;

			if (len >= 64 - j) {
				iterator next = first + (64 - j);
				kerbal::algorithm::copy(first, next, this->buffer + j);
				first = next;

				this->transform(this->buffer);

				while (last - first >= 64) {
					unsigned char c[64] = {};
					next = first + 64;
					kerbal::algorithm::copy(first, next, c);

					first = next;
					this->transform(c);
				}
				j = 0;
			}

			kerbal::algorithm::copy(first, last, this->buffer + j);

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

		template <typename Policy>
		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void SHA1_context<Policy>::update(ForwardIterator first, ForwardIterator last) KERBAL_NOEXCEPT
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			KERBAL_STATIC_ASSERT((kerbal::type_traits::is_same<value_type, unsigned char>::value), "Iterator must refers to unsigned char");

			this->update_helper(first, last, kerbal::iterator::iterator_category(first));
		}

		template <typename Policy>
		KERBAL_CONSTEXPR14
		typename SHA1_context<Policy>::result
		SHA1_context<Policy>::digest() KERBAL_NOEXCEPT
		{
			const unsigned char final_count[8] = {
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
				unsigned char p[1] = {0200};
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

#endif // KERBAL_HASH_IMPL_SHA1_IMPL_HPP
