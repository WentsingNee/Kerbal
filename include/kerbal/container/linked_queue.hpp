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

#ifndef KERBAL_CONTAINER_LINKED_QUEUE_HPP
#define KERBAL_CONTAINER_LINKED_QUEUE_HPP

#include <kerbal/container/single_list.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif

namespace kerbal
{

	namespace container
	{

		template <typename Tp, typename Sequence = kerbal::container::single_list<Tp> >
		class linked_queue
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

				typedef typename Sequence::allocator_type			allocator_type;

				typedef typename Sequence::size_type				size_type;
				typedef typename Sequence::difference_type			difference_type;

			private:
				Sequence c;

			public:
				KERBAL_CONSTEXPR20
				linked_queue()
						: c()
				{
				}

				KERBAL_CONSTEXPR20
				explicit linked_queue(const allocator_type & alloc)
						: c(alloc)
				{
				}

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				linked_queue(InputIterator first, InputIterator last,
						typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
								, int
						>::type = 0
				)
						: c(first, last)
				{
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				linked_queue(std::initializer_list<value_type> src)
						: c(src)
				{
				}

#		endif

				KERBAL_CONSTEXPR20
				bool empty() const
				{
					return c.empty();
				}

				KERBAL_CONSTEXPR20
				size_type size() const
				{
					return c.size();
				}

				KERBAL_CONSTEXPR
				size_type max_size() const
				{
					return c.max_size();
				}

				KERBAL_CONSTEXPR20
				reference front()
				{
					return c.front();
				}

				KERBAL_CONSTEXPR20
				const_reference front() const
				{
					return c.front();
				}

				KERBAL_CONSTEXPR20
				reference back()
				{
					return c.back();
				}

				KERBAL_CONSTEXPR20
				const_reference back() const
				{
					return c.back();
				}

				KERBAL_CONSTEXPR20
				void push(const_reference val)
				{
					c.push_back(val);
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void push(rvalue_reference val)
				{
					c.push_back(kerbal::compatibility::move(val));
				}

#		endif

#		if __cplusplus >= 201103L

				template <typename ... Args>
				KERBAL_CONSTEXPR20
				reference emplace(Args&& ... args)
				{
					return c.emplace_back(kerbal::utility::forward<Args>(args)...);
				}

#		else

				reference emplace()
				{
					return c.emplace_back();
				}

				template <typename Arg0>
				reference emplace(const Arg0& arg0)
				{
					return c.emplace_back(arg0);
				}

				template <typename Arg0, typename Arg1>
				reference emplace(const Arg0& arg0, const Arg1& arg1)
				{
					return c.emplace_back(arg0, arg1);
				}

				template <typename Arg0, typename Arg1, typename Arg2>
				reference emplace(const Arg0& arg0, const Arg1& arg1, const Arg2& arg2)
				{
					return c.emplace_back(arg0, arg1, arg2);
				}

#		endif

				KERBAL_CONSTEXPR20
				void pop()
				{
					c.pop_front();
				}

				KERBAL_CONSTEXPR20
				void clear()
				{
					c.clear();
				}

				KERBAL_CONSTEXPR20
				void swap(linked_queue & with)
				{
					c.swap(with.c);
				}

				/**
				 * Judge whether the queue is equal to the other one.
				 * @param rhs another queue
				 */
				KERBAL_CONSTEXPR20
				friend bool operator==(const linked_queue<Tp, Sequence> & lhs, const linked_queue<Tp, Sequence> & rhs)
				{
					return lhs.c == rhs.c;
				}

				KERBAL_CONSTEXPR20
				friend bool operator!=(const linked_queue<Tp, Sequence> & lhs, const linked_queue<Tp, Sequence> & rhs)
				{
					return lhs.c != rhs.c;
				}

				KERBAL_CONSTEXPR20
				friend bool operator<(const linked_queue<Tp, Sequence> & lhs, const linked_queue<Tp, Sequence> & rhs)
				{
					return lhs.c < rhs.c;
				}

				KERBAL_CONSTEXPR20
				friend bool operator<=(const linked_queue<Tp, Sequence> & lhs, const linked_queue<Tp, Sequence> & rhs)
				{
					return lhs.c <= rhs.c;
				}

				KERBAL_CONSTEXPR20
				friend bool operator>(const linked_queue<Tp, Sequence> & lhs, const linked_queue<Tp, Sequence> & rhs)
				{
					return lhs.c > rhs.c;
				}

				KERBAL_CONSTEXPR20
				friend bool operator>=(const linked_queue<Tp, Sequence> & lhs, const linked_queue<Tp, Sequence> & rhs)
				{
					return lhs.c >= rhs.c;
				}

		};

#	if __cplusplus >= 201703L

		template <typename InputIterator>
		linked_queue(InputIterator, InputIterator)
				-> linked_queue<typename kerbal::iterator::iterator_traits<InputIterator>::value_type>;

#	if __has_include(<memory_resource>)

		namespace pmr
		{
			template <typename Tp>
			using linked_queue = kerbal::container::linked_queue<Tp, kerbal::container::pmr::single_list<Tp> >;
		}

#	endif

#	endif

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_LINKED_QUEUE_HPP
