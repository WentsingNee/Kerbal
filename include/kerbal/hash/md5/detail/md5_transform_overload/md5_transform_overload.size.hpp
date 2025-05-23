/**
 * @file       md5_transform_overload.size.hpp
 * @brief
 * @date       2024-10-11
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_HASH_MD5_DETAIL_MD5_TRANSFORM_OVERLOAD_MD5_TRANSFORM_OVERLOAD_SIZE_HPP
#define KERBAL_HASH_MD5_DETAIL_MD5_TRANSFORM_OVERLOAD_MD5_TRANSFORM_OVERLOAD_SIZE_HPP

#include <kerbal/hash/detail/char4tolong1.hpp>
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
			class MD5_transform_overload<kerbal::hash::MD5_policy::size> :
				protected kerbal::hash::detail::MD5_context_base
			{
				protected:

#		if __cplusplus >= 201103L
					constexpr
					MD5_transform_overload() = default;
#		endif

					// warning: The function will read 64 unsigned char data from the iterator
					KERBAL_CONSTEXPR14
					void transform(const unsigned char buffer[64]) KERBAL_NOEXCEPT;

			};

			KERBAL_CONSTEXPR14
			inline
			void
			MD5_transform_overload<MD5_policy::size>::
			transform(const unsigned char buffer[64]) KERBAL_NOEXCEPT
			{
				KERBAL_CONSTEXPR
				uint32_t const K[] = {
					0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
					0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
					0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
					0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
					0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
					0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
					0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
					0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
					0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
					0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
					0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
					0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
					0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
					0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
					0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
					0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,
				};

				KERBAL_CONSTEXPR
				uint32_t const S[] = {
					 7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
					 5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
					 4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
					 6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,
				};

				uint32_t l[16] = {};
				for (int i = 0; i < 16; ++i) {
					l[i] = kerbal::hash::detail::char4tolong1<BIG_ENDIAN>(buffer + 4 * i);
				}

				uint32_t a = this->a;
				uint32_t b = this->b;
				uint32_t c = this->c;
				uint32_t d = this->d;

				for (int i = 0; i < 64; ++i) {
					uint32_t f = 0;
					uint32_t g = 0;
					if (i < 16) {
						f = F(b, c, d);
						g = i;
					} else if (i < 32) {
						f = G(b, c, d);
						g = (5 * i + 1) % 16;
					} else if (i < 48) {
						f = H(b, c, d);
						g = (3 * i + 5) % 16;
					} else {
						f = I(b, c, d);
						g = (7 * i) % 16;
					}
					f += a + K[i] + l[g];
					a = d;
					d = c;
					c = b;
					b = b + kerbal::numeric::rotl(f, S[i]);
				}

				this->a += a;
				this->b += b;
				this->c += c;
				this->d += d;
			}

		} // namespace detail

	} // namespace hash

} // namespace kerbal

#endif // KERBAL_HASH_MD5_DETAIL_MD5_TRANSFORM_OVERLOAD_MD5_TRANSFORM_OVERLOAD_SIZE_HPP
