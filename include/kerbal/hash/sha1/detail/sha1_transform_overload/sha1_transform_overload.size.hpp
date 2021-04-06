/**
 * @file       sha1_transform_overload.size.hpp
 * @brief
 * @date       2024-10-06
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_HASH_SHA1_DETAIL_SHA1_TRANSFORM_OVERLOAD_SHA1_TRANSFORM_OVERLOAD_SIZE_HPP
#define KERBAL_HASH_SHA1_DETAIL_SHA1_TRANSFORM_OVERLOAD_SHA1_TRANSFORM_OVERLOAD_SIZE_HPP

#include <kerbal/config/library_export.hpp>

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
			class SHA1_transform_overload<kerbal::hash::SHA1_policy::size> :
				protected kerbal::hash::detail::SHA1_context_base
			{
				protected:

#		if __cplusplus >= 201103L
					constexpr
					SHA1_transform_overload() = default;
#		endif

					KERBAL_CONSTEXPR14
					static
					void update_w(uint32_t w[20]) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					void transform(const uint8_t buffer[64]) KERBAL_NOEXCEPT;

			};

#	if KERBAL_LIBRARY_EXPORT

			KERBAL_CONSTEXPR14
			inline
			void
			SHA1_transform_overload<SHA1_policy::size>::
			update_w(uint32_t w[20]) KERBAL_NOEXCEPT
			{
				w[0] = kerbal::numeric::rotl(w[17] ^ w[12] ^ w[6] ^ w[4], 1);
				w[1] = kerbal::numeric::rotl(w[18] ^ w[13] ^ w[7] ^ w[5], 1);
				w[2] = kerbal::numeric::rotl(w[19] ^ w[14] ^ w[8] ^ w[6], 1);
				w[3] = kerbal::numeric::rotl(w[0] ^ w[15] ^ w[9] ^ w[7], 1);
				w[4] = kerbal::numeric::rotl(w[1] ^ w[16] ^ w[10] ^ w[8], 1);
				w[5] = kerbal::numeric::rotl(w[2] ^ w[17] ^ w[11] ^ w[9], 1);
				w[6] = kerbal::numeric::rotl(w[3] ^ w[18] ^ w[12] ^ w[10], 1);
				w[7] = kerbal::numeric::rotl(w[4] ^ w[19] ^ w[13] ^ w[11], 1);
				w[8] = kerbal::numeric::rotl(w[5] ^ w[0] ^ w[14] ^ w[12], 1);
				w[9] = kerbal::numeric::rotl(w[6] ^ w[1] ^ w[15] ^ w[13], 1);
				w[10] = kerbal::numeric::rotl(w[7] ^ w[2] ^ w[16] ^ w[14], 1);
				w[11] = kerbal::numeric::rotl(w[8] ^ w[3] ^ w[17] ^ w[15], 1);
				w[12] = kerbal::numeric::rotl(w[9] ^ w[4] ^ w[18] ^ w[16], 1);
				w[13] = kerbal::numeric::rotl(w[10] ^ w[5] ^ w[19] ^ w[17], 1);
				w[14] = kerbal::numeric::rotl(w[11] ^ w[6] ^ w[0] ^ w[18], 1);
				w[15] = kerbal::numeric::rotl(w[12] ^ w[7] ^ w[1] ^ w[19], 1);
				w[16] = kerbal::numeric::rotl(w[13] ^ w[8] ^ w[2] ^ w[0], 1);
				w[17] = kerbal::numeric::rotl(w[14] ^ w[9] ^ w[3] ^ w[1], 1);
				w[18] = kerbal::numeric::rotl(w[15] ^ w[10] ^ w[4] ^ w[2], 1);
				w[19] = kerbal::numeric::rotl(w[16] ^ w[11] ^ w[5] ^ w[3], 1);
			}

			KERBAL_CONSTEXPR14
			KERBAL_SYMBOL_EXPORT
			void
			SHA1_transform_overload<SHA1_policy::size>::
			transform(const uint8_t buffer[64]) KERBAL_NOEXCEPT
			{
				uint32_t w[20] = {};
				for (int i = 0; i < 16; ++i) {
					w[i] = char4tolong1<BYTE_ORDER>(buffer + 4 * i);
				}
				for (int i = 16; i < 20; ++i) {
					w[i] = kerbal::numeric::rotl(w[i - 16] ^ w[i - 14] ^ w[i - 8] ^ w[i - 3], 1);
				}

				/* Copy context->state[] to working vars */
				uint32_t a = this->state[0];
				uint32_t b = this->state[1];
				uint32_t c = this->state[2];
				uint32_t d = this->state[3];
				uint32_t e = this->state[4];

				uint32_t * ww = w;
				for (int i = 0; i < 4; ++i) {
					R1(ww, a, b, c, d, e, 0);
					R1(ww, e, a, b, c, d, 1);
					R1(ww, d, e, a, b, c, 2);
					R1(ww, c, d, e, a, b, 3);
					R1(ww, b, c, d, e, a, 4);
					ww += 5;
				}

				update_w(w);

				ww = w;
				for (int i = 0; i < 4; ++i) {
					R2(ww, a, b, c, d, e, 0);
					R2(ww, e, a, b, c, d, 1);
					R2(ww, d, e, a, b, c, 2);
					R2(ww, c, d, e, a, b, 3);
					R2(ww, b, c, d, e, a, 4);
					ww += 5;
				}

				update_w(w);

				ww = w;
				for (int i = 0; i < 4; ++i) {
					R3(ww, a, b, c, d, e, 0);
					R3(ww, e, a, b, c, d, 1);
					R3(ww, d, e, a, b, c, 2);
					R3(ww, c, d, e, a, b, 3);
					R3(ww, b, c, d, e, a, 4);
					ww += 5;
				}

				update_w(w);

				ww = w;
				for (int i = 0; i < 4; ++i) {
					R4(ww, a, b, c, d, e, 0);
					R4(ww, e, a, b, c, d, 1);
					R4(ww, d, e, a, b, c, 2);
					R4(ww, c, d, e, a, b, 3);
					R4(ww, b, c, d, e, a, 4);
					ww += 5;
				}

				/* Add the working vars back into context.state[] */
				this->state[0] += a;
				this->state[1] += b;
				this->state[2] += c;
				this->state[3] += d;
				this->state[4] += e;
			}

#	endif // KERBAL_LIBRARY_EXPORT

		} // namespace detail

	} // namespace hash

} // namespace kerbal

#endif // KERBAL_HASH_SHA1_DETAIL_SHA1_TRANSFORM_OVERLOAD_SHA1_TRANSFORM_OVERLOAD_SIZE_HPP
