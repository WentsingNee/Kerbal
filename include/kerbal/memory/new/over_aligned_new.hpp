/**
 * @file       over_aligned_new.hpp
 * @brief
 * @date       2021-02-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_NEW_OVER_ALIGNED_NEW_HPP
#define KERBAL_MEMORY_NEW_OVER_ALIGNED_NEW_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/allocator/over_aligned_allocator.hpp>
#include <kerbal/memory/nothrow_t.hpp>
#include <kerbal/memory/pointer_alignment.hpp>

#include <cstddef>


KERBAL_MODULE_EXPORT
inline
void * operator new(std::size_t size, kerbal::memory::align_val_t align, kerbal::memory::nothrow_t nothrow) KERBAL_NOEXCEPT
{
	kerbal::memory::over_aligned_allocator<void> alloc;
	return alloc.allocate(size, align, nothrow);
}

KERBAL_MODULE_EXPORT
inline
void operator delete(void * p, std::size_t size, kerbal::memory::align_val_t align, kerbal::memory::nothrow_t nothrow) KERBAL_NOEXCEPT
{
	kerbal::memory::over_aligned_allocator<void> alloc;
	alloc.deallocate(p, size, align, nothrow);
}

KERBAL_MODULE_EXPORT
inline
void * operator new[](std::size_t size, kerbal::memory::align_val_t align, kerbal::memory::nothrow_t nothrow) KERBAL_NOEXCEPT
{
	return ::operator new(size, align, nothrow);
}

KERBAL_MODULE_EXPORT
inline
void operator delete[](void * p, std::size_t size, kerbal::memory::align_val_t align, kerbal::memory::nothrow_t nothrow) KERBAL_NOEXCEPT
{
	::operator delete(p, size, align, nothrow);
}



KERBAL_MODULE_EXPORT
inline
void * operator new(std::size_t size, kerbal::memory::align_val_t align)
{
	kerbal::memory::over_aligned_allocator<void> alloc;
	return alloc.allocate(size, align);
}

KERBAL_MODULE_EXPORT
inline
void operator delete(void * p, std::size_t size, kerbal::memory::align_val_t align) KERBAL_NOEXCEPT
{
	kerbal::memory::over_aligned_allocator<void> alloc;
	alloc.deallocate(p, size, align);
}

KERBAL_MODULE_EXPORT
inline
void * operator new[](std::size_t size, kerbal::memory::align_val_t align)
{
	return ::operator new(size, align);
}

KERBAL_MODULE_EXPORT
inline
void operator delete[](void * p, std::size_t size, kerbal::memory::align_val_t align) KERBAL_NOEXCEPT
{
	::operator delete(p, size, align);
}


#endif // KERBAL_MEMORY_NEW_OVER_ALIGNED_NEW_HPP
