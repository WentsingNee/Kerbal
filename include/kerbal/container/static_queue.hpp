/**
 * @file       static_queue.hpp
 * @brief
 * @date       2018-5-17
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_STATIC_QUEUE_HPP_
#define KERBAL_CONTAINER_STATIC_QUEUE_HPP_

#include <cctype>
#include <stdexcept>

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif

namespace kerbal
{
	namespace container
	{
		template <typename Tp, size_t N>
		class static_queue
		{
			public:
				typedef Tp value_type;
				typedef const Tp const_type;
				typedef Tp& reference;
				typedef const Tp& const_reference;
				typedef Tp* pointer;
				typedef const Tp* const_pointer;

			private:
				union
				{
						value_type p[N + 1];
				};

				pointer begin;
				pointer end;

			private:
				pointer next(pointer poi);
				const_pointer next(const_pointer poi) const;

				pointer prev(pointer poi);
				const_pointer prev(const_pointer poi) const;

			public:
				static_queue();

				static_queue(const static_queue & src);

				template <typename ForwardIterator>
				static_queue(ForwardIterator begin, ForwardIterator end);

#			if __cplusplus >= 201103L

				static_queue(std::initializer_list<value_type> src);

#			endif

				~static_queue();

				static_queue& operator=(const static_queue & src);

				void push(const_reference val);

				void pop();

				void clear();

				size_t size() const;

				bool empty() const;

				bool full() const;

				reference front();

				const_reference front() const;

				reference back();

				const_reference back() const;

				void swap(static_queue& with);

		};
	}
}

#include <kerbal/container/impl/static_queue.impl.hpp>

#endif /* KERBAL_CONTAINER_STATIC_QUEUE_HPP_ */
