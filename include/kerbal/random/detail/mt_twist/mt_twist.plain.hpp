/**
 * @file       mt_twist.plain.hpp
 * @brief
 * @date       2022-11-02
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_DETAIL_MT_TWIST_MT_TWIST_PLAIN_HPP
#define KERBAL_RANDOM_DETAIL_MT_TWIST_MT_TWIST_PLAIN_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>


namespace kerbal
{

	namespace random
	{

		namespace detail
		{

#		define EACH1(i) \
				do { \
					result_type y = (mt[i] & UPPER_MASK::value) | (mt[(i) + 1] & LOWER_MASK::value); \
					mt[i] = mt[(i) + M] ^ (y >> 1) ^ ((y & 0x1UL) ? A : 0); \
				} while (0)

#		define EACH2(i) \
				do { \
					result_type y = (mt[i] & UPPER_MASK::value) | (mt[(i) + 1] & LOWER_MASK::value); \
					mt[i] = mt[(i) - (NPM::value)] ^ (y >> 1) ^ ((y & 0x1UL) ? A : 0); \
				} while (0)

			namespace plain
			{

				template <typename UIntType, std::size_t N, std::size_t M, std::size_t R, UIntType A>
				KERBAL_CONSTEXPR14
				void mt_twist(UIntType mt[N]) KERBAL_NOEXCEPT
				{
					typedef UIntType result_type;
					typedef kerbal::type_traits::integral_constant<result_type, (~static_cast<result_type>(0)) << R> UPPER_MASK; // most significant w-r bits
					typedef kerbal::type_traits::integral_constant<result_type, ~UPPER_MASK::value> LOWER_MASK; // least significant r bits
					KERBAL_STATIC_ASSERT(N >= M, "N should >= M");
					typedef kerbal::type_traits::integral_constant<std::size_t, N - M> NPM;

					std::size_t i = 0;

					for (; i < NPM::value; ++i) {
						EACH1(i);
					}
					for (; i < N - 1; ++i) {
						EACH2(i);
					}
					result_type y = (mt[N - 1] & UPPER_MASK::value) | (mt[0] & LOWER_MASK::value);
					mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ ((y & 0x1UL) ? A : 0);
				}

			} // namespace plain

		} // namespace detail

	} // namespace random

} // namespace kerbal


#endif // KERBAL_RANDOM_DETAIL_MT_TWIST_MT_TWIST_PLAIN_HPP
