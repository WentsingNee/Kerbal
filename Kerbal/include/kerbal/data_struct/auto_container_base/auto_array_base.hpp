/**
 * @file		auto_array_base.hpp
 * @brief
 * @date		2018年4月28日
 * @author		Peter
 * @copyright	Peter
 * @copyright
 <a href="http://thinkspirit.org/">ThinkSpirit Laboratory</a>
 of
 <a href="http://www.nuist.edu.cn/">Nanjing University of Information Science & Technology</a>
 */

#ifndef INCLUDE_KERBAL_DATA_STRUCT_AUTO_CONTAINER_BASE_AUTO_ARRAY_BASE_HPP_
#define INCLUDE_KERBAL_DATA_STRUCT_AUTO_CONTAINER_BASE_AUTO_ARRAY_BASE_HPP_

#include <stdexcept>

namespace kerbal
{
	namespace data_struct
	{

#	if __cplusplus < 201103L
		template <typename Tp, size_t N>
		const size_t Auto_array<Tp, N>::max_size = N;
#	endif

		template <typename Tp, size_t N>
		Auto_array<Tp, N>::Auto_array() :
				p_to_end(p)
		{
		}

		template <typename Tp, size_t N>
		Auto_array<Tp, N>::Auto_array(const Auto_array & src) :
				p_to_end(p)
		{
			pointer i = this->p;
			const_pointer begin = src.p, end = src.p_to_end;
			while (begin != end) {
				new (i) value_type(*begin);
				++i;
				++begin;
			}
			p_to_end = i;
		}

#	if __cplusplus >= 201103L

		template <typename Tp, size_t N>
		Auto_array<Tp, N>::Auto_array(std::initializer_list<value_type> src) :
				Auto_array(src.begin(), src.end())
		{
		}

#	endif

		template <typename Tp, size_t N>
		template <typename InputIterator>
		Auto_array<Tp, N>::Auto_array(InputIterator begin, InputIterator end) :
				p_to_end(p)
		{
			pointer i = this->p;
			while (begin != end && i != p + N) {
				new (i) value_type(*begin);
				++i;
				++begin;
			}
			p_to_end = i;
		}

		template <typename Tp, size_t N>
		Auto_array<Tp, N>::~Auto_array()
		{
			clear();
		}

		template <typename Tp, size_t N>
		void Auto_array<Tp, N>::assign(size_t n, const value_type & val)
		{
			pointer const new_p_to_end = p + std::min(n, N);
			pointer i = p;
			if (n >= size()) {
				for (; i < p_to_end; ++i) {
					*i = val;
				}
				for (; i < new_p_to_end; ++i) {
					new (i) value_type(val);
				}
			} else {
				for (; i < new_p_to_end; ++i) {
					*i = val;
				}
				for (; i < p_to_end; ++i) {
					i->~value_type();
				}
			}
			p_to_end = new_p_to_end;
		}


		template <typename Tp, size_t N>
		template <typename InputIterator>
		void Auto_array<Tp, N>::assign(InputIterator begin, InputIterator end)
		{
			pointer i = p;
			for (; i != p_to_end && begin != end; ++i, ++begin) {
//				cout << *i << " = " << *begin << endl;
				*i = *begin;
			}
			if (i != p_to_end) {
				pointer const new_p_to_end = i;
				for (; i != p_to_end; ++i) {
//					cout << "delete " << *i << endl;
					i->~value_type();
				}
				p_to_end = new_p_to_end;
			} else {
				for (; i != p + N && begin != end; ++i, ++begin) {
//					cout << "new " << i - p << " " << *begin << endl;
					new (i) value_type(*begin);
				}
				p_to_end = i;
			}
		}

		template <typename Tp, size_t N>
		Auto_array<Tp, N>& Auto_array<Tp, N>::operator=(const Auto_array & src)
		{
			assign(src.p, src.p_to_end);
			return *this;
		}

#if __cplusplus >= 201103L
		template <typename Tp, size_t N>
		Auto_array<Tp, N>& Auto_array<Tp, N>::operator=(std::initializer_list<value_type> src)
		{
			assign(src.begin(), src.end());
			return *this;
		}
#endif

		template <typename Tp, size_t N>
		void Auto_array<Tp, N>::insert(const_iterator pos, const_reference val)
		{
			if (full()) {
				throw std::exception();
			}
			//TODO when pos == end()
			new (p_to_end) value_type(*(p_to_end - 1));
			std::copy(pos, cend() - 1, pos + 1);
			*pos = val;

			++p_to_end;
		}

		template <typename Tp, size_t N>
		void Auto_array<Tp, N>::push_back(const value_type & src)
		{
			if (full()) {
				throw std::exception();
			}

			new (p_to_end) value_type(src);
			++p_to_end;
		}

		template <typename Tp, size_t N>
		void Auto_array<Tp, N>::pop_back()
		{
			if (empty()) {
				throw std::exception();
			}

			--p_to_end;
			p_to_end->~value_type();
		}

		template <typename Tp, size_t N>
		void Auto_array<Tp, N>::push_front(const value_type & src)
		{
			if (full()) {
				throw std::exception();
			}

			if (empty()) {
				new (p_to_end) value_type(src);
			} else {
				new (p_to_end) value_type(*(p_to_end - 1));
				std::copy(p, p_to_end - 1, p + 1);
				p[0] = src;
			}
			++p_to_end;

		}

		template <typename Tp, size_t N>
		void Auto_array<Tp, N>::pop_front()
		{
			if (empty()) {
				throw std::exception();
			}

			std::copy(p + 1, p_to_end, p);
			--p_to_end;
			p_to_end->~value_type();
		}

		template <typename Tp, size_t N>
		typename Auto_array<Tp, N>::reference
		Auto_array<Tp, N>::front()
		{
			if (empty()) {
				throw std::exception();
			}
			return p[0];
		}

		template <typename Tp, size_t N>
		typename Auto_array<Tp, N>::const_reference
		Auto_array<Tp, N>::front() const
		{
			if (empty()) {
				throw std::exception();
			}
			return p[0];
		}

		template <typename Tp, size_t N>
		typename Auto_array<Tp, N>::reference
		Auto_array<Tp, N>::back()
		{
			if (empty()) {
				throw std::exception();
			}
			return *(p_to_end - 1);
		}

		template <typename Tp, size_t N>
		typename Auto_array<Tp, N>::const_reference
		Auto_array<Tp, N>::back() const
		{
			if (empty()) {
				throw std::exception();
			}
			return *(p_to_end - 1);
		}

		template <typename Tp, size_t N>
		typename Auto_array<Tp, N>::reference
		Auto_array<Tp, N>::operator[](size_t index)
		{
			if (index >= size()) {
				throw std::out_of_range("range check fail in Auto_array");
			}
			return p[index];
		}

		template <typename Tp, size_t N>
		typename Auto_array<Tp, N>::const_reference
		Auto_array<Tp, N>::operator[](size_t index) const
		{
			if (index >= size()) {
				throw std::out_of_range("range check fail in Auto_array");
			}
			return p[index];
		}

		template <typename Tp, size_t N>
		typename Auto_array<Tp, N>::iterator
		Auto_array<Tp, N>::begin()
		{
			return iterator(p);
		}

		template <typename Tp, size_t N>
		typename Auto_array<Tp, N>::iterator
		Auto_array<Tp, N>::end()
		{
			return iterator(p_to_end);
		}

		template <typename Tp, size_t N>
		typename Auto_array<Tp, N>::const_iterator
		Auto_array<Tp, N>::begin() const
		{
			return const_iterator(p);
		}

		template <typename Tp, size_t N>
		typename Auto_array<Tp, N>::const_iterator
		Auto_array<Tp, N>::end() const
		{
			return const_iterator(p_to_end);
		}

		template <typename Tp, size_t N>
		typename Auto_array<Tp, N>::const_iterator
		Auto_array<Tp, N>::cbegin() const
		{
			return const_iterator(p);
		}

		template <typename Tp, size_t N>
		typename Auto_array<Tp, N>::const_iterator
		Auto_array<Tp, N>::cend() const
		{
			return const_iterator(p_to_end);
		}

		template <typename Tp, size_t N>
		typename Auto_array<Tp, N>::reverse_iterator
		Auto_array<Tp, N>::rbegin()
		{
			return reverse_iterator(p_to_end - 1);
		}

		template <typename Tp, size_t N>
		typename Auto_array<Tp, N>::reverse_iterator
		Auto_array<Tp, N>::rend()
		{
			return reverse_iterator(p - 1);
		}

		template <typename Tp, size_t N>
		typename Auto_array<Tp, N>::const_reverse_iterator
		Auto_array<Tp, N>::rbegin() const
		{
			return const_reverse_iterator(p_to_end - 1);
		}
		template <typename Tp, size_t N>
		typename Auto_array<Tp, N>::const_reverse_iterator
		Auto_array<Tp, N>::rend() const
		{
			return const_reverse_iterator(p - 1);
		}

		template <typename Tp, size_t N>
		typename Auto_array<Tp, N>::const_reverse_iterator
		Auto_array<Tp, N>::crbegin() const
		{
			return const_reverse_iterator(p_to_end - 1);
		}

		template <typename Tp, size_t N>
		typename Auto_array<Tp, N>::const_reverse_iterator
		Auto_array<Tp, N>::crend() const
		{
			return const_reverse_iterator(p - 1);
		}

//		template <typename Tp, size_t N>
//		bool Auto_array<Tp, N>::is_valid_iterator(const iterator & it) const
//		{
//			return this == it.p_to_src_array && it.p <= this->p_to_end;
//		}

		template <typename Tp, size_t N>
		typename Auto_array<Tp, N>::equal_c_array_reference
		Auto_array<Tp, N>::c_arr()
		{
			if (!full()) {
				throw std::exception();
			}
			return p;
		}

		template <typename Tp, size_t N>
		typename Auto_array<Tp, N>::const_equal_c_array_reference
		Auto_array<Tp, N>::const_c_arr() const
		{
			if (!full()) {
				throw std::exception();
			}
			return p;
		}

		template <typename Tp, size_t N>
		typename Auto_array<Tp, N>::const_pointer
		Auto_array<Tp, N>::data() const
		{
			return p;
		}

		template <typename Tp, size_t N>
		void Auto_array<Tp, N>::clear()
		{
			while (p_to_end != p) {
				p_to_end--;
				p_to_end->~value_type();
			}
		}

		template <typename Tp, size_t N>
		void Auto_array<Tp, N>::fill()
		{
			for (pointer i = p_to_end; i != p + N; ++i) {
				new (i) value_type();
			}
			p_to_end = p + N;
		}

		template <typename Tp, size_t N>
		void Auto_array<Tp, N>::fill(const value_type & val)
		{
			for (pointer i = p_to_end; i != p + N; ++i) {
				new (i) value_type(val);
			}
			p_to_end = p + N;
		}

		template <typename Tp, size_t N>
		void Auto_array<Tp, N>::swap(Auto_array & with)
		{
			pointer i = p, j = with.p;
			const size_t i_size = this->size(), j_size = with.size();
			if (i_size < j_size) {
				for (; i != p_to_end; ++i, ++j) {
					std::iter_swap(i, j);
				}

				for (; j != with.p_to_end; ++i, ++j) {
					new (i) value_type(*j);
					j->~value_type();
				}
			} else {
				for (; j != with.p_to_end; ++i, ++j) {
					std::iter_swap(i, j);
				}

				for (; i != p_to_end; ++i, ++j) {
					new (j) value_type(*i);
					i->~value_type();
				}
			}
			p_to_end = p + j_size;
			with.p_to_end = with.p + i_size;
		}

		template <typename Tp, size_t N>
		bool Auto_array<Tp, N>::empty() const
		{
			return p == p_to_end;
		}

		template <typename Tp, size_t N>
		bool Auto_array<Tp, N>::full() const
		{
			return p + N == p_to_end;
		}

		template <typename Tp, size_t N>
		size_t Auto_array<Tp, N>::size() const
		{
			return p_to_end - p;
		}

		template <typename Tp, size_t N>
		typename Auto_array<Tp, N>::iterator
		Auto_array<Tp, N>::find(const value_type & src)
		{
			for (pointer i = p; i != p_to_end; ++i) {
				if (src == *i) {
					return iterator(i);
				}
			}
			return end();
		}

		template <typename Tp, size_t N>
		typename Auto_array<Tp, N>::const_iterator
		Auto_array<Tp, N>::find(const value_type & src) const
		{
			for (const_pointer i = p; i != p_to_end; ++i) {
				if (src == *i) {
					return const_iterator(i);
				}
			}
			return cend();
		}

		template <typename Tp, size_t N>
		typename Auto_array<Tp, N>::reverse_iterator
		Auto_array<Tp, N>::rfind(const value_type & src)
		{
			for(pointer i = p + N - 1; i != p - 1; --i) {
				if(src == *i){
					return reverse_iterator(i);
				}
			}
			return rend();
		}


		template <typename Tp, size_t N>
		typename Auto_array<Tp, N>::const_reverse_iterator
		Auto_array<Tp, N>::rfind(const value_type & src) const
		{
			for(pointer i = p + N - 1; i != p - 1; --i) {
				if(src == *i) {
					return const_reverse_iterator(i);
				}
			}
			return crend();
		}

		template <typename Tp, size_t N>
		template <typename JudgeFunction>
		typename Auto_array<Tp, N>::iterator
		Auto_array<Tp, N>::find_if(JudgeFunction judge_function)
		{
			for (pointer i = p; i != p_to_end; ++i) {
				if (judge_function(*i)) {
					return iterator(i);
				}
			}
			return end();
		}

		template<typename Tp, size_t N>
		template<typename JudgeFunction>
		typename Auto_array<Tp, N>::const_iterator
		Auto_array<Tp, N>::find_if(JudgeFunction judge_function) const
		{
			for(const_pointer i = p; i!=p_to_end;++i){
				if(judge_function(*i)){
					return const_iterator(i);
				}
			}
			return cend();
		}

		template <typename Tp, size_t N>
		template <typename JudgeFunction>
		typename Auto_array<Tp, N>::reverse_iterator
		Auto_array<Tp, N>::rfind_if(JudgeFunction judge_function)
		{
			for(pointer i = p + N -1;i!=p-1;--i){
				if(judge_function(*i)){
					return reverse_iterator(i);
				}
			}
			return rend();
		}

		template <typename Tp, size_t N>
		template <typename JudgeFunction>
		typename Auto_array<Tp, N>::const_reverse_iterator
		Auto_array<Tp, N>::rfind_if(JudgeFunction judge_function) const
		{
			for(const_pointer i = p + N -1;i!=p-1;--i){
				if(judge_function(*i)){
					return const_reverse_iterator(i);
				}
			}
			return crend();
		}

		template <typename Tp, size_t N>
		bool Auto_array<Tp, N>::operator==(const Auto_array & with) const
		{
			const_pointer i = this->p, j = with.p;
			for (; i != this->p_to_end && j != with.p_to_end; ++i, ++j) {
				if (!(*i == *j)) {
					return false;
				}
			}
			return i == this->p_to_end && j == with.p_to_end;
		}

		template <typename Tp, size_t N>
		bool Auto_array<Tp, N>::operator!=(const Auto_array & with) const
		{
			const_pointer i = this->p, j = with.p;
			for (; i != this->p_to_end && j != with.p_to_end; ++i, ++j) {
				if (*i != *j) {
					return true;
				}
			}
			return !(i == this->p_to_end && j == with.p_to_end);
		}

//		template <typename Tp, size_t N>
//		bool Auto_array<Tp, N>::operator<(const Auto_array & with) const;
//		template <typename Tp, size_t N>
//		bool Auto_array<Tp, N>::operator<=(const Auto_array & with) const;
//		template <typename Tp, size_t N>
//		bool Auto_array<Tp, N>::operator>(const Auto_array & with) const;
//		template <typename Tp, size_t N>
//		bool Auto_array<Tp, N>::operator>=(const Auto_array & with) const;

	}
}

#endif /* INCLUDE_KERBAL_DATA_STRUCT_AUTO_CONTAINER_BASE_AUTO_ARRAY_BASE_HPP_ */
