/**
 * @file       mt_generate_copy_n.plain.part.hpp
 * @brief
 * @date       2022-11-07
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_DETAIL_MT_GENERATE_COPY_N_MT_GENERATE_COPY_N_PLAIN_PART_HPP
#define KERBAL_RANDOM_DETAIL_MT_GENERATE_COPY_N_MT_GENERATE_COPY_N_PLAIN_PART_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>

#include <cstddef>


namespace kerbal
{

	namespace random
	{

		namespace detail
		{

#		define EACH(i) \
				do { \
					result_type z = mt_now[i]; \
					z ^= (z >> U) & D; \
					z ^= (z << S) & B; \
					z ^= (z << T) & C; \
					z ^= z >> L;       \
					*out = z;          \
					++out;             \
				} while (false)

			namespace plain
			{

				template <
					typename UIntType, typename OutputIterator,
					std::size_t U, UIntType D,
					std::size_t S, UIntType B,
					std::size_t T, UIntType C,
					std::size_t L
				>
				KERBAL_CONSTEXPR14
				OutputIterator mt_generate_copy_n(
					const UIntType mt_now[],
					OutputIterator out,
					std::size_t n
				)
				{
					typedef UIntType result_type;

					std::size_t i = 0;
					while (i < n) {
						EACH(i);
						++i;
					}
					return out;
				}

			} // namespace plain

		} // namespace detail

	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_DETAIL_MT_GENERATE_COPY_N_MT_GENERATE_COPY_N_PLAIN_PART_HPP
