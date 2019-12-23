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

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/operators/addable.hpp>
#include <kerbal/operators/dereferenceable.hpp>
#include <kerbal/operators/equality_comparable.hpp>
#include <kerbal/operators/incr_decr.hpp>
#include <kerbal/operators/less_than_comparable.hpp>
#include <kerbal/operators/subtractable.hpp>

namespace kerbal
{
	namespace container
	{

		template <typename DerivedIterator, typename Pointer, typename StorageType>
		class __stavec_iterbase:
				public std::iterator<
						std::random_access_iterator_tag,
						typename kerbal::iterator::iterator_traits<Pointer>::value_type,
						typename kerbal::iterator::iterator_traits<Pointer>::difference_type,
						typename kerbal::iterator::iterator_traits<Pointer>::pointer,
						typename kerbal::iterator::iterator_traits<Pointer>::reference
				>,
				public kerbal::operators::addable<DerivedIterator, typename kerbal::iterator::iterator_traits<Pointer>::difference_type>,
				public kerbal::operators::addable_left<DerivedIterator, typename kerbal::iterator::iterator_traits<Pointer>::difference_type>,
				public kerbal::operators::dereferenceable<DerivedIterator, Pointer>,
				public kerbal::operators::equality_comparable<DerivedIterator>,
				public kerbal::operators::less_than_comparable<DerivedIterator>,
				public kerbal::operators::incrementable<DerivedIterator>,
				public kerbal::operators::decrementable<DerivedIterator>,
				public kerbal::operators::subtractable<DerivedIterator, typename kerbal::iterator::iterator_traits<Pointer>::difference_type>
		{
			protected:
				typedef StorageType storage_type_for_iterator;

				storage_type_for_iterator* current;

			public:
				explicit KERBAL_CONSTEXPR __stavec_iterbase(storage_type_for_iterator* current) KERBAL_NOEXCEPT :
						current(current)
				{
				}

				typename __stavec_iterbase::reference operator*() const KERBAL_NOEXCEPT
				{
					return current->raw_value();
				}

				friend KERBAL_CONSTEXPR
				typename __stavec_iterbase::difference_type
				operator-(const DerivedIterator & lhs, const DerivedIterator & rhs) KERBAL_NOEXCEPT
				{
					return lhs.current - rhs.current;
				}

				DerivedIterator& operator++() KERBAL_NOEXCEPT
				{
					++this->current;
					return static_cast<DerivedIterator&>(*this);
				}

				DerivedIterator& operator--() KERBAL_NOEXCEPT
				{
					--this->current;
					return static_cast<DerivedIterator&>(*this);
				}

				DerivedIterator& operator+=(const typename __stavec_iterbase::difference_type & delta) KERBAL_NOEXCEPT
				{
					this->current += delta;
					return static_cast<DerivedIterator&>(*this);
				}

				DerivedIterator& operator-=(const typename __stavec_iterbase::difference_type & delta) KERBAL_NOEXCEPT
				{
					this->current -= delta;
					return static_cast<DerivedIterator&>(*this);
				}

				friend KERBAL_CONSTEXPR bool operator<(const DerivedIterator & lhs, const DerivedIterator & rhs) KERBAL_NOEXCEPT
				{
					return lhs.current < rhs.current;
				}

				friend KERBAL_CONSTEXPR bool operator==(const DerivedIterator & lhs, const DerivedIterator & rhs) KERBAL_NOEXCEPT
				{
					return lhs.current == rhs.current;
				}
		};

		template <typename ValueType>
		class __stavec_kiter;

		// Iterator to static_vector.
		template <typename ValueType>
		class __stavec_iter: public __stavec_iterbase<
												__stavec_iter<ValueType>,
												ValueType*,
												kerbal::data_struct::raw_storage<ValueType>
										>
		{
			private:
				template <typename Tp, size_t N>
				friend class static_vector;

				friend class __stavec_kiter<ValueType>;

				typedef kerbal::data_struct::raw_storage<ValueType> storage_type;
				typedef __stavec_iterbase<__stavec_iter<ValueType>, ValueType*, storage_type> super;

			public:
				explicit KERBAL_CONSTEXPR __stavec_iter(storage_type* current) KERBAL_NOEXCEPT :
						super(current)
				{
				}
		};

		// Constant iterator to static_vector.
		template <typename ValueType>
		class __stavec_kiter: public __stavec_iterbase<
												__stavec_kiter<ValueType>,
												const ValueType*,
												const kerbal::data_struct::raw_storage<ValueType>
										>
		{
			private:
				template <typename Tp, size_t N>
				friend class static_vector;

				typedef const kerbal::data_struct::raw_storage<ValueType> storage_type;
				typedef __stavec_iterbase<__stavec_kiter<ValueType>, const ValueType*, storage_type> super;
				typedef __stavec_iter<ValueType> iterator;

			public:
				explicit KERBAL_CONSTEXPR __stavec_kiter(const storage_type* current) KERBAL_NOEXCEPT :
						super(current)
				{
				}

				KERBAL_CONSTEXPR __stavec_kiter(const iterator & current) KERBAL_NOEXCEPT :
						super(current.current)
				{
				}
		};

	}
}


#endif /* KERBAL_CONTAINER_IMPL_STATIC_VECTOR_ITERATOR_IMPL_HPP_ */
