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
		inline
		uint32_t SHA1_context_base::blk0<LITTLE_ENDIAN>(uint32_t l[16], size_t i) KERBAL_NOEXCEPT
		{
			return l[i] = (kerbal::numeric::rotl(l[i], 24) & 0xFF00FF00u) |
					(kerbal::numeric::rotl(l[i], 8) & 0x00FF00FFu);
		}

		template <>
		KERBAL_CONSTEXPR14
		inline
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
			z += (block_l[i] = blk(block_l, i));
			z += kerbal::numeric::rotl(v, 5);
			z += ((w & (x ^ y)) ^ y) + 0x5A827999;
			w = kerbal::numeric::rotl(w, 30);
		}

		KERBAL_CONSTEXPR14
		inline
		void SHA1_context_base::R2(uint32_t block_l[16], uint32_t v, uint32_t & w, uint32_t x, uint32_t y, uint32_t & z, size_t i) KERBAL_NOEXCEPT
		{
			z += (block_l[i] = blk(block_l, i));
			z += kerbal::numeric::rotl(v, 5);
			z += (w ^ x ^ y) + 0x6ED9EBA1;
			w = kerbal::numeric::rotl(w, 30);
		}

		KERBAL_CONSTEXPR14
		inline
		void SHA1_context_base::R3(uint32_t block_l[16], uint32_t v, uint32_t & w, uint32_t x, uint32_t y, uint32_t & z, size_t i) KERBAL_NOEXCEPT
		{
			z += (block_l[i] = blk(block_l, i));
			z += kerbal::numeric::rotl(v, 5);
			z += (((w | x) & y) | (w & x)) + 0x8F1BBCDC;
			w = kerbal::numeric::rotl(w, 30);
		}

		KERBAL_CONSTEXPR14
		inline
		void SHA1_context_base::R4(uint32_t block_l[16], uint32_t v, uint32_t & w, uint32_t x, uint32_t y, uint32_t & z, size_t i) KERBAL_NOEXCEPT
		{
			z += (block_l[i] = blk(block_l, i));
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

			// buffer doesn't need init
		}

#	endif

		KERBAL_CONSTEXPR
		inline uint32_t char4tolong1(const unsigned char c[4])
		{
			return (c[3] << 24u) | (c[2] << 16u) | (c[1] << 8u) | c[0];
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
				R0(l, a, b, c, d, e, i + 0);
				R0(l, e, a, b, c, d, i + 1);
				R0(l, d, e, a, b, c, i + 2);
				R0(l, c, d, e, a, b, i + 3);
				R0(l, b, c, d, e, a, i + 4);
			}
			R0(l, a, b, c, d, e, 15u);

			R1(l, e, a, b, c, d, 0u); R1(l, d, e, a, b, c, 1u); R1(l, c, d, e, a, b, 2u); R1(l, b, c, d, e, a, 3u);

			for (size_t i = 4; i < 24; i += 5) {
				R2(l, a, b, c, d, e, (i + 0) & 15u);
				R2(l, e, a, b, c, d, (i + 1) & 15u);
				R2(l, d, e, a, b, c, (i + 2) & 15u);
				R2(l, c, d, e, a, b, (i + 3) & 15u);
				R2(l, b, c, d, e, a, (i + 4) & 15u);
			}

			for (size_t i = 8; i < 28; i += 5) {
				R3(l, a, b, c, d, e, (i + 0) & 15u);
				R3(l, e, a, b, c, d, (i + 1) & 15u);
				R3(l, d, e, a, b, c, (i + 2) & 15u);
				R3(l, c, d, e, a, b, (i + 3) & 15u);
				R3(l, b, c, d, e, a, (i + 4) & 15u);
			}

			for (size_t i = 12; i < 32; i += 5) {
				R4(l, a, b, c, d, e, (i + 0) & 15u);
				R4(l, e, a, b, c, d, (i + 1) & 15u);
				R4(l, d, e, a, b, c, (i + 2) & 15u);
				R4(l, c, d, e, a, b, (i + 3) & 15u);
				R4(l, b, c, d, e, a, (i + 4) & 15u);
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

			R1(l, e, a, b, c, d,  0u); R1(l, d, e, a, b, c,  1u); R1(l, c, d, e, a, b,  2u); R1(l, b, c, d, e, a,  3u);

			R2(l, a, b, c, d, e,  4u); R2(l, e, a, b, c, d,  5u); R2(l, d, e, a, b, c,  6u); R2(l, c, d, e, a, b,  7u); R2(l, b, c, d, e, a,  8u);
			R2(l, a, b, c, d, e,  9u); R2(l, e, a, b, c, d, 10u); R2(l, d, e, a, b, c, 11u); R2(l, c, d, e, a, b, 12u); R2(l, b, c, d, e, a, 13u);
			R2(l, a, b, c, d, e, 14u); R2(l, e, a, b, c, d, 15u); R2(l, d, e, a, b, c,  0u); R2(l, c, d, e, a, b,  1u); R2(l, b, c, d, e, a,  2u);
			R2(l, a, b, c, d, e,  3u); R2(l, e, a, b, c, d,  4u); R2(l, d, e, a, b, c,  5u); R2(l, c, d, e, a, b,  6u); R2(l, b, c, d, e, a,  7u);

			R3(l, a, b, c, d, e,  8u); R3(l, e, a, b, c, d,  9u); R3(l, d, e, a, b, c, 10u); R3(l, c, d, e, a, b, 11u); R3(l, b, c, d, e, a, 12u);
			R3(l, a, b, c, d, e, 13u); R3(l, e, a, b, c, d, 14u); R3(l, d, e, a, b, c, 15u); R3(l, c, d, e, a, b,  0u); R3(l, b, c, d, e, a,  1u);
			R3(l, a, b, c, d, e,  2u); R3(l, e, a, b, c, d,  3u); R3(l, d, e, a, b, c,  4u); R3(l, c, d, e, a, b,  5u); R3(l, b, c, d, e, a,  6u);
			R3(l, a, b, c, d, e,  7u); R3(l, e, a, b, c, d,  8u); R3(l, d, e, a, b, c,  9u); R3(l, c, d, e, a, b, 10u); R3(l, b, c, d, e, a, 11u);

			R4(l, a, b, c, d, e, 12u); R4(l, e, a, b, c, d, 13u); R4(l, d, e, a, b, c, 14u); R4(l, c, d, e, a, b, 15u); R4(l, b, c, d, e, a,  0u);
			R4(l, a, b, c, d, e,  1u); R4(l, e, a, b, c, d,  2u); R4(l, d, e, a, b, c,  3u); R4(l, c, d, e, a, b,  4u); R4(l, b, c, d, e, a,  5u);
			R4(l, a, b, c, d, e,  6u); R4(l, e, a, b, c, d,  7u); R4(l, d, e, a, b, c,  8u); R4(l, c, d, e, a, b,  9u); R4(l, b, c, d, e, a, 10u);
			R4(l, a, b, c, d, e, 11u); R4(l, e, a, b, c, d, 12u); R4(l, d, e, a, b, c, 13u); R4(l, c, d, e, a, b, 14u); R4(l, b, c, d, e, a, 15u);

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

				int loop = (last - first) / 64;
				for (int i = 0; i < loop; ++i) {
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
		KERBAL_CONSTEXPR14
		void SHA1_context<Policy>::update(const unsigned char * first, const unsigned char * last) KERBAL_NOEXCEPT
		{
			typedef const unsigned char * iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

			difference_type len(last - first);

			uint32_t j = (this->count[0] / 8) % 64;

			if (len >= 64 - j) {
				iterator next = first + (64 - j);
				kerbal::algorithm::copy(first, next, this->buffer + j);
				first = next;

				this->transform(this->buffer);

				int loop = (last - first) / 64;
				for (int i = 0; i < loop; ++i) {
					this->transform(first);
					first += 64;
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
