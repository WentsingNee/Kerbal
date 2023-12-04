/**
 * @file       list_with_size.hpp
 * @brief
 * @date       2023-11-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_V2_DETAIL_LIST_BASE_ENCAP_LIST_WITH_SIZE_HPP
#define KERBAL_CONTAINER_V2_DETAIL_LIST_BASE_ENCAP_LIST_WITH_SIZE_HPP

#include <kerbal/container_v2/detail/list_base/fund/list_node.hpp>
#include <kerbal/container_v2/detail/list_base/layout/list_with_size_layout.hpp>
#include <kerbal/container_v2/detail/list_base/trait/list_trait_hook_node_front.hpp>

#include <cstddef>


namespace kerbal
{

	namespace container_v2
	{

		namespace detail
		{

			template <typename T>
			struct list_with_size :
					list_with_size_layout,
					list_trait_hook_node_front<
						list_with_size_layout,
						std::size_t, &list_with_size_layout::k_size
					>
			{
				private:

					typedef kerbal::container_v2::detail::list_node<T> node;

				public:
					void push_front(T const & val)
					{
						k_hook_node_front(*this, new node(val));
					}

					// void print() const
					// {
					// 	ListPrintTrait<list_layout>::print(*this);
					// }
			};

		} // namespace detail

	} // namespace container_v2

} // namespace kerbal

#endif // KERBAL_CONTAINER_V2_DETAIL_LIST_BASE_ENCAP_LIST_WITH_SIZE_HPP
