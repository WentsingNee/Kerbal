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

#include <kerbal/algorithm/modifier.hpp>
#include <kerbal/algorithm/sequence_compare.hpp>
#include <kerbal/numeric/bit.hpp>
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
					static bool all_chunk(const block_type block[], block_width_type trunk_size) KERBAL_NOEXCEPT
					{

#		ifndef KERBAL_STATIC_BITSET_ALL_CHUNK_POLICY
#			if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU
#				define KERBAL_STATIC_BITSET_ALL_CHUNK_POLICY 1
#			elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_CLANG
#				define KERBAL_STATIC_BITSET_ALL_CHUNK_POLICY 2
#			endif
#		endif

#		ifndef KERBAL_STATIC_BITSET_ALL_CHUNK_POLICY
#			define KERBAL_STATIC_BITSET_ALL_CHUNK_POLICY 0
#		endif


#				define EACH(idx) if (block[idx] != ALL_ONE::value) {return false;}

#					if KERBAL_STATIC_BITSET_ALL_CHUNK_POLICY==0

						size_t i = 0;
						for (; i + 4 <= trunk_size; i += 4) {
							EACH(i);
							EACH(i + 1);
							EACH(i + 2);
							EACH(i + 3);
						}

						size_t remain(trunk_size % 4);
						if (remain >= 2) {
							EACH(i);
							EACH(i + 1);
							i += 2;
							remain -= 2;
						}
						if (remain >= 1) {
							EACH(i);
						}

#					elif KERBAL_STATIC_BITSET_ALL_CHUNK_POLICY==1

						size_t i = 0;
						for (; i + 4 <= trunk_size; i += 4) {
							if ((block[i] & block[i + 1] & block[i + 2] & block[i + 3]) != ALL_ONE::value) {
								return false;
							}
						}

						size_t remain(trunk_size % 4);
						if (remain >= 2) {
							if ((block[i] & block[i + 1]) != ALL_ONE::value) {
								return false;
							}
							i += 2;
							remain -= 2;
						}
						if (remain >= 1) {
							if (block[i] != ALL_ONE::value) {
								return false;
							}
						}

#					elif KERBAL_STATIC_BITSET_ALL_CHUNK_POLICY==2

						size_t i = 0;
						for (; i + 8 <= trunk_size; i += 8) {
							if ((
									block[i] & block[i + 1] & block[i + 2] & block[i + 3] &
									block[i + 4] & block[i + 5] & block[i + 6] & block[i + 7]
							) != ALL_ONE::value) {
								return false;
							}
						}

						size_t remain(trunk_size % 8);
						if (remain >= 4) {
							if ((
									block[i] & block[i + 1] & block[i + 2] & block[i + 3]
							) != ALL_ONE::value) {
								return false;
							}
							i += 4;
							remain -= 4;
						}
						if (remain >= 2) {
							if ((block[i] & block[i + 1]) != ALL_ONE::value) {
								return false;
							}
							i += 2;
							remain -= 2;
						}
						if (remain >= 1) {
							if (block[i] != ALL_ONE::value) {
								return false;
							}
						}

#					else
#						error "unrecognized value of macro KERBAL_STATIC_BITSET_ALL_CHUNK_POLICY"
#					endif

#				undef EACH

						return true;
					}

					KERBAL_CONSTEXPR14
					static bool any_chunk(const block_type block[], block_width_type trunk_size) KERBAL_NOEXCEPT
					{

#		ifndef KERBAL_STATIC_BITSET_ANY_CHUNK_POLICY
#			if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU
#				define KERBAL_STATIC_BITSET_ANY_CHUNK_POLICY 1
#			elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_CLANG
#				define KERBAL_STATIC_BITSET_ANY_CHUNK_POLICY 2
#			endif
#		endif

#		ifndef KERBAL_STATIC_BITSET_ANY_CHUNK_POLICY
#			define KERBAL_STATIC_BITSET_ANY_CHUNK_POLICY 0
#		endif

#				define EACH(idx) if (block[idx]) {return true;}

#					if KERBAL_STATIC_BITSET_ANY_CHUNK_POLICY==0

						size_t i = 0;
						for (; i + 4 <= trunk_size; i += 4) {
							EACH(i);
							EACH(i + 1);
							EACH(i + 2);
							EACH(i + 3);
						}

						size_t remain(trunk_size % 4);
						if (remain >= 2) {
							EACH(i);
							EACH(i + 1);
							i += 2;
							remain -= 2;
						}
						if (remain >= 1) {
							EACH(i);
						}

#					elif KERBAL_STATIC_BITSET_ANY_CHUNK_POLICY==1

						size_t i = 0;
						for (; i + 4 <= trunk_size; i += 4) {
							if (block[i] | block[i + 1] | block[i + 2] | block[i + 3]) {
								return true;
							}
						}

						size_t remain(trunk_size % 4);
						if (remain >= 2) {
							if (block[i] | block[i + 1]) {
								return true;
							}
							i += 2;
							remain -= 2;
						}
						if (remain >= 1) {
							if (block[i]) {
								return true;
							}
						}

#					elif KERBAL_STATIC_BITSET_ANY_CHUNK_POLICY==2

						size_t i = 0;
						for (; i + 8 <= trunk_size; i += 8) {
							if (
									block[i] | block[i + 1] | block[i + 2] | block[i + 3] |
									block[i + 4] | block[i + 5] | block[i + 6] | block[i + 7]
							) {
								return true;
							}
						}

						size_t remain(trunk_size % 8);
						if (remain >= 4) {
							if (block[i] | block[i + 1] | block[i + 2] | block[i + 3]) {
								return true;
							}
							i += 4;
							remain -= 4;
						}
						if (remain >= 2) {
							if (block[i] | block[i + 1]) {
								return true;
							}
							i += 2;
							remain -= 2;
						}
						if (remain >= 1) {
							if (block[i]) {
								return true;
							}
						}

#					else
#						error "unrecognized value of macro KERBAL_STATIC_BITSET_ANY_CHUNK_POLICY"
#					endif

#				undef EACH

						return false;
					}

					KERBAL_CONSTEXPR14
					static size_t count_chunk(const block_type block[], block_width_type block_width) KERBAL_NOEXCEPT
					{
						size_t cnt = 0;

#				define EACH(idx) cnt += kerbal::numeric::popcount(block[idx]);

						size_t i = 0;
						for (; i + 4 <= block_width; i += 4) {
							EACH(i);
							EACH(i + 1);
							EACH(i + 2);
							EACH(i + 3);
						}

						size_t remain(block_width % 4);
						if (remain >= 2) {
							EACH(i);
							EACH(i + 1);
							i += 2;
							remain -= 2;
						}
						if (remain >= 1) {
							EACH(i);
						}

						return cnt;

#				undef EACH

					}

					KERBAL_CONSTEXPR14
					static void reset_chunk(block_type block[], block_width_type block_width) KERBAL_NOEXCEPT
					{
						kerbal::algorithm::fill(block, block + block_width, static_cast<block_type>(0));
					}

					KERBAL_CONSTEXPR14
					static void set_chunk(block_type block[], block_width_type block_width) KERBAL_NOEXCEPT
					{
						kerbal::algorithm::fill(block, block + block_width, ALL_ONE::value);
					}

					KERBAL_CONSTEXPR14
					static void flip_chunk(block_type block[], block_width_type block_width) KERBAL_NOEXCEPT
					{

#				define EACH(idx) block[idx] = ~block[idx]

						size_t i = 0;
						for (; i + 4 <= block_width; i += 4) {
							EACH(i);
							EACH(i + 1);
							EACH(i + 2);
							EACH(i + 3);
						}

						size_t remain(block_width % 4);
						if (remain >= 2) {
							EACH(i);
							EACH(i + 1);
							i += 2;
							remain -= 2;
						}
						if (remain >= 1) {
							EACH(i);
						}

#				undef EACH

					}

					KERBAL_CONSTEXPR14
					static bool equal_chunk(const block_type block[], const block_type ano[], block_width_type trunk_size) KERBAL_NOEXCEPT
					{
						return kerbal::algorithm::sequence_equal_to(
								block, block + trunk_size,
								ano, ano + trunk_size
						);
					}

					KERBAL_CONSTEXPR14
					static void bit_and_assign(block_type block[], const block_type ano[], block_width_type block_width) KERBAL_NOEXCEPT
					{

#				define EACH(idx) block[idx] &= ano[idx]

						size_t i = 0;
						for (; i + 4 <= block_width; i += 4) {
							EACH(i);
							EACH(i + 1);
							EACH(i + 2);
							EACH(i + 3);
						}

						size_t remain(block_width % 4);
						if (remain >= 2) {
							EACH(i);
							EACH(i + 1);
							i += 2;
							remain -= 2;
						}
						if (remain >= 1) {
							EACH(i);
						}

#				undef EACH

					}

					KERBAL_CONSTEXPR14
					static void bit_or_assign(block_type block[], const block_type ano[], block_width_type block_width) KERBAL_NOEXCEPT
					{

#				define EACH(idx) block[idx] |= ano[idx]

						size_t i = 0;
						for (; i + 4 <= block_width; i += 4) {
							EACH(i);
							EACH(i + 1);
							EACH(i + 2);
							EACH(i + 3);
						}

						size_t remain(block_width % 4);
						if (remain >= 2) {
							EACH(i);
							EACH(i + 1);
							i += 2;
							remain -= 2;
						}
						if (remain >= 1) {
							EACH(i);
						}

#				undef EACH

					}

					KERBAL_CONSTEXPR14
					static void bit_xor_assign(block_type block[], const block_type ano[], block_width_type block_width) KERBAL_NOEXCEPT
					{

#				define EACH(idx) block[idx] ^= ano[idx]

						size_t i = 0;
						for (; i + 4 <= block_width; i += 4) {
							EACH(i);
							EACH(i + 1);
							EACH(i + 2);
							EACH(i + 3);
						}

						size_t remain(block_width % 4);
						if (remain >= 2) {
							EACH(i);
							EACH(i + 1);
							i += 2;
							remain -= 2;
						}
						if (remain >= 1) {
							EACH(i);
						}

#				undef EACH

					}

			};

		} // namespace detail

	} // namespace bitset

} //namespace kerbal


#endif // KERBAL_BITSET_DETAIL_BITSET_SIZE_UNRELATED_HPP
