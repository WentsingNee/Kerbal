/**
 * @file       static_vector_iterator.hpp
 * @brief
 * @date       2018-5-16
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_STATIC_VECTOR_ITERATOR_HPP
#define KERBAL_CONTAINER_DETAIL_STATIC_VECTOR_ITERATOR_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/memory/raw_storage.hpp>
#include <kerbal/operators/addable.hpp>
#include <kerbal/operators/dereferenceable.hpp>
#include <kerbal/operators/equality_comparable.hpp>
#include <kerbal/operators/incr_decr.hpp>
#include <kerbal/operators/less_than_comparable.hpp>
#include <kerbal/operators/subtractable.hpp>

#include <cstddef>


namespace kerbal
{

	namespace container
	{

		template <typename Tp, std::size_t N>
		class static_vector;

		namespace detail
		{

			template <typename DerivedIterator, typename Pointer, typename StorageType>
			class __stavec_iterbase:
					//forward iterator interface
					public kerbal::operators::dereferenceable<DerivedIterator, Pointer>, // it->
					public kerbal::operators::equality_comparable<DerivedIterator>, // it != jt
					public kerbal::operators::incrementable<DerivedIterator>, // it++
					//bidirectional iterator interface
					public kerbal::operators::decrementable<DerivedIterator>, // it--
					//random access iterator interface
					public kerbal::operators::addable<DerivedIterator, typename kerbal::iterator::iterator_traits<Pointer>::difference_type>, // it + N
					public kerbal::operators::addable_left<DerivedIterator, typename kerbal::iterator::iterator_traits<Pointer>::difference_type>,// N + it
					public kerbal::operators::less_than_comparable<DerivedIterator>, // it > jt, it <= jt, it >= jt
					public kerbal::operators::subtractable<DerivedIterator, typename kerbal::iterator::iterator_traits<Pointer>::difference_type> // it - N
			{
				protected:
					typedef StorageType storage_type_for_iterator;

					storage_type_for_iterator* current;

				private:
					typedef kerbal::iterator::iterator_traits<Pointer>		iterator_traits;

				public:
					typedef std::random_access_iterator_tag					iterator_category;
					typedef typename iterator_traits::value_type			value_type;
					typedef typename iterator_traits::difference_type		difference_type;
					typedef typename iterator_traits::pointer				pointer;
					typedef typename iterator_traits::reference				reference;

				public:
					KERBAL_CONSTEXPR
					explicit __stavec_iterbase(storage_type_for_iterator* current) KERBAL_NOEXCEPT :
							current(current)
					{
					}

					//===================
					//forward iterator interface

					KERBAL_CONSTEXPR14
					reference operator*() const KERBAL_NOEXCEPT
					{
						return current->raw_value();
					}

					KERBAL_CONSTEXPR14
					DerivedIterator& operator++() KERBAL_NOEXCEPT
					{
						++this->current;
						return static_cast<DerivedIterator&>(*this);
					}

					friend KERBAL_CONSTEXPR
					bool operator==(const DerivedIterator & lhs, const DerivedIterator & rhs) KERBAL_NOEXCEPT
					{
						return lhs.current == rhs.current;
					}

					//===================
					//bidirectional iterator interface

					KERBAL_CONSTEXPR14
					DerivedIterator& operator--() KERBAL_NOEXCEPT
					{
						--this->current;
						return static_cast<DerivedIterator&>(*this);
					}

					//===================
					//random access iterator interface

					friend KERBAL_CONSTEXPR
					difference_type
					operator-(const DerivedIterator & lhs, const DerivedIterator & rhs) KERBAL_NOEXCEPT
					{
						return lhs.current - rhs.current;
					}

					KERBAL_CONSTEXPR14
					DerivedIterator& operator+=(const difference_type & delta) KERBAL_NOEXCEPT
					{
						this->current += delta;
						return static_cast<DerivedIterator&>(*this);
					}

					KERBAL_CONSTEXPR14
					DerivedIterator& operator-=(const difference_type & delta) KERBAL_NOEXCEPT
					{
						this->current -= delta;
						return static_cast<DerivedIterator&>(*this);
					}

					KERBAL_CONSTEXPR14
					reference operator[](const difference_type & dist) const KERBAL_NOEXCEPT
					{
						return *(static_cast<const DerivedIterator&>(*this) + dist);
					}

					friend KERBAL_CONSTEXPR
					bool operator<(const DerivedIterator & lhs, const DerivedIterator & rhs) KERBAL_NOEXCEPT
					{
						return lhs.current < rhs.current;
					}
			};

			template <typename ValueType>
			class __stavec_kiter;

			// Iterator to static_vector.
			template <typename ValueType>
			class __stavec_iter: public __stavec_iterbase<
													__stavec_iter<ValueType>,
													ValueType*,
													kerbal::memory::raw_storage<ValueType>
											>
			{
				private:
					template <typename Tp, std::size_t N>
					friend class kerbal::container::static_vector;

					friend class __stavec_kiter<ValueType>;

					typedef kerbal::memory::raw_storage<ValueType> storage_type;
					typedef __stavec_iterbase<__stavec_iter<ValueType>, ValueType*, storage_type> super;

				public:
					KERBAL_CONSTEXPR
					explicit __stavec_iter(storage_type* current) KERBAL_NOEXCEPT :
							super(current)
					{
					}
			};

			// Constant iterator to static_vector.
			template <typename ValueType>
			class __stavec_kiter: public __stavec_iterbase<
													__stavec_kiter<ValueType>,
													const ValueType*,
													const kerbal::memory::raw_storage<ValueType>
											>
			{
				private:
					template <typename Tp, std::size_t N>
					friend class kerbal::container::static_vector;

					typedef kerbal::memory::raw_storage<ValueType> storage_type;
					typedef __stavec_iterbase<__stavec_kiter<ValueType>, const ValueType*, const storage_type> super;
					typedef __stavec_iter<ValueType> iterator;

				public:
					KERBAL_CONSTEXPR
					explicit __stavec_kiter(const storage_type* current) KERBAL_NOEXCEPT :
							super(current)
					{
					}

					KERBAL_CONSTEXPR
					__stavec_kiter(const iterator & current) KERBAL_NOEXCEPT :
							super(current.current)
					{
					}

				protected:
					KERBAL_CONSTEXPR14
					iterator cast_to_mutable() const KERBAL_NOEXCEPT
					{
						return iterator(const_cast<storage_type*>(this->current));
					}

			};

		} //namespace detail

	} //namespace container

} //namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_STATIC_VECTOR_ITERATOR_HPP
