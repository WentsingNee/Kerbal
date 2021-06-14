/**
 * @file       treap.fwd.hpp
 * @brief
 * @date       2021-06-13
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_TREAP_BASE_TREAP_FWD_HPP
#define KERBAL_CONTAINER_DETAIL_TREAP_BASE_TREAP_FWD_HPP

namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename W>
			struct treap_head_node;

			template <typename W>
			struct treap_node_base;

			template <typename T, typename W>
			struct treap_node;


			template <typename W>
			struct treap_iter_type_unrelated;

			template <typename W>
			struct treap_kiter_type_unrelated;

			template <typename T, typename W>
			struct treap_iter;

			template <typename T, typename W>
			struct treap_kiter;

		} // namespace detail



	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_TREAP_BASE_TREAP_FWD_HPP
