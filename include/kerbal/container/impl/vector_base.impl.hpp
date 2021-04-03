/**
 * @file       vector_base.impl.hpp
 * @brief
 * @date       2020-08-19
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_IMPL_VECTOR_BASE_IMPL_HPP
#define KERBAL_CONTAINER_IMPL_VECTOR_BASE_IMPL_HPP

#include <kerbal/container/detail/vector_base.hpp>
#include <kerbal/utility/throw_this_exception.hpp>

#include <stdexcept>

namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename Tp>
			KERBAL_CONSTEXPR20
			vector_allocator_unrelated<Tp>::vector_allocator_unrelated() KERBAL_NOEXCEPT :
				_K_p(NULL), _K_size(0), _K_capacity(0)
			{
			}

#		if __cplusplus >= 201103L

			template <typename Tp>
			KERBAL_CONSTEXPR20
			vector_allocator_unrelated<Tp>::vector_allocator_unrelated(vector_allocator_unrelated && src) KERBAL_NOEXCEPT :
				_K_p(src._K_p), _K_size(src._K_size), _K_capacity(src._K_capacity)
			{
				src._K_p = NULL;
				src._K_size = 0;
				src._K_capacity = 0;
			}

#		endif

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_allocator_unrelated<Tp>::iterator
			vector_allocator_unrelated<Tp>::begin() KERBAL_NOEXCEPT
			{
				return iterator(this->_K_p + 0);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_allocator_unrelated<Tp>::iterator
			vector_allocator_unrelated<Tp>::end() KERBAL_NOEXCEPT
			{
				return iterator(this->_K_p + this->_K_size);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_allocator_unrelated<Tp>::const_iterator
			vector_allocator_unrelated<Tp>::begin() const KERBAL_NOEXCEPT
			{
				return this->cbegin();
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_allocator_unrelated<Tp>::const_iterator
			vector_allocator_unrelated<Tp>::end() const KERBAL_NOEXCEPT
			{
				return this->cend();
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_allocator_unrelated<Tp>::const_iterator
			vector_allocator_unrelated<Tp>::cbegin() const KERBAL_NOEXCEPT
			{
				return const_iterator(this->_K_p + 0);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_allocator_unrelated<Tp>::const_iterator
			vector_allocator_unrelated<Tp>::cend() const KERBAL_NOEXCEPT
			{
				return const_iterator(this->_K_p + this->_K_size);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_allocator_unrelated<Tp>::reverse_iterator
			vector_allocator_unrelated<Tp>::rbegin() KERBAL_NOEXCEPT
			{
				return reverse_iterator(this->end());
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_allocator_unrelated<Tp>::reverse_iterator
			vector_allocator_unrelated<Tp>::rend() KERBAL_NOEXCEPT
			{
				return reverse_iterator(this->begin());
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_allocator_unrelated<Tp>::const_reverse_iterator
			vector_allocator_unrelated<Tp>::rbegin() const KERBAL_NOEXCEPT
			{
				return this->crbegin();
			}
			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_allocator_unrelated<Tp>::const_reverse_iterator
			vector_allocator_unrelated<Tp>::rend() const KERBAL_NOEXCEPT
			{
				return this->crend();
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_allocator_unrelated<Tp>::const_reverse_iterator
			vector_allocator_unrelated<Tp>::crbegin() const KERBAL_NOEXCEPT
			{
				return const_reverse_iterator(this->end());
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_allocator_unrelated<Tp>::const_reverse_iterator
			vector_allocator_unrelated<Tp>::crend() const KERBAL_NOEXCEPT
			{
				return const_reverse_iterator(this->cbegin());
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_allocator_unrelated<Tp>::iterator
			vector_allocator_unrelated<Tp>::nth(size_type index)
			{
				return this->begin() + index;
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_allocator_unrelated<Tp>::const_iterator
			vector_allocator_unrelated<Tp>::nth(size_type index) const
			{
				return this->cbegin() + index;
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_allocator_unrelated<Tp>::size_type
			vector_allocator_unrelated<Tp>::index_of(iterator it)
			{
				return it - this->begin();
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_allocator_unrelated<Tp>::size_type
			vector_allocator_unrelated<Tp>::index_of(const_iterator it) const
			{
				return it - this->cbegin();
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_allocator_unrelated<Tp>::size_type
			vector_allocator_unrelated<Tp>::size() const KERBAL_NOEXCEPT
			{
				return this->_K_size;
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_allocator_unrelated<Tp>::size_type
			vector_allocator_unrelated<Tp>::capacity() const KERBAL_NOEXCEPT
			{
				return this->_K_capacity;
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			bool vector_allocator_unrelated<Tp>::empty() const KERBAL_NOEXCEPT
			{
				return this->size() == 0;
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_allocator_unrelated<Tp>::reference
			vector_allocator_unrelated<Tp>::operator[](size_type index) KERBAL_NOEXCEPT
			{
				return this->_K_p[index];
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_allocator_unrelated<Tp>::const_reference
			vector_allocator_unrelated<Tp>::operator[](size_type index) const KERBAL_NOEXCEPT
			{
				return this->_K_p[index];
			}

			template <typename Tp>
			typename vector_allocator_unrelated<Tp>::reference
			vector_allocator_unrelated<Tp>::at(size_type index)
			{
				if (index >= size()) {
					kerbal::utility::throw_this_exception_helper<std::out_of_range>::throw_this_exception((const char*)"range check fail in static_array");
				}
				return (*this)[index];
			}

			template <typename Tp>
			typename vector_allocator_unrelated<Tp>::const_reference
			vector_allocator_unrelated<Tp>::at(size_type index) const
			{
				if (index >= size()) {
					kerbal::utility::throw_this_exception_helper<std::out_of_range>::throw_this_exception((const char*)"range check fail in static_array");
				}
				return (*this)[index];
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_allocator_unrelated<Tp>::reference
			vector_allocator_unrelated<Tp>::front()
			{
				return *this->begin();
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_allocator_unrelated<Tp>::const_reference
			vector_allocator_unrelated<Tp>::front() const
			{
				return *this->cbegin();
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_allocator_unrelated<Tp>::reference
			vector_allocator_unrelated<Tp>::back()
			{
				return *this->rbegin();
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_allocator_unrelated<Tp>::const_reference
			vector_allocator_unrelated<Tp>::back() const
			{
				return *this->crbegin();
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_allocator_unrelated<Tp>::const_pointer
			vector_allocator_unrelated<Tp>::data() const KERBAL_NOEXCEPT
			{
				return this->_K_p;
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			void vector_allocator_unrelated<Tp>::_K_swap(vector_allocator_unrelated & lhs, vector_allocator_unrelated & rhs) KERBAL_NOEXCEPT
			{
				kerbal::algorithm::swap(lhs._K_p, rhs._K_p);
				kerbal::algorithm::swap(lhs.len, rhs.len);
				kerbal::algorithm::swap(lhs._K_capacity, rhs._K_capacity);
			}

		} // namespace detail

	} // namespace container

} // namespace kerbal


#endif // KERBAL_CONTAINER_IMPL_VECTOR_BASE_IMPL_HPP
