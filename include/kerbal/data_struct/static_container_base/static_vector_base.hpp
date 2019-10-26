/**
 * @file		static_vector_base.hpp
 * @brief
 * @date		2018-4-28
 * @author		Peter
 * @copyright	Peter
 * @copyright
 <a href="http://thinkspirit.org/">ThinkSpirit Laboratory</a>
 of
 <a href="http://www.nuist.edu.cn/">Nanjing University of Information Science & Technology</a>
 */

#ifndef KERBAL_DATA_STRUCT_STATIC_CONTAINER_BASE_STATIC_VECTOR_BASE_HPP_
#define KERBAL_DATA_STRUCT_STATIC_CONTAINER_BASE_STATIC_VECTOR_BASE_HPP_

#include <kerbal/algorithm/modifiers.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/type_traits/type_traits_details/fundamental_deduction.hpp>
#include <kerbal/type_traits/type_traits_details/pointer_deduction.hpp>
#include <kerbal/utility/throw_this_exception.hpp>

#include <algorithm>

#if __cplusplus >= 201103L
#	include <type_traits>
#endif

namespace kerbal
{

	namespace data_struct
	{

		template <typename Tp, size_t N>
		static_vector<Tp, N>::static_vector() KERBAL_NOEXCEPT :
				p_to_end(storage + 0)
		{
		}

		template <typename Tp, size_t N>
		void static_vector<Tp, N>::__copy_constructor(const static_vector & src, kerbal::type_traits::false_type)
		{
			const_iterator first = src.cbegin();
			const_iterator last = src.cend();

			try {
				while (first != last) {
					this->push_back(*first);
					++first;
				}
			} catch (...) {
				this->clear();
				throw;
			}
		}

		template <typename Tp, size_t N>
		void static_vector<Tp, N>::__copy_constructor(const static_vector & src, kerbal::type_traits::true_type) KERBAL_NOEXCEPT
		{
			const_iterator first = src.cbegin();
			const_iterator last = src.cend();

#	define EACH() do {\
				this->push_back(*first);\
				++first;\
			} while (false)

			for (difference_type trip_count(kerbal::iterator::distance(first, last) >> 2); trip_count > 0; --trip_count) {
				EACH();
				EACH();
				EACH();
				EACH();
			}

			difference_type remain(kerbal::iterator::distance(first, last));
			if (remain == 3) {
				EACH();
			}
			if (remain >= 2) {
				EACH();
			}
			if (remain >= 1) {
				EACH();
			}

#	undef EACH

		}

		template <typename Tp, size_t N>
		static_vector<Tp, N>::static_vector(const static_vector & src) :
				p_to_end(storage + 0)
		{

#		if __cplusplus < 201103L

			struct enable_optimization:
					kerbal::type_traits::bool_constant<
						kerbal::type_traits::is_fundamental<remove_all_extents_t>::value ||
						kerbal::type_traits::is_pointer<remove_all_extents_t>::value
					>
			{
			};

#		else

			struct enable_optimization:
					kerbal::type_traits::bool_constant<
						std::is_nothrow_copy_constructible<remove_all_extents_t>::value
					>
			{
			};

#		endif

			this->__copy_constructor(src, enable_optimization());
		}


#	if __cplusplus >= 201103L

		template <typename Tp, size_t N>
		static_vector<Tp, N>::static_vector(std::initializer_list<value_type> src) :
				static_vector(src.begin(), src.end())
		{
		}


		template <typename Tp, size_t N>
		void static_vector<Tp, N>::__move_constructor(static_vector && src, kerbal::type_traits::false_type)
		{
			iterator first = src.begin();
			iterator last = src.end();

			try {
				while (first != last) {
					this->push_back(std::move(*first));
					++first;
				}
			} catch (...) {
				this->clear();
				throw;
			}
		}

		template <typename Tp, size_t N>
		void static_vector<Tp, N>::__move_constructor(static_vector && src, kerbal::type_traits::true_type) noexcept
		{
			const_iterator first = src.cbegin();
			const_iterator last = src.cend();


#	define EACH() do {\
				this->push_back(std::move(*first));\
				++first;\
			} while (false)

			for (difference_type trip_count(kerbal::iterator::distance(first, last) >> 2); trip_count > 0; --trip_count) {
				EACH();
				EACH();
				EACH();
				EACH();
			}

			difference_type remain(kerbal::iterator::distance(first, last));
			if (remain == 3) {
				EACH();
			}
			if (remain >= 2) {
				EACH();
			}
			if (remain >= 1) {
				EACH();
			}

#	undef EACH

		}

		template <typename Tp, size_t N>
		static_vector<Tp, N>::static_vector(static_vector && src) :
				p_to_end(storage + 0)
		{

			struct enable_optimization:
					kerbal::type_traits::bool_constant<
						std::is_nothrow_move_constructible<remove_all_extents_t>::value
					>
			{
			};

			this->__move_constructor(src, enable_optimization());
		}

#	endif

		template <typename Tp, size_t N>
		static_vector<Tp, N>::static_vector(size_type n) :
				p_to_end(storage + 0)
		{
			value_type val;
			try {
				this->assign(n, val);
			} catch (...) {
				this->clear();
				throw;
			}
		}

		template <typename Tp, size_t N>
		static_vector<Tp, N>::static_vector(size_type n, const_reference val) :
				p_to_end(storage + 0)
		{
			this->assign(n, val);
		}


		template <typename Tp, size_t N>
		template <typename InputIterator>
		void static_vector<Tp, N>::__range_copy_constructor(InputIterator first, InputIterator last,
													std::input_iterator_tag, kerbal::type_traits::false_type)
		{
			// input iterator

			try {
				while (!this->full() && static_cast<bool>(first != last)) {
					this->push_back(*first);
					++first;
				}
			} catch (...) {
				this->clear();
				throw;
			}
		}

		template <typename Tp, size_t N>
		template <typename InputIterator>
		void static_vector<Tp, N>::__range_copy_constructor(InputIterator first, InputIterator last,
													std::input_iterator_tag, kerbal::type_traits::true_type) KERBAL_NOEXCEPT
		{
			// input iterator, no throw copy constructible

			while (!this->full() && static_cast<bool>(first != last)) {
				this->push_back(*first);
				++first;
			}
		}

		template <typename Tp, size_t N>
		template <typename RandomAccessIterator>
		void static_vector<Tp, N>::__range_copy_constructor(RandomAccessIterator first, RandomAccessIterator last,
													std::random_access_iterator_tag, kerbal::type_traits::false_type)
		{
			// random access iterator

			if (last - first > this->max_size()) {
				last = first + this->max_size();
			}

			try {
				while (first != last) {
					this->push_back(*first);
					++first;
				}
			} catch (...) {
				this->clear();
				throw;
			}
		}

		template <typename Tp, size_t N>
		template <typename RandomAccessIterator>
		void static_vector<Tp, N>::__range_copy_constructor(RandomAccessIterator first, RandomAccessIterator last,
													std::random_access_iterator_tag, kerbal::type_traits::true_type) KERBAL_NOEXCEPT
		{
			// random access iterator, no throw copy constructible

			if (last - first > this->max_size()) {
				last = first + this->max_size();
			}

#	define EACH() do {\
				this->push_back(*first);\
				++first;\
			} while (false)

			for (difference_type trip_count(kerbal::iterator::distance(first, last) >> 2); trip_count > 0; --trip_count) {
				EACH();
				EACH();
				EACH();
				EACH();
			}

			difference_type remain(kerbal::iterator::distance(first, last));
			if (remain == 3) {
				EACH();
			}
			if (remain >= 2) {
				EACH();
			}
			if (remain >= 1) {
				EACH();
			}

#	undef EACH

		}

		template <typename Tp, size_t N>
		template <typename InputIterator>
		static_vector<Tp, N>::static_vector(InputIterator first, InputIterator last,
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
						, int
				>::type
		) :
				p_to_end(storage + 0)
		{

#		if __cplusplus < 201103L

			struct enable_optimization: kerbal::type_traits::bool_constant<
					kerbal::type_traits::is_fundamental<remove_all_extents_t>::value ||
					kerbal::type_traits::is_pointer<remove_all_extents_t>::value
				>
			{
			};

#		else

			struct enable_optimization: kerbal::type_traits::bool_constant<
					std::is_trivially_copy_constructible<remove_all_extents_t>::value
				>
			{
			};

#		endif

			this->__range_copy_constructor(first, last, kerbal::iterator::iterator_category(first), enable_optimization());
		}

		template <typename Tp, size_t N>
		static_vector<Tp, N>::~static_vector()
		{
			this->clear();
		}

		template <typename Tp, size_t N>
		static_vector<Tp, N>& static_vector<Tp, N>::operator=(const static_vector & src)
		{
			this->assign(src.cbegin(), src.cend());
			return *this;
		}

#	if __cplusplus >= 201103L
		template <typename Tp, size_t N>
		static_vector<Tp, N>& static_vector<Tp, N>::operator=(std::initializer_list<value_type> src)
		{
			this->assign(src.begin(), src.end());
			return *this;
		}
#	endif

		template <typename Tp, size_t N>
		void static_vector<Tp, N>::__assign(size_type new_size, const_reference val, kerbal::type_traits::false_type)
		{
			size_type previous_size = this->size();

			if (previous_size <= new_size) {
				/*
				 * a a a x x x x x
				 * b b b b b b x x
				 */

				kerbal::algorithm::fill(this->begin(), this->end(), val);
				while (previous_size != new_size) {
					this->push_back(val);
					++previous_size;
				}
			} else {
				/*
				 * a a a a a a x x
				 * b b b x x x x x
				 */
				this->erase(this->nth(new_size), this->end());
				kerbal::algorithm::fill(this->begin(), this->end(), val);
			}
		}

		template <typename Tp, size_t N>
		void static_vector<Tp, N>::__assign(size_type new_size, const_reference val, kerbal::type_traits::true_type)
		{
			kerbal::algorithm::fill(this->begin(), this->nth(new_size), val);
			this->p_to_end = this->storage + new_size;
		}

		template <typename Tp, size_t N>
		void static_vector<Tp, N>::assign(size_type new_size, const value_type & val)
		{
			if (new_size > N) {
				new_size = N;
			}

#		if __cplusplus < 201103L

			struct enable_optimization:
					kerbal::type_traits::bool_constant<
						kerbal::type_traits::is_fundamental<remove_all_extents_t>::value ||
						kerbal::type_traits::is_pointer<remove_all_extents_t>::value
					>
			{
			};

#		else

			struct enable_optimization:
					kerbal::type_traits::bool_constant<
						std::is_trivially_copy_constructible<remove_all_extents_t>::value &&
						std::is_trivially_copy_assignable<remove_all_extents_t>::value &&
						std::is_trivially_destructible<remove_all_extents_t>::value
					>
			{
			};

#		endif

			this->__assign(new_size, val, enable_optimization());
		}

		template <typename Tp, size_t N>
		template <typename InputIterator>
		typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
		>::type
		static_vector<Tp, N>::assign(InputIterator first, InputIterator last)
		{
			iterator assign_it = this->begin();
			while (assign_it != this->end() && static_cast<bool>(first != last)) {
				*assign_it = *first;
				++assign_it;
				++first;
			}

			if (assign_it != this->end()) { // namely: first == last
				// X X X X O O O
				// T T
				this->erase(assign_it, this->end());
			} else {
				// X X X X O O O
				// T T T T T T T T T
				while (!this->full() && static_cast<bool>(first != last)) {
					this->push_back(*first);
					++first;
				}
			}
		}

#	if __cplusplus >= 201103L

		template <typename Tp, size_t N>
		void static_vector<Tp, N>::assign(std::initializer_list<value_type> src)
		{
			this->assign(src.begin(), src.end());
		}

#	endif

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR14
		typename static_vector<Tp, N>::iterator
		static_vector<Tp, N>::begin() KERBAL_NOEXCEPT
		{
			return iterator(this->storage + 0);
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR14
		typename static_vector<Tp, N>::iterator
		static_vector<Tp, N>::end() KERBAL_NOEXCEPT
		{
			return iterator(const_cast<storage_type*>(this->p_to_end));
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR14
		typename static_vector<Tp, N>::const_iterator
		static_vector<Tp, N>::begin() const KERBAL_NOEXCEPT
		{
			return this->cbegin();
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR14
		typename static_vector<Tp, N>::const_iterator
		static_vector<Tp, N>::end() const KERBAL_NOEXCEPT
		{
			return this->cend();
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR14
		typename static_vector<Tp, N>::const_iterator
		static_vector<Tp, N>::cbegin() const KERBAL_NOEXCEPT
		{
			return const_iterator(this->storage + 0);
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR14
		typename static_vector<Tp, N>::const_iterator
		static_vector<Tp, N>::cend() const KERBAL_NOEXCEPT
		{
			return const_iterator(p_to_end);
		}

		template <typename Tp, size_t N>
		typename static_vector<Tp, N>::reverse_iterator
		static_vector<Tp, N>::rbegin() KERBAL_NOEXCEPT
		{
			return reverse_iterator(this->begin() + this->size());
		}

		template <typename Tp, size_t N>
		typename static_vector<Tp, N>::reverse_iterator
		static_vector<Tp, N>::rend() KERBAL_NOEXCEPT
		{
			return reverse_iterator(this->begin());
		}

		template <typename Tp, size_t N>
		typename static_vector<Tp, N>::const_reverse_iterator
		static_vector<Tp, N>::rbegin() const KERBAL_NOEXCEPT
		{
			return this->crbegin();
		}
		template <typename Tp, size_t N>
		typename static_vector<Tp, N>::const_reverse_iterator
		static_vector<Tp, N>::rend() const KERBAL_NOEXCEPT
		{
			return this->crend();
		}

		template <typename Tp, size_t N>
		typename static_vector<Tp, N>::const_reverse_iterator
		static_vector<Tp, N>::crbegin() const KERBAL_NOEXCEPT
		{
			return const_reverse_iterator(this->end());
		}

		template <typename Tp, size_t N>
		typename static_vector<Tp, N>::const_reverse_iterator
		static_vector<Tp, N>::crend() const KERBAL_NOEXCEPT
		{
			return const_reverse_iterator(this->cbegin());
		}

		template <typename Tp, size_t N>
		typename static_vector<Tp, N>::size_type
		static_vector<Tp, N>::size() const KERBAL_NOEXCEPT
		{
			return (this->p_to_end - this->storage);
		}

		template <typename Tp, size_t N>
		bool static_vector<Tp, N>::empty() const KERBAL_NOEXCEPT
		{
			return this->size() == 0;
		}

		template <typename Tp, size_t N>
		bool static_vector<Tp, N>::full() const KERBAL_NOEXCEPT
		{
			return this->size() == N;
		}

		template <typename Tp, size_t N>
		typename static_vector<Tp, N>::reference
		static_vector<Tp, N>::operator[](size_type index) KERBAL_NOEXCEPT
		{
			return this->storage[index].raw_value();
		}

		template <typename Tp, size_t N>
		typename static_vector<Tp, N>::const_reference
		static_vector<Tp, N>::operator[](size_type index) const KERBAL_NOEXCEPT
		{
			return this->storage[index].raw_value();
		}

		template <typename Tp, size_t N>
		typename static_vector<Tp, N>::reference
		static_vector<Tp, N>::at(size_type index)
		{
			if (index >= size()) {
				kerbal::utility::throw_this_exception_helper<std::out_of_range>::throw_this_exception("range check fail in static_array");
			}
			return (*this)[index];
		}

		template <typename Tp, size_t N>
		typename static_vector<Tp, N>::const_reference
		static_vector<Tp, N>::at(size_type index) const
		{
			if (index >= size()) {
				kerbal::utility::throw_this_exception_helper<std::out_of_range>::throw_this_exception("range check fail in static_array");
			}
			return (*this)[index];
		}

		template <typename Tp, size_t N>
		typename static_vector<Tp, N>::reference
		static_vector<Tp, N>::front()
		{
			return *this->begin();
		}

		template <typename Tp, size_t N>
		typename static_vector<Tp, N>::const_reference
		static_vector<Tp, N>::front() const
		{
			return *this->cbegin();
		}

		template <typename Tp, size_t N>
		typename static_vector<Tp, N>::reference
		static_vector<Tp, N>::back()
		{
			return *this->rbegin();
		}

		template <typename Tp, size_t N>
		typename static_vector<Tp, N>::const_reference
		static_vector<Tp, N>::back() const
		{
			return *this->crbegin();
		}

		template <typename Tp, size_t N>
		typename static_vector<Tp, N>::equal_c_array_reference
		static_vector<Tp, N>::c_arr()
		{
			if (!full()) {
				kerbal::utility::throw_this_exception_helper<std::logic_error>::throw_this_exception("static vector is not full");
			}
			return reinterpret_cast<equal_c_array_reference>(this->storage);
		}

		template <typename Tp, size_t N>
		typename static_vector<Tp, N>::const_equal_c_array_reference
		static_vector<Tp, N>::const_c_arr() const
		{
			if (!full()) {
				kerbal::utility::throw_this_exception_helper<std::logic_error>::throw_this_exception("static vector is not full");
			}
			return reinterpret_cast<equal_c_array_reference>(this->storage);
		}

		template <typename Tp, size_t N>
		typename static_vector<Tp, N>::const_pointer
		static_vector<Tp, N>::data() const
		{
			return reinterpret_cast<const_pointer>(&(this->storage[0]));
		}

		template <typename Tp, size_t N>
		void static_vector<Tp, N>::push_back(const_reference src)
		{
			this->__construct_at(this->end(), src);
			++this->p_to_end;
		}

#	if __cplusplus >= 201103L
		template <typename Tp, size_t N>
		void static_vector<Tp, N>::push_back(rvalue_reference src)
		{
			this->emplace_back(std::move(src));
		}
#	endif

#	if __cplusplus >= 201103L

		template <typename Tp, size_t N>
		template <typename ... Args>
		typename static_vector<Tp, N>::reference
		static_vector<Tp, N>::emplace_back(Args&& ...args)
		{
			this->__construct_at(this->end(), std::forward<Args>(args)...);
			++this->p_to_end;
			return this->back();
		}

#	else

		template <typename Tp, size_t N>
		typename static_vector<Tp, N>::reference
		static_vector<Tp, N>::emplace_back()
		{
			this->__construct_at(this->end());
			++this->p_to_end;
			return this->back();
		}

		template <typename Tp, size_t N>
		template <typename Arg0>
		typename static_vector<Tp, N>::reference
		static_vector<Tp, N>::emplace_back(const Arg0 & arg0)
		{
			this->__construct_at(this->end(), arg0);
			++this->p_to_end;
			return this->back();
		}

		template <typename Tp, size_t N>
		template <typename Arg0, typename Arg1>
		typename static_vector<Tp, N>::reference
		static_vector<Tp, N>::emplace_back(const Arg0& arg0, const Arg1& arg1)
		{
			this->__construct_at(this->end(), arg0, arg1);
			++this->p_to_end;
			return this->back();
		}

		template <typename Tp, size_t N>
		template <typename Arg0, typename Arg1, typename Arg2>
		typename static_vector<Tp, N>::reference
		static_vector<Tp, N>::emplace_back(const Arg0& arg0, const Arg1& arg1, const Arg2& arg2)
		{
			this->__construct_at(this->end(), arg0, arg1, arg2);
			++this->p_to_end;
			return this->back();
		}

#	endif

		template <typename Tp, size_t N>
		void static_vector<Tp, N>::pop_back()
		{
			this->__destroy_at(this->nth(this->size() - 1));
			--this->p_to_end;
		}

		template <typename Tp, size_t N>
		void static_vector<Tp, N>::push_front(const_reference src)
		{
			this->insert(this->cbegin(), src);
		}

#	if __cplusplus >= 201103L

		template <typename Tp, size_t N>
		void static_vector<Tp, N>::push_front(rvalue_reference src)
		{
			this->emplace_front(src);
		}

		template <typename Tp, size_t N>
		template <typename ... Args>
		typename static_vector<Tp, N>::reference
		static_vector<Tp, N>::emplace_front(Args&& ...args)
		{
			return *this->emplace(this->cbegin(), std::forward<Args>(args)...);
		}

#	endif

		template <typename Tp, size_t N>
		void static_vector<Tp, N>::pop_front()
		{
			this->erase(this->cbegin());
		}

		template <typename Tp, size_t N>
		typename static_vector<Tp, N>::iterator
		static_vector<Tp, N>::insert(const_iterator pos, const_reference val)
		{
			iterator mutable_pos = this->nth(this->index_of(pos));
			if (pos == this->cend()) {
				// if *this is empty, the only valid iterator pos is equal to cend()!

				// A A A O O O
				//          ^
				this->push_back(val); // copy construct
			} else {
				// *this couldn't be empty otherwise the argument pos is invalid

				// A A A X Y Z O O O
				//          ^      $
				this->push_back(kerbal::compatibility::to_xvalue(this->back())); // move construct

				// after repeat the last element
				// A A A X Y Z Z O O
				//          ^
				kerbal::algorithm::move_backward(mutable_pos, this->end() - 2, this->end() - 1); // move assign
				// A A A X X Y Z O O
				//          ^
				*mutable_pos = val; // copy assign
			}
			return mutable_pos;
		}

#	if __cplusplus >= 201103L

		template <typename Tp, size_t N>
		typename static_vector<Tp, N>::iterator
		static_vector<Tp, N>::insert(const_iterator pos, rvalue_reference val)
		{
			return this->emplace(pos, std::move(val));
		}

		template <typename Tp, size_t N>
		template <typename ... Args>
		typename static_vector<Tp, N>::iterator
		static_vector<Tp, N>::emplace(const const_iterator pos, Args&& ...args)
		{
			iterator mutable_pos = this->nth(this->index_of(pos));
			if (pos == this->cend()) {
				// A A A O O O
				//          ^
				this->emplace_back(std::forward<Args>(args)...); // construct by args
			} else {
				this->push_back(std::move(this->back())); // move construct
				// A A A X Y Z Z O O
				//          ^
				kerbal::algorithm::move_backward(mutable_pos, this->end() - 2, this->end() - 1); // move assign
				// A A A X X Y Z O O
				//          ^
				*mutable_pos = value_type(std::forward<Args>(args)...); // move assign, construct by args
			}
			return mutable_pos;
		}

#	endif

		template <typename Tp, size_t N>
		typename static_vector<Tp, N>::iterator
		static_vector<Tp, N>::erase(const_iterator pos)
		{
			if (pos == this->cend()) {
				return this->nth(this->index_of(pos));
			}

			// pre-condition: pos != cend()
			iterator mutable_pos(this->nth(this->index_of(pos)));
			kerbal::algorithm::move(mutable_pos + 1, this->end(), mutable_pos);
			this->pop_back();
			return mutable_pos;
		}

		template <typename Tp, size_t N>
		typename static_vector<Tp, N>::iterator
		static_vector<Tp, N>::erase(const_iterator first, const_iterator last)
		{
			iterator mutable_first = this->nth(this->index_of(first));
			iterator mutable_last = this->nth(this->index_of(last));

			kerbal::algorithm::move(mutable_last, this->end(), mutable_first);

			iterator new_end = this->end() - (mutable_last - mutable_first);
			while (new_end != this->end()) {
				this->pop_back();
			}
			return mutable_first;
		}

		template <typename Tp, size_t N>
		void static_vector<Tp, N>::swap(static_vector & with)
		{
			if (this->size() > with.size()) {
				with.swap(*this);
			}

			static_vector & s_arr = *this;
			static_vector & l_arr = with;

			kerbal::algorithm::range_swap(s_arr.begin(), s_arr.end(), l_arr.begin());

			size_type s_len = s_arr.size();
			const iterator l_end = l_arr.end();

			for (iterator l_it = l_arr.nth(s_len); l_it != l_end; ++l_it) {
				s_arr.push_back(kerbal::compatibility::to_xvalue(*l_it));
			}

			l_arr.erase(l_arr.nth(s_len), l_end);
		}

		template <typename Tp, size_t N>
		void static_vector<Tp, N>::__clear(kerbal::type_traits::false_type)
		{
			while (!this->empty()) {
				this->pop_back();
			}
		}

		template <typename Tp, size_t N>
		void static_vector<Tp, N>::__clear(kerbal::type_traits::true_type) KERBAL_NOEXCEPT
		{
			this->p_to_end = this->storage + 0;
		}

		template <typename Tp, size_t N>
		void static_vector<Tp, N>::clear()
		{

#		if __cplusplus < 201103L

			struct enable_optimization:
					kerbal::type_traits::bool_constant<
						kerbal::type_traits::is_fundamental<remove_all_extents_t>::value ||
						kerbal::type_traits::is_pointer<remove_all_extents_t>::value
					>
			{
			};

#		else

			struct enable_optimization:
					kerbal::type_traits::bool_constant<
						std::is_trivially_destructible<remove_all_extents_t>::value
					>
			{
			};

#		endif

			this->__clear(enable_optimization());
		}

		template <typename Tp, size_t N>
		void static_vector<Tp, N>::fill()
		{
			while (!this->full()) {
				this->emplace_back();
			}
		}

		template <typename Tp, size_t N>
		void static_vector<Tp, N>::fill(const_reference val)
		{
			while (!this->full()) {
				this->push_back(val);
			}
		}

#	if __cplusplus < 201103L

		template <typename Tp, size_t N>
		void static_vector<Tp, N>::__construct_at(iterator itor)
		{
			(itor.current)->construct();
		}

		template <typename Tp, size_t N>
		template <typename T0>
		void static_vector<Tp, N>::__construct_at(iterator itor, const T0& v0)
		{
			(itor.current)->construct(v0);
		}

		template <typename Tp, size_t N>
		template <typename T0, typename T1>
		void static_vector<Tp, N>::__construct_at(iterator itor, const T0& v0, const T1& v1)
		{
			(itor.current)->construct(v0, v1);
		}

		template <typename Tp, size_t N>
		template <typename T0, typename T1, typename T2>
		void static_vector<Tp, N>::__construct_at(iterator itor, const T0& v0, const T1& v1, const T2& v2)
		{
			(itor.current)->construct(v0, v1, v2);
		}

		template <typename Tp, size_t N>
		template <typename T0, typename T1, typename T2, typename T3>
		void static_vector<Tp, N>::__construct_at(iterator itor, const T0& v0, const T1& v1, const T2& v2, const T3& v3)
		{
			(itor.current)->construct(v0, v1, v2, v3);
		}

		template <typename Tp, size_t N>
		template <typename T0, typename T1, typename T2, typename T3, typename T4>
		void static_vector<Tp, N>::__construct_at(iterator itor, const T0& v0, const T1& v1, const T2& v2, const T3& v3, const T4& v4)
		{
			(itor.current)->construct(v0, v1, v2, v3, v4);
		}

#	else

		template <typename Tp, size_t N>
		template <typename ... Args>
		void static_vector<Tp, N>::__construct_at(iterator itor, Args&& ...args)
		{
			(itor.current)->construct(std::forward<Args>(args)...);
		}

#	endif

		template <typename Tp, size_t N>
		void static_vector<Tp, N>::__destroy_at(iterator itor)
		{
			(itor.current)->destroy();
		}

	}
}

#endif /* KERBAL_DATA_STRUCT_STATIC_CONTAINER_BASE_STATIC_VECTOR_BASE_HPP_ */
