/**
 * @file       list_node.hpp
 * @brief
 * @date       2023-11-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_V2_DETAIL_LIST_BASE_FUND_LIST_NODE_HPP
#define KERBAL_CONTAINER_V2_DETAIL_LIST_BASE_FUND_LIST_NODE_HPP

#include <kerbal/container_v2/detail/list_base/fund/list_node_base.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/utility/in_place.hpp>
#include <kerbal/utility/member_compress_helper.hpp>


namespace kerbal
{

	namespace container_v2
	{

		namespace detail
		{

			template <typename T>
			class list_node :
					protected kerbal::container_v2::detail::node_base,
					protected kerbal::utility::member_compress_helper<T>
			{
				private:
					typedef kerbal::utility::member_compress_helper<T> compress_helper;

				public:
					KERBAL_CONSTEXPR
					list_node(const T & val) :
							compress_helper(kerbal::utility::in_place_t(), val)
					{
					}

					using compress_helper::member;
			};

		} // namespace detail

	} // namespace container_v2

} // namespace kerbal

#endif // KERBAL_CONTAINER_V2_DETAIL_LIST_BASE_FUND_LIST_NODE_HPP
