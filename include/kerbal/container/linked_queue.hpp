/**
 * @file       linked_queue.hpp
 * @brief
 * @date       2019-11-16
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_LINKED_QUEUE_HPP_
#define KERBAL_CONTAINER_LINKED_QUEUE_HPP_

#include <kerbal/container/single_list.hpp>

namespace kerbal
{
	namespace container
	{

		template <typename Tp, typename Sequence = kerbal::container::single_list<Tp> >
		class linked_queue
		{
			public:
				typedef Tp value_type;
				typedef const Tp const_type;
				typedef Tp& reference;
				typedef const Tp& const_reference;
				typedef Sequence container_type;

#		if __cplusplus >= 201103L
				typedef value_type&& rvalue_reference;
				typedef const value_type&& const_rvalue_reference;
#		endif

				typedef typename Sequence::size_type size_type;

			private:
				Sequence c;

			public:
				linked_queue() :
						c()
				{
				}

#if __cplusplus >= 201103L
				linked_queue(std::initializer_list<value_type> src) :
						c(src)
				{
				}
#endif

				bool empty() const
				{
					return c.empty();
				}

				size_type size() const
				{
					return c.size();
				}

				KERBAL_CONSTEXPR size_type max_size() const
				{
					return c.max_size();
				}

				reference front()
				{
					return c.front();
				}

				const_reference front() const
				{
					return c.front();
				}

				reference back()
				{
					return c.back();
				}

				const_reference back() const
				{
					return c.back();
				}

				void push_back(const_reference val)
				{
					c.push_back(val);
				}

#if __cplusplus >= 201103L
				void push_back(rvalue_reference val)
				{
					c.push_back(val);
				}

				template <typename ... Args>
				void emplace_back(Args&&... args)
				{
					c.emplace_back(std::forward<Args>(args)...);
				}
#endif

				void pop_front()
				{
					c.pop_front();
				}

				void clear()
				{
					c.clear();
				}

				void swap(linked_queue & with)
				{
					c.swap(with.c);
				}

				template <typename Sequence>
				friend bool operator==(const linked_queue<Tp, Sequence> & lhs, const linked_queue<Tp, Sequence> & rhs);

				template <typename Sequence>
				friend bool operator!=(const linked_queue<Tp, Sequence> & lhs, const linked_queue<Tp, Sequence> & rhs);

				template <typename Sequence>
				friend bool operator<(const linked_queue<Tp, Sequence> & lhs, const linked_queue<Tp, Sequence> & rhs);

				template <typename Sequence>
				friend bool operator<=(const linked_queue<Tp, Sequence> & lhs, const linked_queue<Tp, Sequence> & rhs);

				template <typename Sequence>
				friend bool operator>(const linked_queue<Tp, Sequence> & lhs, const linked_queue<Tp, Sequence> & rhs);

				template <typename Sequence>
				friend bool operator>=(const linked_queue<Tp, Sequence> & lhs, const linked_queue<Tp, Sequence> & rhs);

		};

		/**
		 * Judge whether the queue is equal to the other one.
		 * @param rhs another queue
		 */
		template <typename Tp, typename Sequence>
		bool operator==(const linked_queue<Tp, Sequence> & lhs, const linked_queue<Tp, Sequence> & rhs)
		{
			return lhs.c == rhs.c;
		}

		template <typename Tp, typename Sequence>
		bool operator!=(const linked_queue<Tp, Sequence> & lhs, const linked_queue<Tp, Sequence> & rhs)
		{
			return lhs.c != rhs.c;
		}

		template <typename Tp, typename Sequence>
		bool operator<(const linked_queue<Tp, Sequence> & lhs, const linked_queue<Tp, Sequence> & rhs)
		{
			return lhs.c < rhs.c;
		}

		template <typename Tp, typename Sequence>
		bool operator<=(const linked_queue<Tp, Sequence> & lhs, const linked_queue<Tp, Sequence> & rhs)
		{
			return lhs.c <= rhs.c;
		}

		template <typename Tp, typename Sequence>
		bool operator>(const linked_queue<Tp, Sequence> & lhs, const linked_queue<Tp, Sequence> & rhs)
		{
			return lhs.c > rhs.c;
		}

		template <typename Tp, typename Sequence>
		bool operator>=(const linked_queue<Tp, Sequence> & lhs, const linked_queue<Tp, Sequence> & rhs)
		{
			return lhs.c >= rhs.c;
		}

	}
}

#endif /* KERBAL_CONTAINER_LINKED_QUEUE_HPP_ */
