/**
 * @file       all_chunk.plain.hpp
 * @brief
 * @date       2022-11-09
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_BITSET_DETAIL_ALL_CHUNK_ALL_CHUNK_PLAIN_HPP
#define KERBAL_BITSET_DETAIL_ALL_CHUNK_ALL_CHUNK_PLAIN_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>


namespace kerbal
{

	namespace bitset
	{

		namespace detail
		{

			namespace plain
			{

#			define EACH(idx) if (block[idx] != ALL_ONE::value) {return false;}

				template <typename Block>
				KERBAL_CONSTEXPR14
				bool all_chunk0(const Block block[], std::size_t trunk_size) KERBAL_NOEXCEPT
				{
					typedef kerbal::type_traits::integral_constant<Block, static_cast<Block>(~static_cast<Block>(0))> ALL_ONE;

					std::size_t i = 0;
					for (; i < trunk_size; ++i) {
						EACH(i);
					}
					return true;
				}

				template <typename Block>
				KERBAL_CONSTEXPR14
				bool all_chunk(const Block block[], std::size_t trunk_size) KERBAL_NOEXCEPT
				{
					typedef kerbal::type_traits::integral_constant<Block, static_cast<Block>(~static_cast<Block>(0))> ALL_ONE;

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


#				if KERBAL_STATIC_BITSET_ALL_CHUNK_POLICY==0

					std::size_t i = 0;
					for (; i + 4 <= trunk_size; i += 4) {
						EACH(i);
						EACH(i + 1);
						EACH(i + 2);
						EACH(i + 3);
					}

					std::size_t remain(trunk_size % 4);
					if (remain >= 2) {
						EACH(i);
						EACH(i + 1);
						i += 2;
						remain -= 2;
					}
					if (remain >= 1) {
						EACH(i);
					}

#				elif KERBAL_STATIC_BITSET_ALL_CHUNK_POLICY==1

					std::size_t i = 0;
					for (; i + 4 <= trunk_size; i += 4) {
						if ((block[i] & block[i + 1] & block[i + 2] & block[i + 3]) != ALL_ONE::value) {
							return false;
						}
					}

					std::size_t remain(trunk_size % 4);
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

#				elif KERBAL_STATIC_BITSET_ALL_CHUNK_POLICY==2

					std::size_t i = 0;
					for (; i + 8 <= trunk_size; i += 8) {
						if ((
								block[i] & block[i + 1] & block[i + 2] & block[i + 3] &
								block[i + 4] & block[i + 5] & block[i + 6] & block[i + 7]
						) != ALL_ONE::value) {
							return false;
						}
					}

					std::size_t remain(trunk_size % 8);
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

#				else
#					error "unrecognized value of macro KERBAL_STATIC_BITSET_ALL_CHUNK_POLICY"
#				endif

					return true;
				}

			} // namespace plain

		} // namespace detail

	} // namespace bitset

} // namespace kerbal


#endif // KERBAL_BITSET_DETAIL_ALL_CHUNK_ALL_CHUNK_PLAIN_HPP
