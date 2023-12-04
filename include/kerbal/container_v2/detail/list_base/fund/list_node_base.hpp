/**
 * @file       list_node_base.hpp
 * @brief
 * @date       2023-11-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_V2_DETAIL_LIST_BASE_FUND_LIST_NODE_BASE_HPP
#define KERBAL_CONTAINER_V2_DETAIL_LIST_BASE_FUND_LIST_NODE_BASE_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>

#include <cstddef>


namespace kerbal
{

	namespace container_v2
	{

		namespace detail
		{

			class node_base
			{
				protected:
					node_base* k_prev;
					node_base* k_next;

					KERBAL_CONSTEXPR
					node_base() KERBAL_NOEXCEPT :
							k_prev(this), k_next(this)
					{
					}
			};

		} // namespace detail

	} // namespace container_v2

} // namespace kerbal

#endif // KERBAL_CONTAINER_V2_DETAIL_LIST_BASE_FUND_LIST_NODE_BASE_HPP
