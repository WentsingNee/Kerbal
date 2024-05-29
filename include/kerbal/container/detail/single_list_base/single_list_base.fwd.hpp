/**
 * @file       single_list_base.fwd.hpp
 * @brief
 * @date       2021-10-12
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_SINGLE_LIST_BASE_SINGLE_LIST_BASE_FWD_HPP
#define KERBAL_CONTAINER_DETAIL_SINGLE_LIST_BASE_SINGLE_LIST_BASE_FWD_HPP


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			class sl_type_unrelated;

			template <typename T>
			class sl_type_only;

			class sl_node_base;

			template <typename T>
			class sl_node;

			class sl_iter_type_unrelated;

			class sl_kiter_type_unrelated;

			template <typename T>
			class sl_iter;

			template <typename T>
			class sl_kiter;

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_SINGLE_LIST_BASE_SINGLE_LIST_BASE_FWD_HPP
