/**
 * @file       md5_result.hpp
 * @brief
 * @date       2024-10-11
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_HASH_MD5_MD5_RESULT_HPP
#define KERBAL_HASH_MD5_MD5_RESULT_HPP

#include <kerbal/hash/md5/md5.fwd.hpp>

#include <kerbal/compare/sequence_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/operators/equality_comparable.hpp>
#include <kerbal/operators/less_than_comparable.hpp>

#include <cstddef>
#include <ostream>
#include <string>


namespace kerbal
{

	namespace hash
	{

		class MD5_result
		{
			private:
				template <typename Policy>
				friend class kerbal::hash::MD5_context;

			private:
				unsigned char hash[16];

			private:
				KERBAL_CONSTEXPR14
				explicit MD5_result(
					kerbal::compatibility::uint32_t a,
					kerbal::compatibility::uint32_t b,
					kerbal::compatibility::uint32_t c,
					kerbal::compatibility::uint32_t d
				) KERBAL_NOEXCEPT

#	if __cplusplus >= 201103L
					: hash { }
#	endif

				{
					this->hash[0] = static_cast<unsigned char>((a >> (0 * 8)) & 255u);
					this->hash[1] = static_cast<unsigned char>((a >> (1 * 8)) & 255u);
					this->hash[2] = static_cast<unsigned char>((a >> (2 * 8)) & 255u);
					this->hash[3] = static_cast<unsigned char>((a >> (3 * 8)) & 255u);

					this->hash[4] = static_cast<unsigned char>((b >> (0 * 8)) & 255u);
					this->hash[5] = static_cast<unsigned char>((b >> (1 * 8)) & 255u);
					this->hash[6] = static_cast<unsigned char>((b >> (2 * 8)) & 255u);
					this->hash[7] = static_cast<unsigned char>((b >> (3 * 8)) & 255u);

					this->hash[8] = static_cast<unsigned char>((c >> (0 * 8)) & 255u);
					this->hash[9] = static_cast<unsigned char>((c >> (1 * 8)) & 255u);
					this->hash[10] = static_cast<unsigned char>((c >> (2 * 8)) & 255u);
					this->hash[11] = static_cast<unsigned char>((c >> (3 * 8)) & 255u);

					this->hash[12] = static_cast<unsigned char>((d >> (0 * 8)) & 255u);
					this->hash[13] = static_cast<unsigned char>((d >> (1 * 8)) & 255u);
					this->hash[14] = static_cast<unsigned char>((d >> (2 * 8)) & 255u);
					this->hash[15] = static_cast<unsigned char>((d >> (3 * 8)) & 255u);

				}

				KERBAL_CONSTEXPR
				static char to_ocx(char c) KERBAL_NOEXCEPT
				{
					return static_cast<char>(c < 10 ? '0' + c : 'a' - 10 + c);
				}

			public:
				friend
				std::ostream & operator<<(std::ostream & out, const MD5_result & result)
				{
					char tmp[33];
					tmp[32] = '\0';
					for (std::size_t i = 0; i < 16; ++i) {
						tmp[i * 2 + 0] = to_ocx(static_cast<char>(result.hash[i] >> 4u));
						tmp[i * 2 + 1] = to_ocx(static_cast<char>(result.hash[i] % 16u));
					}
					out << tmp;
					return out;
				}

				operator std::string() const
				{
					char tmp[33];
					tmp[32] = '\0';
					for (std::size_t i = 0; i < 16; ++i) {
						tmp[i * 2 + 0] = to_ocx(static_cast<char>(hash[i] >> 4u));
						tmp[i * 2 + 1] = to_ocx(static_cast<char>(hash[i] % 16u));
					}
					return std::string(tmp);
				}

				KERBAL_CONSTEXPR14
				const unsigned char * data() const KERBAL_NOEXCEPT
				{
					return this->hash;
				}

				KERBAL_CONSTEXPR14
				friend
				bool operator==(
					kerbal::hash::SHA1_result const & lhs,
					kerbal::hash::SHA1_result const & rhs
				) KERBAL_NOEXCEPT
				{
					return kerbal::compare::sequence_equal_to(
						lhs.hash, lhs.hash + 20,
						rhs.hash, rhs.hash + 20
					);
				}

				KERBAL_CONSTEXPR14
				friend
				bool operator<(
					kerbal::hash::SHA1_result const & lhs,
					kerbal::hash::SHA1_result const & rhs
				) KERBAL_NOEXCEPT
				{
					return kerbal::compare::sequence_less(
						lhs.hash, lhs.hash + 20,
						rhs.hash, rhs.hash + 20
					);
				}

		};

	} // namespace hash

} // namespace kerbal

#endif // KERBAL_HASH_MD5_MD5_RESULT_HPP
