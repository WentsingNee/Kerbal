/**
 * @file       ring_buffer_queue.decl.hpp
 * @brief
 * @date       2022-03-30
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_RING_BUFFER_QUEUE_RING_BUFFER_QUEUE_DECL_HPP
#define KERBAL_CONTAINER_RING_BUFFER_QUEUE_RING_BUFFER_QUEUE_DECL_HPP

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/assign/ilist.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif

#include <kerbal/container/ring_buffer_queue/ring_buffer_queue.fwd.hpp>

#include <kerbal/container/detail/ring_buffer_queue_base/ring_buffer_queue_base.decl.hpp>
#include <kerbal/container/detail/container_allocator_overload.hpp>


namespace kerbal
{

	namespace container
	{

		template <typename T, typename Allocator>
		class ring_buffer_queue :
				protected kerbal::container::detail::container_allocator_overload<Allocator>,
				protected kerbal::container::detail::rbq_allocator_unrelated<T>
		{
			private:
				typedef kerbal::container::detail::rbq_allocator_unrelated<T> rbq_allocator_unrelated;
				typedef kerbal::container::detail::container_allocator_overload<Allocator> container_allocator_overload;
				typedef typename container_allocator_overload::allocator_type allocator_type;

			public:
				typedef typename rbq_allocator_unrelated::value_type		value_type;
				typedef typename rbq_allocator_unrelated::const_type		const_type;
				typedef typename rbq_allocator_unrelated::reference			reference;
				typedef typename rbq_allocator_unrelated::const_reference	const_reference;
				typedef typename rbq_allocator_unrelated::pointer			pointer;
				typedef typename rbq_allocator_unrelated::const_pointer		const_pointer;

#		if __cplusplus >= 201103L
				typedef typename rbq_allocator_unrelated::rvalue_reference			rvalue_reference;
				typedef typename rbq_allocator_unrelated::const_rvalue_reference	const_rvalue_reference;
#		endif

				typedef typename rbq_allocator_unrelated::size_type			size_type;
				typedef typename rbq_allocator_unrelated::difference_type	difference_type;

			protected:
				using container_allocator_overload::alloc;

			public:
				KERBAL_CONSTEXPR20
				ring_buffer_queue();

				KERBAL_CONSTEXPR20
				ring_buffer_queue(const ring_buffer_queue & src);

				KERBAL_CONSTEXPR20
				ring_buffer_queue(const ring_buffer_queue & src, const allocator_type & alloc);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				ring_buffer_queue(ring_buffer_queue && src);

#		endif

				KERBAL_CONSTEXPR20
				~ring_buffer_queue();

			public:

				KERBAL_CONSTEXPR20
				ring_buffer_queue & operator=(const ring_buffer_queue & src);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				ring_buffer_queue & operator=(ring_buffer_queue && src);

#		endif

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				ring_buffer_queue & operator=(std::initializer_list<value_type> ilist);

#		else

				template <typename U>
				ring_buffer_queue & operator=(const kerbal::assign::assign_list<U> & ilist);

#		endif


				KERBAL_CONSTEXPR20
				void assign(const ring_buffer_queue & src);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void assign(ring_buffer_queue && src);

#		endif

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void assign(std::initializer_list<value_type> ilist);

#		else

				template <typename U>
				void assign(const kerbal::assign::assign_list<U> & ilist);

#		endif


#		if __cplusplus >= 201103L

				template <typename ... Args>
				KERBAL_CONSTEXPR20
				void emplace(Args&& ... args);

#		else

#		endif

				KERBAL_CONSTEXPR20
				void push(const_reference src);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void push(rvalue_reference src);

#		endif

				KERBAL_CONSTEXPR20
				reference front();

				KERBAL_CONSTEXPR20
				const_reference front() const;

				KERBAL_CONSTEXPR20
				void pop();

				KERBAL_CONSTEXPR20
				void clear() KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				size_type size() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				size_type max_size() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				size_type capacity() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				bool empty() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				void reserve(size_type n);

				KERBAL_CONSTEXPR20
				void swap(ring_buffer_queue & with);

		};

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_RING_BUFFER_QUEUE_RING_BUFFER_QUEUE_DECL_HPP
