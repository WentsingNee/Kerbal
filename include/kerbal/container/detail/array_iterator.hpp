/**
 * @file       array_iterator.hpp
 * @brief
 * @date       2019-10-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_ARRAY_ITERATOR_HPP
#define KERBAL_CONTAINER_DETAIL_ARRAY_ITERATOR_HPP

#include <kerbal/container/fwd/array.fwd.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/iterator/reverse_iterator.hpp>
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

		namespace detail
		{

			template <typename DerivedIterator, typename Pointer>
			class __arr_iterbase:
					//forward iterator interface
					public kerbal::operators::dereferenceable<DerivedIterator, Pointer>, // it->
					public kerbal::operators::equality_comparable<DerivedIterator>, // it != jt
					public kerbal::operators::incrementable<DerivedIterator>, // it++

					//bidirectional iterator interface
					public kerbal::operators::decrementable<DerivedIterator>, // it--

					//random access iterator interface
					public kerbal::operators::addable<DerivedIterator, typename kerbal::iterator::iterator_traits<Pointer>::difference_type>, // it + N
					public kerbal::operators::addable_left<DerivedIterator, typename kerbal::iterator::iterator_traits<Pointer>::difference_type>, // N + it
					public kerbal::operators::less_than_comparable<DerivedIterator>, // it > jt, it <= jt, it >= jt
					public kerbal::operators::subtractable<DerivedIterator, typename kerbal::iterator::iterator_traits<Pointer>::difference_type> // it - N
			{
				private:
					Pointer current;

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
					explicit __arr_iterbase(Pointer current) KERBAL_NOEXCEPT :
							current(current)
					{
					}

					//===================
					//forward iterator interface

					KERBAL_CONSTEXPR
					reference operator*() const KERBAL_NOEXCEPT
					{
						return *this->current;
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

			/// @brief Iterator to array.
			template <typename ValueType>
			class __arr_iter: public __arr_iterbase<__arr_iter<ValueType>, ValueType*>
			{
				private:
					template <typename Tp, std::size_t N>
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
					template <typename Tp, std::size_t N>
					friend class kerbal::container::array;

					typedef __arr_iterbase<__arr_kiter<ValueType>, const ValueType*> super;
					typedef __arr_iter<ValueType> iterator;

				public:
					KERBAL_CONSTEXPR
					explicit __arr_kiter(const ValueType* current) KERBAL_NOEXCEPT :
							super(current)
					{
					}

					KERBAL_CONSTEXPR
					__arr_kiter(const iterator & current) KERBAL_NOEXCEPT :
							super(current.current)
					{
					}

				protected:
					KERBAL_CONSTEXPR14
					iterator cast_to_mutable() const KERBAL_NOEXCEPT
					{
						return iterator(const_cast<ValueType*>(this->current));
					}

			};

		} //namespace detail

	} //namespace container

	namespace iterator
	{

		namespace detail
		{

			template <typename Tp>
			struct reverse_iterator_base_is_inplace<kerbal::container::detail::__arr_iter<Tp> >:
					kerbal::type_traits::true_type
			{
			};

			template <typename Tp>
			struct reverse_iterator_base_is_inplace<kerbal::container::detail::__arr_kiter<Tp> >:
					kerbal::type_traits::true_type
			{
			};

		} // namespace detail

	} // namespace iterator

} //namespace kerbal


#endif // KERBAL_CONTAINER_DETAIL_ARRAY_ITERATOR_HPP
