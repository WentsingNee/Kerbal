/**
 * @file       ring_buffer_queue.impl.hpp
 * @brief
 * @date       2022-06-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_RING_BUFFER_QUEUE_RING_BUFFER_QUEUE_IMPL_HPP
#define KERBAL_CONTAINER_RING_BUFFER_QUEUE_RING_BUFFER_QUEUE_IMPL_HPP

#include <kerbal/assign/ilist.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/utility/forward.hpp>

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif

#include <kerbal/container/ring_buffer_queue/ring_buffer_queue.decl.hpp>
#include <kerbal/container/detail/ring_buffer_queue_base/ring_buffer_queue_base.impl.hpp>


namespace kerbal
{

	namespace container
	{

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		ring_buffer_queue<T, Allocator>::ring_buffer_queue() :
				rbq_allocator_unrelated()
		{
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		ring_buffer_queue<T, Allocator>::ring_buffer_queue(const ring_buffer_queue & src) :
				container_allocator_overload(src.alloc()),
				rbq_allocator_unrelated(static_cast<const rbq_allocator_unrelated &>(src), this->alloc())
		{
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		ring_buffer_queue<T, Allocator>::ring_buffer_queue(const ring_buffer_queue & src, const allocator_type & alloc) :
				container_allocator_overload(alloc),
				rbq_allocator_unrelated(static_cast<const rbq_allocator_unrelated &>(src), this->alloc())
		{
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		ring_buffer_queue<T, Allocator>::~ring_buffer_queue()
		{
			this->rbq_allocator_unrelated::K_destroy(this->alloc());
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		ring_buffer_queue<T, Allocator> &
		ring_buffer_queue<T, Allocator>::operator=(const ring_buffer_queue & src)
		{
			this->assign(src);
			return *this;
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		ring_buffer_queue<T, Allocator> &
		ring_buffer_queue<T, Allocator>::operator=(ring_buffer_queue && src)
		{
			this->assign(kerbal::compatibility::move(src));
			return *this;
		}

#	endif


#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		ring_buffer_queue<T, Allocator> &
		ring_buffer_queue<T, Allocator>::operator=(std::initializer_list<value_type> ilist)
		{
			this->assign(ilist);
			return *this;
		}

#	else

		template <typename T, typename Allocator>
		template <typename U>
		ring_buffer_queue<T, Allocator> &
		ring_buffer_queue<T, Allocator>::operator=(const kerbal::assign::assign_list<U> & ilist)
		{
			this->assign(ilist);
			return *this;
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		void ring_buffer_queue<T, Allocator>::emplace(Args&& ... args)
		{
			this->rbq_allocator_unrelated::emplace_using_allocator(this->alloc(), kerbal::utility::forward<Args>(args)...);
		}

#	else
#	endif

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void ring_buffer_queue<T, Allocator>::push(const_reference src)
		{
			this->rbq_allocator_unrelated::push_using_allocator(this->alloc(), src);
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void ring_buffer_queue<T, Allocator>::push(rvalue_reference src)
		{
			this->rbq_allocator_unrelated::push_using_allocator(this->alloc(), kerbal::compatibility::move(src));
		}

#	endif

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		typename ring_buffer_queue<T, Allocator>::reference
		ring_buffer_queue<T, Allocator>::front()
		{
			return this->rbq_allocator_unrelated::front();
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		typename ring_buffer_queue<T, Allocator>::const_reference
		ring_buffer_queue<T, Allocator>::front() const
		{
			return this->rbq_allocator_unrelated::front();
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void ring_buffer_queue<T, Allocator>::pop()
		{
			return this->rbq_allocator_unrelated::pop_using_allocator(this->alloc());
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void ring_buffer_queue<T, Allocator>::clear() KERBAL_NOEXCEPT
		{
			return this->rbq_allocator_unrelated::clear_using_allocator(this->alloc());
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		typename ring_buffer_queue<T, Allocator>::size_type
		ring_buffer_queue<T, Allocator>::size() const KERBAL_NOEXCEPT
		{
			return this->rbq_allocator_unrelated::size();
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		typename ring_buffer_queue<T, Allocator>::size_type
		ring_buffer_queue<T, Allocator>::max_size() const KERBAL_NOEXCEPT
		{
			return this->rbq_allocator_unrelated::max_size();
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		typename ring_buffer_queue<T, Allocator>::size_type
		ring_buffer_queue<T, Allocator>::capacity() const KERBAL_NOEXCEPT
		{
			return this->rbq_allocator_unrelated::capacity();
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		bool ring_buffer_queue<T, Allocator>::empty() const KERBAL_NOEXCEPT
		{
			return this->rbq_allocator_unrelated::empty();
		}

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_RING_BUFFER_QUEUE_RING_BUFFER_QUEUE_IMPL_HPP
