/**
 * @file       static_vector_iterator.impl.hpp
 * @brief
 * @date       2018-5-16
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_IMPL_STATIC_VECTOR_ITERATOR_IMPL_HPP_
#define KERBAL_CONTAINER_IMPL_STATIC_VECTOR_ITERATOR_IMPL_HPP_


namespace kerbal
{
	namespace container
	{
		/*
		 * iterator_base
		 */

		template <typename DerivedIterator, typename Pointer, typename StorageType>
		typename __stavec_iterbase<DerivedIterator, Pointer, StorageType>::iterator_base_t::reference
		__stavec_iterbase<DerivedIterator, Pointer, StorageType>::operator*() const KERBAL_NOEXCEPT
		{
			return current->raw_value();
		}

		template <typename DerivedIterator, typename Pointer, typename StorageType>
		DerivedIterator&
		__stavec_iterbase<DerivedIterator, Pointer, StorageType>::operator++() KERBAL_NOEXCEPT
		{
			++this->current;
			return static_cast<DerivedIterator&>(*this);
		}

		template <typename DerivedIterator, typename Pointer, typename StorageType>
		DerivedIterator&
		__stavec_iterbase<DerivedIterator, Pointer, StorageType>::operator--() KERBAL_NOEXCEPT
		{
			--this->current;
			return static_cast<DerivedIterator&>(*this);
		}

		template <typename DerivedIterator, typename Pointer, typename StorageType>
		DerivedIterator
		__stavec_iterbase<DerivedIterator, Pointer, StorageType>::operator+
				(const typename __stavec_iterbase::difference_type & delta) const KERBAL_NOEXCEPT
		{
			return DerivedIterator(this->current + delta);
		}

		template <typename DerivedIterator, typename Pointer, typename StorageType>
		DerivedIterator
		__stavec_iterbase<DerivedIterator, Pointer, StorageType>::operator-
				(const typename __stavec_iterbase::difference_type & delta) const KERBAL_NOEXCEPT
		{
			return DerivedIterator(this->current - delta);
		}

		template <typename DerivedIterator, typename Pointer, typename StorageType>
		KERBAL_CONSTEXPR
		typename __stavec_iterbase<DerivedIterator, Pointer, StorageType>::difference_type
		__stavec_iterbase<DerivedIterator, Pointer, StorageType>::operator-(const DerivedIterator & with) const KERBAL_NOEXCEPT
		{
			return this->current - with.current;
		}

		template <typename DerivedIterator, typename Pointer, typename StorageType>
		DerivedIterator&
		__stavec_iterbase<DerivedIterator, Pointer, StorageType>::operator+=(const typename __stavec_iterbase::difference_type & delta) KERBAL_NOEXCEPT
		{
			this->current += delta;
			return static_cast<DerivedIterator&>(*this);
		}

		template <typename DerivedIterator, typename Pointer, typename StorageType>
		DerivedIterator&
		__stavec_iterbase<DerivedIterator, Pointer, StorageType>::operator-=(const typename __stavec_iterbase::difference_type & delta) KERBAL_NOEXCEPT
		{
			this->current -= delta;
			return static_cast<DerivedIterator&>(*this);
		}

	}
}


#endif /* KERBAL_CONTAINER_IMPL_STATIC_VECTOR_ITERATOR_IMPL_HPP_ */
