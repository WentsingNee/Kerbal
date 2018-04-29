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

#ifndef INCLUDE_KERBAL_DATA_STRUCT_AUTO_ARRAY_BASE_HPP_
#define INCLUDE_KERBAL_DATA_STRUCT_AUTO_ARRAY_BASE_HPP_

#include <stdexcept>

namespace kerbal
{
	namespace data_struct
	{
		namespace auto_array
		{

#		if __cplusplus < 201103L
			template <typename Tp, size_t N>
			const size_t Auto_array<Tp, N>::max_size = N;
#		endif

			template <typename Tp, size_t N>
			typename Auto_array<Tp, N>::reference
			Auto_array<Tp, N>::iterator::operator*() const
			{
				return *p;
			}

			template <typename Tp, size_t N>
			typename Auto_array<Tp, N>::iterator&
			Auto_array<Tp, N>::iterator::operator++()
			{
				++p;
				return *this;
			}

			template <typename Tp, size_t N>
			typename Auto_array<Tp, N>::iterator
			Auto_array<Tp, N>::iterator::operator++(int)
			{
				iterator bakup(*this);
				++p;
				return bakup;
			}

			template <typename Tp, size_t N>
			typename Auto_array<Tp, N>::iterator&
			Auto_array<Tp, N>::iterator::operator--()
			{
				--p;
				return *this;
			}

			template <typename Tp, size_t N>
			typename Auto_array<Tp, N>::iterator
			Auto_array<Tp, N>::iterator::operator--(int)
			{
				iterator bakup(*this);
				--p;
				return bakup;
			}

			template <typename Tp, size_t N>
			typename Auto_array<Tp, N>::iterator
			Auto_array<Tp, N>::iterator::operator+(int delta)
			{
				return p + delta;
			}

			template <typename Tp, size_t N>
			typename Auto_array<Tp, N>::iterator
			Auto_array<Tp, N>::iterator::operator-(int delta)
			{
				return p - delta;
			}

			template <typename Tp, size_t N>
			const Auto_array<Tp, N>::iterator
			Auto_array<Tp, N>::iterator::operator+(int delta) const
			{
				return p + delta;
			}

			template <typename Tp, size_t N>
			const Auto_array<Tp, N>::iterator
			Auto_array<Tp, N>::iterator::operator-(int delta) const
			{
				return p - delta;
			}


			template <typename Tp, size_t N>
			bool Auto_array<Tp, N>::iterator::operator==(const iterator & with) const
			{
				return p == with.p;
			}

			template <typename Tp, size_t N>
			bool Auto_array<Tp, N>::iterator::operator!=(const iterator & with) const
			{
				return p != with.p;
			}

			template <typename Tp, size_t N>
			bool Auto_array<Tp, N>::iterator::operator<(const iterator & with) const
			{
				return p < with.p;
			}

			template <typename Tp, size_t N>
			bool Auto_array<Tp, N>::iterator::operator<=(const iterator & with) const
			{
				return p <= with.p;
			}

			template <typename Tp, size_t N>
			bool Auto_array<Tp, N>::iterator::operator>(const iterator & with) const
			{
				return p > with.p;
			}

			template <typename Tp, size_t N>
			bool Auto_array<Tp, N>::iterator::operator>=(const iterator & with) const
			{
				return p >= with.p;
			}

			template <typename Tp, size_t N>
			Auto_array<Tp, N>::Auto_array() :
					p(reinterpret_cast<equal_c_array &>(p_byte)), n(0)
			{
			}

			template <typename Tp, size_t N>
			Auto_array<Tp, N>::Auto_array(const Auto_array & src) :
					p(reinterpret_cast<equal_c_array &>(p_byte)), n(src.n)
			{
				for (size_t i = 0; i < n; ++i) {
					new (p + i) type(src.p[i]);
				}
			}

#		if __cplusplus >= 201103L
			template<typename Tp, size_t N>
			Auto_array<Tp, N>::Auto_array(std::initializer_list<type> src) :
			p(reinterpret_cast<equal_c_array &>(p_byte)), n(src.size())
			{
				size_t i = 0;
				typename std::initializer_list<type>::iterator it = src.begin(), end = src.end();
				for(; it != end && i != N; ++i, ++it) {
					new (p + i) type(*it);
				}
			}
#		endif


			template <typename Tp, size_t N>
			template <typename InputIterator>
			Auto_array<Tp, N>::Auto_array(InputIterator begin, InputIterator end) :
					p(reinterpret_cast<equal_c_array &>(p_byte)), n(0)
			{
				size_t i;
				for (i = 0; i != N && begin != end; ++begin, ++i) {
					new (p + i) type(*begin);
				}
				n = i;
			}

			template <typename Tp, size_t N>
			Auto_array<Tp, N>::~Auto_array()
			{
				clear();
			}

			template <typename Tp, size_t N>
			void Auto_array<Tp, N>::push_back(const type & src)
			{
				if (full()) {
					throw std::exception();
				}

				new (p + n) type(src);
				++n;
			}

			template <typename Tp, size_t N>
			void Auto_array<Tp, N>::pop_back()
			{
				if (empty()) {
					throw std::exception();
				}
				--n;
				(p + n)->~type();
			}

			template <typename Tp, size_t N>
			void Auto_array<Tp, N>::push_front(const type & src)
			{
				if (full()) {
					throw std::exception();
				}
				//TODO
			}

			template <typename Tp, size_t N>
			void Auto_array<Tp, N>::pop_front()
			{
				if (empty()) {
					throw std::exception();
				}

				std::copy(p + 1, p + n, p);
				--n;
				(p + n )->~type();
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
				return p[n - 1];
			}

			template <typename Tp, size_t N>
			typename Auto_array<Tp, N>::const_reference
			Auto_array<Tp, N>::back() const
			{
				if (empty()) {
					throw std::exception();
				}
				return p[n - 1];
			}

			template <typename Tp, size_t N>
			typename Auto_array<Tp, N>::reference
			Auto_array<Tp, N>::operator[](size_t index)
			{
				if (index >= n) {
					throw std::out_of_range("range check fail in Auto_array");
				}
				return p[index];
			}

			template <typename Tp, size_t N>
			typename Auto_array<Tp, N>::const_reference
			Auto_array<Tp, N>::operator[](size_t index) const
			{
				if (index >= n) {
					throw std::out_of_range("range check fail in Auto_array");
				}
				return p[index];
			}

			template <typename Tp, size_t N>
			typename Auto_array<Tp, N>::iterator
			Auto_array<Tp, N>::begin()
			{
				return iterator(p,this);
			}

			template <typename Tp, size_t N>
			typename Auto_array<Tp, N>::iterator
			Auto_array<Tp, N>::end()
			{
				return iterator(p + n, this);
			}

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
			void Auto_array<Tp, N>::clear()
			{
				while (n--) {
					(p + n)->~type();
				}
			}

			template <typename Tp, size_t N>
			void Auto_array<Tp, N>::fill()
			{
				for (size_t i = n; i < N; ++i) {
					new (p + i) type();
				}
				n = N;
			}

			template <typename Tp, size_t N>
			void Auto_array<Tp, N>::fill(const type & val)
			{
				for (size_t i = n; i < N; ++i) {
					new (p + i) type(val);
				}
				n = N;
			}

			template <typename Tp, size_t N>
			bool Auto_array<Tp, N>::empty() const
			{
				return n == 0;
			}

			template <typename Tp, size_t N>
			bool Auto_array<Tp, N>::full() const
			{
				return n == N;
			}

			template <typename Tp, size_t N>
			size_t Auto_array<Tp, N>::size() const
			{
				return n;
			}


			template <typename Tp, size_t N>
			Auto_array<Tp, N>::iterator
			Auto_array<Tp, N>::find(const type & src)
			{
				for (size_t i = 0; i < n; ++i) {
					if (p[i] == src) {
						return iterator(p + i, this);
					}
				}
				return iterator(p + n, this);
			}



			template <typename Tp, size_t N>
			template <typename JudgeFunction>
			Auto_array<Tp, N>::iterator Auto_array<Tp, N>::find_if(JudgeFunction judge_function)
			{
				for (size_t i = 0; i < n; ++i) {
					if (judge_function(p[i])) {
						return iterator(p + i, this);
					}
				}
				return iterator(p + n, this);
			}

		}
	}
}

#endif /* INCLUDE_KERBAL_DATA_STRUCT_AUTO_ARRAY_BASE_HPP_ */
