/**
 * @file       avl_multiset.fwd.hpp
 * @brief
 * @date       2023-11-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_AVL_MULTISET_AVL_MULTISET_FWD_HPP
#define KERBAL_CONTAINER_AVL_MULTISET_AVL_MULTISET_FWD_HPP

#include <kerbal/compare/binary_type_compare.hpp>

#include <memory>


namespace kerbal
{

	namespace container
	{

		template <
			typename T,
			typename KeyCompare = kerbal::compare::binary_type_less<void, void>,
			typename Allocator = std::allocator<T>
		>
		class avl_multiset;

	} // namespace container

} // namespace kerbal


#endif // KERBAL_CONTAINER_AVL_MULTISET_AVL_MULTISET_FWD_HPP
