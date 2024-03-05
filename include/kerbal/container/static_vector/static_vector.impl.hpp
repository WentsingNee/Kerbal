/**
 * @file       static_vector.impl.hpp
 * @brief
 * @date       2018-4-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_STATIC_VECTOR_STATIC_VECTOR_IMPL_HPP
#define KERBAL_CONTAINER_STATIC_VECTOR_STATIC_VECTOR_IMPL_HPP

#include <kerbal/algorithm/modifier/copy.hpp>
#include <kerbal/algorithm/modifier/copy_n.hpp>
#include <kerbal/algorithm/modifier/fill.hpp>
#include <kerbal/algorithm/modifier/move.hpp>
#include <kerbal/algorithm/modifier/move_backward.hpp>
#include <kerbal/algorithm/swap.hpp>
#include <kerbal/assign/generic_assign.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/config/exceptions.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/memory/raw_storage_uninitialized.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_trivially_copy_assignable.hpp>
#include <kerbal/type_traits/is_trivially_copy_constructible.hpp>
#include <kerbal/type_traits/is_trivially_destructible.hpp>
#include <kerbal/type_traits/tribool_constant.hpp>
#include <kerbal/utility/compressed_pair.hpp>
#include <kerbal/utility/in_place.hpp>
#include <kerbal/utility/throw_this_exception.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#if __cplusplus >= 201103L
#	include <kerbal/iterator/move_iterator.hpp>
#	include <kerbal/utility/forward.hpp>
#endif

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif

#include <cstddef>
#include <stdexcept>

#include <kerbal/container/static_vector/static_vector.decl.hpp>


namespace kerbal
{

	namespace container
	{

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR
		static_vector<Tp, N>::static_vector() KERBAL_NOEXCEPT :
				super()
		{
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR14
		static_vector<Tp, N>::static_vector(const static_vector & src) :
				super(static_cast<const super&>(src))
		{
		}

#	if __cplusplus >= 201103L

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR14
		static_vector<Tp, N>::static_vector(static_vector && src) :
				super(static_cast<super&&>(src))
		{
		}

#	endif

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR14
		static_vector<Tp, N>::static_vector(size_type n) :
				super(n)
		{
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR14
		static_vector<Tp, N>::static_vector(size_type n, const_reference val) :
				super(n, val)
		{
		}

		template <typename Tp, std::size_t N>
		template <typename InputIterator>
		KERBAL_CONSTEXPR14
		static_vector<Tp, N>::static_vector(InputIterator first, InputIterator last,
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
						, int
				>::type
		) :
				super(first, last)
		{
		}


#	if __cplusplus >= 201103L

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR14
		static_vector<Tp, N>::static_vector(std::initializer_list<value_type> ilist) :
				static_vector(ilist.begin(), ilist.end())
		{
		}

#	else

		template <typename Tp, std::size_t N>
		static_vector<Tp, N>::static_vector(const kerbal::assign::assign_list<void> & ilist) :
				super()
		{
		}

		template <typename Tp, std::size_t N>
		template <typename Up>
		static_vector<Tp, N>::static_vector(const kerbal::assign::assign_list<Up> & ilist) :
				super(ilist.cbegin(), ilist.cend())
		{
		}

#	endif

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR14
		static_vector<Tp, N>& static_vector<Tp, N>::operator=(const static_vector & src)
		{
			this->assign_unsafe(src.cbegin(), src.cend());
			return *this;
		}

#	if __cplusplus >= 201103L

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR14
		static_vector<Tp, N>& static_vector<Tp, N>::operator=(static_vector && src)
		{
			this->assign_unsafe(
					kerbal::iterator::make_move_iterator(src.begin()),
					kerbal::iterator::make_move_iterator(src.end())
			);
			return *this;
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR14
		static_vector<Tp, N>& static_vector<Tp, N>::operator=(std::initializer_list<value_type> ilist)
		{
			this->assign_unsafe(ilist.begin(), ilist.end());
			return *this;
		}

#	else

		template <typename Tp, std::size_t N>
		static_vector<Tp, N>& static_vector<Tp, N>::operator=(const kerbal::assign::assign_list<void> & ilist)
		{
			this->assign_unsafe(ilist);
			return *this;
		}

		template <typename Tp, std::size_t N>
		template <typename Up>
		static_vector<Tp, N>& static_vector<Tp, N>::operator=(const kerbal::assign::assign_list<Up> & ilist)
		{
			this->assign_unsafe(ilist);
			return *this;
		}

#	endif

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR14
		void static_vector<Tp, N>::k_assign_unsafe_n_val(size_type new_size, const_reference val, kerbal::type_traits::false_type)
		{
			size_type previous_size = this->size();

			if (previous_size <= new_size) {
				/*
				 * a a a x x x x x
				 * b b b b b b x x
				 */

				kerbal::algorithm::fill(this->begin(), this->end(), val);
				kerbal::memory::raw_storage_uninitialized_fill(this->storage + previous_size, this->storage + new_size, val);
				this->len = static_cast<size_compressed_type>(new_size);
			} else {
				/*
				 * a a a a a a x x
				 * b b b x x x x x
				 */
				this->shrink_back_to(this->nth(new_size));
				kerbal::algorithm::fill(this->begin(), this->end(), val);
			}
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR14
		void static_vector<Tp, N>::k_assign_unsafe_n_val(size_type new_size, const_reference val, kerbal::type_traits::true_type)
		{
			kerbal::algorithm::fill(this->begin(), this->nth(new_size), val);
			this->len = static_cast<size_compressed_type>(new_size);
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR14
		void static_vector<Tp, N>::assign_unsafe(size_type new_size, const_reference val)
		{
			struct enable_optimization:
					kerbal::type_traits::tribool_conjunction<
						kerbal::type_traits::try_test_is_trivially_copy_constructible<remove_all_extents_t>,
						kerbal::type_traits::try_test_is_trivially_copy_assignable<remove_all_extents_t>,
						kerbal::type_traits::try_test_is_trivially_destructible<remove_all_extents_t>
					>::result::IS_TRUE
			{
			};

			this->k_assign_unsafe_n_val(new_size, val, enable_optimization());
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR20
		void static_vector<Tp, N>::assign(size_type new_size, const_reference val)
		{
			if (new_size > N) {
				kerbal::utility::throw_this_exception_helper<std::logic_error>::throw_this_exception(
					(const char*)"New size is larger than static_vector's max size"
				);
			}
			this->assign_unsafe(new_size, val);
		}

		template <typename Tp, std::size_t N>
		template <typename InputIterator>
		KERBAL_CONSTEXPR14
		void static_vector<Tp, N>::k_assign_unsafe_range(InputIterator first, InputIterator last, std::input_iterator_tag)
		{
			iterator it(this->begin());
			iterator end(this->end());
			while (it != end) {
				if (first != last) {
					kerbal::assign::generic_assign(*it, *first); // *it = *first;
					++first;
					++it;
				} else {
					// X X X X O O O
					// T T
					this->shrink_back_to(it);
					return;
				}
			}

			// X X X X O O O
			// T T T T T T T T T
			while (first != last) {
				this->push_back_unsafe(*first);
				++first;
			}
		}

		template <typename Tp, std::size_t N>
		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void static_vector<Tp, N>::k_assign_unsafe_range(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
		{
			size_type ori_size = static_cast<size_type>(this->len);
			size_type new_size = static_cast<size_type>(kerbal::iterator::distance(first, last));

			if (new_size <= ori_size) { // also suitable for new_size == 0
				/*
				 * a a a a a a x x
				 * b b b x x x x x
				 */
				iterator new_end(kerbal::algorithm::copy(first, last, this->begin()));
				kerbal::memory::raw_storage_reverse_destroy(new_end.current, this->end().current);
				this->len = static_cast<size_compressed_type>(new_size);
			} else { // new_size > ori_size
				/*
				 * a a a x x x x x
				 * b b b b b b x x
				 */
				kerbal::utility::compressed_pair<ForwardIterator, iterator> copy_n_r(kerbal::algorithm::copy_n(first, ori_size, this->begin()));
				kerbal::memory::raw_storage_uninitialized_copy(copy_n_r.first(), last, copy_n_r.second().current);
				this->len = static_cast<size_compressed_type>(new_size);
			}
		}

		template <typename Tp, std::size_t N>
		template <typename InputIterator>
		KERBAL_CONSTEXPR14
		typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
		>::type
		static_vector<Tp, N>::assign_unsafe(InputIterator first, InputIterator last)
		{
			this->k_assign_unsafe_range(first, last, kerbal::iterator::iterator_category(first));
		}

		template <typename Tp, std::size_t N>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		void static_vector<Tp, N>::k_assign_range(InputIterator first, InputIterator last, std::input_iterator_tag)
		{
			iterator it(this->begin());
			iterator end(this->end());
			while (it != end) {
				if (first != last) {
					kerbal::assign::generic_assign(*it, *first); // *it = *first;
					++first;
					++it;
				} else {
					// X X X X O O O
					// T T
					this->shrink_back_to(it);
					return;
				}
			}

			// X X X X O O O
			// T T T T T T T T T

			while (first != last) {
				if (this->full()) {
					// this is full
					kerbal::utility::throw_this_exception_helper<std::logic_error>::throw_this_exception(
						(const char *)"Out of storage space"
					);
				}
				this->push_back_unsafe(*first);
				++first;
			}
		}

		template <typename Tp, std::size_t N>
		template <typename ForwardIterator>
		KERBAL_CONSTEXPR20
		void static_vector<Tp, N>::k_assign_range(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
		{
			size_type ori_size = static_cast<size_type>(this->len);
			size_type new_size = static_cast<size_type>(kerbal::iterator::distance(first, last));

			if (new_size > N) {
				kerbal::utility::throw_this_exception_helper<std::logic_error>::throw_this_exception(
					(const char *)"Out of storage space"
				);
			}

			if (new_size <= ori_size) { // also suitable for new_size == 0
				/*
				 * a a a a a a x x
				 * b b b x x x x x
				 */
				iterator new_end(kerbal::algorithm::copy(first, last, this->begin()));
				kerbal::memory::raw_storage_reverse_destroy(new_end.current, this->end().current);
				this->len = static_cast<size_compressed_type>(new_size);
			} else { // new_size > ori_size
				/*
				 * a a a x x x x x
				 * b b b b b b x x
				 */
				kerbal::utility::compressed_pair<ForwardIterator, iterator> copy_n_r(kerbal::algorithm::copy_n(first, ori_size, this->begin()));
				kerbal::memory::raw_storage_uninitialized_copy(copy_n_r.first(), last, copy_n_r.second().current);
				this->len = static_cast<size_compressed_type>(new_size);
			}
		}

		template <typename Tp, std::size_t N>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
		>::type
		static_vector<Tp, N>::assign(InputIterator first, InputIterator last)
		{
			this->k_assign_range(first, last, kerbal::iterator::iterator_category(first));
		}

#	if __cplusplus >= 201103L

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR14
		void static_vector<Tp, N>::assign_unsafe(std::initializer_list<value_type> ilist)
		{
			this->assign_unsafe(ilist.begin(), ilist.end());
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR20
		void static_vector<Tp, N>::assign(std::initializer_list<value_type> ilist)
		{
			this->assign(ilist.begin(), ilist.end());
		}

#	else

		template <typename Tp, std::size_t N>
		void static_vector<Tp, N>::assign_unsafe(const kerbal::assign::assign_list<void> & ilist)
		{
			this->clear();
		}

		template <typename Tp, std::size_t N>
		template <typename Up>
		void static_vector<Tp, N>::assign_unsafe(const kerbal::assign::assign_list<Up> & ilist)
		{
			this->assign_unsafe(ilist.cbegin(), ilist.cend());
		}

		template <typename Tp, std::size_t N>
		void static_vector<Tp, N>::assign(const kerbal::assign::assign_list<void> & ilist)
		{
			this->clear();
		}

		template <typename Tp, std::size_t N>
		template <typename Up>
		void static_vector<Tp, N>::assign(const kerbal::assign::assign_list<Up> & ilist)
		{
			this->assign(ilist.cbegin(), ilist.cend());
		}

#	endif

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR14
		typename static_vector<Tp, N>::iterator
		static_vector<Tp, N>::begin() KERBAL_NOEXCEPT
		{
			return super::begin();
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR14
		typename static_vector<Tp, N>::iterator
		static_vector<Tp, N>::end() KERBAL_NOEXCEPT
		{
			return super::end();
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR
		typename static_vector<Tp, N>::const_iterator
		static_vector<Tp, N>::begin() const KERBAL_NOEXCEPT
		{
			return super::begin();
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR
		typename static_vector<Tp, N>::const_iterator
		static_vector<Tp, N>::end() const KERBAL_NOEXCEPT
		{
			return super::end();
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR
		typename static_vector<Tp, N>::const_iterator
		static_vector<Tp, N>::cbegin() const KERBAL_NOEXCEPT
		{
			return super::cbegin();
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR
		typename static_vector<Tp, N>::const_iterator
		static_vector<Tp, N>::cend() const KERBAL_NOEXCEPT
		{
			return super::cend();
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR14
		typename static_vector<Tp, N>::reverse_iterator
		static_vector<Tp, N>::rbegin() KERBAL_NOEXCEPT
		{
			return reverse_iterator(this->end());
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR14
		typename static_vector<Tp, N>::reverse_iterator
		static_vector<Tp, N>::rend() KERBAL_NOEXCEPT
		{
			return reverse_iterator(this->begin());
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR
		typename static_vector<Tp, N>::const_reverse_iterator
		static_vector<Tp, N>::rbegin() const KERBAL_NOEXCEPT
		{
			return this->crbegin();
		}
		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR
		typename static_vector<Tp, N>::const_reverse_iterator
		static_vector<Tp, N>::rend() const KERBAL_NOEXCEPT
		{
			return this->crend();
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR
		typename static_vector<Tp, N>::const_reverse_iterator
		static_vector<Tp, N>::crbegin() const KERBAL_NOEXCEPT
		{
			return const_reverse_iterator(this->end());
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR
		typename static_vector<Tp, N>::const_reverse_iterator
		static_vector<Tp, N>::crend() const KERBAL_NOEXCEPT
		{
			return const_reverse_iterator(this->cbegin());
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR
		typename static_vector<Tp, N>::size_type
		static_vector<Tp, N>::size() const KERBAL_NOEXCEPT
		{
			return static_cast<size_type>(this->len);
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR
		bool static_vector<Tp, N>::empty() const KERBAL_NOEXCEPT
		{
			return this->size() == 0;
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR
		bool static_vector<Tp, N>::full() const KERBAL_NOEXCEPT
		{
			return this->size() == N;
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR14
		typename static_vector<Tp, N>::reference
		static_vector<Tp, N>::operator[](size_type index) KERBAL_NOEXCEPT
		{
			return this->storage[index].raw_value();
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR14
		typename static_vector<Tp, N>::const_reference
		static_vector<Tp, N>::operator[](size_type index) const KERBAL_NOEXCEPT
		{
			return this->storage[index].raw_value();
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR20
		typename static_vector<Tp, N>::reference
		static_vector<Tp, N>::at(size_type index)
		{
			if (index >= size()) {
				kerbal::utility::throw_this_exception_helper<std::out_of_range>::throw_this_exception(
					(const char*)"Index out of bound"
				);
			}
			return (*this)[index];
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR20
		typename static_vector<Tp, N>::const_reference
		static_vector<Tp, N>::at(size_type index) const
		{
			if (index >= size()) {
				kerbal::utility::throw_this_exception_helper<std::out_of_range>::throw_this_exception(
					(const char*)"Index out of bound"
				);
			}
			return (*this)[index];
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR14
		typename static_vector<Tp, N>::reference
		static_vector<Tp, N>::front()
		{
			return *this->begin();
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR14
		typename static_vector<Tp, N>::const_reference
		static_vector<Tp, N>::front() const
		{
			return *this->cbegin();
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR14
		typename static_vector<Tp, N>::reference
		static_vector<Tp, N>::back()
		{
			return *this->rbegin();
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR14
		typename static_vector<Tp, N>::const_reference
		static_vector<Tp, N>::back() const
		{
			return *this->crbegin();
		}

		template <typename Tp, std::size_t N>
		typename static_vector<Tp, N>::equal_c_array_reference
		static_vector<Tp, N>::c_arr()
		{
			if (!full()) {
				kerbal::utility::throw_this_exception_helper<std::logic_error>::throw_this_exception(
					(const char*)"Static vector is not full"
				);
			}
			return reinterpret_cast<equal_c_array_reference>(this->storage);
		}

		template <typename Tp, std::size_t N>
		typename static_vector<Tp, N>::const_equal_c_array_reference
		static_vector<Tp, N>::c_arr() const
		{
			if (!full()) {
				kerbal::utility::throw_this_exception_helper<std::logic_error>::throw_this_exception(
					(const char*)"Static vector is not full"
				);
			}
			return reinterpret_cast<const_equal_c_array_reference>(this->storage);
		}

		template <typename Tp, std::size_t N>
		typename static_vector<Tp, N>::const_equal_c_array_reference
		static_vector<Tp, N>::const_c_arr() const
		{
			if (!full()) {
				kerbal::utility::throw_this_exception_helper<std::logic_error>::throw_this_exception(
					(const char*)"Static vector is not full"
				);
			}
			return reinterpret_cast<equal_const_c_array_reference>(this->storage);
		}

		template <typename Tp, std::size_t N>
		typename static_vector<Tp, N>::const_pointer
		static_vector<Tp, N>::data() const KERBAL_NOEXCEPT
		{
			return reinterpret_cast<const_pointer>(&(this->storage[0]));
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR14
		void static_vector<Tp, N>::push_back_unsafe(const_reference src)
		{
			this->emplace_back_unsafe(src);
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR20
		void static_vector<Tp, N>::push_back(const_reference src)
		{
			this->emplace_back(src);
		}

#	if __cplusplus >= 201103L

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR14
		void static_vector<Tp, N>::push_back_unsafe(rvalue_reference src)
		{
			this->emplace_back_unsafe(kerbal::compatibility::move(src));
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR20
		void static_vector<Tp, N>::push_back(rvalue_reference src)
		{
			this->emplace_back(kerbal::compatibility::move(src));
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename Tp, std::size_t N>
		template <typename ... Args>
		KERBAL_CONSTEXPR14
		typename static_vector<Tp, N>::reference
		static_vector<Tp, N>::emplace_back_unsafe(Args&& ... args)
		{
			this->storage[this->len].construct(kerbal::utility::forward<Args>(args)...);
			++this->len;
			return this->back();
		}

		template <typename Tp, std::size_t N>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename static_vector<Tp, N>::reference
		static_vector<Tp, N>::emplace_back(Args&& ... args)
		{
			if (static_cast<size_type>(this->len) + 1u > N) {
				kerbal::utility::throw_this_exception_helper<std::logic_error>::throw_this_exception(
					(const char*)"Out of storage space"
				);
			}
			return this->emplace_back_unsafe(kerbal::utility::forward<Args>(args)...);
		}

#	else

#	define EMPTY
#	define REMAINF(exp) exp
#	define THEAD_NOT_EMPTY(exp) template <exp>
#	define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#	define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#	define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#	define FBODY(i) \
		template <typename Tp, std::size_t N> \
		KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
		typename static_vector<Tp, N>::reference \
		static_vector<Tp, N>::emplace_back_unsafe(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)) \
		{ \
			this->storage[this->len].construct(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_USE, i)); \
			++this->len; \
			return this->back(); \
		} \
 \
		template <typename Tp, std::size_t N> \
		KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
		typename static_vector<Tp, N>::reference \
		static_vector<Tp, N>::emplace_back(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)) \
		{ \
			if (static_cast<size_type>(this->len) + 1u > N) { \
				kerbal::utility::throw_this_exception_helper<std::logic_error>::throw_this_exception( \
					(const char*)"Out of storage space" \
				); \
			} \
			return this->emplace_back_unsafe(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_USE, i)); \
		}

		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#	undef EMPTY
#	undef REMAINF
#	undef THEAD_NOT_EMPTY
#	undef TARGS_DECL
#	undef ARGS_DECL
#	undef ARGS_USE
#	undef FBODY

#	endif

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR14
		void static_vector<Tp, N>::pop_back_unsafe()
		{
			this->storage[this->len - 1].destroy();
			--this->len;
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR20
		void static_vector<Tp, N>::pop_back()
		{
			if (this->len == 0) {
				kerbal::utility::throw_this_exception_helper<std::logic_error>::throw_this_exception(
					(const char*)"Static vector is empty"
				);
			}
			this->pop_back_unsafe();
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR14
		void static_vector<Tp, N>::shrink_back_to(const_iterator to)
		{
			size_type new_size = this->index_of(to);
			kerbal::memory::raw_storage_reverse_destroy(this->storage + new_size, this->storage + static_cast<size_type>(this->len));
			this->len = static_cast<size_compressed_type>(new_size);
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR14
		typename static_vector<Tp, N>::iterator
		static_vector<Tp, N>::insert_unsafe(const_iterator pos, const_reference val)
		{
			return this->emplace_unsafe(pos, val);
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR20
		typename static_vector<Tp, N>::iterator
		static_vector<Tp, N>::insert(const_iterator pos, const_reference val)
		{
			return this->emplace(pos, val);
		}

#	if __cplusplus >= 201103L

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR14
		typename static_vector<Tp, N>::iterator
		static_vector<Tp, N>::insert_unsafe(const_iterator pos, rvalue_reference val)
		{
			return this->emplace_unsafe(pos, kerbal::compatibility::move(val));
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR20
		typename static_vector<Tp, N>::iterator
		static_vector<Tp, N>::insert(const_iterator pos, rvalue_reference val)
		{
			return this->emplace(pos, kerbal::compatibility::move(val));
		}

#	endif

		template <typename Tp, std::size_t N>
		template <typename ForwardIterator>
		KERBAL_CONSTEXPR20
		typename static_vector<Tp, N>::iterator
		static_vector<Tp, N>::k_range_insert(const_iterator pos, ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
		{
			size_type insert_pos_index = this->index_of(pos);
			size_type n = static_cast<size_type>(kerbal::iterator::distance(first, last));
			size_type ori_size = static_cast<size_type>(this->len);

			if (n > N - ori_size) {
				kerbal::utility::throw_this_exception_helper<std::logic_error>::throw_this_exception(
					(const char *) "Out of storage space"
				);
			}

			size_type new_size = ori_size + n;

			iterator pos_mut = pos.cast_to_mutable();
			if (n == 0) {
				// pass
			} else if (pos == this->cend()) {
				// A A A O O O
				//       ^
				// construct at the end
				kerbal::memory::raw_storage_uninitialized_copy(first, last, this->end().current);
				this->len = static_cast<size_compressed_type>(new_size);
			} else if (insert_pos_index + n <= ori_size) {
				// A A A 1 2 3 4 5 6
				// A A A X X 1 2 3 4 5 6

				// construct at the end
				// A A A 1 2 3 4 5 6
				// A A A 1 2 3 4 5 6 5 6
				kerbal::memory::raw_storage_uninitialized_copy(this->cend() - n, this->cend(), this->end().current);
				this->len = static_cast<size_compressed_type>(new_size);

				// A A A 1 2 3 4 5 6
				// A A A 1 2 1 2 3 4 5 6
				kerbal::algorithm::move_backward(pos_mut, this->end() - n, this->end());

				// A A A 1 2 3 4 5 6
				// A A A X X 1 2 3 4 5 6
				kerbal::algorithm::copy(first, last, pos_mut);
			} else {
				// A A A 1 2 3
				// A A A X X X X X 1 2 3

				kerbal::memory::raw_storage_uninitialized_copy(pos, this->cend(), pos_mut.current + n);

#		if KERBAL_HAS_EXCEPTIONS_SUPPORT
				try {
#		endif
					kerbal::utility::compressed_pair<ForwardIterator, iterator> copy_n_r(kerbal::algorithm::copy_n(first, ori_size - insert_pos_index, pos_mut));
					kerbal::memory::raw_storage_uninitialized_copy(copy_n_r.first(), last, copy_n_r.second().current);
#		if KERBAL_HAS_EXCEPTIONS_SUPPORT
				} catch (...) {
					kerbal::memory::raw_storage_reverse_destroy(pos_mut.current + n, this->nth(new_size).current);
					throw;
				}
#		endif
				this->len = static_cast<size_compressed_type>(new_size);
			}

			return this->nth(insert_pos_index);
		}

		template <typename Tp, std::size_t N>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
				typename static_vector<Tp, N>::iterator
		>::type
		static_vector<Tp, N>::insert(const_iterator pos, InputIterator first, InputIterator last)
		{
			return this->k_range_insert(pos, first, last, kerbal::iterator::iterator_category(first));
		}

#	if __cplusplus >= 201103L

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR20
		typename static_vector<Tp, N>::iterator
		static_vector<Tp, N>::insert(const_iterator pos, std::initializer_list<Tp> ilist)
		{
			return this->insert(pos, ilist.begin(), ilist.end());
		}

#	else

		template <typename Tp, std::size_t N>
		typename static_vector<Tp, N>::iterator
		static_vector<Tp, N>::insert(const_iterator pos, const kerbal::assign::assign_list<void> & ilist)
		{
			return pos.cast_to_mutable();
		}

		template <typename Tp, std::size_t N>
		template <typename Up>
		typename static_vector<Tp, N>::iterator
		static_vector<Tp, N>::insert(const_iterator pos, const kerbal::assign::assign_list<Up> & ilist)
		{
			return this->insert(pos, ilist.cbegin(), ilist.cend());
		}

#	endif


		template <typename Tp, bool =
			kerbal::type_traits::try_test_is_trivially_destructible<Tp>::IS_TRUE::value
		>
		struct static_vector_emplace_helper;

		template <typename Tp>
		struct static_vector_emplace_helper<Tp, false>
		{
				typedef Tp value_type;
				typedef Tp* pointer;

				kerbal::memory::raw_storage<value_type> storage;

#	if __cplusplus >= 201103L

				template <typename ... Args>
				KERBAL_CONSTEXPR20
				static_vector_emplace_helper(kerbal::utility::in_place_t in_place, Args&& ... args) :
						storage(in_place, kerbal::utility::forward<Args>(args)...)
				{
				}

#	else

#		define EMPTY
#		define THEAD_NOT_EMPTY(exp) template <exp>
#		define LEFT_JOIN_COMMA(exp) , exp
#		define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#		define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#		define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#		define FBODY(i) \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				static_vector_emplace_helper(kerbal::utility::in_place_t in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) : \
						storage(in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)) \
				{ \
				}

				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#		undef EMPTY
#		undef THEAD_NOT_EMPTY
#		undef LEFT_JOIN_COMMA
#		undef TARGS_DECL
#		undef ARGS_DECL
#		undef ARGS_USE
#		undef FBODY

#	endif

				KERBAL_CONSTEXPR20
				~static_vector_emplace_helper()
				{
					this->storage.destroy();
				}

		};

		template <typename Tp>
		struct static_vector_emplace_helper<Tp, true>
		{
				typedef Tp value_type;
				typedef Tp* pointer;

				kerbal::memory::raw_storage<value_type> storage;

#	if __cplusplus >= 201103L

				template <typename ... Args>
				KERBAL_CONSTEXPR
				static_vector_emplace_helper(kerbal::utility::in_place_t in_place, Args&& ... args) :
						storage(in_place, kerbal::utility::forward<Args>(args)...)
				{
				}

#	else

#		define EMPTY
#		define THEAD_NOT_EMPTY(exp) template <exp>
#		define LEFT_JOIN_COMMA(exp) , exp
#		define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#		define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#		define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#		define FBODY(i) \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				static_vector_emplace_helper(kerbal::utility::in_place_t in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) : \
						storage(in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)) \
				{ \
				}

				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#		undef EMPTY
#		undef THEAD_NOT_EMPTY
#		undef LEFT_JOIN_COMMA
#		undef TARGS_DECL
#		undef ARGS_DECL
#		undef ARGS_USE
#		undef FBODY

#	endif

		};

#	if __cplusplus >= 201103L

		template <typename Tp, std::size_t N>
		template <typename ... Args>
		KERBAL_CONSTEXPR14
		typename static_vector<Tp, N>::iterator
		static_vector<Tp, N>::emplace_unsafe(const_iterator pos, Args&& ... args)
		{
			iterator pos_mut(pos.cast_to_mutable());
			if (pos == this->cend()) {
				// if *this is empty, the only valid iterator pos is equal to cend()!

				// A A A O O O
				//          ^
				this->emplace_back_unsafe(kerbal::utility::forward<Args>(args)...); // construct by args
			} else {

				static_vector_emplace_helper<Tp> helper((kerbal::utility::in_place_t()), kerbal::utility::forward<Args>(args)...);

				// *this couldn't be empty otherwise the argument pos is invalid

				// A A A X Y Z O O O
				//          ^      $
				this->emplace_back_unsafe(kerbal::compatibility::move(this->back())); // move construct

				// after repeat the last element
				// A A A X Y Z Z O O
				//          ^
				kerbal::algorithm::move_backward(pos_mut, this->end() - 2, this->end() - 1); // move assign

				// A A A X X Y Z O O
				//          ^
				kerbal::assign::generic_assign(*pos_mut, kerbal::compatibility::move(helper.storage.raw_value()));
				// *pos_mut = kerbal::compatibility::move(helper.storage.raw_value());
			}
			return pos_mut;
		}

		template <typename Tp, std::size_t N>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename static_vector<Tp, N>::iterator
		static_vector<Tp, N>::emplace(const_iterator pos, Args&& ... args)
		{
			if (static_cast<size_type>(this->len) + 1u > N) {
				kerbal::utility::throw_this_exception_helper<std::logic_error>::throw_this_exception(
					(const char *)"Out of storage space"
				);
			}
			return this->emplace_unsafe(pos, kerbal::utility::forward<Args>(args)...);
		}

#	else

#	define EMPTY
#	define THEAD_NOT_EMPTY(exp) template <exp>
#	define LEFT_JOIN_COMMA(exp) , exp
#	define REMAINF(exp) exp
#	define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#	define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#	define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#	define FBODY(i) \
		template <typename Tp, std::size_t N> \
		KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
		typename static_vector<Tp, N>::iterator \
		static_vector<Tp, N>::emplace_unsafe(const_iterator pos KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
		{ \
			iterator mutable_pos(pos.cast_to_mutable()); \
			if (pos == this->cend()) { \
				this->emplace_back_unsafe(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_USE, i)); \
			} else { \
				static_vector_emplace_helper<Tp> helper((kerbal::utility::in_place_t()) KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
				this->push_back_unsafe(kerbal::compatibility::to_xvalue(this->back())); \
				kerbal::algorithm::move_backward(mutable_pos, this->end() - 2, this->end() - 1); \
				kerbal::assign::generic_assign(*mutable_pos, kerbal::compatibility::to_xvalue(helper.storage.raw_value())); \
			} \
			return mutable_pos; \
		} \
 \
		template <typename Tp, std::size_t N> \
		KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
		typename static_vector<Tp, N>::iterator \
		static_vector<Tp, N>::emplace(const_iterator pos KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
		{ \
			if (static_cast<size_type>(this->len) + 1u > N) { \
				kerbal::utility::throw_this_exception_helper<std::logic_error>::throw_this_exception( \
					(const char *)"Out of storage space" \
				); \
			} \
			return this->emplace_unsafe(pos KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
		}

		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#	undef EMPTY
#	undef THEAD_NOT_EMPTY
#	undef LEFT_JOIN_COMMA
#	undef REMAINF
#	undef TARGS_DECL
#	undef ARGS_DECL
#	undef ARGS_USE
#	undef FBODY

#	endif

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR14
		typename static_vector<Tp, N>::iterator
		static_vector<Tp, N>::erase(const_iterator pos)
		{
			iterator pos_mut(pos.cast_to_mutable());

			if (pos == this->cend()) {
				return pos_mut;
			}

			// pre-condition: pos != cend()
			kerbal::algorithm::move(pos_mut + 1, this->end(), pos_mut);
			this->pop_back_unsafe();
			return pos_mut;
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR14
		typename static_vector<Tp, N>::iterator
		static_vector<Tp, N>::erase(const_iterator first, const_iterator last)
		{
			iterator first_mut(first.cast_to_mutable());
			if (first == last) {
				return first_mut;
			}
			iterator last_mut(last.cast_to_mutable());

			iterator new_end(kerbal::algorithm::move(last_mut, this->end(), first_mut));
			this->shrink_back_to(new_end);
			return first_mut;
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR14
		void static_vector<Tp, N>::k_swap_helper(static_vector & with)
		{
			static_vector & s_arr = *this;
			static_vector & l_arr = with;

			size_type s_len = s_arr.size();
			size_type l_len = l_arr.size();

			/*
			 * a a a a
			 * b b b b c c c c
			 */

			kerbal::memory::raw_storage_uninitialized_move(l_arr.nth(s_len), l_arr.nth(l_len), s_arr.storage + s_len);
			s_arr.len = static_cast<size_compressed_type>(l_len);

			kerbal::memory::raw_storage_reverse_destroy(l_arr.storage + s_len, l_arr.storage + l_len);
			l_arr.len = static_cast<size_compressed_type>(s_len);

			kerbal::algorithm::range_swap(s_arr.begin(), s_arr.nth(s_len), l_arr.begin());
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR14
		void static_vector<Tp, N>::swap(static_vector & with)
		{
			if (this->size() > with.size()) {
				with.k_swap_helper(*this);
			} else {
				this->k_swap_helper(with);
			}
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR14
		void static_vector<Tp, N>::clear()
		{
			this->shrink_back_to(this->cbegin());
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR14
		void static_vector<Tp, N>::fill()
		{
			kerbal::memory::raw_storage_uninitialized_value_construct(this->storage + this->len, this->storage + N);
			this->len = static_cast<size_compressed_type>(N);
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR14
		void static_vector<Tp, N>::fill(const_reference val)
		{
			kerbal::memory::raw_storage_uninitialized_fill(this->storage + this->len, this->storage + N, val);
			this->len = static_cast<size_compressed_type>(N);
		}

		template <typename Tp, std::size_t N1, std::size_t N2>
		KERBAL_CONSTEXPR14
		static_vector<Tp, N1 + N2>
		operator+(const static_vector<Tp, N1> & lhs, const static_vector<Tp, N2> & rhs)
		{
			static_vector<Tp, N1 + N2> r(lhs.cbegin(), lhs.cend());
			kerbal::memory::raw_storage_uninitialized_copy(rhs.cbegin(), rhs.cend(), r.storage + r.len);
			r.len += rhs.size();
			return r;
		}

#	if __cplusplus >= 201103L

		template <typename Tp, std::size_t N1, std::size_t N2>
		KERBAL_CONSTEXPR14
		static_vector<Tp, N1 + N2>
		operator+(const static_vector<Tp, N1> & lhs, const static_vector<Tp, N2> && rhs)
		{
			static_vector<Tp, N1 + N2> r(lhs.cbegin(), lhs.cend());
			kerbal::memory::raw_storage_uninitialized_move(rhs.cbegin(), rhs.cend(), r.storage + r.len);
			r.len += rhs.size();
			return r;
		}

		template <typename Tp, std::size_t N1, std::size_t N2>
		KERBAL_CONSTEXPR14
		static_vector<Tp, N1 + N2>
		operator+(const static_vector<Tp, N1> && lhs, const static_vector<Tp, N2> & rhs)
		{
			static_vector<Tp, N1 + N2> r(
				kerbal::iterator::make_move_iterator(lhs.cbegin()),
				kerbal::iterator::make_move_iterator(lhs.cend())
			);
			kerbal::memory::raw_storage_uninitialized_copy(rhs.cbegin(), rhs.cend(), r.storage + r.len);
			r.len += rhs.size();
			return r;
		}

		template <typename Tp, std::size_t N1, std::size_t N2>
		KERBAL_CONSTEXPR14
		static_vector<Tp, N1 + N2>
		operator+(const static_vector<Tp, N1> && lhs, const static_vector<Tp, N2> && rhs)
		{
			static_vector<Tp, N1 + N2> r(
				kerbal::iterator::make_move_iterator(lhs.cbegin()),
				kerbal::iterator::make_move_iterator(lhs.cend())
			);
			kerbal::memory::raw_storage_uninitialized_move(rhs.cbegin(), rhs.cend(), r.storage + r.len);
			r.len += rhs.size();
			return r;
		}

#	endif

		template <typename Tp, std::size_t N>
		template <std::size_t M>
		KERBAL_CONSTEXPR14
		static_vector<Tp, N>
		static_vector<Tp, N>::operator*(const static_vector<Tp, M> & rhs) const
		{
			static_vector<Tp, N> r(*this);
			typename static_vector<Tp, M>::const_iterator it(rhs.cbegin());
			typename static_vector<Tp, M>::const_iterator end(rhs.cend());
			while (!r.full() && it != end) {
				r.push_back_unsafe(*it);
				++it;
			}
			return r;
		}

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_STATIC_VECTOR_STATIC_VECTOR_IMPL_HPP
