/**
 * @file       rb_base.fwd.hpp
 * @brief
 * @date       2023-12-19
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_RB_BASE_RB_BASE_FWD_HPP
#define KERBAL_CONTAINER_DETAIL_RB_BASE_RB_BASE_FWD_HPP

#ifndef KERBAL_RB_ENABLE_VNULL
#	define KERBAL_RB_ENABLE_VNULL 1
#endif

#include <kerbal/container/detail/bst_base/bst.fwd.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/integral_constant.hpp>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			class rb_node_base;

			template <typename T>
			class rb_node;

			template <int = 0>
			class rb_vnull_node_helper;

			inline
			KERBAL_CONSTEXPR
			rb_node_base * get_rb_vnull_node() KERBAL_NOEXCEPT;

			template <typename T>
			class rb_iter;

			template <typename T>
			class rb_kiter;

			class rb_type_unrelated;

			template <typename Entity>
			class rb_type_only;

			enum rb_normal_result_t
			{
					RB_NORMAL_RESULT_CORRECT = 0,
					RB_NORMAL_RESULT_BAD_NODES_CNT = 1,
					RB_NORMAL_RESULT_BST_INVALID = 2,
					RB_NORMAL_RESULT_BAD_PARENT = 3,
					RB_NORMAL_RESULT_ROOT_NOT_BLACK = 4,
					RB_NORMAL_RESULT_NEIBOUR_RED = 5,
					RB_NORMAL_RESULT_BAD_BLACK_CNT_IN_PATH = 6,
			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_RB_BASE_RB_BASE_FWD_HPP
