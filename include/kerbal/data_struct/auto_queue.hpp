/**
 * @file		auto_queue.hpp
 * @brief
 * @date		2018年5月17日
 * @author		Peter
 * @copyright	Peter
 * @copyright
 <a href="http://thinkspirit.org/">ThinkSpirit Laboratory</a>
 of
 <a href="http://www.nuist.edu.cn/">Nanjing University of Information Science & Technology</a>
 */

#ifndef INCLUDE_KERBAL_DATA_STRUCT_AUTO_QUEUE_HPP_
#define INCLUDE_KERBAL_DATA_STRUCT_AUTO_QUEUE_HPP_

#include <cctype>
#include <initializer_list>

namespace kerbal
{
	namespace data_struct
	{
		template <typename Tp, size_t N>
		class Auto_queue
		{
			public:
				typedef Tp value_type;
				typedef const Tp const_type;
				typedef Tp& reference;
				typedef const Tp& const_reference;
				typedef Tp* pointer;
				typedef const Tp* const_pointer;

//			private:
//				typedef class iterator
//				{
//					public:
//						typedef Auto_queue::value_type value_type;
//						typedef Auto_queue::const_type const_type;
//						typedef Auto_queue::reference reference;
//						typedef Auto_queue::const_reference const_reference;
//						typedef Auto_queue::pointer pointer;
//						typedef Auto_queue::const_pointer const_pointer;
//
//					private:
//						pointer current;
//
//					public:
//						explicit iterator(pointer current);
//
//						reference operator*() const;
//						pointer operator->() const;
//
//						//前自增
//						iterator& operator++();
//						//后自增
//						iterator operator++(int);
//						iterator& operator--();
//						iterator operator--(int);
//
//						iterator operator+(int delta);
//						iterator operator-(int delta);
//
//						const iterator operator+(int delta) const;
//						const iterator operator-(int delta) const;
//
//						bool operator==(const iterator & with) const;
//						bool operator!=(const iterator & with) const;
//						bool operator<(const iterator & with) const;
//						bool operator<=(const iterator & with) const;
//						bool operator>(const iterator & with) const;
//						bool operator>=(const iterator & with) const;
//
//				} iterator;

			private:
				union
				{
						value_type p[N];
				};

				pointer begin;
				pointer end;

			private:
				pointer next(pointer poi);
				const_pointer next(const_pointer poi) const;

				pointer prev(pointer poi);
				const_pointer prev(const_pointer poi) const;

			public:
				Auto_queue();

				Auto_queue(const Auto_queue & src);

				template <typename ForwardIterator>
				Auto_queue(ForwardIterator begin, ForwardIterator end);

#			if __cplusplus >= 201103L

				Auto_queue(std::initializer_list<value_type> src);

#			endif

				~Auto_queue();

				Auto_queue& operator=(const Auto_queue & src);

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

				void swap(Auto_queue& with);

		};
	}
}

#include <kerbal/data_struct/auto_container_base/auto_queue_base.hpp>

#endif /* INCLUDE_KERBAL_DATA_STRUCT_AUTO_QUEUE_HPP_ */
