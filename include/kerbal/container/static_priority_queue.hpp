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

#ifndef KERBAL_CONTAINER_STATIC_PRIORITY_QUEUE_HPP
#define KERBAL_CONTAINER_STATIC_PRIORITY_QUEUE_HPP

#include <kerbal/algorithm/heap.hpp>
#include <kerbal/container/static_vector.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/type_traits/enable_if.hpp>

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif


namespace kerbal
{

	namespace container
	{

		template <typename Tp, size_t N, typename KeyCompare = std::less<Tp> >
		class static_priority_queue
		{
			public:
				typedef kerbal::container::static_vector<Tp, N>		container_type;
				typedef KeyCompare									value_compare;

				typedef Tp							value_type;
				typedef const value_type			const_type;
				typedef value_type&					reference;
				typedef const value_type&			const_reference;
				typedef value_type*					pointer;
				typedef const value_type*			const_pointer;

#		if __cplusplus >= 201103L
				typedef value_type&&				rvalue_reference;
				typedef const value_type&&			const_rvalue_reference;
#		endif

				typedef typename container_type::size_type					size_type;
				typedef typename container_type::difference_type			difference_type;

				typedef typename container_type::const_iterator				const_iterator;
				typedef typename container_type::const_reverse_iterator		const_reverse_iterator;


			private:
				container_type c;
				value_compare vc;

			public:
				KERBAL_CONSTEXPR
				static_priority_queue() :
						c(), vc()
				{
				}

				KERBAL_CONSTEXPR
				explicit static_priority_queue(value_compare kc) :
						c(), vc(kc)
				{
				}

				template <typename InputIterator>
				KERBAL_CONSTEXPR14
				static_priority_queue(InputIterator first, InputIterator last,
						typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
								int
						>::type = 0) :
						c(first, last), vc()
				{
					kerbal::algorithm::make_heap(c.begin(), c.end(), this->vc);
				}

				template <typename InputIterator>
				KERBAL_CONSTEXPR14
				static_priority_queue(InputIterator first, InputIterator last, value_compare kc,
						typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
								int
						>::type = 0) :
						c(first, last), vc(kc)
				{
					kerbal::algorithm::make_heap(c.begin(), c.end(), this->vc);
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				static_priority_queue(std::initializer_list<value_type> src) :
						static_priority_queue(src.begin(), src.end())
				{
				}

				KERBAL_CONSTEXPR14
				static_priority_queue(std::initializer_list<value_type> src, value_compare vc) :
						static_priority_queue(src.begin(), src.end(), vc)
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
				const_reference top() const
				{
					return c.front();
				}

				KERBAL_CONSTEXPR14
				void push(const_reference val)
				{
					c.push_back(val);
					kerbal::algorithm::push_heap(c.begin(), c.end(), vc);
				}

				template <typename InputIterator>
				KERBAL_CONSTEXPR14
				void push(InputIterator first, InputIterator last)
				{
					while (first != last) {
						this->push(*first);
						++first;
					}
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				void push(rvalue_reference val)
				{
					c.push_back(std::move(val));
					kerbal::algorithm::push_heap(c.begin(), c.end(), vc);
				}

				template <typename ... Args>
				KERBAL_CONSTEXPR14
				void emplace(Args&&... args)
				{
					c.emplace_back(std::forward<Args>(args)...);
					kerbal::algorithm::push_heap(c.begin(), c.end(), vc);
				}

#		endif

				KERBAL_CONSTEXPR14
				void pop()
				{
					kerbal::algorithm::pop_heap(c.begin(), c.end(), vc);
					c.pop_back();
				}

				template <size_t M>
				KERBAL_CONSTEXPR14
				void swap(static_priority_queue<Tp, M> & with)
				{
					c.swap(with);
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

		};

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_STATIC_PRIORITY_QUEUE_HPP
