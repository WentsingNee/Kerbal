/**
 * @file       sha1_transform_overload.fast.hpp
 * @brief
 * @date       2024-10-06
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_HASH_SHA1_DETAIL_SHA1_TRANSFORM_OVERLOAD_SHA1_TRANSFORM_OVERLOAD_FAST_HPP
#define KERBAL_HASH_SHA1_DETAIL_SHA1_TRANSFORM_OVERLOAD_SHA1_TRANSFORM_OVERLOAD_FAST_HPP

#include <kerbal/hash/detail/char4tolong1.hpp>
#include <kerbal/hash/sha1/sha1.fwd.hpp>
#include <kerbal/hash/sha1/detail/sha1_context_base.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/config/endian.hpp>
#include <kerbal/numeric/bit.hpp>


namespace kerbal
{

	namespace hash
	{

		namespace detail
		{

			template <>
			class SHA1_transform_overload<kerbal::hash::SHA1_policy::fast> :
				protected kerbal::hash::detail::SHA1_context_base
			{
				protected:

#		if __cplusplus >= 201103L
					constexpr
					SHA1_transform_overload() = default;
#		endif

					KERBAL_CONSTEXPR14
					static
					void k_rotate5(uint32_t & a, uint32_t & b, uint32_t & c, uint32_t & d, uint32_t & e);

					KERBAL_CONSTEXPR14
					static
					void update_w(uint32_t w[16]) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					void transform(const uint8_t buffer[64]) KERBAL_NOEXCEPT;

			};

			KERBAL_CONSTEXPR14
			inline
			void
			SHA1_transform_overload<SHA1_policy::fast>::
			k_rotate5(uint32_t & a, uint32_t & b, uint32_t & c, uint32_t & d, uint32_t & e)
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
			void
			SHA1_transform_overload<SHA1_policy::fast>::
			update_w(uint32_t w[16]) KERBAL_NOEXCEPT
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
			void
			SHA1_transform_overload<SHA1_policy::fast>::
			transform(const uint8_t buffer[64]) KERBAL_NOEXCEPT
			{
				uint32_t w[16] = {};
				for (int i = 0; i < 16; ++i) {
					w[i] = char4tolong1<kerbal::config::KERBAL_BYTE_ORDER_TYPEDEF::value>(buffer + 4 * i);
				}

				/* Copy context->state[] to working vars */
				uint32_t a = this->state[0];
				uint32_t b = this->state[1];
				uint32_t c = this->state[2];
				uint32_t d = this->state[3];
				uint32_t e = this->state[4];

				R1(w[ 0], a, b, c, d, e); R1(w[ 1], e, a, b, c, d); R1(w[ 2], d, e, a, b, c); R1(w[ 3], c, d, e, a, b); k_rotate5(b, c, d, e, a);
				R1(w[ 4], a, b, c, d, e); R1(w[ 5], e, a, b, c, d); R1(w[ 6], d, e, a, b, c); R1(w[ 7], c, d, e, a, b); k_rotate5(b, c, d, e, a);
				R1(w[ 8], a, b, c, d, e); R1(w[ 9], e, a, b, c, d); R1(w[10], d, e, a, b, c); R1(w[11], c, d, e, a, b); k_rotate5(b, c, d, e, a);
				R1(w[12], a, b, c, d, e); R1(w[13], e, a, b, c, d); R1(w[14], d, e, a, b, c); R1(w[15], c, d, e, a, b); k_rotate5(b, c, d, e, a);

				update_w(w);

				R1(w[ 0], a, b, c, d, e); R1(w[ 1], e, a, b, c, d); R1(w[ 2], d, e, a, b, c); R1(w[ 3], c, d, e, a, b); k_rotate5(b, c, d, e, a);
				R2(w[ 4], a, b, c, d, e); R2(w[ 5], e, a, b, c, d); R2(w[ 6], d, e, a, b, c); R2(w[ 7], c, d, e, a, b); k_rotate5(b, c, d, e, a);
				R2(w[ 8], a, b, c, d, e); R2(w[ 9], e, a, b, c, d); R2(w[10], d, e, a, b, c); R2(w[11], c, d, e, a, b); k_rotate5(b, c, d, e, a);
				R2(w[12], a, b, c, d, e); R2(w[13], e, a, b, c, d); R2(w[14], d, e, a, b, c); R2(w[15], c, d, e, a, b); k_rotate5(b, c, d, e, a);

				update_w(w);

				R2(w[ 0], a, b, c, d, e); R2(w[ 1], e, a, b, c, d); R2(w[ 2], d, e, a, b, c); R2(w[ 3], c, d, e, a, b); k_rotate5(b, c, d, e, a);
				R2(w[ 4], a, b, c, d, e); R2(w[ 5], e, a, b, c, d); R2(w[ 6], d, e, a, b, c); R2(w[ 7], c, d, e, a, b); k_rotate5(b, c, d, e, a);
				R3(w[ 8], a, b, c, d, e); R3(w[ 9], e, a, b, c, d); R3(w[10], d, e, a, b, c); R3(w[11], c, d, e, a, b); k_rotate5(b, c, d, e, a);
				R3(w[12], a, b, c, d, e); R3(w[13], e, a, b, c, d); R3(w[14], d, e, a, b, c); R3(w[15], c, d, e, a, b); k_rotate5(b, c, d, e, a);

				update_w(w);

				R3(w[ 0], a, b, c, d, e); R3(w[ 1], e, a, b, c, d); R3(w[ 2], d, e, a, b, c); R3(w[ 3], c, d, e, a, b); k_rotate5(b, c, d, e, a);
				R3(w[ 4], a, b, c, d, e); R3(w[ 5], e, a, b, c, d); R3(w[ 6], d, e, a, b, c); R3(w[ 7], c, d, e, a, b); k_rotate5(b, c, d, e, a);
				R3(w[ 8], a, b, c, d, e); R3(w[ 9], e, a, b, c, d); R3(w[10], d, e, a, b, c); R3(w[11], c, d, e, a, b); k_rotate5(b, c, d, e, a);
				R4(w[12], a, b, c, d, e); R4(w[13], e, a, b, c, d); R4(w[14], d, e, a, b, c); R4(w[15], c, d, e, a, b); k_rotate5(b, c, d, e, a);

				update_w(w);

				R4(w[ 0], a, b, c, d, e); R4(w[ 1], e, a, b, c, d); R4(w[ 2], d, e, a, b, c); R4(w[ 3], c, d, e, a, b); k_rotate5(b, c, d, e, a);
				R4(w[ 4], a, b, c, d, e); R4(w[ 5], e, a, b, c, d); R4(w[ 6], d, e, a, b, c); R4(w[ 7], c, d, e, a, b); k_rotate5(b, c, d, e, a);
				R4(w[ 8], a, b, c, d, e); R4(w[ 9], e, a, b, c, d); R4(w[10], d, e, a, b, c); R4(w[11], c, d, e, a, b); k_rotate5(b, c, d, e, a);
				R4(w[12], a, b, c, d, e); R4(w[13], e, a, b, c, d); R4(w[14], d, e, a, b, c); R4(w[15], c, d, e, a, b); k_rotate5(b, c, d, e, a);

				/* Add the working vars back into context.state[] */
				this->state[0] += a;
				this->state[1] += b;
				this->state[2] += c;
				this->state[3] += d;
				this->state[4] += e;
			}

		} // namespace detail

	} // namespace hash

} // namespace kerbal

#endif // KERBAL_HASH_SHA1_DETAIL_SHA1_TRANSFORM_OVERLOAD_SHA1_TRANSFORM_OVERLOAD_FAST_HPP
