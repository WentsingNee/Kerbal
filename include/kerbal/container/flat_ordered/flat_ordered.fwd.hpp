/**
 * @file       flat_ordered.fwd.hpp
 * @brief
 * @date       2024-12-08
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_FLAT_ORDERED_FLAT_ORDERED_FWD_HPP
#define KERBAL_CONTAINER_FLAT_ORDERED_FLAT_ORDERED_FWD_HPP

#include <kerbal/compare/binary_type_compare.hpp>
#include <kerbal/container/associative_container_facility/key_extractors/identity_extractor.hpp>

#include <memory>


namespace kerbal
{

	namespace container
	{

		template <
			typename Entity,
			typename Extract = kerbal::container::identity_extractor<Entity>,
			typename KeyCompare = kerbal::compare::binary_type_less<void, void>,
			typename Allocator = std::allocator<Entity>
		>
		class flat_ordered;

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_FLAT_ORDERED_FLAT_ORDERED_FWD_HPP
