/**
 * @file       array_iterator.impl.hpp
 * @brief
 * @date       2019-10-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_IMPL_ARRAY_ITERATOR_IMPL_HPP_
#define KERBAL_CONTAINER_IMPL_ARRAY_ITERATOR_IMPL_HPP_


namespace kerbal
{

	namespace container
	{

		namespace detail
		{
			/*
			 * iterator_base
			 */

			template <typename DerivedIterator, typename Pointer>
			KERBAL_CONSTEXPR
			typename __arr_iterbase<DerivedIterator, Pointer>::iterator_base_t::reference
			__arr_iterbase<DerivedIterator, Pointer>::operator*() const KERBAL_NOEXCEPT
			{
				return *this->current;
			}

			template <typename DerivedIterator, typename Pointer>
			KERBAL_CONSTEXPR14
			DerivedIterator&
			__arr_iterbase<DerivedIterator, Pointer>::operator++() KERBAL_NOEXCEPT
			{
				++this->current;
				return static_cast<DerivedIterator&>(*this);
			}

			template <typename DerivedIterator, typename Pointer>
			KERBAL_CONSTEXPR14
			DerivedIterator&
			__arr_iterbase<DerivedIterator, Pointer>::operator--() KERBAL_NOEXCEPT
			{
				--this->current;
				return static_cast<DerivedIterator&>(*this);
			}

			template <typename DerivedIterator, typename Pointer>
			KERBAL_CONSTEXPR
			DerivedIterator
			__arr_iterbase<DerivedIterator, Pointer>::operator+
					(const typename __arr_iterbase::difference_type & delta) const KERBAL_NOEXCEPT
			{
				return DerivedIterator(this->current + delta);
			}

			template <typename DerivedIterator, typename Pointer>
			KERBAL_CONSTEXPR
			DerivedIterator
			__arr_iterbase<DerivedIterator, Pointer>::operator-
					(const typename __arr_iterbase::difference_type & delta) const KERBAL_NOEXCEPT
			{
				return DerivedIterator(this->current - delta);
			}

			template <typename DerivedIterator, typename Pointer>
			KERBAL_CONSTEXPR
			typename __arr_iterbase<DerivedIterator, Pointer>::difference_type
			__arr_iterbase<DerivedIterator, Pointer>::operator-(const DerivedIterator & with) const KERBAL_NOEXCEPT
			{
				return this->current - with.current;
			}

			template <typename DerivedIterator, typename Pointer>
			KERBAL_CONSTEXPR14
			DerivedIterator&
			__arr_iterbase<DerivedIterator, Pointer>::operator+=(const typename __arr_iterbase::difference_type & delta) KERBAL_NOEXCEPT
			{
				this->current += delta;
				return *this;
			}

			template <typename DerivedIterator, typename Pointer>
			KERBAL_CONSTEXPR14
			DerivedIterator&
			__arr_iterbase<DerivedIterator, Pointer>::operator-=(const typename __arr_iterbase::difference_type & delta) KERBAL_NOEXCEPT
			{
				this->current -= delta;
				return *this;
			}

		} //namespace detail

	} //namespace container

} //namespace kerbal


#endif /* KERBAL_CONTAINER_IMPL_ARRAY_ITERATOR_IMPL_HPP_ */
