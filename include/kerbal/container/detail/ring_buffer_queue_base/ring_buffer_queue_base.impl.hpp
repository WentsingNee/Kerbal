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

					if (src.K_no_wrapper()) {
						pointer begin = src.K_buffer + src.K_begin;
						kerbal::memory::uninitialized_copy_using_allocator(alloc, begin, begin + src.K_size, this->K_buffer);
					} else {
						pointer first_end = kerbal::memory::uninitialized_copy_using_allocator(alloc, src.K_first_begin(), src.K_first_end(), this->K_buffer);

#		if __cpp_exceptions
						try {
#		endif
							kerbal::memory::uninitialized_copy_using_allocator(alloc, src.K_second_begin(), src.K_second_end(), first_end);

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

#		if __cplusplus >= 201103L

			template <typename Tp>
			KERBAL_CONSTEXPR14
			rbq_allocator_unrelated<Tp>::rbq_allocator_unrelated(rbq_allocator_unrelated && src) KERBAL_NOEXCEPT :
					K_buffer(src.K_buffer), K_capacity(src.K_capacity), K_begin(src.K_begin), K_size(src.K_size)
			{
				src.K_buffer = NULL;
				src.K_capacity = 0;
				src.K_begin = 0;
				src.K_size = 0;
			}

			// move construct using allocator, allocator is equal
			template <typename Tp>
			KERBAL_CONSTEXPR14
			void rbq_allocator_unrelated<Tp>::K_move_cnstrct_ua_ae(rbq_allocator_unrelated && src) KERBAL_NOEXCEPT
			{
				this->K_buffer = src.K_buffer;
				this->K_capacity = src.K_capacity;
				this->K_begin = src.K_begin;
				this->K_size = src.K_size;
				src.K_buffer = NULL;
				src.K_capacity = 0;
				src.K_begin = 0;
				src.K_size = 0;
			}

			// move construct using allocator, allocator is not equal
			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void rbq_allocator_unrelated<Tp>::K_move_cnstrct_ua_ane(Allocator & this_alloc, rbq_allocator_unrelated && src)
			{
				if (src.K_buffer != NULL) {
					typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

					this->K_capacity = src.K_size;
					this->K_buffer = allocator_traits::allocate(this_alloc, this->K_capacity);
#		if !__cpp_exceptions
					if (this->K_buffer == NULL) {
						kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
					}
#		endif

#		if __cpp_exceptions
					try {
#		endif
						if (src.K_no_wrapper()) {
							kerbal::memory::uninitialized_move_using_allocator(this_alloc, src.K_buffer, src.K_buffer + src.K_size, this->K_buffer);
						} else {
							pointer first_end = kerbal::memory::uninitialized_move_using_allocator(this_alloc, src.K_first_begin(), src.K_first_end(), this->K_buffer);
							try {
								kerbal::memory::uninitialized_move_using_allocator(this_alloc, src.K_second_begin(), src.K_second_end(), first_end);
							} catch (...) {
								kerbal::memory::reverse_destroy_using_allocator(this_alloc, this->K_buffer, first_end);
								throw;
							}
						}
#		if __cpp_exceptions
					} catch (...) {
						allocator_traits::deallocate(this_alloc, this->K_buffer, this->K_capacity);
						throw;
					}
#		endif
					this->K_begin = 0;
					this->K_size = src.K_size;
				} else {
					this->K_buffer = NULL;
					this->K_capacity = 0;
					this->K_begin = 0;
					this->K_size = 0;
				}
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void rbq_allocator_unrelated<Tp>::K_move_cnstrct_ua_helper(Allocator & this_alloc, Allocator && src_alloc, rbq_allocator_unrelated && src,
																	   kerbal::type_traits::false_type /*is_always_equal*/)
			{
				if (this_alloc != src_alloc) {
					this->K_move_cnstrct_ua_ane(this_alloc, kerbal::compatibility::move(src_alloc), kerbal::compatibility::move(src));
				} else {
					this->K_move_cnstrct_ua_ae(kerbal::compatibility::move(src));
				}
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR14
			void rbq_allocator_unrelated<Tp>::K_move_cnstrct_ua_helper(Allocator & /*this_alloc*/, Allocator && /*src_alloc*/, rbq_allocator_unrelated && src,
																	   kerbal::type_traits::true_type /*is_always_equal*/) KERBAL_NOEXCEPT
			{
				this->K_move_cnstrct_ua_ae(kerbal::compatibility::move(src));
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR14
			rbq_allocator_unrelated<Tp>::rbq_allocator_unrelated(Allocator & this_alloc, Allocator && src_alloc, rbq_allocator_unrelated && src)
					KERBAL_CONDITIONAL_NOEXCEPT(is_nothrow_move_constructible_using_allocator<Allocator>::value)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;
				typedef typename allocator_traits::is_always_equal is_always_equal;

				this->K_move_cnstrct_ua_helper(this_alloc, kerbal::compatibility::move(src_alloc), kerbal::compatibility::move(src), is_always_equal());
			}

#		endif

			template <typename T>
			template <typename Alloc>
			KERBAL_CONSTEXPR20
			void rbq_allocator_unrelated<T>::destroy_using_allocator(Alloc & alloc) KERBAL_NOEXCEPT
			{
				typedef kerbal::memory::allocator_traits<Alloc> allocator_traits;

				if (this->K_no_wrapper()) {
					pointer begin = this->K_buffer + this->K_begin;
					kerbal::memory::reverse_destroy_using_allocator(alloc, begin, begin + this->K_size);
				} else {
					kerbal::memory::reverse_destroy_using_allocator(alloc, this->K_second_begin(), this->K_second_end());
					kerbal::memory::reverse_destroy_using_allocator(alloc, this->K_first_begin(), this->K_first_end());
				}
				if (this->K_buffer != NULL) {
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
							if (this->K_no_wrapper()) {
								pointer begin = this->K_buffer + this->K_begin;
								kerbal::memory::uninitialized_copy_using_allocator(alloc, begin, begin + this->K_size, new_buffer);
							} else {
								pointer first_end = kerbal::memory::uninitialized_copy_using_allocator(alloc, this->K_first_begin(), this->K_first_end(), new_buffer);

								try {
									kerbal::memory::uninitialized_copy_using_allocator(alloc, this->K_second_begin(), this->K_second_end(), first_end);
								} catch (...) {
									kerbal::memory::reverse_destroy_using_allocator(alloc, new_buffer, first_end);
									throw;
								}
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
					if (this->K_buffer != NULL) {
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
				if (this->K_no_wrapper()) {
					pointer begin = this->K_buffer + this->K_begin;
					kerbal::memory::reverse_destroy_using_allocator(alloc, begin, begin + this->K_size);
				} else {
					kerbal::memory::reverse_destroy_using_allocator(alloc, this->K_second_begin(), this->K_second_end());
					kerbal::memory::reverse_destroy_using_allocator(alloc, this->K_first_begin(), this->K_first_end());
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
