/**
 * @file       static_flat_map.fwd.hpp
 * @brief
 * @date       2024-03-07
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_STATIC_FLAT_MAP_STATIC_FLAT_MAP_FWD_HPP
#define KERBAL_CONTAINER_STATIC_FLAT_MAP_STATIC_FLAT_MAP_FWD_HPP

#include <kerbal/compare/binary_type_compare.hpp>

#include <cstddef>


namespace kerbal
{

	namespace container
	{

		template <
			typename K, typename M,
			std::size_t N,
			typename KeyCompare = kerbal::compare::binary_type_less<void, void>
		>
		class static_flat_map;

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_STATIC_FLAT_MAP_STATIC_FLAT_MAP_FWD_HPP
