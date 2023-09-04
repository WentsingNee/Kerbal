/**
 * @file       forward_list_base.fwd.hpp
 * @brief
 * @date       2021-10-12
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_FORWARD_LIST_BASE_FORWARD_LIST_BASE_FWD_HPP
#define KERBAL_CONTAINER_DETAIL_FORWARD_LIST_BASE_FORWARD_LIST_BASE_FWD_HPP


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			class fl_type_unrelated;

			template <typename Tp>
			class fl_type_only;

			class sl_node_base;

			template <typename Tp>
			class sl_node;

			class fl_iter_type_unrelated;

			class fl_kiter_type_unrelated;

			template <typename Tp>
			class fl_iter;

			template <typename Tp>
			class fl_kiter;

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_FORWARD_LIST_BASE_FORWARD_LIST_BASE_FWD_HPP
