/**
 * @file       avl_multi_index_base.fwd.hpp
 * @brief
 * @date       2023-11-16
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science &
 * Technology](http://www.nuist.edu.cn/) all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_AVL_MULTI_INDEX_BASE_AVL_MULTI_INDEX_BASE_FWD_HPP
#define KERBAL_CONTAINER_DETAIL_AVL_MULTI_INDEX_BASE_AVL_MULTI_INDEX_BASE_FWD_HPP

#include <cstddef>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename Entity, std::size_t KeyCount>
			class avl_multi_index_node;


			template <typename Entity, std::size_t KeyCount, std::size_t I>
			class avl_multi_index_iter;


			template <typename Entity, typename ... PolicyField>
			class avl_multi_index_base;

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_AVL_MULTI_INDEX_BASE_AVL_MULTI_INDEX_BASE_FWD_HPP
