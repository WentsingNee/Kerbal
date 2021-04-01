/**
 * @file       md5_transform_overload.fast.hpp
 * @brief
 * @date       2024-10-11
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_HASH_MD5_DETAIL_MD5_TRANSFORM_OVERLOAD_MD5_TRANSFORM_OVERLOAD_FAST_HPP
#define KERBAL_HASH_MD5_DETAIL_MD5_TRANSFORM_OVERLOAD_MD5_TRANSFORM_OVERLOAD_FAST_HPP

#include <kerbal/hash/md5/md5.fwd.hpp>
#include <kerbal/hash/md5/detail/md5_context_base.hpp>

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
			class MD5_transform_overload<kerbal::hash::MD5_policy::fast> :
				protected kerbal::hash::detail::MD5_context_base
			{
				protected:

#			if __cplusplus >= 201103L
					constexpr
					MD5_transform_overload() = default;
#			endif

					KERBAL_CONSTEXPR14
					void transform(const unsigned char buffer[64]) KERBAL_NOEXCEPT;

			};

			KERBAL_CONSTEXPR14
			inline
			void
			MD5_transform_overload<MD5_policy::fast>::
			transform(const unsigned char buffer[64]) KERBAL_NOEXCEPT
			{
				uint32_t l[16] = {};
				for (int i = 0; i < 16; ++i) {
					l[i] = char4tolong1(buffer + 4 * i);
				}

				/* Copy context->state[] to working vars */
				uint32_t a = this->a;
				uint32_t b = this->b;
				uint32_t c = this->c;
				uint32_t d = this->d;

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
				this->a += a;
				this->b += b;
				this->c += c;
				this->d += d;
			}

		} // namespace detail

	} // namespace hash

} // namespace kerbal

#endif // KERBAL_HASH_MD5_DETAIL_MD5_TRANSFORM_OVERLOAD_MD5_TRANSFORM_OVERLOAD_FAST_HPP
