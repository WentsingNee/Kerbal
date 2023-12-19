/**
 * @file       bst.fwd.hpp
 * @brief
 * @date       2023-12-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_BST_BASE_BST_FWD_HPP
#define KERBAL_CONTAINER_DETAIL_BST_BASE_BST_FWD_HPP

namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename VNULL_HELPER>
			class bst_head_node;

			template <typename VNULL_HELPER>
			class bst_node_base;

			template <typename VNULL_HELPER>
			class bst_iter_type_unrelated;

			template <typename VNULL_HELPER>
			class bst_kiter_type_unrelated;

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_BST_BASE_BST_FWD_HPP
