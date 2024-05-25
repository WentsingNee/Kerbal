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

#ifndef KERBAL_CONTAINER_DETAIL_ARRAY_BASE_ARRAY_ITERATOR_HPP
#define KERBAL_CONTAINER_DETAIL_ARRAY_BASE_ARRAY_ITERATOR_HPP

#include <kerbal/container/detail/array_base/array_base.fwd.hpp>
#include <kerbal/container/array/array.fwd.hpp>

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
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename T>
			class arr_iter:
				// forward iterator interface
				public kerbal::operators::dereferenceable<arr_iter<T>, T *>, // it->
				public kerbal::operators::equality_comparable<arr_iter<T> >, // it != jt
				public kerbal::operators::incrementable<arr_iter<T> >, // it++
				// bidirectional iterator interface
				public kerbal::operators::decrementable<arr_iter<T> >, // it--
				// random access iterator interface
				public kerbal::operators::addable<
					arr_iter<T>,
					typename kerbal::iterator::iterator_traits<T *>::difference_type
				>, // it + N
				public kerbal::operators::addable_left<
					arr_iter<T>,
					typename kerbal::iterator::iterator_traits<T *>::difference_type
				>,// N + it
				public kerbal::operators::less_than_comparable<arr_iter<T> >, // it > jt, it <= jt, it >= jt
				public kerbal::operators::subtractable<
					arr_iter<T>,
					typename kerbal::iterator::iterator_traits<T *>::difference_type
				> // it - N
			{
					friend class kerbal::container::detail::arr_kiter<T>;

					template <typename U, std::size_t N>
					friend class kerbal::container::array;

				private:
					typedef kerbal::iterator::iterator_traits<T *>			iterator_traits;

				public:
					typedef std::random_access_iterator_tag					iterator_category;
					typedef typename iterator_traits::value_type			value_type;
					typedef typename iterator_traits::difference_type		difference_type;
					typedef typename iterator_traits::pointer				pointer;
					typedef typename iterator_traits::reference				reference;

				protected:
					pointer current;

				public:
					KERBAL_CONSTEXPR
					arr_iter() KERBAL_NOEXCEPT :
						current(NULL)
					{
					}

				protected:
					KERBAL_CONSTEXPR
					explicit
					arr_iter(pointer current) KERBAL_NOEXCEPT :
						current(current)
					{
					}

				public:

					//===================
					// forward iterator interface

					KERBAL_CONSTEXPR14
					reference operator*() const KERBAL_NOEXCEPT
					{
						return *this->current;
					}

					KERBAL_CONSTEXPR14
					arr_iter & operator++() KERBAL_NOEXCEPT
					{
						++this->current;
						return static_cast<arr_iter &>(*this);
					}

					KERBAL_CONSTEXPR
					friend
					bool operator==(const arr_iter & lhs, const arr_iter & rhs) KERBAL_NOEXCEPT
					{
						return lhs.current == rhs.current;
					}

					//===================
					// bidirectional iterator interface

					KERBAL_CONSTEXPR14
					arr_iter & operator--() KERBAL_NOEXCEPT
					{
						--this->current;
						return static_cast<arr_iter &>(*this);
					}

					//===================
					// random access iterator interface

					KERBAL_CONSTEXPR
					friend
					difference_type
					operator-(const arr_iter & lhs, const arr_iter & rhs) KERBAL_NOEXCEPT
					{
						return lhs.current - rhs.current;
					}

					KERBAL_CONSTEXPR14
					arr_iter & operator+=(const difference_type & delta) KERBAL_NOEXCEPT
					{
						this->current += delta;
						return static_cast<arr_iter &>(*this);
					}

					KERBAL_CONSTEXPR14
					arr_iter & operator-=(const difference_type & delta) KERBAL_NOEXCEPT
					{
						this->current -= delta;
						return static_cast<arr_iter &>(*this);
					}

					KERBAL_CONSTEXPR14
					reference operator[](const difference_type & dist) const KERBAL_NOEXCEPT
					{
						return *(static_cast<const arr_iter &>(*this) + dist);
					}

					KERBAL_CONSTEXPR
					friend
					bool operator<(const arr_iter & lhs, const arr_iter & rhs) KERBAL_NOEXCEPT
					{
						return lhs.current < rhs.current;
					}
			};

			template <typename T>
			class arr_kiter:
				// forward iterator interface
				public kerbal::operators::dereferenceable<arr_kiter<T>, const T *>, // it->
				public kerbal::operators::equality_comparable<arr_kiter<T> >, // it != jt
				public kerbal::operators::incrementable<arr_kiter<T> >, // it++
				// bidirectional iterator interface
				public kerbal::operators::decrementable<arr_kiter<T> >, // it--
				// random access iterator interface
				public kerbal::operators::addable<
					arr_kiter<T>,
					typename kerbal::iterator::iterator_traits<const T *>::difference_type
				>, // it + N
				public kerbal::operators::addable_left<
					arr_kiter<T>,
					typename kerbal::iterator::iterator_traits<const T *>::difference_type
				>,// N + it
				public kerbal::operators::less_than_comparable<arr_kiter<T> >, // it > jt, it <= jt, it >= jt
				public kerbal::operators::subtractable<
					arr_kiter<T>,
					typename kerbal::iterator::iterator_traits<const T *>::difference_type
				> // it - N
			{
					template <typename U, std::size_t N>
					friend class kerbal::container::array;

				private:
					typedef kerbal::iterator::iterator_traits<const T *>	iterator_traits;
					typedef kerbal::container::detail::arr_iter<T> iterator;

				public:
					typedef std::random_access_iterator_tag					iterator_category;
					typedef typename iterator_traits::value_type			value_type;
					typedef typename iterator_traits::difference_type		difference_type;
					typedef typename iterator_traits::pointer				pointer;
					typedef typename iterator_traits::reference				reference;

				protected:
					pointer current;

				public:
					KERBAL_CONSTEXPR
					arr_kiter() KERBAL_NOEXCEPT :
						current(NULL)
					{
					}

				protected:
					KERBAL_CONSTEXPR
					explicit
					arr_kiter(pointer current) KERBAL_NOEXCEPT :
						current(current)
					{
					}

				public:

					KERBAL_CONSTEXPR
					arr_kiter(const iterator & iter) KERBAL_NOEXCEPT :
						current(iter.current)
					{
					}

					//===================
					// forward iterator interface

					KERBAL_CONSTEXPR14
					reference operator*() const KERBAL_NOEXCEPT
					{
						return *this->current;
					}

					KERBAL_CONSTEXPR14
					arr_kiter & operator++() KERBAL_NOEXCEPT
					{
						++this->current;
						return static_cast<arr_kiter &>(*this);
					}

					KERBAL_CONSTEXPR
					friend
					bool operator==(const arr_kiter & lhs, const arr_kiter & rhs) KERBAL_NOEXCEPT
					{
						return lhs.current == rhs.current;
					}

					//===================
					// bidirectional iterator interface

					KERBAL_CONSTEXPR14
					arr_kiter & operator--() KERBAL_NOEXCEPT
					{
						--this->current;
						return static_cast<arr_kiter &>(*this);
					}

					//===================
					// random access iterator interface

					KERBAL_CONSTEXPR
					friend
					difference_type
					operator-(const arr_kiter & lhs, const arr_kiter & rhs) KERBAL_NOEXCEPT
					{
						return lhs.current - rhs.current;
					}

					KERBAL_CONSTEXPR14
					arr_kiter & operator+=(const difference_type & delta) KERBAL_NOEXCEPT
					{
						this->current += delta;
						return static_cast<arr_kiter &>(*this);
					}

					KERBAL_CONSTEXPR14
					arr_kiter & operator-=(const difference_type & delta) KERBAL_NOEXCEPT
					{
						this->current -= delta;
						return static_cast<arr_kiter &>(*this);
					}

					KERBAL_CONSTEXPR14
					reference operator[](const difference_type & dist) const KERBAL_NOEXCEPT
					{
						return *(static_cast<const arr_kiter &>(*this) + dist);
					}

					KERBAL_CONSTEXPR
					friend
					bool operator<(const arr_kiter & lhs, const arr_kiter & rhs) KERBAL_NOEXCEPT
					{
						return lhs.current < rhs.current;
					}

				protected:
					KERBAL_CONSTEXPR14
					iterator cast_to_mutable() const KERBAL_NOEXCEPT
					{
						return iterator(const_cast<T *>(this->current));
					}

			};

		} //namespace detail

	} //namespace container

	namespace iterator
	{

		namespace detail
		{

			template <typename T>
			struct reverse_iterator_base_is_inplace<kerbal::container::detail::arr_iter<T> > :
				kerbal::type_traits::true_type
			{
			};

			template <typename T>
			struct reverse_iterator_base_is_inplace<kerbal::container::detail::arr_kiter<T> > :
				kerbal::type_traits::true_type
			{
			};

		} // namespace detail

	} // namespace iterator

} //namespace kerbal


#endif // KERBAL_CONTAINER_DETAIL_ARRAY_BASE_ARRAY_ITERATOR_HPP
