/**
 * @file       nothrow_new.hpp
 * @brief
 * @date       2021-02-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_NEW_NOTHROW_NEW_HPP
#define KERBAL_MEMORY_NEW_NOTHROW_NEW_HPP

#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/allocator/malloc_allocator.hpp>
#include <kerbal/memory/nothrow_t.hpp>

#include <cstddef>


inline
void * operator new(std::size_t size, kerbal::memory::nothrow_t nothrow) KERBAL_NOEXCEPT
{
	return kerbal::memory::malloc_allocator<void>::allocate(size, nothrow);
}

inline
void operator delete(void * p, std::size_t /*size*/, kerbal::memory::nothrow_t) KERBAL_NOEXCEPT
{
	kerbal::memory::malloc_allocator<void>::deallocate(p);
}

inline
void * operator new[](std::size_t size, kerbal::memory::nothrow_t nothrow) KERBAL_NOEXCEPT
{
	return kerbal::memory::malloc_allocator<void>::allocate(size, nothrow);
}

inline
void operator delete[](void * p, std::size_t /*size*/, kerbal::memory::nothrow_t) KERBAL_NOEXCEPT
{
	kerbal::memory::malloc_allocator<void>::deallocate(p);
}


#endif // KERBAL_MEMORY_NEW_NOTHROW_NEW_HPP
