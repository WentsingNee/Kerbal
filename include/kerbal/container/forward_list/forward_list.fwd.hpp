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

#ifndef KERBAL_CONTAINER_FORWARD_LIST_FORWARD_LIST_FWD_HPP
#define KERBAL_CONTAINER_FORWARD_LIST_FORWARD_LIST_FWD_HPP

#include <memory>

#if __cplusplus >= 201703L
#	if __has_include(<memory_resource>)
#		include <memory_resource>
#	endif
#endif


namespace kerbal
{

	namespace container
	{

		template <typename T, typename Allocator = std::allocator<T> >
		class forward_list;

#if __cplusplus >= 201703L
#	if __has_include(<memory_resource>)

		namespace pmr
		{

			template <typename T>
			using forward_list = kerbal::container::forward_list<T, std::pmr::polymorphic_allocator<T> >;

		}

#	endif
#endif

		template <typename T, typename Allocator = std::allocator<T> >
		struct forward_list_node_size;

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_FORWARD_LIST_FORWARD_LIST_FWD_HPP
