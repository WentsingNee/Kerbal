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
					void update_w(uint32_t w[16]) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					void transform(const uint8_t buffer[64]) KERBAL_NOEXCEPT;

			};

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
					w[i] = char4tolong1<BYTE_ORDER>(buffer + 4 * i);
				}

				/* Copy context->state[] to working vars */
				uint32_t a = this->state[0];
				uint32_t b = this->state[1];
				uint32_t c = this->state[2];
				uint32_t d = this->state[3];
				uint32_t e = this->state[4];

				R1(w, a, b, c, d, e,  0); R1(w, e, a, b, c, d,  1); R1(w, d, e, a, b, c,  2); R1(w, c, d, e, a, b,  3);
				R1(w, b, c, d, e, a,  4); R1(w, a, b, c, d, e,  5); R1(w, e, a, b, c, d,  6); R1(w, d, e, a, b, c,  7);
				R1(w, c, d, e, a, b,  8); R1(w, b, c, d, e, a,  9); R1(w, a, b, c, d, e, 10); R1(w, e, a, b, c, d, 11);
				R1(w, d, e, a, b, c, 12); R1(w, c, d, e, a, b, 13); R1(w, b, c, d, e, a, 14); R1(w, a, b, c, d, e, 15);

				update_w(w);

				R1(w, e, a, b, c, d,  0); R1(w, d, e, a, b, c,  1); R1(w, c, d, e, a, b,  2); R1(w, b, c, d, e, a,  3);

				R2(w, a, b, c, d, e,  4); R2(w, e, a, b, c, d,  5); R2(w, d, e, a, b, c,  6); R2(w, c, d, e, a, b,  7);
				R2(w, b, c, d, e, a,  8); R2(w, a, b, c, d, e,  9); R2(w, e, a, b, c, d, 10); R2(w, d, e, a, b, c, 11);
				R2(w, c, d, e, a, b, 12); R2(w, b, c, d, e, a, 13); R2(w, a, b, c, d, e, 14); R2(w, e, a, b, c, d, 15);

				update_w(w);

				R2(w, d, e, a, b, c,  0); R2(w, c, d, e, a, b,  1); R2(w, b, c, d, e, a,  2); R2(w, a, b, c, d, e,  3);
				R2(w, e, a, b, c, d,  4); R2(w, d, e, a, b, c,  5); R2(w, c, d, e, a, b,  6); R2(w, b, c, d, e, a,  7);

				R3(w, a, b, c, d, e,  8); R3(w, e, a, b, c, d,  9); R3(w, d, e, a, b, c, 10); R3(w, c, d, e, a, b, 11);
				R3(w, b, c, d, e, a, 12); R3(w, a, b, c, d, e, 13); R3(w, e, a, b, c, d, 14); R3(w, d, e, a, b, c, 15);

				update_w(w);

				R3(w, c, d, e, a, b,  0); R3(w, b, c, d, e, a,  1); R3(w, a, b, c, d, e,  2); R3(w, e, a, b, c, d,  3);
 				R3(w, d, e, a, b, c,  4); R3(w, c, d, e, a, b,  5); R3(w, b, c, d, e, a,  6); R3(w, a, b, c, d, e,  7); 
				R3(w, e, a, b, c, d,  8); R3(w, d, e, a, b, c,  9); R3(w, c, d, e, a, b, 10); R3(w, b, c, d, e, a, 11);

				R4(w, a, b, c, d, e, 12); R4(w, e, a, b, c, d, 13); R4(w, d, e, a, b, c, 14); R4(w, c, d, e, a, b, 15);

				update_w(w);

				R4(w, b, c, d, e, a,  0); R4(w, a, b, c, d, e,  1); R4(w, e, a, b, c, d,  2); R4(w, d, e, a, b, c,  3);
				R4(w, c, d, e, a, b,  4); R4(w, b, c, d, e, a,  5); R4(w, a, b, c, d, e,  6); R4(w, e, a, b, c, d,  7);
				R4(w, d, e, a, b, c,  8); R4(w, c, d, e, a, b,  9); R4(w, b, c, d, e, a, 10); R4(w, a, b, c, d, e, 11);
				R4(w, e, a, b, c, d, 12); R4(w, d, e, a, b, c, 13); R4(w, c, d, e, a, b, 14); R4(w, b, c, d, e, a, 15);

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
