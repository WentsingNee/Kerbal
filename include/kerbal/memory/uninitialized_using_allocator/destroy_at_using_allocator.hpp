/**
 * @file       destroy_at_using_allocator.hpp
 * @brief
 * @date       2023-10-29
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_UNINITIALIZED_USING_ALLOCATOR_DESTROY_AT_USING_ALLOCATOR_HPP
#define KERBAL_MEMORY_UNINITIALIZED_USING_ALLOCATOR_DESTROY_AT_USING_ALLOCATOR_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/memory/uninitialized_using_allocator/destroy_on_using_allocator.hpp>


namespace kerbal
{

	namespace memory
	{

		template <typename Allocator, typename T>
		KERBAL_CONSTEXPR14
		void destroy_at_using_allocator(Allocator & alloc, T * p)
		{
			kerbal::memory::destroy_on_using_allocator(alloc, *p);
		}

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_UNINITIALIZED_USING_ALLOCATOR_DESTROY_AT_USING_ALLOCATOR_HPP
