/**
 * @file       static_bitset.fwd.hpp
 * @brief
 * @date       2021-10-10
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_BITSET_STATIC_BITSET_STATIC_BITSET_FWD_HPP
#define KERBAL_BITSET_STATIC_BITSET_STATIC_BITSET_FWD_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/bitset/detail/default_block_type.hpp>

#include <cstddef>


namespace kerbal
{

	namespace bitset
	{

		KERBAL_MODULE_EXPORT
		template <std::size_t N, typename Block = KERBAL_BITSET_DEFAULT_BLOCK_TYPE>
		class static_bitset;

	} // namespace bitset

} // namespace kerbal

#endif // KERBAL_BITSET_STATIC_BITSET_STATIC_BITSET_FWD_HPP
