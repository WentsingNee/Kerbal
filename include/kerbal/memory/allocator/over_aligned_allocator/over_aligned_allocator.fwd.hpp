/**
 * @file       over_aligned_allocator.fwd.hpp
 * @brief
 * @date       2023-04-12
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_OVER_ALIGNED_ALLOCATOR_OVER_ALIGNED_ALLOCATOR_FWD_HPP
#define KERBAL_MEMORY_ALLOCATOR_OVER_ALIGNED_ALLOCATOR_OVER_ALIGNED_ALLOCATOR_FWD_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/namespace_std_scope.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/allocator/malloc_allocator/malloc_allocator.fwd.hpp>


namespace kerbal
{

	namespace memory
	{

		template <typename T = void, typename UpstreamAllocator = kerbal::memory::malloc_allocator<void> >
		class over_aligned_allocator;

	} // namespace memory

	namespace algorithm
	{

		template <typename T, typename UpstreamAllocator>
		KERBAL_CONSTEXPR14
		void swap(
			kerbal::memory::over_aligned_allocator<T, UpstreamAllocator> & lhs,
			kerbal::memory::over_aligned_allocator<T, UpstreamAllocator> & rhs
		)
			KERBAL_CONDITIONAL_NOEXCEPT(
				noexcept(lhs.swap(rhs))
			)
		;

	} // namespace algorithm

} // namespace kerbal


KERBAL_NAMESPACE_STD_BEGIN

	template <typename T, typename UpstreamAllocator>
	KERBAL_CONSTEXPR14
	void swap(
			kerbal::memory::over_aligned_allocator<T, UpstreamAllocator> & lhs,
			kerbal::memory::over_aligned_allocator<T, UpstreamAllocator> & rhs
	)
	KERBAL_CONDITIONAL_NOEXCEPT(
		noexcept(lhs.swap(rhs))
	);

KERBAL_NAMESPACE_STD_END


#endif // KERBAL_MEMORY_ALLOCATOR_OVER_ALIGNED_ALLOCATOR_OVER_ALIGNED_ALLOCATOR_FWD_HPP
