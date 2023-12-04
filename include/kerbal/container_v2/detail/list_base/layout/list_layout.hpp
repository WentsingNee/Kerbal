/**
 * @file       list_layout.hpp
 * @brief
 * @date       2023-11-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_V2_DETAIL_LIST_BASE_LAYOUT_LIST_LAYOUT_HPP
#define KERBAL_CONTAINER_V2_DETAIL_LIST_BASE_LAYOUT_LIST_LAYOUT_HPP

#include <kerbal/container_v2/detail/list_base/fund/list_node_base.hpp>


namespace kerbal
{

	namespace container_v2
	{

		namespace detail
		{

			class list_layout
			{
				private:
					typedef kerbal::container_v2::detail::node_base node_base;

				protected:
					node_base k_head;

				public:
					list_layout() = default;
			};

		} // namespace detail

	} // namespace container_v2

} // namespace kerbal

#endif // KERBAL_CONTAINER_V2_DETAIL_LIST_BASE_LAYOUT_LIST_LAYOUT_HPP
