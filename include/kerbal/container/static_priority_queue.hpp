/**
 * @file       static_priority_queue.hpp
 * @brief
 * @date       2019-5-7
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_STATIC_PRIORITY_QUEUE_HPP_
#define KERBAL_CONTAINER_STATIC_PRIORITY_QUEUE_HPP_

#include <kerbal/container/static_vector.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/type_traits/type_traits_details/enable_if.hpp>

#include <queue>

namespace kerbal
{
	namespace container
	{

		template <typename Tp, size_t N, typename KeyCompare = std::less<Tp>,
					typename Sequence = kerbal::container::static_vector<Tp, N> >
		class static_priority_queue
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

				typedef KeyCompare key_compare;

			private:
				Sequence c;
				key_compare kc;

			public:
				static_priority_queue() :
						c(), kc()
				{
				}

				explicit static_priority_queue(key_compare kc) :
						c(), kc(kc)
				{
				}

				template <typename InputIterator, typename =
						typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
						>::type
				>
				static_priority_queue(InputIterator first, InputIterator last) :
						c(first, last), kc()
				{
					std::make_heap(c.begin(), c.end(), this->kc);
				}

				template <typename InputIterator, typename =
						typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
						>::type
				>
				static_priority_queue(InputIterator first, InputIterator last, key_compare kc) :
						c(first, last), kc(kc)
				{
					std::make_heap(c.begin(), c.end(), this->kc);
				}

#if __cplusplus >= 201103L
				static_priority_queue(std::initializer_list<value_type> src) :
						static_priority_queue(src.begin(), src.end())
				{
				}

				static_priority_queue(std::initializer_list<value_type> src, key_compare kc) :
						static_priority_queue(src.begin(), src.end(), kc)
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

				const_reference top() const
				{
					return c.front();
				}

				void push(const_reference val)
				{
					c.push_back(val);
					std::push_heap(c.begin(), c.end(), kc);
				}

				template <typename InputIterator>
				void push(InputIterator first, InputIterator last)
				{
					while (first != last) {
						this->push(*first);
						++first;
					}
				}

#		if __cplusplus >= 201103L
				void push(rvalue_reference val)
				{
					c.push_back(std::move(val));
					std::push_heap(c.begin(), c.end(), kc);
				}

				template <typename ... Args>
				void emplace(Args&&... args)
				{
					c.emplace_back(std::forward<Args>(args)...);
					std::push_heap(c.begin(), c.end(), kc);
				}
#		endif

				void pop()
				{
					std::pop_heap(c.begin(), c.end(), kc);
					c.pop_back();
				}

				template <size_t M>
				void swap(static_priority_queue<Tp, M> & with)
				{
					c.swap(with);
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

		};
	}
}

#endif /* KERBAL_CONTAINER_STATIC_PRIORITY_QUEUE_HPP_ */
