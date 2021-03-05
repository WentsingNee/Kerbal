/**
 * @file       bitset_size_unrelated.hpp
 * @brief
 * @date       2020-08-12
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_BITSET_DETAIL_BITSET_SIZE_UNRELATED_HPP
#define KERBAL_BITSET_DETAIL_BITSET_SIZE_UNRELATED_HPP

#include <kerbal/algorithm/sequence_compare.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <climits>
#include <cstddef>


namespace kerbal
{

	namespace bitset
	{

		namespace detail
		{

			template <typename Block>
			struct bitset_bits_per_block
					: kerbal::type_traits::integral_constant<size_t, CHAR_BIT * sizeof(Block)>
			{
			};

			template <typename Block>
			class bitset_size_unrelated
			{
				public:
					typedef Block										block_type;
					typedef detail::bitset_bits_per_block<Block>		BITS_PER_BLOCK;
					typedef size_t										block_width_type;

				protected:
					typedef kerbal::type_traits::integral_constant<block_type, static_cast<block_type>(~static_cast<block_type>(0))> ALL_ONE;

					KERBAL_CONSTEXPR14
					static bool all_trunk(const block_type m_block[], block_width_type trunk_size) KERBAL_NOEXCEPT
					{

#				define EACH(idx) if (m_block[idx] != ALL_ONE::value) {return false;}

							for (size_t i = 0; i + 4 <= trunk_size; i += 4) {
								EACH(i);
								EACH(i + 1);
								EACH(i + 2);
								EACH(i + 3);
							}

							switch (trunk_size % 4) {
								case 3:
									EACH(trunk_size - 3);
								case 2:
									EACH(trunk_size - 2);
								case 1:
									EACH(trunk_size - 1);
							}

#				undef EACH

							return true;
					}

					KERBAL_CONSTEXPR14
					static bool any_trunk(const block_type m_block[], block_width_type trunk_size) KERBAL_NOEXCEPT
					{

#				define EACH(idx) if (m_block[idx]) {return true;}

						for (size_t i = 0; i + 4 <= trunk_size; i += 4) {
							EACH(i);
							EACH(i + 1);
							EACH(i + 2);
							EACH(i + 3);
						}

						switch (trunk_size % 4) {
							case 3:
								EACH(trunk_size - 3);
							case 2:
								EACH(trunk_size - 2);
							case 1:
								EACH(trunk_size - 1);
						}

#				undef EACH

						return false;
					}

					KERBAL_CONSTEXPR14
					static void flip(block_type m_block[], block_width_type block_width) KERBAL_NOEXCEPT
					{

#				define EACH(idx) m_block[idx] = ~m_block[idx]

						for (size_t i = 0; i + 4 <= block_width; i += 4) {
							EACH(i);
							EACH(i + 1);
							EACH(i + 2);
							EACH(i + 3);
						}

						switch (block_width % 4) {
							case 3:
								EACH(block_width - 3);
							case 2:
								EACH(block_width - 2);
							case 1:
								EACH(block_width - 1);
						}

#				undef EACH

					}

					KERBAL_CONSTEXPR14
					static bool equal_trunk(const block_type m_block[], const block_type ano[], block_width_type trunk_size) KERBAL_NOEXCEPT
					{
						return kerbal::algorithm::sequence_equal_to(
								m_block, m_block + trunk_size,
								ano, ano + trunk_size
						);
					}

					KERBAL_CONSTEXPR14
					static void bit_and_assign(block_type m_block[], const block_type ano[], block_width_type block_width) KERBAL_NOEXCEPT
					{

#				define EACH(idx) m_block[idx] &= ano[idx]

						for (size_t i = 0; i + 4 <= block_width; i += 4) {
							EACH(i);
							EACH(i + 1);
							EACH(i + 2);
							EACH(i + 3);
						}

						switch (block_width % 4) {
							case 3:
								EACH(block_width - 3);
							case 2:
								EACH(block_width - 2);
							case 1:
								EACH(block_width - 1);
						}

#				undef EACH

					}

					KERBAL_CONSTEXPR14
					static void bit_or_assign(block_type m_block[], const block_type ano[], block_width_type block_width) KERBAL_NOEXCEPT
					{

#				define EACH(idx) m_block[idx] |= ano[idx]

						for (size_t i = 0; i + 4 <= block_width; i += 4) {
							EACH(i);
							EACH(i + 1);
							EACH(i + 2);
							EACH(i + 3);
						}

						switch (block_width % 4) {
							case 3:
								EACH(block_width - 3);
							case 2:
								EACH(block_width - 2);
							case 1:
								EACH(block_width - 1);
						}

#				undef EACH

					}

					KERBAL_CONSTEXPR14
					static void bit_xor_assign(block_type m_block[], const block_type ano[], block_width_type block_width) KERBAL_NOEXCEPT
					{

#				define EACH(idx) m_block[idx] ^= ano[idx]

						for (size_t i = 0; i + 4 <= block_width; i += 4) {
							EACH(i);
							EACH(i + 1);
							EACH(i + 2);
							EACH(i + 3);
						}

						switch (block_width % 4) {
							case 3:
								EACH(block_width - 3);
							case 2:
								EACH(block_width - 2);
							case 1:
								EACH(block_width - 1);
						}

#				undef EACH

					}

			};

		} // namespace detail

	} // namespace bitset

} //namespace kerbal


#endif // KERBAL_BITSET_DETAIL_BITSET_SIZE_UNRELATED_HPP
