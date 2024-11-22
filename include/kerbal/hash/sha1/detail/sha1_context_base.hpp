/**
 * @file       sha1_context_base.hpp
 * @brief
 * @date       2024-10-06
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_HASH_SHA1_DETAIL_SHA1_CONTEXT_BASE_HPP
#define KERBAL_HASH_SHA1_DETAIL_SHA1_CONTEXT_BASE_HPP

#include <kerbal/hash/sha1/sha1.fwd.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/numeric/bit.hpp>


namespace kerbal
{

	namespace hash
	{

		namespace detail
		{

			class SHA1_context_base
			{
				public:
					typedef kerbal::hash::SHA1_result result;

				protected:
					typedef kerbal::compatibility::uint32_t		uint32_t;
					typedef kerbal::compatibility::uint8_t		uint8_t;

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
					static
					void R1(uint32_t wi, uint32_t a, uint32_t & b, uint32_t c, uint32_t d, uint32_t & e) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					static
					void R2(uint32_t wi, uint32_t a, uint32_t & b, uint32_t c, uint32_t d, uint32_t & e) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					static
					void R3(uint32_t wi, uint32_t a, uint32_t & b, uint32_t c, uint32_t d, uint32_t & e) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					static
					void R4(uint32_t wi, uint32_t a, uint32_t & b, uint32_t c, uint32_t d, uint32_t & e) KERBAL_NOEXCEPT;

					static KERBAL_CONSTEXPR
					uint8_t const PADDING[1 + 64]
#		if __cplusplus >= 201103L
						= {0200}
#		endif
					;

			};

#		if __cplusplus < 201103L

			SHA1_context_base::uint8_t const
			SHA1_context_base::
			PADDING[1 + 64] = {0200};

#		endif


#		if __cplusplus >= 201103L

			inline
			constexpr
			SHA1_context_base::
			SHA1_context_base() noexcept :
				state{0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0},
				count{0, 0}, buffer{}
			{
			}

#		else

			inline
			SHA1_context_base::
			SHA1_context_base() KERBAL_NOEXCEPT
			{
				this->state[0] = 0x67452301;
				this->state[1] = 0xEFCDAB89;
				this->state[2] = 0x98BADCFE;
				this->state[3] = 0x10325476;
				this->state[4] = 0xC3D2E1F0;

				this->count[0] = this->count[1] = 0;

				// buffer doesn't need init
			}

#		endif


			KERBAL_CONSTEXPR14
			inline
			void
			SHA1_context_base::
			R1(uint32_t wi, uint32_t a, uint32_t & b, uint32_t c, uint32_t d, uint32_t & e) KERBAL_NOEXCEPT
			{
				e += wi;
				e += kerbal::numeric::rotl(a, 5);
				e += ((b & (c ^ d)) ^ d) + 0x5A827999;
				b = kerbal::numeric::rotl(b, 30);
			}

			KERBAL_CONSTEXPR14
			inline
			void
			SHA1_context_base::
			R2(uint32_t wi, uint32_t a, uint32_t & b, uint32_t c, uint32_t d, uint32_t & e) KERBAL_NOEXCEPT
			{
				e += wi;
				e += kerbal::numeric::rotl(a, 5);
				e += (b ^ c ^ d) + 0x6ED9EBA1;
				b = kerbal::numeric::rotl(b, 30);
			}

			KERBAL_CONSTEXPR14
			inline
			void
			SHA1_context_base::
			R3(uint32_t wi, uint32_t a, uint32_t & b, uint32_t c, uint32_t d, uint32_t & e) KERBAL_NOEXCEPT
			{
				e += wi;
				e += kerbal::numeric::rotl(a, 5);
				e += (((b | c) & d) | (b & c)) + 0x8F1BBCDC;
				b = kerbal::numeric::rotl(b, 30);
			}

			KERBAL_CONSTEXPR14
			inline
			void
			SHA1_context_base::
			R4(uint32_t wi, uint32_t a, uint32_t & b, uint32_t c, uint32_t d, uint32_t & e) KERBAL_NOEXCEPT
			{
				e += wi;
				e += kerbal::numeric::rotl(a, 5);
				e += (b ^ c ^ d) + 0xCA62C1D6;
				b = kerbal::numeric::rotl(b, 30);
			}

		} // namespace detail

	} // namespace hash

} // namespace kerbal

#endif // KERBAL_HASH_SHA1_DETAIL_SHA1_CONTEXT_BASE_HPP
