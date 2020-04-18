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

#ifndef KERBAL_CONTAINER_IMPL_ARRAY_IMPL_HPP_
#define KERBAL_CONTAINER_IMPL_ARRAY_IMPL_HPP_


#include <kerbal/algorithm/modifier.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/utility/throw_this_exception.hpp>

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif

#include <kerbal/container/array.hpp>

namespace kerbal
{

	namespace container
	{

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR array<Tp, N>::array()
#	if __cplusplus >= 201103L
					: storage{}
#	endif
		{
		}

#	if __cplusplus >= 201103L

#	else
		template <typename Tp, size_t N>
		array<Tp, N>::array(const array & src)
		{
			kerbal::algorithm::copy(src.storage, src.storage + N, this->storage);
		}

#	endif


#	if __cplusplus >= 201103L

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR14 array<Tp, N>::array(std::initializer_list<value_type> src) :
				array(src.begin(), src.end())
		{
		}

#	endif


		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR14 array<Tp, N>::array(size_type n, const_reference val)
#	if __cplusplus >= 201103L
					: storage{}
#	endif
		{
			this->assign(n, val);
		}


		template <typename Tp, size_t N>
		template <typename InputIterator>
		KERBAL_CONSTEXPR14
		array<Tp, N>::array(InputIterator first, InputIterator last,
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
						, int
				>::type
		)
#	if __cplusplus >= 201103L
					: storage{}
#	endif
		{
			this->assign(first, last);
		}

#	if __cplusplus >= 201103L

#	else

		template <typename Tp, size_t N>
		array<Tp, N>& array<Tp, N>::operator=(const array & src)
		{
			this->assign(src.cbegin(), src.cend());
			return *this;
		}

#	endif


#	if __cplusplus >= 201103L

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR14
		array<Tp, N>& array<Tp, N>::operator=(std::initializer_list<value_type> src)
		{
			this->assign(src.begin(), src.end());
			return *this;
		}

#	endif


		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR14
		void array<Tp, N>::assign(size_type new_size, const_reference val)
		{
			if (new_size > N) {
				new_size = N;
			}

			kerbal::algorithm::fill(this->begin(), this->nth(new_size), val);
		}

		template <typename Tp, size_t N>
		template <typename InputIterator>
		KERBAL_CONSTEXPR14
		typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
		>::type
		array<Tp, N>::assign(InputIterator first, InputIterator last)
		{
			iterator assign_it = this->begin();
			while (assign_it != this->end() && static_cast<bool>(first != last)) {
				*assign_it = *first;
				++assign_it;
				++first;
			}
		}

#	if __cplusplus >= 201103L

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR14
		void array<Tp, N>::assign(std::initializer_list<value_type> src)
		{
			this->assign(src.begin(), src.end());
		}

#	endif

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR14
		typename array<Tp, N>::iterator
		array<Tp, N>::begin() KERBAL_NOEXCEPT
		{
			return iterator(this->storage + 0);
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR14
		typename array<Tp, N>::iterator
		array<Tp, N>::end() KERBAL_NOEXCEPT
		{
			return iterator(this->storage + N);
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR14
		typename array<Tp, N>::const_iterator
		array<Tp, N>::begin() const KERBAL_NOEXCEPT
		{
			return this->cbegin();
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR14
		typename array<Tp, N>::const_iterator
		array<Tp, N>::end() const KERBAL_NOEXCEPT
		{
			return this->cend();
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR
		typename array<Tp, N>::const_iterator
		array<Tp, N>::cbegin() const KERBAL_NOEXCEPT
		{
			return const_iterator(this->storage + 0);
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR
		typename array<Tp, N>::const_iterator
		array<Tp, N>::cend() const KERBAL_NOEXCEPT
		{
			return const_iterator(this->storage + N);
		}

		template <typename Tp, size_t N>
		typename array<Tp, N>::reverse_iterator
		array<Tp, N>::rbegin() KERBAL_NOEXCEPT
		{
			return reverse_iterator(this->begin() + this->size());
		}

		template <typename Tp, size_t N>
		typename array<Tp, N>::reverse_iterator
		array<Tp, N>::rend() KERBAL_NOEXCEPT
		{
			return reverse_iterator(this->begin());
		}

		template <typename Tp, size_t N>
		typename array<Tp, N>::const_reverse_iterator
		array<Tp, N>::rbegin() const KERBAL_NOEXCEPT
		{
			return this->crbegin();
		}
		template <typename Tp, size_t N>
		typename array<Tp, N>::const_reverse_iterator
		array<Tp, N>::rend() const KERBAL_NOEXCEPT
		{
			return this->crend();
		}

		template <typename Tp, size_t N>
		typename array<Tp, N>::const_reverse_iterator
		array<Tp, N>::crbegin() const KERBAL_NOEXCEPT
		{
			return const_reverse_iterator(this->end());
		}

		template <typename Tp, size_t N>
		typename array<Tp, N>::const_reverse_iterator
		array<Tp, N>::crend() const KERBAL_NOEXCEPT
		{
			return const_reverse_iterator(this->cbegin());
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR14
		typename array<Tp, N>::iterator
		array<Tp, N>::nth(size_type index) KERBAL_NOEXCEPT
		{
			return this->begin() + index;
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR14
		typename array<Tp, N>::const_iterator
		array<Tp, N>::nth(size_type index) const KERBAL_NOEXCEPT
		{
			return this->cbegin() + index;
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR14
		typename array<Tp, N>::size_type
		array<Tp, N>::index_of(iterator it) KERBAL_NOEXCEPT
		{
			return it - this->begin();
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR
		typename array<Tp, N>::size_type
		array<Tp, N>::index_of(const_iterator it) const KERBAL_NOEXCEPT
		{
			return it - this->cbegin();
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR
		typename array<Tp, N>::size_type
		array<Tp, N>::size() const KERBAL_NOEXCEPT
		{
			return N;
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR bool array<Tp, N>::empty() const KERBAL_NOEXCEPT
		{
			return this->size() == 0;
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR14
		typename array<Tp, N>::reference
		array<Tp, N>::operator[](size_type index) KERBAL_NOEXCEPT
		{
			return this->storage[index];
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR14
		typename array<Tp, N>::const_reference
		array<Tp, N>::operator[](size_type index) const KERBAL_NOEXCEPT
		{
			return this->storage[index];
		}

		template <typename Tp, size_t N>
		typename array<Tp, N>::reference
		array<Tp, N>::at(size_type index)
		{
			if (index >= this->size()) {
				kerbal::utility::throw_this_exception_helper<std::out_of_range>::throw_this_exception("range check fail in static_array");
			}
			return (*this)[index];
		}

		template <typename Tp, size_t N>
		typename array<Tp, N>::const_reference
		array<Tp, N>::at(size_type index) const
		{
			if (index >= this->size()) {
				kerbal::utility::throw_this_exception_helper<std::out_of_range>::throw_this_exception("range check fail in static_array");
			}
			return (*this)[index];
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR14
		typename array<Tp, N>::reference
		array<Tp, N>::front()
		{
			return *this->begin();
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR14
		typename array<Tp, N>::const_reference
		array<Tp, N>::front() const
		{
			return *this->cbegin();
		}

		template <typename Tp, size_t N>
		typename array<Tp, N>::reference
		array<Tp, N>::back()
		{
			return *this->rbegin();
		}

		template <typename Tp, size_t N>
		typename array<Tp, N>::const_reference
		array<Tp, N>::back() const
		{
			return *this->crbegin();
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR14
		typename array<Tp, N>::equal_c_array_reference
		array<Tp, N>::c_arr()
		{
			return this->storage;
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR14
		typename array<Tp, N>::const_equal_c_array_reference
		array<Tp, N>::c_arr() const
		{
			return this->storage;
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR
		typename array<Tp, N>::const_equal_c_array_reference
		array<Tp, N>::const_c_arr() const
		{
			return this->storage;
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR
		typename array<Tp, N>::const_pointer
		array<Tp, N>::data() const
		{
			return this->storage + 0;
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR14
		void array<Tp, N>::swap(array & with)
		{
			kerbal::algorithm::swap(this->storage, with.storage);
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR14
		void array<Tp, N>::fill(const_reference val)
		{
			kerbal::algorithm::fill(this->begin(), this->end(), val);
		}

	} // namespace container

} //namespace kerbal

#endif /* KERBAL_CONTAINER_IMPL_ARRAY_IMPL_HPP_ */
