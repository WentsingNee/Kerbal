/**
 * @file       md5_context_base.hpp
 * @brief
 * @date       2024-10-11
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_HASH_MD5_DETAIL_MD5_CONTEXT_BASE_HPP
#define KERBAL_HASH_MD5_DETAIL_MD5_CONTEXT_BASE_HPP

#include <kerbal/hash/md5/md5.fwd.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/noexcept.hpp>


namespace kerbal
{

	namespace hash
	{

		namespace detail
		{

			class MD5_context_base
			{
				public:
					typedef kerbal::hash::MD5_result result;

				protected:
					typedef kerbal::compatibility::uint32_t		uint32_t;
					typedef kerbal::compatibility::uint8_t		uint8_t;

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
					// /* blk0() and blk() perform the initial expand. */
					// /* I got the idea of expanding during the round function from SSLeay */
					// template <int byte_order>
					// KERBAL_CONSTEXPR14
					// static
					// uint32_t blk0(uint32_t l[16], size_t i) KERBAL_NOEXCEPT;
					//
					// KERBAL_CONSTEXPR
					// static
					// uint32_t blk(const uint32_t l[16], size_t i) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					static
					uint32_t F(uint32_t b, uint32_t c, uint32_t d) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					static
					uint32_t G(uint32_t b, uint32_t c, uint32_t d) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					static
					uint32_t H(uint32_t b, uint32_t c, uint32_t d) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					static
					uint32_t I(uint32_t b, uint32_t c, uint32_t d) KERBAL_NOEXCEPT;

			};


#		if __cplusplus >= 201103L

			inline
			constexpr
			MD5_context_base::
			MD5_context_base() noexcept :
				a(0x67452301), b(0xefcdab89), c(0x98badcfe), d(0x10325476),
				count{0, 0}, buffer{}
			{
			}

#		else

			inline
			MD5_context_base::
			MD5_context_base() KERBAL_NOEXCEPT :
				a(0x67452301), b(0xefcdab89), c(0x98badcfe), d(0x10325476)
			{
				this->count[0] = this->count[1] = 0;

				// buffer doesn't need init
			}

#		endif


			KERBAL_CONSTEXPR14
			inline
			MD5_context_base::uint32_t
			MD5_context_base::
			F(uint32_t b, uint32_t c, uint32_t d) KERBAL_NOEXCEPT
			{
				return (b & c) | (~b & d);
			}

			KERBAL_CONSTEXPR14
			inline
			MD5_context_base::uint32_t
			MD5_context_base::
			G(uint32_t b, uint32_t c, uint32_t d) KERBAL_NOEXCEPT
			{
				return (b & d) | (c & ~d);
			}

			KERBAL_CONSTEXPR14
			inline
			MD5_context_base::uint32_t
			MD5_context_base::
			H(uint32_t b, uint32_t c, uint32_t d) KERBAL_NOEXCEPT
			{
				return b ^ c ^ d;
			}

			KERBAL_CONSTEXPR14
			inline
			MD5_context_base::uint32_t
			MD5_context_base::
			I(uint32_t b, uint32_t c, uint32_t d) KERBAL_NOEXCEPT
			{
				return c ^ (b | ~d);
			}

		} // namespace detail

	} // namespace hash

} // namespace kerbal

#endif // KERBAL_HASH_MD5_DETAIL_MD5_CONTEXT_BASE_HPP
