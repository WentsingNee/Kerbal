/**
 * @file       malloc_allocator.impl.hpp
 * @brief
 * @date       2023-07-21
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_MALLOC_ALLOCATOR_MALLOC_ALLOCATOR_IMPL_HPP
#define KERBAL_MEMORY_ALLOCATOR_MALLOC_ALLOCATOR_MALLOC_ALLOCATOR_IMPL_HPP

#include <kerbal/memory/allocator/malloc_allocator/malloc_allocator.decl.hpp>

#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/bad_alloc.hpp>
#include <kerbal/memory/bad_array_new_length.hpp>
#include <kerbal/memory/nothrow_t.hpp>
#include <kerbal/utility/throw_this_exception.hpp>

#include <cstdlib>


namespace kerbal
{

	namespace memory
	{

		inline
		malloc_allocator<void>::pointer
		malloc_allocator<void>::allocate(size_type n, kerbal::memory::nothrow_t) KERBAL_NOEXCEPT
		{
			void * p = std::malloc(n);
			return p;
		}

		inline
		malloc_allocator<void>::pointer
		malloc_allocator<void>::allocate(size_type n)
		{
			void * p = std::malloc(n);
			if (p == NULL) {
				kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
			}
			return p;
		}

		inline
		void malloc_allocator<void>::deallocate(pointer p) KERBAL_NOEXCEPT
		{
			std::free(p);
		}

		inline
		void malloc_allocator<void>::deallocate(pointer p, size_type /*n*/) KERBAL_NOEXCEPT
		{
			deallocate(p);
		}

		inline
		void malloc_allocator<void>::deallocate(pointer p, kerbal::memory::nothrow_t) KERBAL_NOEXCEPT
		{
			deallocate(p);
		}

		inline
		void malloc_allocator<void>::deallocate(pointer p, size_type n, kerbal::memory::nothrow_t) KERBAL_NOEXCEPT
		{
			deallocate(p, n);
		}



		template <typename T>
		typename
		malloc_allocator<T>::pointer
		malloc_allocator<T>::allocate(size_type n, kerbal::memory::nothrow_t nothrow) KERBAL_NOEXCEPT
		{
			if (n > MAX_SIZE::value) {
				return NULL;
			}
			void * p = kerbal::memory::malloc_allocator<void>::allocate(n * sizeof(value_type), nothrow);
			return static_cast<pointer>(p);
		}

		template <typename T>
		typename
		malloc_allocator<T>::pointer
		malloc_allocator<T>::allocate(size_type n)
		{
			if (n > MAX_SIZE::value) {
				kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_array_new_length>::throw_this_exception();
			}
			void * p = kerbal::memory::malloc_allocator<void>::allocate(n * sizeof(value_type));
			return static_cast<pointer>(p);
		}

		template <typename T>
		void malloc_allocator<T>::deallocate(pointer p, size_type n, kerbal::memory::nothrow_t nothrow) KERBAL_NOEXCEPT
		{
			kerbal::memory::malloc_allocator<void>::deallocate(p, n, nothrow);
		}

		template <typename T>
		void malloc_allocator<T>::deallocate(pointer p, kerbal::memory::nothrow_t nothrow) KERBAL_NOEXCEPT
		{
			kerbal::memory::malloc_allocator<void>::deallocate(p, nothrow);
		}

		template <typename T>
		void malloc_allocator<T>::deallocate(pointer p, size_type n) KERBAL_NOEXCEPT
		{
			kerbal::memory::malloc_allocator<void>::deallocate(p, n);
		}

		template <typename T>
		void malloc_allocator<T>::deallocate(pointer p) KERBAL_NOEXCEPT
		{
			kerbal::memory::malloc_allocator<void>::deallocate(p);
		}

	} // namespace memory

} // namespace kerbal


#endif // KERBAL_MEMORY_ALLOCATOR_MALLOC_ALLOCATOR_MALLOC_ALLOCATOR_IMPL_HPP
