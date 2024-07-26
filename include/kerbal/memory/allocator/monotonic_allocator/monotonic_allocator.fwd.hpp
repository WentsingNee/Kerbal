/**
 * @file       monotonic_allocator.fwd.hpp
 * @brief
 * @date       2023-04-04
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_MONOTONIC_ALLOCATOR_MONOTONIC_ALLOCATOR_FWD_HPP
#define KERBAL_MEMORY_ALLOCATOR_MONOTONIC_ALLOCATOR_MONOTONIC_ALLOCATOR_FWD_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/compatibility/namespace_std_scope.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/allocator/default_allocator/default_allocator.fwd.hpp>
#include <kerbal/utility/declval.hpp>


namespace kerbal
{

	namespace memory
	{

		KERBAL_MODULE_EXPORT
		template <typename T, typename UpstreamAllocator = kerbal::memory::default_allocator<void> >
		class monotonic_allocator;

	} // namespace memory

	namespace algorithm
	{

		KERBAL_MODULE_EXPORT
		template <typename T, typename UpstreamAllocator>
		void swap(
			kerbal::memory::monotonic_allocator<T, UpstreamAllocator> & lhs,
			kerbal::memory::monotonic_allocator<T, UpstreamAllocator> & rhs
		)
			KERBAL_CONDITIONAL_NOEXCEPT(
				noexcept(
					kerbal::utility::declval<kerbal::memory::monotonic_allocator<T, UpstreamAllocator> &>().swap(
						kerbal::utility::declval<kerbal::memory::monotonic_allocator<T, UpstreamAllocator> &>()
					)
				)
			)
		;

	} // namespace algorithm

} // namespace kerbal


KERBAL_NAMESPACE_STD_BEGIN

	KERBAL_MODULE_EXPORT
	template <typename T, typename UpstreamAllocator>
	void swap(
			kerbal::memory::monotonic_allocator<T, UpstreamAllocator> & lhs,
			kerbal::memory::monotonic_allocator<T, UpstreamAllocator> & rhs
	)
	KERBAL_CONDITIONAL_NOEXCEPT(
		noexcept(
			kerbal::utility::declval<kerbal::memory::monotonic_allocator<T, UpstreamAllocator> &>().swap(
				kerbal::utility::declval<kerbal::memory::monotonic_allocator<T, UpstreamAllocator> &>()
			)
		)
	);

KERBAL_NAMESPACE_STD_END


#endif // KERBAL_MEMORY_ALLOCATOR_MONOTONIC_ALLOCATOR_MONOTONIC_ALLOCATOR_FWD_HPP
