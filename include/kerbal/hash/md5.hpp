/**
 * @file       md5.hpp
 * @brief
 * @date       20020-08-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_HASH_MD5_HPP
#define KERBAL_HASH_MD5_HPP

#include <kerbal/hash/detail/sha1_result.hpp>

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

		class MD5_context_base
		{
			public:
				typedef SHA1_result result;

			protected:
				uint32_t a;
				uint32_t b;
				uint32_t c;
				uint32_t d;
				uint32_t count[2];
				unsigned char buffer[64];

#		if __cplusplus >= 201103L
				constexpr
				MD5_context_base() noexcept;
#		else
				MD5_context_base() KERBAL_NOEXCEPT;
#		endif

			protected:
				/* blk0() and blk() perform the initial expand. */
				/* I got the idea of expanding during the round function from SSLeay */
				template <int byte_order>
				KERBAL_CONSTEXPR14
				static uint32_t blk0(uint32_t l[16], size_t i) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR
				static uint32_t blk(const uint32_t l[16], size_t i) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14
				static void R0(uint32_t block_l[16], uint32_t v, uint32_t & w, uint32_t x, uint32_t y, uint32_t & z, size_t i) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14
				static void R1(uint32_t block_l[16], uint32_t v, uint32_t & w, uint32_t x, uint32_t y, uint32_t & z, size_t i) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14
				static void R2(uint32_t block_l[16], uint32_t v, uint32_t & w, uint32_t x, uint32_t y, uint32_t & z, size_t i) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14
				static void R3(uint32_t block_l[16], uint32_t v, uint32_t & w, uint32_t x, uint32_t y, uint32_t & z, size_t i) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14
				static void R4(uint32_t block_l[16], uint32_t v, uint32_t & w, uint32_t x, uint32_t y, uint32_t & z, size_t i) KERBAL_NOEXCEPT;

		};

		struct MD5_policy
		{
			struct fast {};
			struct size {};
		};

		template <typename Policy>
		class MD5_transform_overload;

		template <>
		class MD5_transform_overload<MD5_policy::size> : protected MD5_context_base
		{
			protected:

#		if __cplusplus >= 201103L
				constexpr
				MD5_transform_overload() noexcept = default;
#		endif

				// warning: The function will read 64 unsigned char data from the iterator
				KERBAL_CONSTEXPR14
				void transform(const unsigned char buffer[64]) KERBAL_NOEXCEPT;

		};

		template <>
		class MD5_transform_overload<MD5_policy::fast> : protected MD5_context_base
		{
			protected:

#		if __cplusplus >= 201103L
				constexpr
				MD5_transform_overload() noexcept = default;
#		endif

				KERBAL_CONSTEXPR14
				void transform(const unsigned char buffer[64]) KERBAL_NOEXCEPT;

		};

		template <typename Policy>
		class MD5_context : protected MD5_transform_overload<Policy>
		{
			public:
				typedef MD5_result result;

#		if __cplusplus >= 201103L
				constexpr
				MD5_context() noexcept = default;
#		else
				MD5_context() KERBAL_NOEXCEPT
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
				template <typename ForwardIterator> // unsigned char
				KERBAL_CONSTEXPR14
				void update(ForwardIterator first, ForwardIterator last) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14
				void update(const unsigned char * first, const unsigned char * last) KERBAL_NOEXCEPT;

				/**
				 * Add padding and return the message digest.
				 */
				KERBAL_CONSTEXPR14
				result digest() KERBAL_NOEXCEPT;

		};

	} // namespace hash

} // namespace kerbal

#include <kerbal/hash/impl/sha1.impl.hpp>

#endif // KERBAL_HASH_MD5_HPP
