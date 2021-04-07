/**
 * @file       forward_list.fwd.hpp
 * @brief
 * @date       2021-01-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_FWD_FORWARD_LIST_FWD_HPP
#define KERBAL_CONTAINER_FWD_FORWARD_LIST_FWD_HPP

#include <memory>

namespace kerbal
{

	namespace container
	{

		template <typename Tp, typename Allocator = std::allocator<Tp> >
		class forward_list;

		namespace detail
		{

			class fl_type_unrelated;

			template <typename Tp>
			class fl_allocator_unrelated;

			template <typename Tp, typename Allocator>
			class fl_allocator_overload;

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

#endif // KERBAL_CONTAINER_FWD_FORWARD_LIST_FWD_HPP
