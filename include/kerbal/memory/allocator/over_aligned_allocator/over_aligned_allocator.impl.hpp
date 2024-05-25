/**
 * @file       over_aligned_allocator.impl.hpp
 * @brief
 * @date       2023-07-21
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_OVER_ALIGNED_ALLOCATOR_OVER_ALIGNED_ALLOCATOR_IMPL_HPP
#define KERBAL_MEMORY_ALLOCATOR_OVER_ALIGNED_ALLOCATOR_OVER_ALIGNED_ALLOCATOR_IMPL_HPP

#include <kerbal/memory/allocator/over_aligned_allocator/over_aligned_allocator.decl.hpp>

// header(s) for default template argument(s)
#include <kerbal/memory/allocator/malloc_allocator/malloc_allocator.impl.hpp>

#include <kerbal/compatibility/alignof.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/config/exceptions.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/memory/bad_alloc.hpp>
#include <kerbal/memory/bad_array_new_length.hpp>
#include <kerbal/memory/nothrow_t.hpp>
#include <kerbal/memory/pointer_alignment.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/utility/throw_this_exception.hpp>

#include <cstddef>


namespace kerbal
{

	namespace memory
	{

		template <typename UpstreamAllocator>
		typename
		over_aligned_allocator<void, UpstreamAllocator>::pointer
		over_aligned_allocator<void, UpstreamAllocator>::
		do_align(pointer p_raw, align_val_t align) KERBAL_NOEXCEPT
		{
			std::size_t p_raw_sz = reinterpret_cast<std::size_t>(p_raw);

			std::size_t pt_sz = kerbal::memory::align_ceil(kerbal::memory::align_ceil(p_raw_sz, KERBAL_ALIGNOF(void_p)) + sizeof(void_p), align);
			std::size_t pu_sz = kerbal::memory::align_floor(pt_sz - sizeof(void_p), KERBAL_ALIGNOF(void_p));

			void_p * pu = reinterpret_cast<void_p *>(pu_sz);
			*pu = p_raw;

			pointer p = reinterpret_cast<pointer>(pt_sz);
			return p;
		}

		template <typename UpstreamAllocator>
		typename
		over_aligned_allocator<void, UpstreamAllocator>::pointer
		over_aligned_allocator<void, UpstreamAllocator>::
		allocate(size_type size, align_val_t align, kerbal::memory::nothrow_t) KERBAL_NOEXCEPT
		{
			std::size_t basic_align = upstream_allocator_traits::minimum_alignment(upstream_alloc());

			pointer p_raw = NULL;
			if (align <= basic_align) {
#		if KERBAL_HAS_EXCEPTIONS_SUPPORT
				try {
					p_raw = upstream_allocator_traits::allocate(upstream_alloc(), size);
				} catch (...) {
					return NULL;
				}
#		else
				p_raw = upstream_allocator_traits::allocate(upstream_alloc(), size);
				if (p_raw == NULL) {
					return NULL;
				}
#		endif
				return p_raw;
			}

			std::size_t raw_allocate_size =
				kerbal::memory::alignment_maximum_offset(KERBAL_ALIGNOF(void_p), basic_align) +
				sizeof(void_p) +
				kerbal::memory::alignment_maximum_offset(align.val, KERBAL_ALIGNOF(void_p)) +
				size
			;
#		if KERBAL_HAS_EXCEPTIONS_SUPPORT
			try {
				p_raw = upstream_allocator_traits::allocate(upstream_alloc(), raw_allocate_size);
			} catch (...) {
				return NULL;
			}
#		else
			p_raw = upstream_allocator_traits::allocate(upstream_alloc(), raw_allocate_size);
			if (p_raw == NULL) {
				return NULL;
			}
#		endif
			if (p_raw == NULL) {
				return NULL;
			}

			return do_align(p_raw, align);
		}

		template <typename UpstreamAllocator>
		typename
		over_aligned_allocator<void, UpstreamAllocator>::pointer
		over_aligned_allocator<void, UpstreamAllocator>::
		allocate(size_type size, align_val_t align)
		{
			std::size_t basic_align = upstream_allocator_traits::minimum_alignment(upstream_alloc());

			pointer p_raw = NULL;
			if (align <= basic_align) {
				p_raw = upstream_allocator_traits::allocate(upstream_alloc(), size);
				return p_raw;
			}

			std::size_t raw_allocate_size =
				kerbal::memory::alignment_maximum_offset(KERBAL_ALIGNOF(void_p), basic_align) +
				sizeof(void_p) +
				kerbal::memory::alignment_maximum_offset(align.val, KERBAL_ALIGNOF(void_p)) +
				size
			;
			p_raw = upstream_allocator_traits::allocate(upstream_alloc(), raw_allocate_size);

			return do_align(p_raw, align);
		}

		template <typename UpstreamAllocator>
		void
		over_aligned_allocator<void, UpstreamAllocator>::
		k_deallocate_upstream_allow_deallocate_null(
			pointer p, size_type size, align_val_t align,
			kerbal::type_traits::false_type
		) KERBAL_NOEXCEPT
		{
			if (p == NULL) {
				return;
			}

			std::size_t basic_align = upstream_allocator_traits::minimum_alignment(upstream_alloc());

			if (align <= basic_align) {
				upstream_allocator_traits::deallocate(upstream_alloc(), p, size);
				return;
			}

			std::size_t raw_allocate_size =
				kerbal::memory::alignment_maximum_offset(KERBAL_ALIGNOF(void_p), basic_align) +
				sizeof(void_p) +
				kerbal::memory::alignment_maximum_offset(align.val, KERBAL_ALIGNOF(void_p)) +
				size
			;
			std::size_t pt_sz = reinterpret_cast<std::size_t>(p);
			std::size_t pu_sz = kerbal::memory::align_floor(pt_sz - sizeof(void_p), KERBAL_ALIGNOF(void_p));
			void_p * pu = reinterpret_cast<void_p *>(pu_sz);
			pointer p_raw = *pu;
			upstream_allocator_traits::deallocate(upstream_alloc(), p_raw, raw_allocate_size);
		}

		template <typename UpstreamAllocator>
		void
		over_aligned_allocator<void, UpstreamAllocator>::
		k_deallocate_upstream_allow_deallocate_null(
			pointer p, size_type size, align_val_t align,
			kerbal::type_traits::true_type
		) KERBAL_NOEXCEPT
		{
			pointer p_raw;
			std::size_t raw_allocate_size;

			if (p == NULL) {
				p_raw = p;
				raw_allocate_size = size;
			} else {
				std::size_t basic_align = upstream_allocator_traits::minimum_alignment(upstream_alloc());

				if (align <= basic_align) {
					p_raw = p;
					raw_allocate_size = size;
				} else {
					raw_allocate_size =
						kerbal::memory::alignment_maximum_offset(KERBAL_ALIGNOF(void_p), basic_align) +
						sizeof(void_p) +
						kerbal::memory::alignment_maximum_offset(align.val, KERBAL_ALIGNOF(void_p)) +
						size
					;
					std::size_t pt_sz = reinterpret_cast<std::size_t>(p);
					std::size_t pu_sz = kerbal::memory::align_floor(pt_sz - sizeof(void_p), KERBAL_ALIGNOF(void_p));
					void_p * pu = reinterpret_cast<void_p *>(pu_sz);
					p_raw = *pu;
				}
			}

			upstream_allocator_traits::deallocate(upstream_alloc(), p_raw, raw_allocate_size);
		}

		template <typename UpstreamAllocator>
		void
		over_aligned_allocator<void, UpstreamAllocator>::
		deallocate(pointer p, size_type size, align_val_t align) KERBAL_NOEXCEPT
		{
			this->k_deallocate_upstream_allow_deallocate_null(
				p, size, align,
				typename upstream_allocator_traits::allow_deallocate_null()
			);
		}

		template <typename UpstreamAllocator>
		void
		over_aligned_allocator<void, UpstreamAllocator>::
		deallocate(pointer p, size_type size, align_val_t align, kerbal::memory::nothrow_t) KERBAL_NOEXCEPT
		{
			deallocate(p, size, align);
		}



		template <typename T, typename UpstreamAllocator>
		typename
		over_aligned_allocator<T, UpstreamAllocator>::pointer
		over_aligned_allocator<T, UpstreamAllocator>::
		allocate(size_type n, align_val_t align)
		{
			if (n > MAX_SIZE::value) {
				kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_array_new_length>::throw_this_exception();
			}
			void * p = this->super::allocate(n * sizeof(value_type), align);
			return static_cast<pointer>(p);
		}

		template <typename T, typename UpstreamAllocator>
		typename
		over_aligned_allocator<T, UpstreamAllocator>::pointer
		over_aligned_allocator<T, UpstreamAllocator>::
		allocate(size_type n, align_val_t align, kerbal::memory::nothrow_t nothrow) KERBAL_NOEXCEPT
		{
			if (n > MAX_SIZE::value) {
				return NULL;
			}
			void * p = this->super::allocate(n * sizeof(value_type), align, nothrow);
			return static_cast<pointer>(p);
		}

		template <typename T, typename UpstreamAllocator>
		typename
		over_aligned_allocator<T, UpstreamAllocator>::pointer
		over_aligned_allocator<T, UpstreamAllocator>::
		allocate(size_type n)
		{
			return this->allocate(n, KERBAL_ALIGNOF(value_type));
		}

		template <typename T, typename UpstreamAllocator>
		typename
		over_aligned_allocator<T, UpstreamAllocator>::pointer
		over_aligned_allocator<T, UpstreamAllocator>::
		allocate(size_type n, kerbal::memory::nothrow_t nothrow) KERBAL_NOEXCEPT
		{
			return this->allocate(n, KERBAL_ALIGNOF(value_type), nothrow);
		}

		template <typename T, typename UpstreamAllocator>
		void
		over_aligned_allocator<T, UpstreamAllocator>::
		deallocate(pointer p, size_type n, align_val_t align) KERBAL_NOEXCEPT
		{
			if (n > MAX_SIZE::value) {
				kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_array_new_length>::throw_this_exception();
			}
			this->super::deallocate(p, n * sizeof(value_type), align);
		}

		template <typename T, typename UpstreamAllocator>
		void
		over_aligned_allocator<T, UpstreamAllocator>::
		deallocate(pointer p, size_type n, align_val_t align, kerbal::memory::nothrow_t nothrow) KERBAL_NOEXCEPT
		{
			if (n > MAX_SIZE::value) {
				kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_array_new_length>::throw_this_exception();
			}
			this->super::deallocate(p, n * sizeof(value_type), align, nothrow);
		}

		template <typename T, typename UpstreamAllocator>
		void
		over_aligned_allocator<T, UpstreamAllocator>::
		deallocate(pointer p, size_type n) KERBAL_NOEXCEPT
		{
			this->deallocate(p, n, KERBAL_ALIGNOF(value_type));
		}

		template <typename T, typename UpstreamAllocator>
		void
		over_aligned_allocator<T, UpstreamAllocator>::
		deallocate(pointer p, size_type n, kerbal::memory::nothrow_t nothrow) KERBAL_NOEXCEPT
		{
			this->deallocate(p, n, KERBAL_ALIGNOF(value_type), nothrow);
		}


	} // namespace memory

} // namespace kerbal


#endif // KERBAL_MEMORY_ALLOCATOR_OVER_ALIGNED_ALLOCATOR_OVER_ALIGNED_ALLOCATOR_IMPL_HPP
