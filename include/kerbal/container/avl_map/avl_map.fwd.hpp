/**
 * @file       avl_map.fwd.hpp
 * @brief
 * @date       2022-09-09
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_AVL_MAP_AVL_MAP_FWD_HPP
#define KERBAL_CONTAINER_AVL_MAP_AVL_MAP_FWD_HPP

#include <kerbal/compare/binary_type_compare.hpp>
#include <kerbal/container/associative_container_facility/map_data.hpp>

#include <memory>


namespace kerbal
{

	namespace container
	{

		template <
			typename K, typename M,
			typename KeyCompare = kerbal::compare::binary_type_less<void, void>,
			typename Allocator = std::allocator<kerbal::container::map_data<K, M> >
		>
		class avl_map;

	} // namespace container

} // namespace kerbal


#endif // KERBAL_CONTAINER_AVL_MAP_AVL_MAP_FWD_HPP
