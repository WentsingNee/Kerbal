/**
 * @file       default_allocator.impl.hpp
 * @brief
 * @date       2023-07-21
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_DEFAULT_ALLOCATOR_DEFAULT_ALLOCATOR_IMPL_HPP
#define KERBAL_MEMORY_ALLOCATOR_DEFAULT_ALLOCATOR_DEFAULT_ALLOCATOR_IMPL_HPP

#include <kerbal/memory/allocator/default_allocator/default_allocator.decl.hpp>

#include <kerbal/compatibility/alignof.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/allocator/malloc_allocator.hpp>
#include <kerbal/memory/allocator/over_aligned_allocator.hpp>
#include <kerbal/memory/pointer_alignment.hpp>

#if __cplusplus > 201703L
#	include <kerbal/compatibility/is_constant_evaluated.hpp>

#	if KERBAL_SUPPORTS_IS_CONSTANT_EVALUATED
#		include <memory>
#	endif
#endif

#include <cstddef>


namespace kerbal
{

	namespace memory
	{

		template <typename T>
		KERBAL_CONSTEXPR14
		typename
		default_allocator<T>::size_type
		default_allocator<T>::minimum_alignment() KERBAL_NOEXCEPT
		{
			upstream_allocator up_alloc;
			return up_alloc.minimum_alignment();
		}

		template <typename T>
		KERBAL_CONSTEXPR20
		typename
		default_allocator<T>::pointer
		default_allocator<T>::allocate(size_type n)
		{

#	if __cplusplus > 201703L
#		if KERBAL_SUPPORTS_IS_CONSTANT_EVALUATED
			if (KERBAL_IS_CONSTANT_EVALUATED()) {
				return std::allocator<T>().allocate(n);
			}
#		endif
#	endif

			upstream_allocator up_alloc;
			return up_alloc.allocate(n, KERBAL_ALIGNOF(value_type));
		}

		template <typename T>
		KERBAL_CONSTEXPR20
		void default_allocator<T>::deallocate(pointer p, size_type n) KERBAL_NOEXCEPT
		{

#	if __cplusplus > 201703L
#		if KERBAL_SUPPORTS_IS_CONSTANT_EVALUATED
			if (KERBAL_IS_CONSTANT_EVALUATED()) {
				if (p != NULL) {
					std::allocator<T>().deallocate(p, n);
				}
				return;
			}
#		endif
#	endif

			upstream_allocator up_alloc;
			up_alloc.deallocate(p, n, KERBAL_ALIGNOF(value_type));
		}



		inline
		default_allocator<void>::pointer
		default_allocator<void>::allocate(size_type n)
		{
			return kerbal::memory::malloc_allocator<void>::allocate(n);
		}

		inline
		default_allocator<void>::pointer
		default_allocator<void>::allocate(size_type n, kerbal::memory::align_val_t align)
		{
			over_aligned_allocator over_aligned_alloc;
			return over_aligned_alloc.allocate(n, align);
		}

		inline
		void default_allocator<void>::deallocate(pointer p) KERBAL_NOEXCEPT
		{
			kerbal::memory::malloc_allocator<void>::deallocate(p);
		}

		inline
		void default_allocator<void>::deallocate(pointer p, size_type /*n*/) KERBAL_NOEXCEPT
		{
			kerbal::memory::malloc_allocator<void>::deallocate(p);
		}

		inline
		void default_allocator<void>::deallocate(pointer p, size_type n, kerbal::memory::align_val_t align) KERBAL_NOEXCEPT
		{
			over_aligned_allocator over_aligned_alloc;
			over_aligned_alloc.deallocate(p, n, align);
		}

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_ALLOCATOR_DEFAULT_ALLOCATOR_DEFAULT_ALLOCATOR_IMPL_HPP
