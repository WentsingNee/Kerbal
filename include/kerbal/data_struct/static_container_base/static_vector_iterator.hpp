/**
 * @file		static_vector_iterator.hpp
 * @brief
 * @date		2018年5月16日
 * @author		Peter
 * @copyright	Peter
 * @copyright
 <a href="http://thinkspirit.org/">ThinkSpirit Laboratory</a>
 of
 <a href="http://www.nuist.edu.cn/">Nanjing University of Information Science & Technology</a>
 */

#ifndef KERBAL_DATA_STRUCT_STATIC_CONTAINER_BASE_STATIC_VECTOR_ITERATOR_HPP_
#define KERBAL_DATA_STRUCT_STATIC_CONTAINER_BASE_STATIC_VECTOR_ITERATOR_HPP_


namespace kerbal
{
	namespace data_struct
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
			return *this;
		}

		template <typename DerivedIterator, typename Pointer, typename StorageType>
		DerivedIterator&
		__stavec_iterbase<DerivedIterator, Pointer, StorageType>::operator-=(const typename __stavec_iterbase::difference_type & delta) KERBAL_NOEXCEPT
		{
			this->current -= delta;
			return *this;
		}

	}
}


#endif /* KERBAL_DATA_STRUCT_STATIC_CONTAINER_BASE_STATIC_VECTOR_ITERATOR_HPP_ */
