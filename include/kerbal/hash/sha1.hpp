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

#ifndef KERBAL_HASH_SHA1_HPP
#define KERBAL_HASH_SHA1_HPP

#include <kerbal/hash/sha1/sha1_result.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/noexcept.hpp>

#include <cstddef>


namespace kerbal
{

	namespace hash
	{

		using kerbal::compatibility::uint8_t;
		using kerbal::compatibility::uint32_t;

		class SHA1_context_base
		{
			public:
				typedef SHA1_result result;

			protected:
				uint32_t state[5];
				uint32_t count[2];
				uint8_t buffer[64];

#		if __cplusplus >= 201103L
				constexpr
				SHA1_context_base() noexcept;
#		else
				SHA1_context_base() KERBAL_NOEXCEPT;
#		endif

			protected:

				KERBAL_CONSTEXPR14
				static void R1(const uint32_t * w, uint32_t a, uint32_t & b, uint32_t c, uint32_t y, uint32_t & d, std::size_t i) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14
				static void R2(const uint32_t * w, uint32_t a, uint32_t & b, uint32_t c, uint32_t y, uint32_t & d, std::size_t i) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14
				static void R3(const uint32_t * w, uint32_t a, uint32_t & b, uint32_t c, uint32_t y, uint32_t & d, std::size_t i) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14
				static void R4(const uint32_t * w, uint32_t a, uint32_t & b, uint32_t c, uint32_t y, uint32_t & d, std::size_t i) KERBAL_NOEXCEPT;

		};

		struct SHA1_policy
		{
			struct fast {};
			struct size {};
		};

		template <typename Policy>
		class SHA1_transform_overload;

		template <>
		class SHA1_transform_overload<SHA1_policy::size> : protected SHA1_context_base
		{
			protected:

#		if __cplusplus >= 201103L
				constexpr
				SHA1_transform_overload() noexcept = default;
#		endif

				KERBAL_CONSTEXPR14
				void transform(const uint8_t buffer[64]) KERBAL_NOEXCEPT;

		};

		template <>
		class SHA1_transform_overload<SHA1_policy::fast> : protected SHA1_context_base
		{
			protected:

#		if __cplusplus >= 201103L
				constexpr
				SHA1_transform_overload() noexcept = default;
#		endif

				KERBAL_CONSTEXPR14
				void transform(const uint8_t buffer[64]) KERBAL_NOEXCEPT;

		};

		template <typename Policy>
		class SHA1_context : protected SHA1_transform_overload<Policy>
		{
			public:
				typedef SHA1_result result;

#		if __cplusplus >= 201103L
				constexpr
				SHA1_context() noexcept = default;
#		else
				SHA1_context() KERBAL_NOEXCEPT
				{
				}
#		endif

			private:

				template <typename RandomAccessIterator>
				KERBAL_CONSTEXPR14
				void update_helper(RandomAccessIterator first, RandomAccessIterator last, std::random_access_iterator_tag) KERBAL_NOEXCEPT;

			public:
				/*
				 * Run your data through this.
				 */
				template <typename ForwardIterator> // uint8_t
				KERBAL_CONSTEXPR14
				void update(ForwardIterator first, ForwardIterator last) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14
				void update(const uint8_t * first, const uint8_t * last) KERBAL_NOEXCEPT;

				/**
				 * Add padding and return the message digest.
				 */
				KERBAL_CONSTEXPR14
				result digest() KERBAL_NOEXCEPT;

		};

	} // namespace hash

} // namespace kerbal

#include <kerbal/hash/sha1/sha1.impl.hpp>

#endif // KERBAL_HASH_SHA1_HPP
