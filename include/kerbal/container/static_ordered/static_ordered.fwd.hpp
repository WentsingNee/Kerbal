/**
 * @file       static_ordered.fwd.hpp
 * @brief
 * @date       2024-12-09
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_STATIC_ORDERED_STATIC_ORDERED_FWD_HPP
#define KERBAL_CONTAINER_STATIC_ORDERED_STATIC_ORDERED_FWD_HPP

#include <kerbal/compare/basic_compare.hpp>
#include <kerbal/container/associative_container_facility/key_extractors/identity_extractor.hpp>

#include <cstddef>


namespace kerbal
{

	namespace container
	{

		template <
			typename Entity,
			std::size_t N,
			typename Extract = kerbal::container::identity_extractor<Entity>,
			typename KeyCompare = kerbal::compare::less<>
		>
		class static_ordered;

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_STATIC_ORDERED_STATIC_ORDERED_FWD_HPP
