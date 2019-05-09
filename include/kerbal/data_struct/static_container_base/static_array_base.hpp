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

#include <cstring>

#if __cplusplus >= 201103L
#	include <type_traits>
#endif

#include <kerbal/type_traits/type_traits_details/fundamental_deduction.hpp>
#include <kerbal/type_traits/type_traits_details/pointer_deduction.hpp>

namespace kerbal
{
	namespace data_struct
	{

		template <typename Tp, size_t N>
		static_array<Tp, N>::static_array() :
				p_to_end(storage + 0)
		{
		}

		template <bool enable_memecpy_optimization>
		struct __static_array_copy_details;

		template <>
		struct __static_array_copy_details<false>
		{
				template <typename storage_type, typename size_type>
				void
				operator()(storage_type dest[], const storage_type * & p_to_end,
						const storage_type src[], size_type src_length) const
				{
					size_type i = 0;
					while (i < src_length) {
						dest[i].construct(src[i].raw_value());
						++p_to_end;
						++i;
					}
				}
		};

		template <>
		struct __static_array_copy_details<true>
		{
				template <typename storage_type, typename size_type>
				void
				operator()(storage_type dest[], const storage_type * & p_to_end,
						const storage_type src[], size_type src_length) const
				{
					::memcpy(dest, src, src_length * sizeof(storage_type));
					p_to_end = dest + src_length;
				}
		};

		template <typename Tp, size_t N>
		static_array<Tp, N>::static_array(const static_array & src) :
				p_to_end(storage + 0)
		{

#	if __cplusplus < 201103L


			if (N < 16 || src.size() < 16) {
				// if the length is less than 16, doesn't need to take memecpy optimization into consideration
				__static_array_copy_details<false>()(this->storage, this->p_to_end, src.storage, src.size());
			} else {
				__static_array_copy_details<
					kerbal::type_traits::is_fundamental<value_type>::value ||
					kerbal::type_traits::is_pointer<value_type>::value
				>
				()(this->storage, this->p_to_end, src.storage, src.size());
			}

#	else
			if (N < 16 || src.size() < 16) {
				// if the length is less than 16, doesn't need to take memecpy optimization into consideration
				__static_array_copy_details<false>()(this->storage, this->p_to_end, src.storage, src.size());
			} else {
				__static_array_copy_details<std::is_trivially_copyable<value_type>::value>
				()(this->storage, this->p_to_end, src.storage, src.size());
			}
#	endif

		}


#	if __cplusplus >= 201103L

		template <typename Tp, size_t N>
		static_array<Tp, N>::static_array(std::initializer_list<value_type> src) :
				static_array(src.begin(), src.end())
		{
//			static_assert(N >= src.size(), "you must enlarge the static_array length");
		}

#	endif

		template <typename Tp, size_t N>
		template <typename InputIterator>
		static_array<Tp, N>::static_array(InputIterator first, InputIterator last,
				typename kerbal::type_traits::enable_if<
						kerbal::algorithm::is_compatible_iterator_type_of<InputIterator, std::input_iterator_tag>::value
						, int
				>::type
		) :
				p_to_end(storage + 0)
		{
			while (first != last && !this->full()) {
				this->__construct_the_last(*first);
				++first;
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

#	if __cplusplus >= 201103L
		template <typename Tp, size_t N>
		static_array<Tp, N>& static_array<Tp, N>::operator=(std::initializer_list<value_type> src)
		{
			assign(src.begin(), src.end());
			return *this;
		}
#	endif

		template <typename Tp, size_t N>
		void static_array<Tp, N>::assign(size_type n, const value_type & val)
		{
			if (n > N) {
				n = N;
			}
			const size_type new_size = n;
			const size_type previous_size = this->size();

			if (previous_size <= new_size) {
				/*
				 * a a a x x x x x
				 * b b b b b b x x
				 */
				size_type assign_index = 0;
				while (assign_index != previous_size) {
					(*this)[assign_index] = val;
					++assign_index;
				}
				while (assign_index != new_size) {
					this->__construct_the_last(val);
					++assign_index;
				}
			} else {
				/*
				 * a a a a a a x x
				 * b b b x x x x x
				 */
				size_type destroy_index = previous_size;
				while (destroy_index != new_size) {
					--destroy_index;
					this->__destroy_at(destroy_index);
					--this->p_to_end; // = this->storage.raw_pointer_at(destroy_index);
				}
				size_type assign_index = 0;
				while (assign_index != new_size) {
					(*this)[assign_index] = val;
					++assign_index;
				}
			}
		}

		template <typename Tp, size_t N>
		template <typename InputIterator>
		typename kerbal::type_traits::enable_if<
				kerbal::algorithm::is_compatible_iterator_type_of<InputIterator, std::input_iterator_tag>::value
		>::type
		static_array<Tp, N>::assign(InputIterator first, InputIterator last)
		{
			const size_type previous_size = this->size();
			size_type assign_index = 0;
			while (assign_index != previous_size && first != last) {
				(*this)[assign_index] = *first;
				++assign_index;
				++first;
			}

			if (assign_index != previous_size) { // namely: begin == end
				// X X X X O O O
				// T T
				size_type destroy_index = previous_size;
				while (destroy_index != assign_index) {
					--destroy_index;
					this->__destroy_at(destroy_index);
					--this->p_to_end;
				}
			} else {
				// X X X X O O O
				// T T T T T T T T T
				while (assign_index != N && first != last) {
					this->__construct_at(assign_index, *first);
					++assign_index;
					++this->p_to_end;
					++first;
				}
			}
		}

#	if __cplusplus >= 201103L
		template <typename Tp, size_t N>
		void static_array<Tp, N>::assign(std::initializer_list<value_type> src)
		{
			assign(src.begin(), src.end());
		}
#	endif

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::iterator
		static_array<Tp, N>::begin()
		{
			return iterator(this->storage + 0);
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::iterator
		static_array<Tp, N>::end()
		{
			return iterator(const_cast<storage_type*>(this->p_to_end));
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
			return const_iterator(this->storage + 0);
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
			return reverse_iterator(this->begin() + this->size());
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::reverse_iterator
		static_array<Tp, N>::rend()
		{
			return reverse_iterator(this->begin());
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
			return const_reverse_iterator(this->end());
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_reverse_iterator
		static_array<Tp, N>::crend() const
		{
			return const_reverse_iterator(this->cbegin());
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::size_type
		static_array<Tp, N>::size() const
		{
			return (this->p_to_end - this->storage);
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
			return this->storage[index].raw_value();
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_reference
		static_array<Tp, N>::operator[](size_type index) const
		{
			return this->storage[index].raw_value();
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
			return *this->begin();
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_reference
		static_array<Tp, N>::front() const
		{
			return *this->cbegin();
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::reference
		static_array<Tp, N>::back()
		{
			return *this->rbegin();
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_reference
		static_array<Tp, N>::back() const
		{
			return *this->crbegin();
		}

//		template <typename Tp, size_t N>
//		typename static_array<Tp, N>::equal_c_array_reference
//		static_array<Tp, N>::c_arr()
//		{
//			if (!full()) {
//				throw std::exception();
//			}
//			return this->storage.raw_value();
//		}
//
//		template <typename Tp, size_t N>
//		typename static_array<Tp, N>::const_equal_c_array_reference
//		static_array<Tp, N>::const_c_arr() const
//		{
//			if (!full()) {
//				throw std::exception();
//			}
//			return this->storage.raw_value();
//		}
//
//		template <typename Tp, size_t N>
//		typename static_array<Tp, N>::const_pointer
//		static_array<Tp, N>::data() const
//		{
//			return this->storage.raw_value_at(0);
//		}

		template <typename Tp, size_t N>
		void static_array<Tp, N>::push_back(const_reference src)
		{
			this->insert(this->cend(), src);
		}

#	if __cplusplus >= 201103L
		template <typename Tp, size_t N>
		void static_array<Tp, N>::push_back(rvalue_reference src)
		{
			this->emplace_back(std::move(src));
		}

		template <typename Tp, size_t N>
		template <typename ... Args>
		typename static_array<Tp, N>::reference
		static_array<Tp, N>::emplace_back(Args&& ...args)
		{
			return *this->emplace(this->cend(), std::forward<Args>(args)...);
		}
#	endif

		template <typename Tp, size_t N>
		void static_array<Tp, N>::pop_back()
		{
			this->__destroy_at(this->size() - 1);
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

		template <typename Tp, size_t N>
		template <typename ... Args>
		typename static_array<Tp, N>::reference
		static_array<Tp, N>::emplace_front(Args&& ...args)
		{
			return *this->emplace(this->cbegin(), std::forward<Args>(args)...);
		}

#	endif

		template <typename Tp, size_t N>
		void static_array<Tp, N>::pop_front()
		{
			const size_type previous_size = this->size();
			size_type new_pos_index = 0;
			while (new_pos_index < previous_size - 1) {
#	if __cplusplus < 201103L
				(*this)[new_pos_index] = (*this)[new_pos_index + 1];
#	else
				(*this)[new_pos_index] = std::move((*this)[new_pos_index + 1]);
#	endif
				++new_pos_index;
			}
			this->__destroy_at(this->size() - 1);
			--this->p_to_end;
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::iterator
		static_array<Tp, N>::insert(const const_iterator pos, const_reference val)
		{
			if (pos == this->cend()) {
				// A A A O O O
				//          ^
				this->__construct_the_last(val);
			} else {
				const size_type previous_size = this->size(); // 6

				// A A A X Y Z O O O
				//          ^      $
#	if __cplusplus < 201103L
				this->__construct_the_last(this->back());
#	else
				this->__construct_the_last(std::move(this->back()));
#	endif

				// A A A X Y Z Z O O
				//          ^

				const size_type insert_index = pos - this->cbegin();
				size_type new_pos_index = previous_size;
				while (--new_pos_index != insert_index) {
#	if __cplusplus < 201103L
					(*this)[new_pos_index] = (*this)[new_pos_index - 1];
#	else
					(*this)[new_pos_index] = std::move((*this)[new_pos_index - 1]);
#	endif
				}

				(*this)[insert_index] = val;
			}
			return iterator(this->begin() + (pos - this->cbegin()));
		}

#	if __cplusplus >= 201103L
		template <typename Tp, size_t N>
		typename static_array<Tp, N>::iterator
		static_array<Tp, N>::insert(const_iterator pos, rvalue_reference val)
		{
			return this->emplace(pos, std::move(val));
		}

		template <typename Tp, size_t N>
		template <typename ... Args>
		typename static_array<Tp, N>::iterator
		static_array<Tp, N>::emplace(const const_iterator pos, Args&& ...args)
		{
			if (pos == this->cend()) {
				// A A A O O O
				//          ^
				this->__construct_the_last(std::forward<Args>(args)...);
			} else {
				const size_type previous_size = this->size(); // 6

				this->__construct_the_last(std::move((*this)[previous_size - 1]));
				// A A A X Y Z Z O O
				//          ^

				const size_type insert_index = pos - this->cbegin();
				size_type new_pos_index = previous_size;
				while (--new_pos_index != insert_index) {
					(*this)[new_pos_index] = std::move((*this)[new_pos_index - 1]);
				}
				(*this)[insert_index] = value_type { std::forward<Args>(args)... };
			}
			return this->begin() + (pos - this->cbegin());
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
				std::swap(s_arr[i], l_arr[j]);
				++i;
				++j;
			}

			while (j != l_size) {
#	if __cplusplus < 201103L
				s_arr.__construct_at(i, l_arr[j]);
#	else
				s_arr.__construct_at(i, std::move(l_arr[j]));
#	endif
				++i;
				++s_arr.p_to_end;
				++j;
			}

			size_type destroy_index = l_arr.size();
			while (destroy_index > s_size) {
				--destroy_index;
				l_arr.__destroy_at(destroy_index);
				--l_arr.p_to_end;
			}
		}

		template <typename Tp, size_t N>
		void static_array<Tp, N>::clear()
		{
			size_type destroy_index = this->size();
			while (destroy_index > 0) {
				--destroy_index;
				this->__destroy_at(destroy_index);
				--this->p_to_end;
			}
		}

		template <typename Tp, size_t N>
		void static_array<Tp, N>::fill()
		{
			size_type assign_index = this->size();
			while (assign_index != N) {
				this->__construct_at(assign_index);
				++assign_index;
				++this->p_to_end;
			}
		}

		template <typename Tp, size_t N>
		void static_array<Tp, N>::fill(const_reference val)
		{
			size_type assign_index = this->size();
			while (assign_index != N) {
				this->__construct_at(assign_index, val);
				++assign_index;
				++this->p_to_end;
			}
		}

#	if __cplusplus < 201103L
		template <typename Tp, size_t N>
		void static_array<Tp, N>::__construct_at(size_type index)
		{
			this->storage[index].construct();
		}

		template <typename Tp, size_t N>
		template <typename T0>
		void static_array<Tp, N>::__construct_at(size_type index, const T0& v0)
		{
			this->storage[index].construct(v0);
		}

		template <typename Tp, size_t N>
		template <typename T0, typename T1>
		void static_array<Tp, N>::__construct_at(size_type index, const T0& v0, const T1& v1)
		{
			this->storage[index].construct(v0, v1);
		}

		template <typename Tp, size_t N>
		template <typename T0, typename T1, typename T2>
		void static_array<Tp, N>::__construct_at(size_type index, const T0& v0, const T1& v1, const T2& v2)
		{
			this->storage[index].construct(v0, v1, v2);
		}

		template <typename Tp, size_t N>
		template <typename T0, typename T1, typename T2, typename T3>
		void static_array<Tp, N>::__construct_at(size_type index, const T0& v0, const T1& v1, const T2& v2, const T3& v3)
		{
			this->storage[index].construct(v0, v1, v2, v3);
		}

		template <typename Tp, size_t N>
		template <typename T0, typename T1, typename T2, typename T3, typename T4>
		void static_array<Tp, N>::__construct_at(size_type index, const T0& v0, const T1& v1, const T2& v2, const T3& v3, const T4& v4)
		{
			this->storage[index].construct(v0, v1, v2, v3, v4);
		}

		template <typename Tp, size_t N>
		void static_array<Tp, N>::__construct_at(iterator itor)
		{
			(itor.current)->construct();
		}

		template <typename Tp, size_t N>
		template <typename T0>
		void static_array<Tp, N>::__construct_at(iterator itor, const T0& v0)
		{
			(itor.current)->construct(v0);
		}

		template <typename Tp, size_t N>
		template <typename T0, typename T1>
		void static_array<Tp, N>::__construct_at(iterator itor, const T0& v0, const T1& v1)
		{
			(itor.current)->construct(v0, v1);
		}

		template <typename Tp, size_t N>
		template <typename T0, typename T1, typename T2>
		void static_array<Tp, N>::__construct_at(iterator itor, const T0& v0, const T1& v1, const T2& v2)
		{
			(itor.current)->construct(v0, v1, v2);
		}

		template <typename Tp, size_t N>
		template <typename T0, typename T1, typename T2, typename T3>
		void static_array<Tp, N>::__construct_at(iterator itor, const T0& v0, const T1& v1, const T2& v2, const T3& v3)
		{
			(itor.current)->construct(v0, v1, v2, v3);
		}

		template <typename Tp, size_t N>
		template <typename T0, typename T1, typename T2, typename T3, typename T4>
		void static_array<Tp, N>::__construct_at(iterator itor, const T0& v0, const T1& v1, const T2& v2, const T3& v3, const T4& v4)
		{
			(itor.current)->construct(v0, v1, v2, v3, v4);
		}

#	else

		template <typename Tp, size_t N>
		template <typename ... Args>
		void static_array<Tp, N>::__construct_at(size_type index, Args&& ...args)
		{
			this->storage[index].construct(std::forward<Args>(args)...);
		}

		template <typename Tp, size_t N>
		template <typename ... Args>
		void static_array<Tp, N>::__construct_at(iterator itor, Args&& ...args)
		{
			(itor.current)->construct(std::forward<Args>(args)...);
		}


#	endif

		template <typename Tp, size_t N>
		void static_array<Tp, N>::__construct_the_last(const_reference val)
		{
			this->__construct_at(this->size(), val);
			++this->p_to_end;
		}

#	if __cplusplus >= 201103L
		template <typename Tp, size_t N>
		void static_array<Tp, N>::__construct_the_last(rvalue_reference val)
		{
			this->__construct_at(this->size(), std::move(val));
			++this->p_to_end;
		}

		template <typename Tp, size_t N>
		template <typename ...Args>
		void static_array<Tp, N>::__construct_the_last(Args&& ...args)
		{
			this->__construct_at(this->size(), std::forward<Args>(args)...);
			++this->p_to_end;
		}

#	endif

		template <typename Tp, size_t N>
		void static_array<Tp, N>::__destroy_at(size_type index)
		{
			this->storage[index].destroy();
		}

		template <typename Tp, size_t N>
		void static_array<Tp, N>::__destroy_at(iterator itor)
		{
			(itor.current)->destroy();
		}

	}
}

#endif /* INCLUDE_KERBAL_DATA_STRUCT_STATIC_CONTAINER_BASE_STATIC_ARRAY_BASE_HPP_ */
