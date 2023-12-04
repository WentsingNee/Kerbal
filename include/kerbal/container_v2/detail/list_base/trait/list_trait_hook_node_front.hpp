/**
 * @file       list_trait_hook_node_front.hpp
 * @brief
 * @date       2023-11-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_V2_DETAIL_LIST_BASE_TRAIT_LIST_TRAIT_HOOK_NODE_FRONT_HPP
#define KERBAL_CONTAINER_V2_DETAIL_LIST_BASE_TRAIT_LIST_TRAIT_HOOK_NODE_FRONT_HPP

#include <kerbal/container_v2/detail/list_base/fund/list_node_base.hpp>


namespace kerbal
{

	namespace container_v2
	{

		namespace detail
		{

			template <
					typename ListLayout,
					typename SizeType, SizeType ListLayout::* Size
			>
			class list_trait_hook_node_front
			{
				private:
					typedef kerbal::container_v2::detail::node_base node_base;

				public:
					static void k_hook_node_front(ListLayout & self, node_base * p)
					{
						node_base * old_front = self.k_head.k_next;
						p->k_next = old_front;
						old_front->k_prev = p;
						p->k_prev = &self.k_head;
						self.k_head.k_next = p;
						if (Size != NULL) {
							++(self.*Size);
						}
					}
			};

		} // namespace detail

	} // namespace container_v2

} // namespace kerbal

#endif // KERBAL_CONTAINER_V2_DETAIL_LIST_BASE_TRAIT_LIST_TRAIT_HOOK_NODE_FRONT_HPP
