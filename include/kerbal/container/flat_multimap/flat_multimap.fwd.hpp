/**
 * @file       flat_multimap.fwd.hpp
 * @brief
 * @date       2024-10-17
 * @author     peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_FLAT_MULTIMAP_FLAT_MULTIMAP_FWD_HPP
#define KERBAL_CONTAINER_FLAT_MULTIMAP_FLAT_MULTIMAP_FWD_HPP

#include <kerbal/compare/basic_compare.hpp>
#include <kerbal/container/associative_container_facility/map_data.hpp>

#include <memory>


namespace kerbal
{

	namespace container
	{

		template <
			typename K, typename M,
			typename KeyCompare = kerbal::compare::less<K>,
			typename Allocator = std::allocator<kerbal::container::map_data<K, M> >
		>
		class flat_multimap;

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_FLAT_MULTIMAP_FLAT_MULTIMAP_FWD_HPP
