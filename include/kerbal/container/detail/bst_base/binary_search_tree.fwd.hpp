/**
 * @file       binary_search_tree.fwd.hpp
 * @brief
 * @date       2020-10-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_BST_BASE_BINARY_SEARCH_TREE_FWD_HPP
#define KERBAL_CONTAINER_DETAIL_BST_BASE_BINARY_SEARCH_TREE_FWD_HPP

namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			class bst_head_node;

			class bst_node_base;

			template <typename Tp>
			class bst_node;

			class bst_iter_type_unrelated;
			class bst_kiter_type_unrelated;

			template <typename Tp>
			class bst_iter;

			template <typename Tp>
			class bst_kiter;

			template <typename Entity, typename Extract, typename KeyCompare>
			class bst;

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_BST_BASE_BINARY_SEARCH_TREE_FWD_HPP
