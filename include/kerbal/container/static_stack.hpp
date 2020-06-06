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

#ifndef KERBAL_CONTAINER_STATIC_STACK_HPP
#define KERBAL_CONTAINER_STATIC_STACK_HPP

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
		template <typename Tp, std::size_t N>
		class static_stack
		{
			public:
				typedef kerbal::container::static_vector<Tp, N>		container_type;

				typedef Tp						value_type;
				typedef const Tp				const_type;
				typedef Tp&						reference;
				typedef const Tp&				const_reference;

#		if __cplusplus >= 201103L
				typedef value_type&&			rvalue_reference;
				typedef const value_type&&		const_rvalue_reference;
#		endif

				typedef typename container_type::size_type					size_type;

				typedef typename container_type::const_iterator				const_iterator;
				typedef typename container_type::const_reverse_iterator		const_reverse_iterator;

			private:
				container_type c;

			public:
				KERBAL_CONSTEXPR
				static_stack() :
						c()
				{
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				static_stack(std::initializer_list<value_type> src) :
						c(src)
				{
				}

#		endif

				KERBAL_CONSTEXPR
				bool empty() const
				{
					return c.empty();
				}

				KERBAL_CONSTEXPR
				bool full() const
				{
					return c.full();
				}

				KERBAL_CONSTEXPR
				size_type size() const
				{
					return c.size();
				}

				KERBAL_CONSTEXPR
				size_type max_size() const
				{
					return c.max_size();
				}

				KERBAL_CONSTEXPR14
				reference top()
				{
					return c.back();
				}

				KERBAL_CONSTEXPR14
				const_reference top() const
				{
					return c.back();
				}

				KERBAL_CONSTEXPR14
				void push(const_reference val)
				{
					c.push_back(val);
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				void push(rvalue_reference val)
				{
					c.push_back(val);
				}

#		endif

#		if __cplusplus >= 201103L

				template <typename ... Args>
				KERBAL_CONSTEXPR14
				void emplace(Args&&... args)
				{
					c.emplace_back(std::forward<Args>(args)...);
				}

#		endif

				KERBAL_CONSTEXPR14
				void pop()
				{
					c.pop_back();
				}

				KERBAL_CONSTEXPR
				const_iterator begin() const
				{
					return c.cbegin();
				}

				KERBAL_CONSTEXPR
				const_iterator end() const
				{
					return c.cend();
				}

				KERBAL_CONSTEXPR
				const_iterator cbegin() const
				{
					return c.cbegin();
				}

				KERBAL_CONSTEXPR
				const_iterator cend() const
				{
					return c.cend();
				}

				KERBAL_CONSTEXPR
				const_reverse_iterator rbegin() const
				{
					return c.crbegin();
				}

				KERBAL_CONSTEXPR
				const_reverse_iterator rend() const
				{
					return c.crend();
				}

				KERBAL_CONSTEXPR
				const_reverse_iterator crbegin() const
				{
					return c.crbegin();
				}

				KERBAL_CONSTEXPR
				const_reverse_iterator crend() const
				{
					return c.crend();
				}

				KERBAL_CONSTEXPR14
				void clear()
				{
					c.clear();
				}

				KERBAL_CONSTEXPR14
				void swap(static_stack & with)
				{
					c.swap(with.c);
				}

				template <size_t M>
				friend KERBAL_CONSTEXPR14
				bool operator==(const static_stack<Tp, M> & lhs, const static_stack<Tp, N> & rhs);

				template <size_t M>
				friend KERBAL_CONSTEXPR14
				bool operator!=(const static_stack<Tp, M> & lhs, const static_stack<Tp, N> & rhs);

				template <size_t M>
				friend KERBAL_CONSTEXPR14
				bool operator<(const static_stack<Tp, M> & lhs, const static_stack<Tp, N> & rhs);

				template <size_t M>
				friend KERBAL_CONSTEXPR14
				bool operator<=(const static_stack<Tp, M> & lhs, const static_stack<Tp, N> & rhs);

				template <size_t M>
				friend KERBAL_CONSTEXPR14
				bool operator>(const static_stack<Tp, M> & lhs, const static_stack<Tp, N> & rhs);

				template <size_t M>
				friend KERBAL_CONSTEXPR14
				bool operator>=(const static_stack<Tp, M> & lhs, const static_stack<Tp, N> & rhs);

		};

		/**
		 * Judge whether the stack is equal to the other one.
		 * @param rhs another stack
		 */
		template <typename Tp, size_t M, size_t N>
		KERBAL_CONSTEXPR14
		bool operator==(const static_stack<Tp, M> & lhs, const static_stack<Tp, N> & rhs)
		{
			return lhs.c == rhs.c;
		}

		template <typename Tp, size_t M, size_t N>
		KERBAL_CONSTEXPR14
		bool operator!=(const static_stack<Tp, M> & lhs, const static_stack<Tp, N> & rhs)
		{
			return lhs.c != rhs.c;
		}

		template <typename Tp, size_t M, size_t N>
		KERBAL_CONSTEXPR14
		bool operator<(const static_stack<Tp, M> & lhs, const static_stack<Tp, N> & rhs)
		{
			return lhs.c < rhs.c;
		}

		template <typename Tp, size_t M, size_t N>
		KERBAL_CONSTEXPR14
		bool operator<=(const static_stack<Tp, M> & lhs, const static_stack<Tp, N> & rhs)
		{
			return lhs.c <= rhs.c;
		}

		template <typename Tp, size_t M, size_t N>
		KERBAL_CONSTEXPR14
		bool operator>(const static_stack<Tp, M> & lhs, const static_stack<Tp, N> & rhs)
		{
			return lhs.c > rhs.c;
		}

		template <typename Tp, size_t M, size_t N>
		KERBAL_CONSTEXPR14
		bool operator>=(const static_stack<Tp, M> & lhs, const static_stack<Tp, N> & rhs)
		{
			return lhs.c >= rhs.c;
		}

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_STATIC_STACK_HPP
