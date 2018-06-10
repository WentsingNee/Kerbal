/**
 * @file		auto_queue_base.hpp
 * @brief
 * @date		2018年5月17日
 * @author		Peter
 * @copyright	Peter
 * @copyright
 <a href="http://thinkspirit.org/">ThinkSpirit Laboratory</a>
 of
 <a href="http://www.nuist.edu.cn/">Nanjing University of Information Science & Technology</a>
 */

#ifndef INCLUDE_KERBAL_DATA_STRUCT_AUTO_CONTAINER_BASE_AUTO_QUEUE_BASE_HPP_
#define INCLUDE_KERBAL_DATA_STRUCT_AUTO_CONTAINER_BASE_AUTO_QUEUE_BASE_HPP_

namespace kerbal
{
	namespace data_struct
	{

		template <typename Tp, size_t N>
		typename Auto_queue<Tp, N>::pointer
		Auto_queue<Tp, N>::next(pointer poi)
		{
			return (poi == p + N - 1) ? p : poi + 1;
		}

		template <typename Tp, size_t N>
		typename Auto_queue<Tp, N>::const_pointer
		Auto_queue<Tp, N>::next(const_pointer poi) const
		{
			return (poi == p + N - 1) ? p : poi + 1;
		}

		template <typename Tp, size_t N>
		typename Auto_queue<Tp, N>::pointer
		Auto_queue<Tp, N>::prev(pointer poi)
		{
			return (poi == p) ? p + N - 1 : poi - 1;
		}

		template <typename Tp, size_t N>
		typename Auto_queue<Tp, N>::const_pointer
		Auto_queue<Tp, N>::prev(const_pointer poi) const
		{
			return (poi == p) ? p + N - 1 : poi - 1;
		}

		template <typename Tp, size_t N>
		Auto_queue<Tp, N>::Auto_queue() :
				begin(p), end(p)
		{
		}

		template <typename Tp, size_t N>
		Auto_queue<Tp, N>::Auto_queue(const Auto_queue & src) :
				begin(p), end(p)
		{
			pointer i = begin;
			const_pointer j = src.begin;

			for (; j != src.end; i = this->next(i), j = src.next(j)) {
				new (i) value_type(*j);
			}

			end = i;
		}

		template <typename Tp, size_t N>
		template <typename ForwardIterator>
		Auto_queue<Tp, N>::Auto_queue(ForwardIterator src_begin, ForwardIterator src_end) :
				begin(p), end(p)
		{
			pointer i = begin;
			for (; src_begin != src_end && i != p + N; i = this->next(i), ++src_begin) {
				new (i) value_type(*begin);
			}

			end = i;
		}

#	if __cplusplus >= 201103L

		template <typename Tp, size_t N>
		Auto_queue<Tp, N>::Auto_queue(std::initializer_list<value_type> src) :
				Auto_queue(src.begin(), src.end())
		{
		}

#	endif


		template <typename Tp, size_t N>
		Auto_queue<Tp, N>::~Auto_queue()
		{
			clear();
		}

		template <typename Tp, size_t N>
		void Auto_queue<Tp, N>::push(const_reference val)
		{
			if (full()) {
				throw std::exception();
			}

			new (end) value_type(val);
			end = this->next(end);
		}

		template <typename Tp, size_t N>
		void Auto_queue<Tp, N>::Auto_queue<Tp, N>::pop()
		{
			if (empty()) {
				throw std::exception();
			}

			end = this->prev(end);
			end->~value_type();
		}


		template <typename Tp, size_t N>
		void Auto_queue<Tp, N>::clear()
		{
			for (pointer i = begin; i != end; i = this->next(i)) {
				i->~value_type();
			}
		}

		template <typename Tp, size_t N>
		size_t Auto_queue<Tp, N>::size() const
		{
			if (begin < end) {
				return end - begin;
			} else {
				return N - (begin - end);
			}
		}

		template <typename Tp, size_t N>
		bool Auto_queue<Tp, N>::empty() const
		{
			return begin == end;
		}

		template <typename Tp, size_t N>
		bool Auto_queue<Tp, N>::full() const
		{

		}

		template <typename Tp, size_t N>
		typename Auto_queue<Tp, N>::reference
		Auto_queue<Tp, N>::front()
		{
			if (empty()) {
				throw std::exception();
			}
			return *begin;
		}

		template <typename Tp, size_t N>
		typename Auto_queue<Tp, N>::const_reference
		Auto_queue<Tp, N>::front() const
		{
			if (empty()) {
				throw std::exception();
			}
			return *begin;
		}

		template <typename Tp, size_t N>
		typename Auto_queue<Tp, N>::reference
		Auto_queue<Tp, N>::back();

		template <typename Tp, size_t N>
		typename Auto_queue<Tp, N>::const_reference
		Auto_queue<Tp, N>::back() const;

	}
}

#endif /* INCLUDE_KERBAL_DATA_STRUCT_AUTO_CONTAINER_BASE_AUTO_QUEUE_BASE_HPP_ */
