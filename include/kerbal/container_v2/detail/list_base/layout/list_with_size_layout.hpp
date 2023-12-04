/**
 * @file       list_with_size_layout.hpp
 * @brief
 * @date       2023-11-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_V2_DETAIL_LIST_BASE_LAYOUT_LIST_WITH_SIZE_LAYOUT_HPP
#define KERBAL_CONTAINER_V2_DETAIL_LIST_BASE_LAYOUT_LIST_WITH_SIZE_LAYOUT_HPP

#include <kerbal/container_v2/detail/list_base/layout/list_layout.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>

#include <cstddef>


namespace kerbal
{

	namespace container_v2
	{

		namespace detail
		{

			class list_with_size_layout :
					protected list_layout
			{
				private:
					typedef list_layout super;
					typedef kerbal::container_v2::detail::node_base node_base;

				public:
					std::size_t k_size;

				public:
					KERBAL_CONSTEXPR
					list_with_size_layout() KERBAL_NOEXCEPT :
							k_size(0)
					{
					}

			};

		} // namespace detail

	} // namespace container_v2

} // namespace kerbal

#endif // KERBAL_CONTAINER_V2_DETAIL_LIST_BASE_LAYOUT_LIST_WITH_SIZE_LAYOUT_HPP
