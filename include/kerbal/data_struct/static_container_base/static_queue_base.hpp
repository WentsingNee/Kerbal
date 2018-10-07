/**
 * @file		static_queue_base.hpp
 * @brief
 * @date		2018年5月17日
 * @author		Peter
 * @copyright	Peter
 * @copyright
 <a href="http://thinkspirit.org/">ThinkSpirit Laboratory</a>
 of
 <a href="http://www.nuist.edu.cn/">Nanjing University of Information Science & Technology</a>
 */

#ifndef INCLUDE_KERBAL_DATA_STRUCT_STATIC_CONTAINER_BASE_STATIC_QUEUE_BASE_HPP_
#define INCLUDE_KERBAL_DATA_STRUCT_STATIC_CONTAINER_BASE_STATIC_QUEUE_BASE_HPP_

namespace kerbal
{
	namespace data_struct
	{

		template <typename Tp, size_t N>
		typename static_queue<Tp, N>::pointer
		static_queue<Tp, N>::next(pointer poi)
		{
			return (poi == p + N) ? p : poi + 1;
		}

		template <typename Tp, size_t N>
		typename static_queue<Tp, N>::const_pointer
		static_queue<Tp, N>::next(const_pointer poi) const
		{
			return (poi == p + N) ? p : poi + 1;
		}

		template <typename Tp, size_t N>
		typename static_queue<Tp, N>::pointer
		static_queue<Tp, N>::prev(pointer poi)
		{
			return (poi == p) ? p + N : poi - 1;
		}

		template <typename Tp, size_t N>
		typename static_queue<Tp, N>::const_pointer
		static_queue<Tp, N>::prev(const_pointer poi) const
		{
			return (poi == p) ? p + N : poi - 1;
		}

		template <typename Tp, size_t N>
		static_queue<Tp, N>::static_queue() :
				begin(p), end(p)
		{
		}

		template <typename Tp, size_t N>
		static_queue<Tp, N>::static_queue(const static_queue & src) :
				begin(p), end(p)
		{
			for (const_pointer j = src.begin; j != src.end; j = src.next(j)) {
				new (end) value_type(*j);
				end = this->next(end);
			}
		}

		template <typename Tp, size_t N>
		template <typename ForwardIterator>
		static_queue<Tp, N>::static_queue(ForwardIterator src_begin, ForwardIterator src_end) :
				begin(p), end(p)
		{
			for (; src_begin != src_end && end != p + N; ++src_begin) {
				new (end) value_type(*src_begin);
				end = this->next(end);
			}
		}

#	if __cplusplus >= 201103L

		template <typename Tp, size_t N>
		static_queue<Tp, N>::static_queue(std::initializer_list<value_type> src) :
				static_queue(src.begin(), src.end())
		{
		}

#	endif


		template <typename Tp, size_t N>
		static_queue<Tp, N>::~static_queue()
		{
			clear();
		}
		
		template <typename Tp, size_t N>
		static_queue<Tp, N>& static_queue<Tp, N>::operator=(const static_queue<Tp, N> & src)
		{
			this->clear();
			for (const_pointer j = src.begin; j != src.end; j = src.next(j)) {
				new (end) value_type(*j);
				end = this->next(end);
			}
		}

		template <typename Tp, size_t N>
		void static_queue<Tp, N>::push(const_reference val)
		{
			if (full()) {
				throw std::logic_error("auto queue has been full!");
			}

			new (end) value_type(val);
			end = this->next(end);
		}

		template <typename Tp, size_t N>
		void static_queue<Tp, N>::pop()
		{
			if (empty()) {
				throw std::logic_error("auto queue has been empty!");
			}

			begin->~value_type();
			begin = this->next(begin);
		}


		template <typename Tp, size_t N>
		void static_queue<Tp, N>::clear()
		{
			for (; begin != end; begin = this->next(begin)) {
				begin->~value_type();
			}
		}

		template <typename Tp, size_t N>
		size_t static_queue<Tp, N>::size() const
		{
			if (begin <= end) {
				return end - begin;
			} else {
				return N + 1 - (begin - end);
			}
		}

		template <typename Tp, size_t N>
		bool static_queue<Tp, N>::empty() const
		{
			return begin == end;
		}

		template <typename Tp, size_t N>
		bool static_queue<Tp, N>::full() const
		{
			return this->size() == N;
		}

		template <typename Tp, size_t N>
		typename static_queue<Tp, N>::reference
		static_queue<Tp, N>::front()
		{
			if (empty()) {
				throw std::logic_error("empty queue!");
			}
			return *begin;
		}

		template <typename Tp, size_t N>
		typename static_queue<Tp, N>::const_reference
		static_queue<Tp, N>::front() const
		{
			if (empty()) {
				throw std::logic_error("empty queue!");
			}
			return *begin;
		}

		template <typename Tp, size_t N>
		typename static_queue<Tp, N>::reference
		static_queue<Tp, N>::back()
		{
			if (empty()) {
				throw std::logic_error("empty queue!");
			}
			return *this->prev(end);
		}

		template <typename Tp, size_t N>
		typename static_queue<Tp, N>::const_reference
		static_queue<Tp, N>::back() const
		{
			if (empty()) {
				throw std::logic_error("empty queue!");
			}
			return *this->prev(end);
		}

	}
}

#endif /* INCLUDE_KERBAL_DATA_STRUCT_STATIC_CONTAINER_BASE_STATIC_QUEUE_BASE_HPP_ */
