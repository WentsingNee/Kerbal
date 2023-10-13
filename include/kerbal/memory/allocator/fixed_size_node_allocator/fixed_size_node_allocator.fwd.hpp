/**
 * @file       fixed_size_node_allocator.fwd.hpp
 * @brief
 * @date       2023-04-04
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_FIXED_SIZE_NODE_ALLOCATOR_FIXED_SIZE_NODE_ALLOCATOR_FWD_HPP
#define KERBAL_MEMORY_ALLOCATOR_FIXED_SIZE_NODE_ALLOCATOR_FIXED_SIZE_NODE_ALLOCATOR_FWD_HPP

#include <kerbal/compatibility/namespace_std_scope.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/allocator/default_allocator/default_allocator.fwd.hpp>


namespace kerbal
{

	namespace memory
	{

		template <typename T, typename UpstreamAllocator = kerbal::memory::default_allocator<T> >
		class fixed_size_node_allocator;

	} // namespace memory

	namespace algorithm
	{

		template <typename T, typename UpstreamAllocator>
		void swap(
				kerbal::memory::fixed_size_node_allocator<T, UpstreamAllocator> & lhs,
				kerbal::memory::fixed_size_node_allocator<T, UpstreamAllocator> & rhs
		)
		KERBAL_CONDITIONAL_NOEXCEPT(
			noexcept(lhs.swap(rhs))
		);

	} // namespace algorithm

} // namespace kerbal


KERBAL_NAMESPACE_STD_BEGIN

	template <typename T, typename UpstreamAllocator>
	void swap(
			kerbal::memory::fixed_size_node_allocator<T, UpstreamAllocator> & lhs,
			kerbal::memory::fixed_size_node_allocator<T, UpstreamAllocator> & rhs
	)
	KERBAL_CONDITIONAL_NOEXCEPT(
		noexcept(lhs.swap(rhs))
	);

KERBAL_NAMESPACE_STD_END


#endif // KERBAL_MEMORY_ALLOCATOR_FIXED_SIZE_NODE_ALLOCATOR_FIXED_SIZE_NODE_ALLOCATOR_FWD_HPP
