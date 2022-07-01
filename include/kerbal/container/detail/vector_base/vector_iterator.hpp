/**
 * @file       vector_iterator.hpp
 * @brief
 * @date       2020-6-12
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_VECTOR_BASE_VECTOR_ITERATOR_HPP
#define KERBAL_CONTAINER_DETAIL_VECTOR_BASE_VECTOR_ITERATOR_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/operators/addable.hpp>
#include <kerbal/operators/dereferenceable.hpp>
#include <kerbal/operators/equality_comparable.hpp>
#include <kerbal/operators/incr_decr.hpp>
#include <kerbal/operators/less_than_comparable.hpp>
#include <kerbal/operators/subtractable.hpp>

#include <kerbal/container/vector/vector.fwd.hpp>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename Tp>
			class vec_iter:
					//forward iterator interface
					public kerbal::operators::dereferenceable<vec_iter<Tp>, Tp*>, // it->
					public kerbal::operators::equality_comparable<vec_iter<Tp> >, // it != jt
					public kerbal::operators::incrementable<vec_iter<Tp> >, // it++
					//bidirectional iterator interface
					public kerbal::operators::decrementable<vec_iter<Tp> >, // it--
					//random access iterator interface
					public kerbal::operators::addable<vec_iter<Tp>, typename kerbal::iterator::iterator_traits<Tp*>::difference_type>, // it + N
					public kerbal::operators::addable_left<vec_iter<Tp>, typename kerbal::iterator::iterator_traits<Tp*>::difference_type>,// N + it
					public kerbal::operators::less_than_comparable<vec_iter<Tp> >, // it > jt, it <= jt, it >= jt
					public kerbal::operators::subtractable<vec_iter<Tp>, typename kerbal::iterator::iterator_traits<Tp*>::difference_type> // it - N
			{
					friend class kerbal::container::detail::vec_kiter<Tp>;

					friend class kerbal::container::detail::vector_allocator_unrelated<Tp>;

					template <typename Up, typename Allocator>
					friend class kerbal::container::vector;

				private:
					typedef kerbal::iterator::iterator_traits<Tp*>			iterator_traits;

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
					vec_iter() KERBAL_NOEXCEPT :
							current(NULL)
					{
					}

				protected:
					KERBAL_CONSTEXPR
					explicit
					vec_iter(pointer current) KERBAL_NOEXCEPT :
							current(current)
					{
					}

				public:

					//===================
					//forward iterator interface

					KERBAL_CONSTEXPR14
					reference operator*() const KERBAL_NOEXCEPT
					{
						return *this->current;
					}

					KERBAL_CONSTEXPR14
					vec_iter& operator++() KERBAL_NOEXCEPT
					{
						++this->current;
						return static_cast<vec_iter&>(*this);
					}

					friend KERBAL_CONSTEXPR
					bool operator==(const vec_iter & lhs, const vec_iter & rhs) KERBAL_NOEXCEPT
					{
						return lhs.current == rhs.current;
					}

					//===================
					//bidirectional iterator interface

					KERBAL_CONSTEXPR14
					vec_iter& operator--() KERBAL_NOEXCEPT
					{
						--this->current;
						return static_cast<vec_iter&>(*this);
					}

					//===================
					//random access iterator interface

					friend KERBAL_CONSTEXPR
					difference_type
					operator-(const vec_iter & lhs, const vec_iter & rhs) KERBAL_NOEXCEPT
					{
						return lhs.current - rhs.current;
					}

					KERBAL_CONSTEXPR14
					vec_iter& operator+=(const difference_type & delta) KERBAL_NOEXCEPT
					{
						this->current += delta;
						return static_cast<vec_iter&>(*this);
					}

					KERBAL_CONSTEXPR14
					vec_iter& operator-=(const difference_type & delta) KERBAL_NOEXCEPT
					{
						this->current -= delta;
						return static_cast<vec_iter&>(*this);
					}

					KERBAL_CONSTEXPR14
					reference operator[](const difference_type & dist) const KERBAL_NOEXCEPT
					{
						return *(static_cast<const vec_iter&>(*this) + dist);
					}

					friend KERBAL_CONSTEXPR
					bool operator<(const vec_iter & lhs, const vec_iter & rhs) KERBAL_NOEXCEPT
					{
						return lhs.current < rhs.current;
					}
			};

			template <typename Tp>
			class vec_kiter:
					//forward iterator interface
					public kerbal::operators::dereferenceable<vec_kiter<Tp>, const Tp*>, // it->
					public kerbal::operators::equality_comparable<vec_kiter<Tp> >, // it != jt
					public kerbal::operators::incrementable<vec_kiter<Tp> >, // it++
					//bidirectional iterator interface
					public kerbal::operators::decrementable<vec_kiter<Tp> >, // it--
					//random access iterator interface
					public kerbal::operators::addable<vec_kiter<Tp>, typename kerbal::iterator::iterator_traits<const Tp*>::difference_type>, // it + N
					public kerbal::operators::addable_left<vec_kiter<Tp>, typename kerbal::iterator::iterator_traits<const Tp*>::difference_type>,// N + it
					public kerbal::operators::less_than_comparable<vec_kiter<Tp> >, // it > jt, it <= jt, it >= jt
					public kerbal::operators::subtractable<vec_kiter<Tp>, typename kerbal::iterator::iterator_traits<const Tp*>::difference_type> // it - N
			{
					friend class kerbal::container::detail::vector_allocator_unrelated<Tp>;

					template <typename Up, typename Allocator>
					friend class kerbal::container::vector;

				private:
					typedef kerbal::iterator::iterator_traits<const Tp*>			iterator_traits;
					typedef kerbal::container::detail::vec_iter<Tp> iterator;

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
					vec_kiter() KERBAL_NOEXCEPT :
							current(NULL)
					{
					}

				protected:
					KERBAL_CONSTEXPR
					explicit
					vec_kiter(pointer current) KERBAL_NOEXCEPT :
							current(current)
					{
					}

				public:

					KERBAL_CONSTEXPR
					vec_kiter(const iterator & iter) KERBAL_NOEXCEPT :
							current(iter.current)
					{
					}

					//===================
					//forward iterator interface

					KERBAL_CONSTEXPR14
					reference operator*() const KERBAL_NOEXCEPT
					{
						return *this->current;
					}

					KERBAL_CONSTEXPR14
					vec_kiter& operator++() KERBAL_NOEXCEPT
					{
						++this->current;
						return static_cast<vec_kiter&>(*this);
					}

					friend KERBAL_CONSTEXPR
					bool operator==(const vec_kiter & lhs, const vec_kiter & rhs) KERBAL_NOEXCEPT
					{
						return lhs.current == rhs.current;
					}

					//===================
					//bidirectional iterator interface

					KERBAL_CONSTEXPR14
					vec_kiter& operator--() KERBAL_NOEXCEPT
					{
						--this->current;
						return static_cast<vec_kiter&>(*this);
					}

					//===================
					//random access iterator interface

					friend KERBAL_CONSTEXPR
					difference_type
					operator-(const vec_kiter & lhs, const vec_kiter & rhs) KERBAL_NOEXCEPT
					{
						return lhs.current - rhs.current;
					}

					KERBAL_CONSTEXPR14
					vec_kiter& operator+=(const difference_type & delta) KERBAL_NOEXCEPT
					{
						this->current += delta;
						return static_cast<vec_kiter&>(*this);
					}

					KERBAL_CONSTEXPR14
					vec_kiter& operator-=(const difference_type & delta) KERBAL_NOEXCEPT
					{
						this->current -= delta;
						return static_cast<vec_kiter&>(*this);
					}

					KERBAL_CONSTEXPR14
					reference operator[](const difference_type & dist) const KERBAL_NOEXCEPT
					{
						return *(static_cast<const vec_kiter&>(*this) + dist);
					}

					friend KERBAL_CONSTEXPR
					bool operator<(const vec_kiter & lhs, const vec_kiter & rhs) KERBAL_NOEXCEPT
					{
						return lhs.current < rhs.current;
					}

				protected:
					KERBAL_CONSTEXPR14
					iterator cast_to_mutable() const KERBAL_NOEXCEPT
					{
						return iterator(const_cast<Tp*>(this->current));
					}

			};

		} //namespace detail

	} //namespace container

} //namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_VECTOR_BASE_VECTOR_ITERATOR_HPP
