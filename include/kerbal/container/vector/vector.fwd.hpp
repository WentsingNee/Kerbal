/**
 * @file       vector.fwd.hpp
 * @brief
 * @date       2020-08-15
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_VECTOR_VECTOR_FWD_HPP
#define KERBAL_CONTAINER_VECTOR_VECTOR_FWD_HPP

#include <kerbal/container/detail/vector_base/vector_base.fwd.hpp>

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
		class vector;


#if __cplusplus >= 201703L
#	if __has_include(<memory_resource>)

		namespace pmr
		{
			template <typename Tp>
			using vector = kerbal::container::vector<Tp, std::pmr::polymorphic_allocator<Tp> >;
		}

#	endif
#endif


	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_VECTOR_VECTOR_FWD_HPP
