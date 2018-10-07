/**
 * @file		static_array_base.hpp
 * @brief
 * @date		2018年4月28日
 * @author		Peter
 * @copyright	Peter
 * @copyright
 <a href="http://thinkspirit.org/">ThinkSpirit Laboratory</a>
 of
 <a href="http://www.nuist.edu.cn/">Nanjing University of Information Science & Technology</a>
 */

#ifndef INCLUDE_KERBAL_DATA_STRUCT_STATIC_CONTAINER_BASE_STATIC_ARRAY_BASE_HPP_
#define INCLUDE_KERBAL_DATA_STRUCT_STATIC_CONTAINER_BASE_STATIC_ARRAY_BASE_HPP_

#include <stdexcept>

namespace kerbal
{
	namespace data_struct
	{

#	if __cplusplus < 201103L
		template <typename Tp, size_t N>
		const size_t static_array<Tp, N>::max_size = N;
#	endif

		template <typename Tp, size_t N>
		static_array<Tp, N>::static_array() :
				p_to_end(p)
		{
		}

		template <typename Tp, size_t N>
		static_array<Tp, N>::static_array(const static_array & src) :
				p_to_end(p)
		{
			const_pointer begin = src.p, end = src.p_to_end;
			while (begin != end) {
				new (p_to_end) value_type(*begin);
				++p_to_end;
				++begin;
			}
		}

#	if __cplusplus >= 201103L

		template <typename Tp, size_t N>
		static_array<Tp, N>::static_array(std::initializer_list<value_type> src) :
				static_array(src.begin(), src.end())
		{
		}

#	endif

		template <typename Tp, size_t N>
		template <typename InputIterator>
		static_array<Tp, N>::static_array(InputIterator begin, InputIterator end) :
				p_to_end(p)
		{
			while (begin != end && p_to_end != p + N) {
				new (p_to_end) value_type(*begin);
				++p_to_end;
				++begin;
			}
		}

		template <typename Tp, size_t N>
		static_array<Tp, N>::~static_array()
		{
			clear();
		}

		template <typename Tp, size_t N>
		void static_array<Tp, N>::assign(size_t n, const value_type & val)
		{
			if(n > N) {
				n = N;
			}
			const_pointer const new_p_to_end = p + n;
			const_pointer const previous_p_to_end = this->p_to_end;

			this->p_to_end = p;
			if (previous_p_to_end < new_p_to_end) {
				while (this->p_to_end < previous_p_to_end) {
					*this->p_to_end = val;
					++this->p_to_end;
				}
				while (this->p_to_end < new_p_to_end) {
					new (this->p_to_end) value_type(val);
					++this->p_to_end;
				}
			} else {
				while (this->p_to_end < new_p_to_end) {
					*this->p_to_end = val;
					++this->p_to_end;
				}
				while (this->p_to_end < previous_p_to_end) {
					this->p_to_end->~value_type();
					++this->p_to_end;
				}
			}
		}


		template <typename Tp, size_t N>
		template <typename InputIterator>
		void static_array<Tp, N>::assign(InputIterator begin, InputIterator end)
		{
			const_pointer const previous_p_to_end = this->p_to_end;
			this->p_to_end = p;

			while (this->p_to_end != previous_p_to_end && begin != end) {
				*this->p_to_end = *begin;
				++this->p_to_end;
				++begin;
			}

			if (this->p_to_end != previous_p_to_end) {
				for (pointer i = this->p_to_end; i != previous_p_to_end; ++i) {
					i->~value_type();
				}
			} else {
				while (this->p_to_end != p + N && begin != end) {
					new (this->p_to_end) value_type(*begin);
					++this->p_to_end;
					++begin;
				}
			}
		}

		template <typename Tp, size_t N>
		static_array<Tp, N>& static_array<Tp, N>::operator=(const static_array & src)
		{
			assign(src.p, src.p_to_end);
			return *this;
		}

#if __cplusplus >= 201103L
		template <typename Tp, size_t N>
		static_array<Tp, N>& static_array<Tp, N>::operator=(std::initializer_list<value_type> src)
		{
			assign(src.begin(), src.end());
			return *this;
		}
#endif

		template <typename Tp, size_t N>
		void static_array<Tp, N>::insert(const_iterator pos, const_reference val)
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
		void static_array<Tp, N>::push_back(const value_type & src)
		{
			if (full()) {
				throw std::exception();
			}

			new (p_to_end) value_type(src);
			++p_to_end;
		}

#	if __cplusplus >= 201103L
		template <typename Tp, size_t N>
		void static_array<Tp, N>::push_back(value_type && src)
		{
			if (full()) {
				throw std::exception();
			}

			new (p_to_end) value_type(std::move(src));
			++p_to_end;
		}
#	endif

		template <typename Tp, size_t N>
		void static_array<Tp, N>::pop_back()
		{
			if (empty()) {
				throw std::exception();
			}

			--p_to_end;
			p_to_end->~value_type();
		}

		template <typename Tp, size_t N>
		void static_array<Tp, N>::push_front(const value_type & src)
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
		void static_array<Tp, N>::pop_front()
		{
			if (empty()) {
				throw std::exception();
			}

			std::copy(p + 1, p_to_end, p);
			--p_to_end;
			p_to_end->~value_type();
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::reference
		static_array<Tp, N>::front()
		{
			if (empty()) {
				throw std::exception();
			}
			return p[0];
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_reference
		static_array<Tp, N>::front() const
		{
			if (empty()) {
				throw std::exception();
			}
			return p[0];
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::reference
		static_array<Tp, N>::back()
		{
			if (empty()) {
				throw std::exception();
			}
			return *this->rbegin();
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_reference
		static_array<Tp, N>::back() const
		{
			if (empty()) {
				throw std::exception();
			}
			return *this->crbegin();
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::reference
		static_array<Tp, N>::operator[](size_t index)
		{
			if (index >= size()) {
				throw std::out_of_range("range check fail in static_array");
			}
			return p[index];
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_reference
		static_array<Tp, N>::operator[](size_t index) const
		{
			if (index >= size()) {
				throw std::out_of_range("range check fail in static_array");
			}
			return p[index];
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::iterator
		static_array<Tp, N>::begin()
		{
			return iterator(p);
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::iterator
		static_array<Tp, N>::end()
		{
			return iterator(p_to_end);
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_iterator
		static_array<Tp, N>::begin() const
		{
			return const_iterator(p);
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_iterator
		static_array<Tp, N>::end() const
		{
			return const_iterator(p_to_end);
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_iterator
		static_array<Tp, N>::cbegin() const
		{
			return const_iterator(p);
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_iterator
		static_array<Tp, N>::cend() const
		{
			return const_iterator(p_to_end);
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::reverse_iterator
		static_array<Tp, N>::rbegin()
		{
			return reverse_iterator(p_to_end - 1);
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::reverse_iterator
		static_array<Tp, N>::rend()
		{
			return reverse_iterator(p - 1);
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_reverse_iterator
		static_array<Tp, N>::rbegin() const
		{
			return const_reverse_iterator(p_to_end - 1);
		}
		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_reverse_iterator
		static_array<Tp, N>::rend() const
		{
			return const_reverse_iterator(p - 1);
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_reverse_iterator
		static_array<Tp, N>::crbegin() const
		{
			return const_reverse_iterator(p_to_end - 1);
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_reverse_iterator
		static_array<Tp, N>::crend() const
		{
			return const_reverse_iterator(p - 1);
		}

//		template <typename Tp, size_t N>
//		bool Auto_array<Tp, N>::is_valid_iterator(const iterator & it) const
//		{
//			return this == it.p_to_src_array && it.p <= this->p_to_end;
//		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::equal_c_array_reference
		static_array<Tp, N>::c_arr()
		{
			if (!full()) {
				throw std::exception();
			}
			return p;
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_equal_c_array_reference
		static_array<Tp, N>::const_c_arr() const
		{
			if (!full()) {
				throw std::exception();
			}
			return p;
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_pointer
		static_array<Tp, N>::data() const
		{
			return p;
		}

		template <typename Tp, size_t N>
		void static_array<Tp, N>::clear()
		{
			while (p_to_end != p) {
				p_to_end--;
				p_to_end->~value_type();
			}
		}

		template <typename Tp, size_t N>
		void static_array<Tp, N>::fill()
		{
			const_pointer const previous_p_to_end = this->p_to_end;
			this->p_to_end = p;
			while (this->p_to_end != previous_p_to_end) {
				*this->p_to_end = value_type();
				++this->p_to_end;
			}
			while (this->p_to_end != p + N) {
				new (this->p_to_end) value_type();
				++this->p_to_end;
			}
		}

		template <typename Tp, size_t N>
		void static_array<Tp, N>::fill(const value_type & val)
		{
			const_pointer const previous_p_to_end = this->p_to_end;
			this->p_to_end = p;
			while (this->p_to_end != previous_p_to_end) {
				*this->p_to_end = val;
				++this->p_to_end;
			}
			while (this->p_to_end != p + N) {
				new (this->p_to_end) value_type(val);
				++this->p_to_end;
			}
		}

		template <typename Tp, size_t N>
		void static_array<Tp, N>::swap(static_array & with)
		{
			bool condition = this->size() < with.size();
			static_array & s_arr = condition ? *this : with;
			static_array & l_arr = condition ? with : *this;

			pointer i = s_arr.p;
			pointer j = l_arr.p;

			while (i != s_arr.p_to_end) {
				std::iter_swap(i, j);
				++i;
				++j;
			}

			pointer const l_arr_new_p_to_end = j;
			while (j != l_arr.p_to_end) {
				new (s_arr.p_to_end) value_type(*j);
				++s_arr.p_to_end;
				++j;
			}

			while (l_arr.p_to_end != l_arr_new_p_to_end) {
				--l_arr.p_to_end;
				l_arr.p_to_end->~value_type();
			}
		}

		template <typename Tp, size_t N>
		bool static_array<Tp, N>::empty() const
		{
			return p == p_to_end;
		}

		template <typename Tp, size_t N>
		bool static_array<Tp, N>::full() const
		{
			return p + N == p_to_end;
		}

		template <typename Tp, size_t N>
		size_t static_array<Tp, N>::size() const
		{
			return p_to_end - p;
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::iterator
		static_array<Tp, N>::find(const value_type & src)
		{
			iterator i = this->begin();
			while (i != this->end() && !(src == *i)) {
				++i;
			}
			return i;
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_iterator
		static_array<Tp, N>::find(const value_type & src) const
		{
			const_iterator i = this->cbegin();
			while (i != this->cend() && !(src == *i)) {
				++i;
			}
			return i;
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::reverse_iterator
		static_array<Tp, N>::rfind(const value_type & src)
		{
			reverse_iterator i = this->rbegin();
			while (i != this->rend() && !(src == *i)) {
				++i;
			}
			return i;
		}


		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_reverse_iterator
		static_array<Tp, N>::rfind(const value_type & src) const
		{
			const_reverse_iterator i = this->crbegin();
			while (i != this->crend() && !(src == *i)) {
				++i;
			}
			return i;
		}

		template <typename Tp, size_t N>
		template <typename JudgeFunction>
		typename static_array<Tp, N>::iterator
		static_array<Tp, N>::find_if(JudgeFunction judge_function)
		{
			iterator i = this->begin();
			while (i != this->end() && !judge_function(*i)) {
				++i;
			}
			return i;
		}

		template<typename Tp, size_t N>
		template<typename JudgeFunction>
		typename static_array<Tp, N>::const_iterator
		static_array<Tp, N>::find_if(JudgeFunction judge_function) const
		{
			const_iterator i = this->cbegin();
			while (i != this->cend() && !judge_function(*i)) {
				++i;
			}
			return i;
		}

		template <typename Tp, size_t N>
		template <typename JudgeFunction>
		typename static_array<Tp, N>::reverse_iterator
		static_array<Tp, N>::rfind_if(JudgeFunction judge_function)
		{
			reverse_iterator i = this->rbegin();
			while (i != this->rend() && !judge_function(*i)) {
				++i;
			}
			return i;
		}

		template <typename Tp, size_t N>
		template <typename JudgeFunction>
		typename static_array<Tp, N>::const_reverse_iterator
		static_array<Tp, N>::rfind_if(JudgeFunction judge_function) const
		{
			const_reverse_iterator i = this->crbegin();
			while (i != this->crend() && !judge_function(*i)) {
				++i;
			}
			return i;
		}

		template <typename Tp, size_t N>
		bool static_array<Tp, N>::operator==(const static_array & with) const
		{
			const_iterator i = this->cbegin();
			const_iterator j = with.cbegin();
			while (i != this->cend() && j != with.cend() && *i == *j) {
				++i;
				++j;
			}
			return !(i != this->cend()) && !(j != with.cend());
		}

		template <typename Tp, size_t N>
		bool static_array<Tp, N>::operator!=(const static_array & with) const
		{
			const_iterator i = this->cbegin();
			const_iterator j = with.cbegin();
			while (i != this->cend() && j != with.cend() && !(*i != *j)) {
				++i;
				++j;
			}
			return i != this->cend() || j != with.cend();
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

#endif /* INCLUDE_KERBAL_DATA_STRUCT_STATIC_CONTAINER_BASE_STATIC_ARRAY_BASE_HPP_ */
