/**
 * @file       list.fwd.hpp
 * @brief
 * @date       2020-08-15
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_FWD_LIST_FWD_HPP
#define KERBAL_CONTAINER_FWD_LIST_FWD_HPP

namespace kerbal
{

	namespace container
	{

		template <typename Tp, typename Allocator>
		class list;

		namespace detail
		{

			class list_type_unrelated;

			template <typename Tp>
			class list_allocator_unrelated;

			template <typename Tp, typename Allocator, bool>
			class list_allocator_overload;

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

#endif // KERBAL_CONTAINER_FWD_LIST_FWD_HPP
