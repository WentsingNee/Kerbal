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

#include <kerbal/concepts/config.hpp>
#include <kerbal/container/erasable.hpp>

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

#define KERBAL_CONTAINER_VECTOR_THEAD(T, Allocator) \
		template <typename T, typename Allocator> \
			KERBAL_REQUIRES((kerbal::container::erasable<T, Allocator>))

		template <typename T, typename Allocator = std::allocator<T> >
			KERBAL_REQUIRES((kerbal::container::erasable<T, Allocator>))
		class vector;


#if __cplusplus >= 201703L
#	if __has_include(<memory_resource>)

		namespace pmr
		{
			template <typename T>
			using vector = kerbal::container::vector<T, std::pmr::polymorphic_allocator<T> >;
		}

#	endif
#endif


	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_VECTOR_VECTOR_FWD_HPP
