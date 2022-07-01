/**
 * @file       list_base.fwd.hpp
 * @brief
 * @date       2021-10-12
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_LIST_BASE_LIST_BASE_FWD_HPP
#define KERBAL_CONTAINER_DETAIL_LIST_BASE_LIST_BASE_FWD_HPP


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			class list_type_unrelated;

			template <typename Tp>
			class list_allocator_unrelated;

			class list_node_base;

			template <typename Tp>
			class list_node;

			class list_iter_type_unrelated;

			class list_kiter_type_unrelated;

			template <typename Tp>
			class list_iter;

			template <typename Tp>
			class list_kiter;

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_LIST_BASE_LIST_BASE_FWD_HPP
