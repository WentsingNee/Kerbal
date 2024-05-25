/**
 * @file       avl_ordered.fwd.hpp
 * @brief
 * @date       2022-09-08
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_AVL_ORDERED_AVL_ORDERED_FWD_HPP
#define KERBAL_CONTAINER_AVL_ORDERED_AVL_ORDERED_FWD_HPP

#include <kerbal/compare/binary_type_compare.hpp>

#include <memory>


namespace kerbal
{

	namespace container
	{

		template <
			typename Entity,
			typename Extract,
			typename KeyCompare = kerbal::compare::binary_type_less<void, void>,
			typename Allocator = std::allocator<Entity>
		>
		class avl_ordered;

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_AVL_ORDERED_AVL_ORDERED_FWD_HPP
