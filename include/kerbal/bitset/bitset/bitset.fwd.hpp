/**
 * @file       bitset.fwd.hpp
 * @brief
 * @date       2023-12-13
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_BITSET_BITSET_BITSET_FWD_HPP
#define KERBAL_BITSET_BITSET_BITSET_FWD_HPP

#include <kerbal/bitset/detail/default_block_type.hpp>

#include <memory>


namespace kerbal
{

	namespace bitset
	{

		template <
			typename Block = KERBAL_BITSET_DEFAULT_BLOCK_TYPE,
			typename Allocator = std::allocator<Block>
		>
		class bitset;

	} // namespace bitset

} // namespace kerbal

#endif // KERBAL_BITSET_BITSET_BITSET_FWD_HPP
