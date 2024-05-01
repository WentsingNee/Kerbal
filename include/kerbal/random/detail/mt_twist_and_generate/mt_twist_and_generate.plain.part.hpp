/**
 * @file       mt_twist_and_generate.plain.part.hpp
 * @brief
 * @date       2024-05-01
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_DETAIL_MT_TWIST_AND_GENERATE_MT_TWIST_AND_GENERATE_PLAIN_PART_HPP
#define KERBAL_RANDOM_DETAIL_MT_TWIST_AND_GENERATE_MT_TWIST_AND_GENERATE_PLAIN_PART_HPP

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

#		define EACH() \
				do { \
					z ^= (z >> U) & D; \
					z ^= (z << S) & B; \
					z ^= (z << T) & C; \
					z ^= z >> L;       \
					*out = z;          \
					++out;             \
				} while (false)


#		define EACH1(i) \
				do { \
					result_type y = (mt[i] & UPPER_MASK::value) | (mt[(i) + 1] & LOWER_MASK::value); \
					result_type z = mt[(i) + M] ^ (y >> 1) ^ ((y & 0x1UL) ? A : 0); \
					mt[i] = z; \
					EACH(); \
				} while (false)

#		define EACH2(i) \
				do { \
					result_type y = (mt[i] & UPPER_MASK::value) | (mt[(i) + 1] & LOWER_MASK::value); \
					result_type z = mt[(i) - (NPM::value)] ^ (y >> 1) ^ ((y & 0x1UL) ? A : 0); \
					mt[i] = z; \
					EACH(); \
				} while (false)

#		define EACH3() \
				do { \
					result_type y = (mt[N - 1] & UPPER_MASK::value) | (mt[0] & LOWER_MASK::value); \
					result_type z = mt[M - 1] ^ (y >> 1) ^ ((y & 0x1UL) ? A : 0); \
					mt[N - 1] = z; \
					EACH(); \
				} while (false)

			namespace plain
			{

				template <
					typename UIntType, typename OutputIterator,
					std::size_t N, std::size_t M, std::size_t R, UIntType A,
					std::size_t U, UIntType D,
					std::size_t S, UIntType B,
					std::size_t T, UIntType C,
					std::size_t L
				>
				KERBAL_CONSTEXPR14
				void mt_twist_and_generate(
					UIntType mt[N],
					OutputIterator out
				) KERBAL_NOEXCEPT
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
					EACH3();
				}

			} // namespace plain

		} // namespace detail

	} // namespace random

} // namespace kerbal


#endif // KERBAL_RANDOM_DETAIL_MT_TWIST_AND_GENERATE_MT_TWIST_AND_GENERATE_PLAIN_PART_HPP
