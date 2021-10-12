/**
 * @file       single_list.fwd.hpp
 * @brief
 * @date       2020-08-31
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_FWD_SINGLE_LIST_FWD_HPP
#define KERBAL_CONTAINER_FWD_SINGLE_LIST_FWD_HPP

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

		template <typename Tp, typename Allocator = std::allocator<Tp> >
		class single_list;

#if __cplusplus >= 201703L
#	if __has_include(<memory_resource>)

		namespace pmr
		{
			template <typename Tp>
			using single_list = kerbal::container::single_list<Tp, std::pmr::polymorphic_allocator<Tp> >;
		}

#	endif
#endif

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_FWD_SINGLE_LIST_FWD_HPP
