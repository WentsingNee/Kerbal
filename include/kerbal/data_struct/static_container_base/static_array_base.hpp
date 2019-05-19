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

		template <bool enable_mem_optimization>
		struct __static_array_copy_details;

		template <>
		struct __static_array_copy_details<false>
		{
				template <typename Tp, size_t N>
				void
				operator()(static_array<Tp, N> & self,
						const typename static_array<Tp, N>::storage_type src[], typename static_array<Tp, N>::size_type src_length) const
				{
					typename static_array<Tp, N>::size_type i = 0;
					while (i < src_length) {
						self.__construct_at(i, src[i].raw_value());
						++self.p_to_end;
						++i;
					}
				}
		};

		template <>
		struct __static_array_copy_details<true>
		{
				template <typename Tp, size_t N>
				void
				operator()(static_array<Tp, N> & self,
						const typename static_array<Tp, N>::storage_type src[], typename static_array<Tp, N>::size_type src_length) const
				{
					::memcpy(self.storage, src, src_length * sizeof(typename static_array<Tp, N>::storage_type));
					self.p_to_end = self.storage + src_length;
				}
		};

		template <typename Tp, size_t N>
		static_array<Tp, N>::static_array(const static_array & src) :
				p_to_end(storage + 0)
		{
//			__static_array_copy_details<false>
//						()(*this, src.storage, src.size());
#		if __cplusplus < 201103L
			__static_array_copy_details<
				kerbal::type_traits::is_fundamental<value_type>::value ||
				kerbal::type_traits::is_pointer<value_type>::value
			>
			()(*this, src.storage, src.size());
#		else
			__static_array_copy_details<std::is_trivially_copy_constructible<value_type>::value>
			()(*this, src.storage, src.size());
#		endif
		}


#	if __cplusplus >= 201103L

		template <typename Tp, size_t N>
		static_array<Tp, N>::static_array(std::initializer_list<value_type> src) :
				static_array(src.begin(), src.end())
		{
//			static_assert(N >= src.size(), "you must enlarge the static_array length");
		}

#	endif


		template <bool enable_mem_optimization>
		struct __static_array_range_copy_details;

		template <>
		struct __static_array_range_copy_details<false>
		{
				template <typename Tp, size_t N, typename InputIterator>
				void
				operator()(static_array<Tp, N> & self, InputIterator first, InputIterator last) const
				{
					while (first != last && !self.full()) {
						self.__construct_at(self.end(), *first);
						++self.p_to_end;
						++first;
					}
				}
		};

		template <>
		struct __static_array_range_copy_details<true>
		{
				template <typename Tp, size_t N, typename InputIterator>
				void
				operator()(static_array<Tp, N> & self, InputIterator first, InputIterator last) const
				{
					::memcpy(self.storage, first, (last - first) * sizeof(typename static_array<Tp, N>::storage_type));
					self.p_to_end = self.storage + (last - first);
				}
		};

		template <typename Tp, size_t N>
		static_array<Tp, N>::static_array(size_type n, const_reference val) :
				p_to_end(storage + 0)
		{
			this->assign(n, val);
		}

		template <typename Tp, size_t N>
		template <typename InputCompatibleIterator>
		static_array<Tp, N>::static_array(InputCompatibleIterator first, InputCompatibleIterator last,
				typename kerbal::type_traits::enable_if<
						kerbal::type_traits::is_input_compatible_iterator<InputCompatibleIterator>::value
						, int
				>::type
		) :
				p_to_end(storage + 0)
		{
//			__static_array_range_copy_details<false>()(*this, first, last);
			__static_array_range_copy_details<
			(
				kerbal::type_traits::is_same<pointer, InputCompatibleIterator>::value ||
				kerbal::type_traits::is_same<const_pointer, InputCompatibleIterator>::value
			)
			&&
			(
#		if __cplusplus < 201103L
				kerbal::type_traits::is_fundamental<value_type>::value ||
				kerbal::type_traits::is_pointer<value_type>::value
#		else
				std::is_trivially_copy_constructible<value_type>::value
#		endif
			)
			>
			()(*this, first, last);
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

		template <bool enable_mem_optimization>
		struct __static_array_n_assign_details;

		template <>
		struct __static_array_n_assign_details<false>
		{
				template <typename Tp, size_t N>
				void
				operator()(static_array<Tp, N> & self,
						typename static_array<Tp, N>::size_type n, const typename static_array<Tp, N>::value_type & val) const
				{
					typedef typename static_array<Tp, N>::size_type size_type;

					const size_type new_size = n;
					const size_type previous_size = self.size();

					if (previous_size <= new_size) {
						/*
						 * a a a x x x x x
						 * b b b b b b x x
						 */
						size_type assign_index = 0;
						while (assign_index != previous_size) {
							self[assign_index] = val;
							++assign_index;
						}
						while (assign_index != new_size) {
							self.__construct_at(self.end(), val);
							++self.p_to_end;
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
							self.__destroy_at(destroy_index);
							--self.p_to_end;
						}
						size_type assign_index = 0;
						while (assign_index != new_size) {
							self[assign_index] = val;
							++assign_index;
						}
					}
				}
		};

		template <>
		struct __static_array_n_assign_details<true>
		{
				template <typename Tp, size_t N>
				void
				operator()(static_array<Tp, N> & self,
						typename static_array<Tp, N>::size_type n, const typename static_array<Tp, N>::value_type & val) const
				{
					typedef typename static_array<Tp, N>::size_type size_type;
					for (size_type i = 0; i < n; ++i) {
						self[i] = val;
					}
					self.p_to_end = self.storage + n;
				}
		};

		template <typename Tp, size_t N>
		void static_array<Tp, N>::assign(size_type n, const value_type & val)
		{
			if (n > N) {
				n = N;
			}
//			__static_array_n_assign_details<false>()(*this, n, val);
			__static_array_n_assign_details<
#		if __cplusplus < 201103L
				kerbal::type_traits::is_fundamental<value_type>::value ||
				kerbal::type_traits::is_pointer<value_type>::value
#		else
				std::is_trivially_copy_constructible<value_type>::value &&
				std::is_trivially_copy_assignable<value_type>::value
#		endif
			>
			()(*this, n, val);
		}

		template <typename Tp, size_t N>
		template <typename InputCompatibleIterator>
		typename kerbal::type_traits::enable_if<
				kerbal::type_traits::is_input_compatible_iterator<InputCompatibleIterator>::value
		>::type
		static_array<Tp, N>::assign(InputCompatibleIterator first, InputCompatibleIterator last)
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
		static_array<Tp, N>::begin() KERBAL_NOEXCEPT
		{
			return iterator(this->storage + 0);
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::iterator
		static_array<Tp, N>::end() KERBAL_NOEXCEPT
		{
			return iterator(const_cast<storage_type*>(this->p_to_end));
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_iterator
		static_array<Tp, N>::begin() const KERBAL_NOEXCEPT
		{
			return this->cbegin();
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_iterator
		static_array<Tp, N>::end() const KERBAL_NOEXCEPT
		{
			return this->cend();
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_iterator
		static_array<Tp, N>::cbegin() const KERBAL_NOEXCEPT
		{
			return const_iterator(this->storage + 0);
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_iterator
		static_array<Tp, N>::cend() const KERBAL_NOEXCEPT
		{
			return const_iterator(p_to_end);
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::reverse_iterator
		static_array<Tp, N>::rbegin() KERBAL_NOEXCEPT
		{
			return reverse_iterator(this->begin() + this->size());
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::reverse_iterator
		static_array<Tp, N>::rend() KERBAL_NOEXCEPT
		{
			return reverse_iterator(this->begin());
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_reverse_iterator
		static_array<Tp, N>::rbegin() const KERBAL_NOEXCEPT
		{
			return this->crbegin();
		}
		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_reverse_iterator
		static_array<Tp, N>::rend() const KERBAL_NOEXCEPT
		{
			return this->crend();
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_reverse_iterator
		static_array<Tp, N>::crbegin() const KERBAL_NOEXCEPT
		{
			return const_reverse_iterator(this->end());
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_reverse_iterator
		static_array<Tp, N>::crend() const KERBAL_NOEXCEPT
		{
			return const_reverse_iterator(this->cbegin());
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::size_type
		static_array<Tp, N>::size() const KERBAL_NOEXCEPT
		{
			return (this->p_to_end - this->storage);
		}

		template <typename Tp, size_t N>
		bool static_array<Tp, N>::empty() const KERBAL_NOEXCEPT
		{
			return this->size() == 0;
		}

		template <typename Tp, size_t N>
		bool static_array<Tp, N>::full() const KERBAL_NOEXCEPT
		{
			return this->size() == N;
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::reference
		static_array<Tp, N>::operator[](size_type index) KERBAL_NOEXCEPT
		{
			return this->storage[index].raw_value();
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_reference
		static_array<Tp, N>::operator[](size_type index) const KERBAL_NOEXCEPT
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

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::equal_c_array_reference
		static_array<Tp, N>::c_arr()
		{
			if (!full()) {
				throw std::exception();
			}
			return reinterpret_cast<equal_c_array_reference>(this->storage);
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_equal_c_array_reference
		static_array<Tp, N>::const_c_arr() const
		{
			if (!full()) {
				throw std::exception();
			}
			return reinterpret_cast<equal_c_array_reference>(this->storage);
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_pointer
		static_array<Tp, N>::data() const
		{
			return reinterpret_cast<const_pointer>(&(this->storage[0]));
		}

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
			this->emplace_front(this->cbegin(), src);
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
			this->erase(this->cbegin());
		}

		template <bool enable_mem_optimization>
		struct __static_array_insert_details;

		template <>
		struct __static_array_insert_details<false>
		{
				template <typename Tp, size_t N>
				void
				operator()(static_array<Tp, N> & self,
						typename static_array<Tp, N>::size_type pos,
						typename static_array<Tp, N>::const_reference val) const
				{
					if (pos == self.size()) {
						// A A A O O O
						//          ^
						self.__construct_at(pos, val);
						++self.p_to_end;
					} else {
						typedef typename static_array<Tp, N>::size_type size_type;

						// A A A X Y Z O O O
						//          ^      $
#			if __cplusplus < 201103L
						self.__construct_at(self.end(), self.back());
#			else
						self.__construct_at(self.end(), std::move(self.back()));
#			endif
						++self.p_to_end;

						// A A A X Y Z Z O O
						//          ^

						size_type i = self.size() - 1;
						while (--i != pos) {
#			if __cplusplus < 201103L
							self[i] = self[i - 1];
#			else
							self[i] = std::move(self[i - 1]);
#			endif
						}

						self[pos] = val;
					}
				}
		};

		template <>
		struct __static_array_insert_details<true>
		{
				template <typename Tp, size_t N>
				void
				operator()(static_array<Tp, N> & self,
						typename static_array<Tp, N>::size_type pos,
						typename static_array<Tp, N>::const_reference val) const
				{
					typedef typename static_array<Tp, N>::value_type value_type;
					::memmove(self.storage + pos + 1, self.storage + pos,
							(self.size() - pos) * sizeof(value_type));
					self[pos] = val;
					++self.p_to_end;
				}
		};

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::iterator
		static_array<Tp, N>::insert(const const_iterator pos, const_reference val)
		{
			size_type n = pos - this->cbegin();
//			__static_array_insert_details<false>()(*this, n, val);
			__static_array_insert_details<
#		if __cplusplus < 201103L
				kerbal::type_traits::is_fundamental<value_type>::value ||
				kerbal::type_traits::is_pointer<value_type>::value
#		else
				std::is_trivially_constructible<value_type>::value &&
				std::is_trivially_move_assignable<value_type>::value
#		endif
			>
			()(*this, n, val);
			return iterator(this->begin() + n);
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
				this->__construct_at(this->end(), std::forward<Args>(args)...);
				++this->p_to_end;
			} else {
				const size_type previous_size = this->size(); // 6

				this->__construct_at(this->end(), std::move((*this)[previous_size - 1]));
				++this->p_to_end;
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


		template <bool enable_mem_optimization>
		struct __static_array_erase_details;

		template <>
		struct __static_array_erase_details<false>
		{
				template <typename Tp, size_t N>
				void
				operator()(static_array<Tp, N> & self,
						typename static_array<Tp, N>::size_type pos) const
				{
					typedef typename static_array<Tp, N>::size_type size_type;
					for (size_type i = pos; i + 1 < self.size(); ++i) {
#				if __cplusplus < 201103L
						self[i] = self[i + 1];
#				else
						self[i] = std::move(self[i + 1]);
#				endif
					}
					if (self.size() != 0) {
						self.__destroy_at(self.size() - 1);
					}
					--self.p_to_end;
				}
		};

		template <>
		struct __static_array_erase_details<true>
		{
				template <typename Tp, size_t N>
				void
				operator()(static_array<Tp, N> & self,
						typename static_array<Tp, N>::size_type pos) const
				{
					if (pos == self.size()) {
						return;
					}
					typedef typename static_array<Tp, N>::value_type value_type;
					::memmove(self.storage + pos, self.storage + pos + 1,
							(self.size() - pos - 1) * sizeof(value_type));
					--self.p_to_end;
				}
		};

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::iterator
		static_array<Tp, N>::erase(const_iterator pos)
		{
			size_type n = pos - this->cbegin();
//			__static_array_erase_details<false>()(*this, n);
			__static_array_erase_details<
#			if __cplusplus < 201103L
				kerbal::type_traits::is_fundamental<value_type>::value ||
				kerbal::type_traits::is_pointer<value_type>::value
#			else
				std::is_trivially_destructible<value_type>::value &&
				std::is_trivially_move_assignable<value_type>::value
#			endif
			>
			()(*this, n);
			return iterator(this->storage + n);
		}
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
