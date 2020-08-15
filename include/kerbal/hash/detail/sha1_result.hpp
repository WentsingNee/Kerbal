/**
 * @file       sha1_result.hpp
 * @brief
 * @date       2019-8-11
 * @author     peter
 * @copyright
 *      peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_HASH_DETAIL_SHA1_RESULT_HPP
#define KERBAL_HASH_DETAIL_SHA1_RESULT_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/noexcept.hpp>

#include <ostream>
#include <string>

namespace kerbal
{

	namespace hash
	{

		class SHA1_result
		{
			private:
				template <typename Policy>
				friend class SHA1_context;

			private:
				unsigned char hash[20];

			private:
				KERBAL_CONSTEXPR14
				explicit SHA1_result(const kerbal::compatibility::uint32_t state[5]) KERBAL_NOEXCEPT

#	if __cplusplus >= 201103L
					: hash { }
#	endif

				{
					for (size_t i = 0; i < 20; ++i) {
						this->hash[i] = static_cast<unsigned char>((state[i >> 2u] >> ((3 - (i & 3u)) * 8)) & 255u);
					}
				}

				KERBAL_CONSTEXPR
				static char to_ocx(char c) KERBAL_NOEXCEPT
				{
					return static_cast<char>(c < 10 ? '0' + c : 'a' - 10 + c);
				}

			public:
				friend
				std::ostream& operator<<(std::ostream& out, const SHA1_result & result)
				{
					char tmp[3];
					tmp[2] = '\0';
					for (size_t i = 0; i < 20; ++i) {
						tmp[0] = to_ocx(static_cast<char>(result.hash[i] >> 4u));
						tmp[1] = to_ocx(static_cast<char>(result.hash[i] % 16u));
						out << tmp;
					}
					return out;
				}

				operator std::string() const
				{
					std::string s;
					s.reserve(40);
					for (size_t i = 0; i < 20; ++i) {
						s.push_back(to_ocx(static_cast<char>(hash[i] >> 4u)));
						s.push_back(to_ocx(static_cast<char>(hash[i] % 16u)));
					}
					return s;
				}

				KERBAL_CONSTEXPR14
				const unsigned char * data() const KERBAL_NOEXCEPT
				{
					return this->hash;
				}

		};

	} // namespace hash

} // namespace kerbal

#endif // KERBAL_HASH_DETAIL_SHA1_RESULT_HPP
