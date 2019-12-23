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

		template <typename Tp, size_t N>
		class array;

		namespace detail
		{

			template <typename DerivedIterator, typename Pointer>
			class __arr_iterbase:
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
				private:

					Pointer current;

				public:
					explicit KERBAL_CONSTEXPR __arr_iterbase(Pointer current) KERBAL_NOEXCEPT :
							current(current)
					{
					}

					KERBAL_CONSTEXPR
					typename __arr_iterbase::reference operator*() const KERBAL_NOEXCEPT
					{
						return *this->current;
					}

					friend KERBAL_CONSTEXPR
					typename __arr_iterbase::difference_type
					operator-(const DerivedIterator & lhs, const DerivedIterator & rhs) KERBAL_NOEXCEPT
					{
						return lhs.current - rhs.current;
					}

					KERBAL_CONSTEXPR14 DerivedIterator& operator++() KERBAL_NOEXCEPT
					{
						++this->current;
						return static_cast<DerivedIterator&>(*this);
					}

					KERBAL_CONSTEXPR14 DerivedIterator& operator--() KERBAL_NOEXCEPT
					{
						--this->current;
						return static_cast<DerivedIterator&>(*this);
					}

					KERBAL_CONSTEXPR14 DerivedIterator& operator+=(const typename __arr_iterbase::difference_type & delta) KERBAL_NOEXCEPT
					{
						this->current += delta;
						return static_cast<DerivedIterator&>(*this);
					}

					KERBAL_CONSTEXPR14 DerivedIterator& operator-=(const typename __arr_iterbase::difference_type & delta) KERBAL_NOEXCEPT
					{
						this->current -= delta;
						return static_cast<DerivedIterator&>(*this);
					}

					friend KERBAL_CONSTEXPR
					bool operator<(const DerivedIterator & lhs, const DerivedIterator & rhs) KERBAL_NOEXCEPT
					{
						return lhs.current < rhs.current;
					}

					friend KERBAL_CONSTEXPR
					bool operator==(const DerivedIterator & lhs, const DerivedIterator & rhs) KERBAL_NOEXCEPT
					{
						return lhs.current == rhs.current;
					}
			};

			template <typename ValueType>
			class __arr_kiter;

			/// @brief Iterator to array.
			template <typename ValueType>
			class __arr_iter: public __arr_iterbase<__arr_iter<ValueType>, ValueType*>
			{
				private:
					template <typename Tp, size_t N>
					friend class kerbal::container::array;

					friend class __arr_kiter<ValueType>;

					typedef __arr_iterbase<__arr_iter<ValueType>, ValueType*> super;

				public:
					explicit KERBAL_CONSTEXPR __arr_iter(ValueType* current) KERBAL_NOEXCEPT :
							super(current)
					{
					}
			};

			/// @brief Iterator to array.
			template <typename ValueType>
			class __arr_kiter: public __arr_iterbase<__arr_kiter<ValueType>, const ValueType*>
			{
				private:
					template <typename Tp, size_t N>
					friend class kerbal::container::array;

					typedef __arr_iterbase<__arr_kiter<ValueType>, const ValueType*> super;
					typedef __arr_iter<ValueType> iterator;

				public:
					explicit KERBAL_CONSTEXPR __arr_kiter(const ValueType* current) KERBAL_NOEXCEPT :
							super(current)
					{
					}

					KERBAL_CONSTEXPR __arr_kiter(const iterator & current) KERBAL_NOEXCEPT :
							super(current.current)
					{
					}
			};

		} //namespace detail

	} //namespace container

} //namespace kerbal


#endif /* KERBAL_CONTAINER_IMPL_ARRAY_ITERATOR_IMPL_HPP_ */
