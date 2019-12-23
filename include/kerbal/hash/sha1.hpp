/**
 * @file       sha1.hpp
 * @brief
 * @date       2019-8-11
 * @author     Peter Nee, Steve Reid
 * @copyright
 *
 *
 *  This file refers the source code written by Steve Reid, of which
 *  you can find the original c-style source file from redis5.0/sha1.
 *  To use elegantly, the algorithm was transferred to C++-style and then
 *  optimized by Peter Nee of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *  of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/).
 *
 *  Here is the copyright of the original file. Though Steve didn't have any other argument
 *  about copyright in these files but I sincerely hope that you can retain the
 *  copyright notice in redistributions of source code. Thank you!

 	================ sha1.c ================
	SHA-1 in C
	By Steve Reid <steve@edmweb.com>
	100% Public Domain

	Test Vectors (from FIPS PUB 180-1)
	"abc"
	  A9993E36 4706816A BA3E2571 7850C26C 9CD0D89D
	"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"
	  84983E44 1C3BD26E BAAE4AA1 F95129E5 E54670F1
	A million repetitions of "a"
	  34AA973C D4C4DAA4 F61EEB2B DBAD2731 6534016F


	================ sha1.h ================
	SHA-1 in C
	By Steve Reid <steve@edmweb.com>
	100% Public Domain

 */

#ifndef KERBAL_HASH_SHA1_HPP_
#define KERBAL_HASH_SHA1_HPP_

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>

#if __cplusplus >= 201103L
#	include <cstdint>
#endif
#include <ostream>
#include <string>

namespace kerbal
{
	namespace hash
	{

#	if __cplusplus >= 201103L
		typedef std::uint32_t uint32_t;
#	else
		typedef u_int32_t uint32_t;
#	endif


		class SHA1_result
		{
			private:
				KERBAL_CONSTEXPR static char to_ocx(char c) KERBAL_NOEXCEPT
				{
					return c < 10 ? '0' + c : 'a' - 10 + c;
				}

				unsigned char hash[20];

				KERBAL_CONSTEXPR14
				explicit SHA1_result(const uint32_t state[5]) KERBAL_NOEXCEPT

#	if __cplusplus >= 201402L
					: hash { }
#	endif

				{
					for (unsigned i = 0; i < 20; i++) {
						this->hash[i] = static_cast<unsigned char>((state[i >> 2] >> ((3 - (i & 3)) * 8)) & 255);
					}
				}

				template <typename Son>
				friend class __SHA1_context_base2;

			public:
				friend std::ostream& operator<<(std::ostream& out, const SHA1_result & result)
				{
					char tmp[3];
					tmp[2] = '\0';
					for (int i = 0; i < 20; ++i) {
						tmp[0] = to_ocx(result.hash[i] >> 4);
						tmp[1] = to_ocx(result.hash[i] % 16);
						out << tmp;
					}
					return out;
				}

				operator std::string() const
				{
					std::string s;
					s.reserve(40);
					for (int i = 0; i < 20; ++i) {
						s.push_back(to_ocx(hash[i] >> 4));
						s.push_back(to_ocx(hash[i] % 16));
					}
					return s;
				}

				KERBAL_CONSTEXPR14 const unsigned char * c_str() const KERBAL_NOEXCEPT
				{
					return this->hash;
				}
		};


		class __SHA1_context_base
		{
			protected:
				static KERBAL_CONSTEXPR
				uint32_t __roll_uint32(uint32_t value, int bits) KERBAL_NOEXCEPT
				{
					return (value << bits) | (value >> (32 - bits));
				}

			protected:
				uint32_t state[5];
				uint32_t count[2];
				unsigned char buffer[64];

			public:

#		if __cplusplus >= 201103L
				constexpr __SHA1_context_base() noexcept;
#		else
				__SHA1_context_base() KERBAL_NOEXCEPT;
#		endif

			protected:
				/* blk0() and blk() perform the initial expand. */
				/* I got the idea of expanding during the round function from SSLeay */
				template <int byte_order>
				static KERBAL_CONSTEXPR
				uint32_t blk0(const uint32_t l[16], int i) KERBAL_NOEXCEPT;

				static KERBAL_CONSTEXPR14
				uint32_t blk(uint32_t block_l[16], int i) KERBAL_NOEXCEPT;

				static KERBAL_CONSTEXPR14
				void R0(uint32_t block_l[16], uint32_t v, uint32_t & w, uint32_t x, uint32_t y, uint32_t & z, int i) KERBAL_NOEXCEPT;

				static KERBAL_CONSTEXPR14
				void R1(uint32_t block_l[16], uint32_t v, uint32_t & w, uint32_t x, uint32_t y, uint32_t & z, int i) KERBAL_NOEXCEPT;

				static KERBAL_CONSTEXPR14
				void R2(uint32_t block_l[16], uint32_t v, uint32_t & w, uint32_t x, uint32_t y, uint32_t & z, int i) KERBAL_NOEXCEPT;

				static KERBAL_CONSTEXPR14
				void R3(uint32_t block_l[16], uint32_t v, uint32_t & w, uint32_t x, uint32_t y, uint32_t & z, int i) KERBAL_NOEXCEPT;

				static KERBAL_CONSTEXPR14
				void R4(uint32_t block_l[16], uint32_t v, uint32_t & w, uint32_t x, uint32_t y, uint32_t & z, int i) KERBAL_NOEXCEPT;

		};

		struct SHA1_policy
		{
			struct fast {};
			struct size {};
		};

		template <typename Son>
		class __SHA1_context_base2 : protected __SHA1_context_base
		{
			private:
				KERBAL_CONSTEXPR14
				void __transform__redistribute(uint32_t l[16]) KERBAL_NOEXCEPT
				{
					static_cast<Son&>(*this).__transform(l);
				}

			public:
				typedef SHA1_result result;

				/*
				 * Run your data through this.
				 */
				template <typename ForwardIterator> // unsigned char
				KERBAL_CONSTEXPR14
				void update(ForwardIterator first, ForwardIterator last) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14
				void update(unsigned char * first, unsigned char * last) KERBAL_NOEXCEPT
				{
					this->update(static_cast<const unsigned char *>(first),
								static_cast<const unsigned char *>(last));
				}

				/**
				 * Add padding and return the message digest.
				 */
				KERBAL_CONSTEXPR14
				result digest() KERBAL_NOEXCEPT;
		};

		template <typename Policy>
		class SHA1_context;

		template <>
		class SHA1_context<SHA1_policy::size> : public __SHA1_context_base2<SHA1_context<SHA1_policy::size> >
		{
				friend class __SHA1_context_base2<SHA1_context<SHA1_policy::size> >;

				// warning: The function will read 64 unsigned char data from the iterator
				KERBAL_CONSTEXPR14
				void __transform(const uint32_t block[16]) KERBAL_NOEXCEPT;

		};

		template <>
		class SHA1_context<SHA1_policy::fast> : public __SHA1_context_base2<SHA1_context<SHA1_policy::fast> >
		{
				friend class __SHA1_context_base2<SHA1_context<SHA1_policy::fast> >;

				KERBAL_CONSTEXPR14
				void __transform(const uint32_t block[16]) KERBAL_NOEXCEPT;

		};

	} // namespace hash

} // namespace kerbal

#include <kerbal/hash/impl/sha1.impl.hpp>

#endif /* KERBAL_HASH_SHA1_HPP_ */
