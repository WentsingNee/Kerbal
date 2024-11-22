/**
 * @file       malloc_allocator.fwd.hpp
 * @brief
 * @date       2023-04-12
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_MALLOC_ALLOCATOR_MALLOC_ALLOCATOR_FWD_HPP
#define KERBAL_MEMORY_ALLOCATOR_MALLOC_ALLOCATOR_MALLOC_ALLOCATOR_FWD_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>


namespace kerbal
{

	namespace memory
	{

		KERBAL_MODULE_EXPORT
		template <typename T = void>
		class malloc_allocator;

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_ALLOCATOR_MALLOC_ALLOCATOR_MALLOC_ALLOCATOR_FWD_HPP
