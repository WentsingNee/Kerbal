/**
 * @file       linked_stack.hpp
 * @brief
 * @date       2019-11-16
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_LINKED_STACK_HPP_
#define KERBAL_CONTAINER_LINKED_STACK_HPP_

#include <kerbal/container/single_list.hpp>

namespace kerbal
{
	namespace container
	{

		template <typename Tp, typename Sequence = kerbal::container::single_list<Tp> >
		class linked_stack
		{
			public:
				typedef Tp						value_type;
				typedef const value_type		const_type;
				typedef value_type&				reference;
				typedef const value_type&		const_reference;
				typedef value_type*				pointer;
				typedef const value_type*		const_pointer;

#		if __cplusplus >= 201103L
				typedef value_type&&			rvalue_reference;
				typedef const value_type&&		const_rvalue_reference;
#		endif

				typedef typename Sequence::size_type				size_type;
				typedef typename Sequence::difference_type			difference_type;

			private:
				Sequence c;

			public:
				linked_stack() :
						c()
				{
				}

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

				reference top()
				{
					return c.front();
				}

				const_reference top() const
				{
					return c.front();
				}

				void push(const_reference val)
				{
					c.push_front(val);
				}

#		if __cplusplus >= 201103L
				void push(rvalue_reference val)
				{
					c.push_front(val);
				}

				template <typename ... Args>
				void emplace(Args&&... args)
				{
					c.emplace_front(std::forward<Args>(args)...);
				}
#		endif

				void pop()
				{
					c.pop_front();
				}

				void clear()
				{
					c.clear();
				}

				void swap(linked_stack & with)
				{
					c.swap(with.c);
				}

				/**
				 * Judge whether the stack is equal to the other one.
				 * @param rhs another stack
				 */
				friend bool operator==(const linked_stack<Tp, Sequence> & lhs, const linked_stack<Tp, Sequence> & rhs)
				{
					return lhs.c == rhs.c;
				}

				friend bool operator!=(const linked_stack<Tp, Sequence> & lhs, const linked_stack<Tp, Sequence> & rhs)
				{
					return lhs.c != rhs.c;
				}

				friend bool operator<(const linked_stack<Tp, Sequence> & lhs, const linked_stack<Tp, Sequence> & rhs)
				{
					return lhs.c < rhs.c;
				}

				friend bool operator<=(const linked_stack<Tp, Sequence> & lhs, const linked_stack<Tp, Sequence> & rhs)
				{
					return lhs.c <= rhs.c;
				}

				friend bool operator>(const linked_stack<Tp, Sequence> & lhs, const linked_stack<Tp, Sequence> & rhs)
				{
					return lhs.c > rhs.c;
				}

				friend bool operator>=(const linked_stack<Tp, Sequence> & lhs, const linked_stack<Tp, Sequence> & rhs)
				{
					return lhs.c >= rhs.c;
				}

		};

	} // namespace container

} // namespace kerbal

#endif /* KERBAL_CONTAINER_LINKED_STACK_HPP_ */
