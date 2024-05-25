/**
 * @file       monotonic_allocator.impl.hpp
 * @brief
 * @date       2023-07-23
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_MONOTONIC_ALLOCATOR_MONOTONIC_ALLOCATOR_IMPL_HPP
#define KERBAL_MEMORY_ALLOCATOR_MONOTONIC_ALLOCATOR_MONOTONIC_ALLOCATOR_IMPL_HPP

#include <kerbal/memory/allocator/monotonic_allocator/monotonic_allocator.decl.hpp>

// header(s) for default template argument(s)
#include <kerbal/memory/allocator/default_allocator/default_allocator.impl.hpp>

#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/memory/bad_alloc.hpp>
#include <kerbal/memory/bad_array_new_length.hpp>
#include <kerbal/memory/pointer_alignment.hpp>
#include <kerbal/memory/uninitialized.hpp>
#include <kerbal/numeric/numeric_limits.hpp>
#include <kerbal/utility/in_place.hpp>
#include <kerbal/utility/throw_this_exception.hpp>

#include <cstddef>


namespace kerbal
{

	namespace memory
	{

		template <typename T, typename UpstreamAllocator>
		monotonic_allocator<T, UpstreamAllocator>::monotonic_allocator() KERBAL_NOEXCEPT :
			k_list(),
			k_current_pure_buffer_head(NULL),
			k_current_used_in_bytes(0),
			k_current_buffer_end(NULL)
		{
		}

		template <typename T, typename UpstreamAllocator>
		monotonic_allocator<T, UpstreamAllocator>::monotonic_allocator(const monotonic_allocator & src)
			KERBAL_CONDITIONAL_NOEXCEPT(
				try_test_is_nothrow_copy_constructible::IS_TRUE::value
			) :
			upstream_allocator_overload(src.upstream_alloc()),
			k_list(),
			k_current_pure_buffer_head(NULL),
			k_current_used_in_bytes(0),
			k_current_buffer_end(NULL)
		{
		}

#	if __cplusplus >= 201103L

		template <typename T, typename UpstreamAllocator>
		monotonic_allocator<T, UpstreamAllocator>::monotonic_allocator(monotonic_allocator && src)
			KERBAL_CONDITIONAL_NOEXCEPT(
				try_test_is_nothrow_move_constructible::IS_TRUE::value
			) :
			monotonic_allocator()
		{
			this->swap(src);
		}

#	endif

		template <typename T, typename UpstreamAllocator>
		template <typename U, typename UpstreamAllocator2>
		monotonic_allocator<T, UpstreamAllocator>::monotonic_allocator(const monotonic_allocator<U, UpstreamAllocator2> &)
			KERBAL_CONDITIONAL_NOEXCEPT(
				try_test_is_nothrow_constructible_from_other::IS_TRUE::value
			) :
			k_list(),
			k_current_pure_buffer_head(NULL),
			k_current_used_in_bytes(0),
			k_current_buffer_end(NULL)
		{
		}

		template <typename T, typename UpstreamAllocator>
		monotonic_allocator<T, UpstreamAllocator>::~monotonic_allocator()
		{
			typedef kerbal::memory::allocator_traits<upstream_allocator> allocator_traits;
			typedef typename auto_list::const_iterator iterator;
			iterator before_begin = this->k_list.before_begin();
			while (!this->k_list.empty()) {
				iterator cur = this->k_list.begin();
				void * buffer = cur->gross_buffer;
				std::size_t size = cur->gross_size_in_bytes;
				this->k_list.erase_after(before_begin);
				kerbal::memory::destroy_at(&*cur);
				allocator_traits::deallocate(upstream_alloc(), buffer, size);
			}
		}

#	if __cplusplus >= 201103L

		template <typename T, typename UpstreamAllocator>
		monotonic_allocator<T, UpstreamAllocator> &
		monotonic_allocator<T, UpstreamAllocator>::operator=(monotonic_allocator && src)
			KERBAL_CONDITIONAL_NOEXCEPT(
				try_test_is_nothrow_move_assignable::IS_TRUE::value
			)
		{
			this->swap(src);
			return *this;
		}

#	endif


		template <typename T, typename UpstreamAllocator>
		typename
		monotonic_allocator<T, UpstreamAllocator>::size_type
		monotonic_allocator<T, UpstreamAllocator>::get_next_pure_buffer_size() const
		{
			if (this->k_current_pure_buffer_head == NULL) {
				return 16 * sizeof(value_type);
			}
			size_type current_pure_buffer_size = (this->k_current_buffer_end - this->k_current_pure_buffer_head) * sizeof(value_type);
			if (current_pure_buffer_size > kerbal::numeric::numeric_limits<size_type>::MAX::value / 2) {
				kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
			}
			return current_pure_buffer_size * 2;
		}

		template <typename T, typename UpstreamAllocator>
		void monotonic_allocator<T, UpstreamAllocator>::fill_buffer(size_type next_pure_buffer_size)
		{
			typedef kerbal::memory::allocator_traits<upstream_allocator> allocator_traits;
			typedef auto_node U;

			std::size_t const basic_align = allocator_traits::minimum_alignment(upstream_alloc());
			std::size_t gross_buffer_size =
				kerbal::memory::alignment_maximum_offset(KERBAL_ALIGNOF(U), basic_align) +
				sizeof(U) +
				kerbal::memory::alignment_maximum_offset(ALIGNOF_T::value, KERBAL_ALIGNOF(U)) +
				next_pure_buffer_size
			;

			void * const p_gross = allocator_traits::allocate(upstream_alloc(), gross_buffer_size);
			std::size_t p_gross_sz = reinterpret_cast<std::size_t>(p_gross);

			std::size_t pu_sz = kerbal::memory::align_ceil(p_gross_sz, KERBAL_ALIGNOF(U));
			std::size_t pt_sz = kerbal::memory::align_ceil(pu_sz + sizeof(U), ALIGNOF_T::value);

			U * pu = reinterpret_cast<U *>(pu_sz);
			kerbal::memory::construct_at(pu, kerbal::utility::in_place_t(), p_gross, gross_buffer_size);
			this->k_list.push_front(*pu);

			this->k_current_pure_buffer_head = reinterpret_cast<pointer>(pt_sz);
			this->k_current_used_in_bytes = 0;
			this->k_current_buffer_end = reinterpret_cast<pointer>(pt_sz + next_pure_buffer_size);
		}

		template <typename T, typename UpstreamAllocator>
		typename
		monotonic_allocator<T, UpstreamAllocator>::pointer
		monotonic_allocator<T, UpstreamAllocator>::allocate(size_type n)
		{
			return this->allocate(n, kerbal::memory::align_val_t(KERBAL_ALIGNOF(value_type)));
		}

		template <typename T, typename UpstreamAllocator>
		typename
		monotonic_allocator<T, UpstreamAllocator>::pointer
		monotonic_allocator<T, UpstreamAllocator>::allocate(size_type n, kerbal::memory::align_val_t align)
		{
			if (n > MAX_SIZE::value) {
				kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_array_new_length>::throw_this_exception();
			}
			std::size_t pure_size = n * sizeof(value_type);
			char * pstart = reinterpret_cast<char *>(this->k_current_pure_buffer_head) + this->k_current_used_in_bytes;
			char * phead = align_ceil(pstart, align.val);
			char * pend = phead + pure_size;
			if (pend <= reinterpret_cast<char *>(this->k_current_buffer_end)) {
				this->k_current_used_in_bytes = pend - reinterpret_cast<char *>(this->k_current_pure_buffer_head);
				return reinterpret_cast<pointer>(phead);
			}
			size_type next_pure_buffer_size = this->get_next_pure_buffer_size();
			if (static_cast<size_type>(pend - pstart) > next_pure_buffer_size) {
				next_pure_buffer_size = static_cast<size_type>(pend - pstart);
			}
			fill_buffer(next_pure_buffer_size);
			pstart = reinterpret_cast<char *>(this->k_current_pure_buffer_head) + this->k_current_used_in_bytes;
			phead = align_ceil(pstart, align.val);
			pend = phead + pure_size;
			this->k_current_used_in_bytes = pend - reinterpret_cast<char *>(this->k_current_pure_buffer_head);
			return reinterpret_cast<pointer>(phead);
		}

		template <typename T, typename UpstreamAllocator>
		void monotonic_allocator<T, UpstreamAllocator>::swap(monotonic_allocator & other)
			KERBAL_CONDITIONAL_NOEXCEPT(
				try_test_is_nothrow_swappable::IS_TRUE::value
			)
		{
			upstream_allocator_overload::k_swap_allocator_if_propagate(
				static_cast<upstream_allocator_overload &>(*this),
				static_cast<upstream_allocator_overload &>(other)
			);
			this->k_list.swap(other.k_list);
			kerbal::algorithm::swap(this->k_current_pure_buffer_head, other.k_current_pure_buffer_head);
			kerbal::algorithm::swap(this->k_current_used_in_bytes, other.k_current_used_in_bytes);
			kerbal::algorithm::swap(this->k_current_buffer_end, other.k_current_buffer_end);
		}

	} // namespace memory

} // namespace kerbal


#endif // KERBAL_MEMORY_ALLOCATOR_MONOTONIC_ALLOCATOR_MONOTONIC_ALLOCATOR_IMPL_HPP
