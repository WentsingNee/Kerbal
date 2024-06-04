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

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/compare/binary_type_compare.hpp>

#include <memory>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			KERBAL_MODULE_EXPORT
			template <typename Entity2, typename Extract, typename KeyCompare, typename Allocator>
			struct avl_ordered_typedef_helper;

		} // namespace detail

		KERBAL_MODULE_EXPORT
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
