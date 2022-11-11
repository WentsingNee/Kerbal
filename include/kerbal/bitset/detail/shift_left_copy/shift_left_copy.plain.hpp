/**
 * @file       shift_left_copy.plain.hpp
 * @brief
 * @date       2022-11-10
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_BITSET_DETAIL_SHIFT_LEFT_COPY_SHIFT_LEFT_COPY_PLAIN_HPP
#define KERBAL_BITSET_DETAIL_SHIFT_LEFT_COPY_SHIFT_LEFT_COPY_PLAIN_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>
#include <climits>


namespace kerbal
{

	namespace bitset
	{

		namespace detail
		{

			namespace plain
			{

#			define EACH(i) do { \
					out[i] = (block[i] >> inner_ofs) | (block[(i) + 1] << ano_ofs); \
				} while (false)

				template <typename Block>
				KERBAL_CONSTEXPR14
				void shift_left_copy(const Block block[], std::size_t n, std::size_t inner_ofs, Block out[]) KERBAL_NOEXCEPT
				{
					typedef kerbal::type_traits::integral_constant<std::size_t, CHAR_BIT * sizeof(Block)> BITS_PER_BLOCK;

					const std::size_t ano_ofs = (BITS_PER_BLOCK::value - inner_ofs);
					std::size_t i = 0;
					while (i + 1 != n) {
						out[i] = (block[i] >> inner_ofs) | (block[i + 1] << ano_ofs);
						++i;
					}
				}

			} // namespace plain

		} // namespace detail

	} // namespace bitset

} // namespace kerbal


#endif // KERBAL_BITSET_DETAIL_SHIFT_LEFT_COPY_SHIFT_LEFT_COPY_PLAIN_HPP
