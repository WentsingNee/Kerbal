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
#include <kerbal/numeric/numeric_limits.hpp>

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
					pointer K_buffer;
					size_type K_capacity;
					size_type K_begin;
					size_type K_size;

				protected:

					KERBAL_CONSTEXPR
					rbq_allocator_unrelated() KERBAL_NOEXCEPT;

					template <typename Alloc>
					KERBAL_CONSTEXPR20
					rbq_allocator_unrelated(const rbq_allocator_unrelated & src, Alloc & alloc);

					template <typename Alloc>
					KERBAL_CONSTEXPR20
					void K_destroy(Alloc & alloc) KERBAL_NOEXCEPT;

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


				private:

					KERBAL_CONSTEXPR
					size_type K_second_len() const KERBAL_NOEXCEPT
					{
						return this->K_size - (this->K_capacity - this->K_begin);
					}

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_RING_BUFFER_QUEUE_BASE_RING_BUFFER_QUEUE_BASE_DECL_HPP
