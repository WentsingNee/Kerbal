/**
 * @file       static_stack.hpp
 * @brief
 * @date       2018-5-2
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_STATIC_STACK_HPP_
#define KERBAL_CONTAINER_STATIC_STACK_HPP_

#include <kerbal/container/static_vector.hpp>

namespace kerbal
{
	namespace container
	{
		/**
		 * @brief Stack with flexible length that stored on automatic storage duration
		 * @details The class is an encapsulation class of stack that could be stored on
		 *          automatic storage duration. It is more effective than std::stack because
		 *          std::stack store elements on heap storage duration (that's required memory
		 *          allocate and deallocate).
		 * @tparam Tp Type of the elements.
		 * @tparam N The maximum number of elements that the stack can hold.
		 */
		template <typename Tp, std::size_t N, typename Sequence = kerbal::container::static_vector<Tp, N> >
		class static_stack
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

				typedef typename Sequence::const_iterator const_iterator;
				typedef typename Sequence::const_reverse_iterator const_reverse_iterator;

			private:
				Sequence c;

			public:
				static_stack() :
						c()
				{
				}

#if __cplusplus >= 201103L
				static_stack(std::initializer_list<value_type> src) :
						c(src)
				{
				}
#endif

				bool empty() const
				{
					return c.empty();
				}

				bool full() const
				{
					return c.full();
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
					return c.back();
				}

				const_reference top() const
				{
					return c.back();
				}

				void push(const_reference val)
				{
					c.push_back(val);
				}

#if __cplusplus >= 201103L
				void push(rvalue_reference val)
				{
					c.push_back(val);
				}
#endif

#if __cplusplus >= 201103L
				template <typename ... Args>
				void emplace(Args&&... args)
				{
					c.emplace_back(std::forward<Args>(args)...);
				}
#endif

				void pop()
				{
					c.pop_back();
				}

				const_iterator begin() const
				{
					return c.cbegin();
				}

				const_iterator end() const
				{
					return c.cend();
				}

				const_iterator cbegin() const
				{
					return c.cbegin();
				}

				const_iterator cend() const
				{
					return c.cend();
				}

				const_reverse_iterator rbegin() const
				{
					return c.crbegin();
				}

				const_reverse_iterator rend() const
				{
					return c.crend();
				}

				const_reverse_iterator crbegin() const
				{
					return c.crbegin();
				}

				const_reverse_iterator crend() const
				{
					return c.crend();
				}

				void clear()
				{
					c.clear();
				}

				void swap(static_stack & with)
				{
					c.swap(with.c);
				}

				template <size_t M>
				friend bool operator==(const static_stack<Tp, M> & lhs, const static_stack<Tp, N> & rhs);

				template <size_t M>
				friend bool operator!=(const static_stack<Tp, M> & lhs, const static_stack<Tp, N> & rhs);

				template <size_t M>
				friend bool operator<(const static_stack<Tp, M> & lhs, const static_stack<Tp, N> & rhs);

				template <size_t M>
				friend bool operator<=(const static_stack<Tp, M> & lhs, const static_stack<Tp, N> & rhs);

				template <size_t M>
				friend bool operator>(const static_stack<Tp, M> & lhs, const static_stack<Tp, N> & rhs);

				template <size_t M>
				friend bool operator>=(const static_stack<Tp, M> & lhs, const static_stack<Tp, N> & rhs);

		};

		/**
		 * Judge whether the stack is equal to the other one.
		 * @param rhs another stack
		 */
		template <typename Tp, size_t M, size_t N>
		bool operator==(const static_stack<Tp, M> & lhs, const static_stack<Tp, N> & rhs)
		{
			return lhs.c == rhs.c;
		}

		template <typename Tp, size_t M, size_t N>
		bool operator!=(const static_stack<Tp, M> & lhs, const static_stack<Tp, N> & rhs)
		{
			return lhs.c != rhs.c;
		}

		template <typename Tp, size_t M, size_t N>
		bool operator<(const static_stack<Tp, M> & lhs, const static_stack<Tp, N> & rhs)
		{
			return lhs.c < rhs.c;
		}

		template <typename Tp, size_t M, size_t N>
		bool operator<=(const static_stack<Tp, M> & lhs, const static_stack<Tp, N> & rhs)
		{
			return lhs.c <= rhs.c;
		}

		template <typename Tp, size_t M, size_t N>
		bool operator>(const static_stack<Tp, M> & lhs, const static_stack<Tp, N> & rhs)
		{
			return lhs.c > rhs.c;
		}

		template <typename Tp, size_t M, size_t N>
		bool operator>=(const static_stack<Tp, M> & lhs, const static_stack<Tp, N> & rhs)
		{
			return lhs.c >= rhs.c;
		}

	}
}

#endif /* KERBAL_CONTAINER_STATIC_STACK_HPP_ */
