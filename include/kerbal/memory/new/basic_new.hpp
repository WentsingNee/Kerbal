/**
 * @file       basic_new.hpp
 * @brief
 * @date       2021-02-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_NEW_BASIC_NEW_HPP
#define KERBAL_MEMORY_NEW_BASIC_NEW_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/allocator/malloc_allocator.hpp>
#include <kerbal/memory/basic_t.hpp>


KERBAL_MODULE_EXPORT
inline
void * operator new(std::size_t size, kerbal::memory::basic_t)
{
	return kerbal::memory::malloc_allocator<void>::allocate(size);
}

KERBAL_MODULE_EXPORT
inline
void operator delete(void * p, kerbal::memory::basic_t) KERBAL_NOEXCEPT
{
	return kerbal::memory::malloc_allocator<void>::deallocate(p);
}

KERBAL_MODULE_EXPORT
inline
void operator delete(void * p, std::size_t /*size*/, kerbal::memory::basic_t) KERBAL_NOEXCEPT
{
	return kerbal::memory::malloc_allocator<void>::deallocate(p);
}

KERBAL_MODULE_EXPORT
inline
void * operator new[](std::size_t size, kerbal::memory::basic_t basic_new_tag)
{
	return kerbal::memory::malloc_allocator<void>::allocate(size);
}

KERBAL_MODULE_EXPORT
inline
void operator delete[](void * p, kerbal::memory::basic_t basic_new_tag) KERBAL_NOEXCEPT
{
	return kerbal::memory::malloc_allocator<void>::deallocate(p);
}

KERBAL_MODULE_EXPORT
inline
void operator delete[](void * p, std::size_t /*size*/, kerbal::memory::basic_t basic_new_tag) KERBAL_NOEXCEPT
{
	return kerbal::memory::malloc_allocator<void>::deallocate(p);
}


#endif // KERBAL_MEMORY_NEW_BASIC_NEW_HPP
