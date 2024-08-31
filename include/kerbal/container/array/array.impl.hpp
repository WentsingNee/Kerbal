/**
 * @file       array.impl.hpp
 * @brief
 * @date       2019-10-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_ARRAY_ARRAY_IMPL_HPP
#define KERBAL_CONTAINER_ARRAY_ARRAY_IMPL_HPP

#include <kerbal/algorithm/modifier/fill.hpp>
#include <kerbal/algorithm/swap.hpp>
#include <kerbal/assign/generic_assign.hpp>
#include <kerbal/assign/ilist.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/utility/throw_this_exception.hpp>

#include <cstddef>

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif

#include <kerbal/container/array/array.decl.hpp>


namespace kerbal
{

	namespace container
	{

#	if __cplusplus < 201103L

		template <typename T, std::size_t N>
		array<T, N>::array()
		{
		}

		template <typename T, std::size_t N>
		array<T, N>::array(const kerbal::assign::assign_list<void> & ilist)
		{
		}

		template <typename T, std::size_t N>
		template <typename U>
		array<T, N>::array(const kerbal::assign::assign_list<U> & ilist)
		{
			this->assign(ilist.cbegin(), ilist.cend());
		}

		template <typename T, std::size_t N>
		array<T, N> &
		array<T, N>::operator=(const kerbal::assign::assign_list<void> & ilist)
		{
			this->assign(ilist);
			return *this;
		}

		template <typename T, std::size_t N>
		template <typename U>
		array<T, N> &
		array<T, N>::operator=(const kerbal::assign::assign_list<U> & ilist)
		{
			this->assign(ilist);
			return *this;
		}

#	endif


		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR14
		void array<T, N>::assign(size_type new_size, const_reference val)
		{
			if (new_size > N) {
				new_size = N;
			}

			kerbal::algorithm::fill(this->begin(), this->nth(new_size), val);
		}

		template <typename T, std::size_t N>
		template <typename InputIterator>
		KERBAL_CONSTEXPR14
		typename kerbal::type_traits::enable_if<
			kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
		>::type
		array<T, N>::assign(InputIterator first, InputIterator last)
		{
			iterator assign_it = this->begin();
			while (assign_it != this->end() && static_cast<bool>(first != last)) {
				kerbal::assign::generic_assign(*assign_it, *first); // *assign_it = *first;
				++assign_it;
				++first;
			}
		}

#	if __cplusplus >= 201103L

		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR14
		void array<T, N>::assign(std::initializer_list<value_type> ilist)
		{
			this->assign(ilist.begin(), ilist.end());
		}

#	else

		template <typename T, std::size_t N>
		void array<T, N>::assign(const kerbal::assign::assign_list<void> & ilist)
		{
		}

		template <typename T, std::size_t N>
		template <typename U>
		void array<T, N>::assign(const kerbal::assign::assign_list<U> & ilist)
		{
			this->assign(ilist.begin(), ilist.end());
		}

#	endif

		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR14
		typename
		array<T, N>::iterator
		array<T, N>::begin() KERBAL_NOEXCEPT
		{
			return iterator(this->k_data + 0);
		}

		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR14
		typename
		array<T, N>::const_iterator
		array<T, N>::begin() const KERBAL_NOEXCEPT
		{
			return const_iterator(this->k_data + 0);
		}

		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR
		typename
		array<T, N>::const_iterator
		array<T, N>::cbegin() const KERBAL_NOEXCEPT
		{
			return this->begin();
		}

		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR14
		typename
		array<T, N>::iterator
		array<T, N>::end() KERBAL_NOEXCEPT
		{
			return iterator(this->k_data + N);
		}

		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR14
		typename
		array<T, N>::const_iterator
		array<T, N>::end() const KERBAL_NOEXCEPT
		{
			return const_iterator(this->k_data + N);
		}

		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR
		typename
		array<T, N>::const_iterator
		array<T, N>::cend() const KERBAL_NOEXCEPT
		{
			return this->end();
		}

		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR14
		typename
		array<T, N>::reverse_iterator
		array<T, N>::rbegin() KERBAL_NOEXCEPT
		{
			return reverse_iterator(this->end());
		}

		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR14
		typename
		array<T, N>::const_reverse_iterator
		array<T, N>::rbegin() const KERBAL_NOEXCEPT
		{
			return const_reverse_iterator(this->end());
		}

		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR
		typename
		array<T, N>::const_reverse_iterator
		array<T, N>::crbegin() const KERBAL_NOEXCEPT
		{
			return this->rbegin();
		}

		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR14
		typename
		array<T, N>::reverse_iterator
		array<T, N>::rend() KERBAL_NOEXCEPT
		{
			return reverse_iterator(this->begin());
		}

		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR14
		typename
		array<T, N>::const_reverse_iterator
		array<T, N>::rend() const KERBAL_NOEXCEPT
		{
			return const_reverse_iterator(this->begin());
		}

		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR
		typename
		array<T, N>::const_reverse_iterator
		array<T, N>::crend() const KERBAL_NOEXCEPT
		{
			return this->rend();
		}

		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR14
		typename
		array<T, N>::iterator
		array<T, N>::nth(size_type index) KERBAL_NOEXCEPT
		{
			return this->begin() + index;
		}

		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR14
		typename
		array<T, N>::const_iterator
		array<T, N>::nth(size_type index) const KERBAL_NOEXCEPT
		{
			return this->cbegin() + index;
		}

		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR14
		typename
		array<T, N>::size_type
		array<T, N>::index_of(iterator it) KERBAL_NOEXCEPT
		{
			return it - this->begin();
		}

		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR
		typename
		array<T, N>::size_type
		array<T, N>::index_of(const_iterator it) const KERBAL_NOEXCEPT
		{
			return it - this->cbegin();
		}

		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR
		typename
		array<T, N>::size_type
		array<T, N>::size() const KERBAL_NOEXCEPT
		{
			return N;
		}

		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR
		bool array<T, N>::empty() const KERBAL_NOEXCEPT
		{
			return this->size() == 0;
		}

		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR14
		typename
		array<T, N>::reference
		array<T, N>::operator[](size_type index) KERBAL_NOEXCEPT
		{
			return this->k_data[index];
		}

		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR14
		typename
		array<T, N>::const_reference
		array<T, N>::operator[](size_type index) const KERBAL_NOEXCEPT
		{
			return this->k_data[index];
		}

		template <typename T, std::size_t N>
		typename
		array<T, N>::reference
		array<T, N>::at(size_type index)
		{
			if (index >= this->size()) {
				kerbal::utility::throw_this_exception_helper<std::out_of_range>::throw_this_exception(
					+"range check fail in static_array"
				);
			}
			return (*this)[index];
		}

		template <typename T, std::size_t N>
		typename
		array<T, N>::const_reference
		array<T, N>::at(size_type index) const
		{
			if (index >= this->size()) {
				kerbal::utility::throw_this_exception_helper<std::out_of_range>::throw_this_exception(
					+"range check fail in static_array"
				);
			}
			return (*this)[index];
		}

		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR14
		typename
		array<T, N>::reference
		array<T, N>::front()
		{
			return this->k_data[0];
		}

		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR14
		typename
		array<T, N>::const_reference
		array<T, N>::front() const
		{
			return this->k_data[0];
		}

		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR14
		typename
		array<T, N>::reference
		array<T, N>::back()
		{
			return this->k_data[N - 1];
		}

		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR14
		typename
		array<T, N>::const_reference
		array<T, N>::back() const
		{
			return this->k_data[N - 1];
		}

		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR14
		typename
		array<T, N>::equal_c_array_reference
		array<T, N>::c_arr() KERBAL_NOEXCEPT
		{
			return this->k_data;
		}

		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR14
		typename
		array<T, N>::const_equal_c_array_reference
		array<T, N>::c_arr() const KERBAL_NOEXCEPT
		{
			return this->k_data;
		}

		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR
		typename
		array<T, N>::const_equal_c_array_reference
		array<T, N>::const_c_arr() const KERBAL_NOEXCEPT
		{
			return this->k_data;
		}

		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR
		typename
		array<T, N>::const_pointer
		array<T, N>::data() const KERBAL_NOEXCEPT
		{
			return this->k_data + 0;
		}

		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR14
		void array<T, N>::swap(array & with)
		{
			kerbal::algorithm::swap(this->k_data, with.k_data);
		}

		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR14
		void array<T, N>::fill(const_reference val)
		{
			kerbal::algorithm::fill(this->begin(), this->end(), val);
		}

	} // namespace container

} //namespace kerbal

#endif // KERBAL_CONTAINER_ARRAY_ARRAY_IMPL_HPP
