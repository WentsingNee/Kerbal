/**
 * @file       avl_base.fwd.hpp
 * @brief
 * @date       2022-09-06
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_AVL_BASE_AVL_BASE_FWD_HPP
#define KERBAL_CONTAINER_DETAIL_AVL_BASE_AVL_BASE_FWD_HPP

#ifndef KERBAL_AVL_ENABLE_VNULL
#	define KERBAL_AVL_ENABLE_VNULL 1
#endif

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			class avl_head_node;

			class avl_node_base;

			template <typename T>
			class avl_node;

			template <int = 0>
			class avl_vnull_node_helper;

			inline
			KERBAL_CONSTEXPR
			avl_node_base * get_avl_vnull_node() KERBAL_NOEXCEPT;

			class avl_iter_type_unrelated;

			class avl_kiter_type_unrelated;

			template <typename T>
			class avl_iter;

			template <typename T>
			class avl_kiter;

			class avl_type_unrelated;

			template <typename Entity>
			class avl_type_only;

			enum avl_normal_result_t
			{
					AVL_NORMAL_RESULT_CORRECT = 0,
					AVL_NORMAL_RESULT_BST_INVALID = 1,
					AVL_NORMAL_RESULT_BAD_PARENT = 2,
					AVL_NORMAL_RESULT_NOT_BALANCED = 3,
					AVL_NORMAL_RESULT_DEPTH_CACHED_WRONG = 4,
			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_AVL_BASE_AVL_BASE_FWD_HPP
