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

#include <kerbal/data_struct/static_container_base/static_container_exception.hpp>

namespace kerbal
{
	namespace data_struct
	{

		template <typename Tp, size_t N>
		static_array<Tp, N>::static_array() :
				p_to_end(storage.raw_pointer_at(0))
		{
		}

		template <typename Tp, size_t N>
		static_array<Tp, N>::static_array(const static_array & src) :
				p_to_end(storage.raw_pointer_at(0))
		{
			const_iterator begin = src.cbegin(), end = src.cend();
			size_type init_index = 0;
			while (begin != end) {
				this->storage.construct_at(init_index, *begin);
				++init_index;
				++p_to_end; // = storage.raw_pointer_at(init_index);
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
				p_to_end(storage.raw_pointer_at(0))
		{
			size_type init_index = 0;
			while (begin != end && init_index != N) {
				this->storage.construct_at(init_index, *begin);
				++init_index;
				p_to_end = storage.raw_pointer_at(init_index);
				++begin;
			}
		}

		template <typename Tp, size_t N>
		static_array<Tp, N>::~static_array()
		{
			clear();
		}

		template <typename Tp, size_t N>
		static_array<Tp, N>& static_array<Tp, N>::operator=(const static_array & src)
		{
			assign(src.cbegin(), src.cend());
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
		void static_array<Tp, N>::assign(size_type n, const value_type & val)
		{
			if (n > N) {
				n = N;
			}
			const size_type new_size = n;
			const size_type previous_size = this->size();

			if (previous_size <= new_size) {
				size_type assign_index = 0;
				while (assign_index != previous_size) {
					this->storage.raw_value_at(assign_index) = val;
					++assign_index;
				}
				while (assign_index != new_size) {
					this->storage.construct_at(assign_index, val);
					++assign_index;
					++this->p_to_end; // = this->storage.raw_pointer_at(assign_index);
				}
			} else {
				size_type destroy_index = previous_size;
				while (destroy_index != new_size) {
					--destroy_index;
					this->storage.destroy_at(destroy_index, val);
					--this->p_to_end; // = this->storage.raw_pointer_at(destroy_index);
				}
				size_type assign_index = 0;
				while (assign_index != new_size) {
					this->storage.raw_value_at(assign_index) = val;
					++assign_index;
				}
			}
		}

		template <typename Tp, size_t N>
		template <typename InputIterator>
		void static_array<Tp, N>::assign(InputIterator begin, InputIterator end)
		{
			const size_type previous_size = this->size();
			size_type assign_index = 0;
			while (assign_index != previous_size && begin != end) {
				this->storage.raw_value_at(assign_index) = *begin;
				++assign_index;
				++begin;
			}

			if (assign_index != previous_size) { // namely: begin == end
				// X X X X O O O
				// T T
				size_type destroy_index = previous_size;
				while (destroy_index != assign_index) {
					--destroy_index;
					this->storage.destroy_at(destroy_index);
					--this->p_to_end;
				}
			} else {
				// X X X X O O O
				// T T T T T T T T T
				while (assign_index != N && begin != end) {
					this->storage.construct_at(assign_index, *begin);
					++assign_index;
					++this->p_to_end;
					++begin;
				}
			}
		}

#if __cplusplus >= 201103L
		template <typename Tp, size_t N>
		void static_array<Tp, N>::assign(std::initializer_list<value_type> src)
		{
			assign(src.begin(), src.end());
		}
#endif

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::iterator
		static_array<Tp, N>::begin()
		{
			return iterator(this->storage.raw_pointer_at(0));
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_iterator
		static_array<Tp, N>::begin() const
		{
			return this->cbegin();
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_iterator
		static_array<Tp, N>::end() const
		{
			return this->cend();
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_iterator
		static_array<Tp, N>::cbegin() const
		{
			return const_iterator(this->storage.raw_pointer_at(0));
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
		typename static_array<Tp, N>::const_reverse_iterator
		static_array<Tp, N>::rbegin() const
		{
			return this->crbegin();
		}
		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_reverse_iterator
		static_array<Tp, N>::rend() const
		{
			return this->crend();
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
			return const_reverse_iterator(this->storage.raw_pointer_at(0) - 1);
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::size_type
		static_array<Tp, N>::size() const
		{
			return p_to_end - this->storage.raw_pointer_at(0);
		}

		template <typename Tp, size_t N>
		bool static_array<Tp, N>::empty() const
		{
			return this->size() == 0;
		}

		template <typename Tp, size_t N>
		bool static_array<Tp, N>::full() const
		{
			return this->size() == N;
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::reference
		static_array<Tp, N>::operator[](size_type index)
		{
			return this->storage.raw_value_at(index);
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_reference
		static_array<Tp, N>::operator[](size_type index) const
		{
			return this->storage.raw_value_at(index);
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::reference
		static_array<Tp, N>::at(size_type index)
		{
			if (index >= size()) {
				throw std::out_of_range("range check fail in static_array");
			}
			return (*this)[index];
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_reference
		static_array<Tp, N>::at(size_type index) const
		{
			if (index >= size()) {
				throw std::out_of_range("range check fail in static_array");
			}
			return (*this)[index];
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::reference
		static_array<Tp, N>::front()
		{
			if (empty()) {
				throw std::out_of_range("range check fail in static_array");
			}
			return this->storage.raw_value_at(0);
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_reference
		static_array<Tp, N>::front() const
		{
			if (empty()) {
				throw std::out_of_range("range check fail in static_array");
			}
			return this->storage.raw_value_at(0);
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::reference
		static_array<Tp, N>::back()
		{
			if (empty()) {
				throw std::out_of_range("range check fail in static_array");
			}
			return *this->rbegin();
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_reference
		static_array<Tp, N>::back() const
		{
			if (empty()) {
				throw std::out_of_range("range check fail in static_array");
			}
			return *this->crbegin();
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::equal_c_array_reference
		static_array<Tp, N>::c_arr()
		{
			if (!full()) {
				throw std::exception();
			}
			return this->storage.raw_value();
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_equal_c_array_reference
		static_array<Tp, N>::const_c_arr() const
		{
			if (!full()) {
				throw std::exception();
			}
			return this->storage.raw_value();
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_pointer
		static_array<Tp, N>::data() const
		{
			return this->storage.raw_value_at(0);
		}

		template <typename Tp, size_t N>
		void static_array<Tp, N>::push_back(const_reference src)
		{
			if (full()) {
				throw kerbal::data_struct::static_container_full_exception(N);
			}

			this->storage.construct_at(this->size(), src);
			++this->p_to_end; // = this->storage.raw_pointer_at(insert_index);
		}

#	if __cplusplus >= 201103L
		template <typename Tp, size_t N>
		void static_array<Tp, N>::push_back(rvalue_reference src)
		{
			if (full()) {
				throw kerbal::data_struct::static_container_full_exception(N);
			}

			size_type insert_index = this->size();
			this->storage.construct_at(insert_index, src);
			++this->p_to_end; // = this->storage.raw_pointer_at(insert_index);
		}
#	endif

		template <typename Tp, size_t N>
		void static_array<Tp, N>::pop_back()
		{
			if (empty()) {
				throw kerbal::data_struct::static_container_empty_exception();
			}

			this->storage.destroy_at(this->size() - 1);
			--this->p_to_end;
		}

		template <typename Tp, size_t N>
		void static_array<Tp, N>::push_front(const_reference src)
		{
			this->insert(this->cbegin(), src);
		}

#	if __cplusplus >= 201103L
		template <typename Tp, size_t N>
		void static_array<Tp, N>::push_front(rvalue_reference src)
		{
			this->insert(this->cbegin(), src);
		}
#	endif

		template <typename Tp, size_t N>
		void static_array<Tp, N>::pop_front()
		{
			if (empty()) {
				throw kerbal::data_struct::static_container_empty_exception();
			}

			const size_type previous_size = this->size();
			size_type new_pos_index = 0;
			while (new_pos_index < previous_size - 1) {
#	if __cplusplus < 201103L
				this->storage.raw_value_at(new_pos_index) = this->storage.raw_value_at(new_pos_index + 1);
#	else
				this->storage.raw_value_at(new_pos_index) = std::move(this->storage.raw_value_at(new_pos_index + 1));
#	endif
				++new_pos_index;
			}
			this->storage.destroy_at(this->size() - 1);
			--this->p_to_end;
		}

		template <typename Tp, size_t N>
		void static_array<Tp, N>::insert(const_iterator pos, const_reference val)
		{
			if (full()) {
				throw kerbal::data_struct::static_container_full_exception(N);
			}

			if (pos == this->cend()) {
				// A A A O O O
				//          ^
				this->storage.construct_at(this->size(), val);
				++this->p_to_end;
			} else {
				const size_type previous_size = this->size(); // 6

				// A A A X Y Z O O O
				//          ^      $
#	if __cplusplus < 201103L
				this->storage.construct_at(previous_size, this->storage.raw_value_at(previous_size - 1));
#	else
				this->storage.construct_at(previous_size, std::move(this->storage.raw_value_at(previous_size - 1)));
#	endif
				++this->p_to_end;
				// A A A X Y Z Z O O
				//          ^

				const size_type insert_index = pos - this->cbegin();
				size_type new_pos_index = previous_size;
				while (--new_pos_index != insert_index) {
#	if __cplusplus < 201103L
					this->storage.raw_value_at(new_pos_index) = this->storage.raw_value_at(new_pos_index - 1);
#	else
					this->storage.raw_value_at(new_pos_index) = std::move(this->storage.raw_value_at(new_pos_index - 1));
#	endif
				}

				this->storage.raw_value_at(insert_index) = val;
			}
		}

#	if __cplusplus >= 201103L
		template <typename Tp, size_t N>
		void static_array<Tp, N>::insert(const_iterator pos, rvalue_reference val)
		{
			if (full()) {
				throw kerbal::data_struct::static_container_full_exception(N);
			}

			if (pos == this->cend()) {
				// A A A O O O
				//          ^
				this->storage.construct_at(this->size(), val);
				++this->p_to_end;
			} else {
				const size_type previous_size = this->size(); // 6

				this->storage.construct_at(previous_size, std::move(this->storage.raw_value_at(previous_size - 1)));
				++this->p_to_end;
				// A A A X Y Z Z O O
				//          ^

				const size_type insert_index = pos - this->cbegin();
				size_type new_pos_index = previous_size;
				while (--new_pos_index != insert_index) {
					this->storage.raw_value_at(new_pos_index) = std::move(this->storage.raw_value_at(new_pos_index - 1));
				}

				this->storage.raw_value_at(insert_index) = val;
			}
		}
#	endif

//		template <typename Tp, size_t N>
//		void static_array<Tp, N>::erase(const_iterator pos);
//
//		template <typename Tp, size_t N>
//		void static_array<Tp, N>::erase(const_iterator begin, const_iterator end);

		template <typename Tp, size_t N>
		void static_array<Tp, N>::swap(static_array & with)
		{
			bool condition = this->size() < with.size();
			static_array & s_arr = condition ? *this : with;
			static_array & l_arr = condition ? with : *this;

			const size_type s_size = s_arr.size();
			const size_type l_size = l_arr.size();

			size_type i = 0;
			size_type j = 0;
			while (i != s_size) {
				std::swap(s_arr.storage.raw_value_at(i), l_arr.storage.raw_value_at(j));
				++i;
				++j;
			}

			while (j != l_size) {
#	if __cplusplus < 201103L
				s_arr.storage.construct_at(i, l_arr.storage.raw_value_at(j));
#	else
				s_arr.storage.construct_at(i, std::move(l_arr.storage.raw_value_at(j)));
#	endif
				++i;
				++s_arr.p_to_end;
				++j;
			}

			size_type destroy_index = l_arr.size();
			while (destroy_index > s_size) {
				--destroy_index;
				l_arr.storage.destroy_at(destroy_index);
				--l_arr.p_to_end;
			}
		}

		template <typename Tp, size_t N>
		void static_array<Tp, N>::clear()
		{
			size_type destroy_index = this->size();
			while (destroy_index > 0) {
				--destroy_index;
				this->storage.destroy_at(destroy_index);
				--this->p_to_end;
			}
		}

		template <typename Tp, size_t N>
		void static_array<Tp, N>::fill()
		{
			size_type assign_index = this->size();
			while (assign_index != N) {
				this->storage.construct_at(assign_index);
				++assign_index;
				++this->p_to_end;
			}
		}

		template <typename Tp, size_t N>
		void static_array<Tp, N>::fill(const_reference val)
		{
			size_type assign_index = this->size();
			while (assign_index != N) {
				this->storage.construct_at(assign_index, val);
				++assign_index;
				++this->p_to_end;
			}
		}

		template <typename Tp, size_t N>
		bool static_array<Tp, N>::operator==(const static_array & rhs) const
		{
			const_iterator i = this->cbegin();
			const_iterator j = rhs.cbegin();
			while (i != this->cend() && j != rhs.cend() && *i == *j) {
				++i;
				++j;
			}
			return !(i != this->cend()) && !(j != rhs.cend());
		}

		template <typename Tp, size_t N>
		bool static_array<Tp, N>::operator!=(const static_array & rhs) const
		{
			const_iterator i = this->cbegin();
			const_iterator j = rhs.cbegin();
			while (i != this->cend() && j != rhs.cend() && !(*i != *j)) {
				++i;
				++j;
			}
			return i != this->cend() || j != rhs.cend();
		}

//		template <typename Tp, size_t N>
//		bool static_array<Tp, N>::operator<(const static_array & rhs) const;
//		template <typename Tp, size_t N>
//		bool static_array<Tp, N>::operator<=(const static_array & rhs) const;
//		template <typename Tp, size_t N>
//		bool static_array<Tp, N>::operator>(const static_array & rhs) const;
//		template <typename Tp, size_t N>
//		bool static_array<Tp, N>::operator>=(const static_array & rhs) const;

	}
}

#endif /* INCLUDE_KERBAL_DATA_STRUCT_STATIC_CONTAINER_BASE_STATIC_ARRAY_BASE_HPP_ */
