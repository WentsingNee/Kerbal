/**
 * @file       ring_buffer_queue_base.impl.hpp
 * @brief
 * @date       2022-03-30
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_RING_BUFFER_QUEUE_BASE_RING_BUFFER_QUEUE_BASE_IMPL_HPP
#define KERBAL_CONTAINER_DETAIL_RING_BUFFER_QUEUE_BASE_RING_BUFFER_QUEUE_BASE_IMPL_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/memory/uninitialized_using_allocator.hpp>

#include <kerbal/container/detail/ring_buffer_queue_base/ring_buffer_queue_base.decl.hpp>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename T>
			KERBAL_CONSTEXPR
			rbq_allocator_unrelated<T>::rbq_allocator_unrelated() KERBAL_NOEXCEPT :
					K_buffer(NULL), K_capacity(0), K_begin(0), K_size(0)
			{
			}

			template <typename T>
			template <typename Alloc>
			KERBAL_CONSTEXPR20
			rbq_allocator_unrelated<T>::rbq_allocator_unrelated(const rbq_allocator_unrelated & src, Alloc & alloc) :
					K_buffer(NULL), K_capacity(0), K_begin(0), K_size(0)
			{
				typedef kerbal::memory::allocator_traits<Alloc> allocator_traits;

				this->K_capacity = src.K_size + 16;
				this->K_begin = 0;
				this->K_size = src.K_size;
				this->K_buffer = allocator_traits::allocate(alloc, this->K_capacity);

#		if __cpp_exceptions
				try {
#		endif

					if (src.K_capacity - src.K_begin >= src.K_size) {
						pointer begin = src.K_buffer + src.K_begin;
						kerbal::memory::uninitialized_copy_using_allocator(alloc, begin, begin + src.K_size, this->K_buffer);
					} else {
						pointer first_end = kerbal::memory::uninitialized_copy_using_allocator(alloc, src.K_buffer + src.K_begin, src.K_buffer + src.K_capacity, this->K_buffer);

#		if __cpp_exceptions
						try {
#		endif
							kerbal::memory::uninitialized_copy_using_allocator(alloc, src.K_buffer, src.K_buffer + src.K_second_len(), first_end);

#		if __cpp_exceptions
						} catch (...) {
							kerbal::memory::reverse_destroy_using_allocator(alloc, this->K_buffer, first_end);
							throw;
						}
#		endif

					}

#		if __cpp_exceptions
				} catch (...) {
					allocator_traits::deallocate(alloc, this->K_buffer, this->K_capacity);
					throw;
				}
#		endif

			}

			template <typename T>
			template <typename Alloc>
			KERBAL_CONSTEXPR20
			void rbq_allocator_unrelated<T>::K_destroy(Alloc & alloc) KERBAL_NOEXCEPT
			{
				typedef kerbal::memory::allocator_traits<Alloc> allocator_traits;

				if (this->K_capacity - this->K_begin >= this->K_size) {
					pointer begin = this->K_buffer + this->K_begin;
					kerbal::memory::reverse_destroy_using_allocator(alloc, begin, begin + this->K_size);
				} else {
					kerbal::memory::reverse_destroy_using_allocator(alloc, this->K_buffer, this->K_buffer + this->K_second_len());
					kerbal::memory::reverse_destroy_using_allocator(alloc, this->K_buffer + this->K_begin, this->K_buffer + this->K_capacity);
				}
				if (this->K_capacity != 0) {
					allocator_traits::deallocate(alloc, this->K_buffer, this->K_capacity);
				}
			}

#		if __cplusplus >= 201103L

			template <typename T>
			template <typename Alloc, typename ... Args>
			KERBAL_CONSTEXPR20
			void
			rbq_allocator_unrelated<T>::emplace_using_allocator(Alloc & alloc, Args&& ... args)
			{
				typedef kerbal::memory::allocator_traits<Alloc> allocator_traits;

				if (this->K_size == this->K_capacity) {

					size_type new_capacity = this->K_capacity == 0 ? 1 : 2 * this->K_capacity;
					pointer new_buffer = allocator_traits::allocate(alloc, new_capacity);

					try {
						allocator_traits::construct(alloc, &new_buffer[this->K_size], kerbal::utility::forward<Args>(args)...);
						try {
							pointer first_end = kerbal::memory::uninitialized_copy_using_allocator(alloc, this->K_buffer + this->K_begin, this->K_buffer + this->K_capacity,
																								   new_buffer);

							try {
								kerbal::memory::uninitialized_copy_using_allocator(alloc, this->K_buffer, this->K_buffer + this->K_second_len(), first_end);
							} catch (...) {
								kerbal::memory::reverse_destroy_using_allocator(alloc, new_buffer, first_end);
								throw;
							}
						} catch (...) {
							allocator_traits::destroy(alloc, &new_buffer[this->K_size]);
							throw;
						}
					} catch (...) {
						allocator_traits::deallocate(alloc, new_buffer, new_capacity);
						throw;
					}

					kerbal::memory::reverse_destroy_using_allocator(alloc, this->K_buffer, this->K_buffer + this->K_capacity);
					if (this->K_capacity != 0) {
						allocator_traits::deallocate(alloc, this->K_buffer, this->K_capacity);
					}
					this->K_buffer = new_buffer;
					this->K_capacity = new_capacity;
					this->K_begin = 0;

				} else {
					size_type idx = (this->K_capacity - this->K_begin > this->K_size) // note: greater than, not greater equal than
							? this->K_begin + this->K_size
							: this->K_second_len();
					allocator_traits::construct(alloc, &this->K_buffer[idx], kerbal::utility::forward<Args>(args)...);
				}
				++this->K_size;
			}

#		endif


			template <typename T>
			template <typename Alloc>
			KERBAL_CONSTEXPR20
			void rbq_allocator_unrelated<T>::push_using_allocator(Alloc & alloc, const_reference src)
			{
				this->emplace_using_allocator(alloc, src);
			}

#		if __cplusplus >= 201103L

			template <typename T>
			template <typename Alloc>
			KERBAL_CONSTEXPR20
			void rbq_allocator_unrelated<T>::push_using_allocator(Alloc & alloc, rvalue_reference src)
			{
				this->emplace_using_allocator(alloc, kerbal::compatibility::move(src));
			}

#		endif

			template <typename T>
			template <typename Alloc>
			KERBAL_CONSTEXPR20
			void
			rbq_allocator_unrelated<T>::pop_using_allocator(Alloc & alloc)
			{
				typedef kerbal::memory::allocator_traits<Alloc> allocator_traits;

				allocator_traits::destroy(alloc, &this->K_buffer[this->K_begin]);
				++this->K_begin;
				if (this->K_begin == this->K_capacity) {
					this->K_begin = 0;
				}
				--this->K_size;
			}

			template <typename T>
			template <typename Alloc>
			KERBAL_CONSTEXPR20
			void rbq_allocator_unrelated<T>::clear_using_allocator(Alloc & alloc) KERBAL_NOEXCEPT
			{
				if (this->K_capacity - this->K_begin >= this->K_size) {
					pointer begin = this->K_buffer + this->K_begin;
					kerbal::memory::reverse_destroy_using_allocator(alloc, begin, begin + this->K_size);
				} else {
					kerbal::memory::reverse_destroy_using_allocator(alloc, this->K_buffer, this->K_buffer + this->K_second_len());
					kerbal::memory::reverse_destroy_using_allocator(alloc, this->K_buffer + this->K_begin, this->K_buffer + this->K_capacity);
				}
				this->K_begin = 0;
				this->K_size = 0;
			}

			template <typename T>
			KERBAL_CONSTEXPR14
			typename rbq_allocator_unrelated<T>::reference
			rbq_allocator_unrelated<T>::front()
			{
				return this->K_buffer[this->K_begin];
			}

			template <typename T>
			KERBAL_CONSTEXPR
			typename rbq_allocator_unrelated<T>::const_reference
			rbq_allocator_unrelated<T>::front() const
			{
				return this->K_buffer[this->K_begin];
			}

			template <typename T>
			KERBAL_CONSTEXPR
			typename rbq_allocator_unrelated<T>::size_type
			rbq_allocator_unrelated<T>::capacity() const KERBAL_NOEXCEPT
			{
				return this->K_capacity;
			}

			template <typename T>
			KERBAL_CONSTEXPR
			typename rbq_allocator_unrelated<T>::size_type
			rbq_allocator_unrelated<T>::size() const KERBAL_NOEXCEPT
			{
				return this->K_size;
			}

			template <typename T>
			KERBAL_CONSTEXPR
			bool
			rbq_allocator_unrelated<T>::empty() const KERBAL_NOEXCEPT
			{
				return this->K_size == 0;
			}

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_RING_BUFFER_QUEUE_BASE_RING_BUFFER_QUEUE_BASE_IMPL_HPP
