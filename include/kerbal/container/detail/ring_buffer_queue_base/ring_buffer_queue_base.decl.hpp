/**
 * @file       ring_buffer_queue_base.decl.hpp
 * @brief
 * @date       2022-03-30
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_RING_BUFFER_QUEUE_BASE_RING_BUFFER_QUEUE_BASE_DECL_HPP
#define KERBAL_CONTAINER_DETAIL_RING_BUFFER_QUEUE_BASE_RING_BUFFER_QUEUE_BASE_DECL_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/numeric/numeric_limits.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename T>
			class rbq_allocator_unrelated
			{
				public:
					typedef T							value_type;
					typedef const value_type			const_type;
					typedef value_type&					reference;
					typedef const value_type&			const_reference;
					typedef value_type*					pointer;
					typedef const value_type*			const_pointer;

#		if __cplusplus >= 201103L
					typedef value_type&&				rvalue_reference;
					typedef const value_type&&			const_rvalue_reference;
#		endif

					typedef std::size_t					size_type;
					typedef std::ptrdiff_t				difference_type;

				protected:
					pointer k_buffer;
					size_type k_capacity;
					size_type k_begin;
					size_type k_size;

				protected:

					KERBAL_CONSTEXPR
					rbq_allocator_unrelated() KERBAL_NOEXCEPT;

					template <typename Alloc>
					KERBAL_CONSTEXPR20
					rbq_allocator_unrelated(const rbq_allocator_unrelated & src, Alloc & alloc);

#			if __cplusplus >= 201103L

					struct is_nothrow_move_constructible : kerbal::type_traits::true_type
					{
					};

					KERBAL_CONSTEXPR14
					rbq_allocator_unrelated(rbq_allocator_unrelated && src) KERBAL_NOEXCEPT;

				private:

					// move construct using allocator, allocator is equal
					KERBAL_CONSTEXPR14
					void k_move_cnstrct_ua_ae(rbq_allocator_unrelated && src) KERBAL_NOEXCEPT;

					// move construct using allocator, allocator is not equal
					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void k_move_cnstrct_ua_ane(Allocator & this_alloc, rbq_allocator_unrelated && src);

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void k_move_cnstrct_ua_helper(Allocator & this_alloc, Allocator && src_alloc, rbq_allocator_unrelated && src,
												   kerbal::type_traits::false_type /*is_always_equal*/);

					template <typename Allocator>
					KERBAL_CONSTEXPR14
					void k_move_cnstrct_ua_helper(Allocator & this_alloc, Allocator && src_alloc, rbq_allocator_unrelated && src,
												   kerbal::type_traits::true_type /*is_always_equal*/) KERBAL_NOEXCEPT;

				public:

					template <typename Allocator>
					struct is_nothrow_move_constructible_using_allocator :
							kerbal::memory::allocator_traits<Allocator>::is_always_equal
					{
					};

					template <typename Allocator>
					KERBAL_CONSTEXPR14
					rbq_allocator_unrelated(Allocator & this_alloc, Allocator && src_alloc, rbq_allocator_unrelated && src)
							KERBAL_CONDITIONAL_NOEXCEPT(is_nothrow_move_constructible_using_allocator<Allocator>::value)
					;

#			endif

					template <typename Alloc>
					KERBAL_CONSTEXPR20
					void destroy_using_allocator(Alloc & alloc) KERBAL_NOEXCEPT;

				private:
					template <typename Alloc>
					KERBAL_CONSTEXPR20
					void k_emplace_realloc_aux(Alloc & alloc);

				public:

#		if __cplusplus >= 201103L

					template <typename Alloc, typename ... Args>
					KERBAL_CONSTEXPR20
					void emplace_using_allocator(Alloc & alloc, Args&& ... args);

#		else

#		endif

					template <typename Alloc>
					KERBAL_CONSTEXPR20
					void push_using_allocator(Alloc & alloc, const_reference src);

#		if __cplusplus >= 201103L

					template <typename Alloc>
					KERBAL_CONSTEXPR20
					void push_using_allocator(Alloc & alloc, rvalue_reference src);

#		endif

					template <typename Alloc>
					KERBAL_CONSTEXPR20
					void pop_using_allocator(Alloc & alloc);

					template <typename Alloc>
					KERBAL_CONSTEXPR20
					void clear_using_allocator(Alloc & alloc) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					reference front();

					KERBAL_CONSTEXPR
					const_reference front() const;

				//===================
				// capacity

					KERBAL_CONSTEXPR
					size_type capacity() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR
					size_type size() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR
					size_type max_size() const KERBAL_NOEXCEPT
					{
						return kerbal::numeric::numeric_limits<size_type>::MAX::value / sizeof(value_type);
					}

					KERBAL_CONSTEXPR
					bool empty() const KERBAL_NOEXCEPT;

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void reserve_using_allocator(Allocator & alloc, size_type new_capacity);

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void shrink_to_fit_using_allocator(Allocator & alloc);

				private:

					bool k_no_wrapper() const KERBAL_NOEXCEPT
					{
						return this->k_capacity - this->k_begin >= this->k_size;
					}

					KERBAL_CONSTEXPR
					pointer k_first_begin() KERBAL_NOEXCEPT
					{
						return this->k_buffer + this->k_begin;
					}

					KERBAL_CONSTEXPR
					pointer k_first_end() KERBAL_NOEXCEPT
					{
						return this->k_buffer + this->k_capacity;
					}

					KERBAL_CONSTEXPR
					const_pointer k_first_begin() const KERBAL_NOEXCEPT
					{
						return this->k_buffer + this->k_begin;
					}

					KERBAL_CONSTEXPR
					const_pointer k_first_end() const KERBAL_NOEXCEPT
					{
						return this->k_buffer + this->k_capacity;
					}

					KERBAL_CONSTEXPR
					size_type k_first_len() const KERBAL_NOEXCEPT
					{
						return this->k_capacity - this->k_begin;
					}

					KERBAL_CONSTEXPR
					pointer k_second_begin() KERBAL_NOEXCEPT
					{
						return this->k_buffer;
					}

					KERBAL_CONSTEXPR
					pointer k_second_end() KERBAL_NOEXCEPT
					{
						return this->k_buffer + this->k_second_len();
					}

					KERBAL_CONSTEXPR
					const_pointer k_second_begin() const KERBAL_NOEXCEPT
					{
						return this->k_buffer;
					}

					KERBAL_CONSTEXPR
					const_pointer k_second_end() const KERBAL_NOEXCEPT
					{
						return this->k_buffer + this->k_second_len();
					}

					KERBAL_CONSTEXPR
					size_type k_second_len() const KERBAL_NOEXCEPT
					{
						return this->k_size - this->k_first_len();
					}

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_RING_BUFFER_QUEUE_BASE_RING_BUFFER_QUEUE_BASE_DECL_HPP
