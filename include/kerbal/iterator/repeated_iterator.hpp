/**
 * @file       repeated_iterator.hpp
 * @brief
 * @date       2020-03-17
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ITERATOR_REPEATED_ITERATOR_HPP
#define KERBAL_ITERATOR_REPEATED_ITERATOR_HPP

#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/operators/addable.hpp>
#include <kerbal/operators/dereferenceable.hpp>
#include <kerbal/operators/equality_comparable.hpp>
#include <kerbal/operators/incr_decr.hpp>
#include <kerbal/operators/less_than_comparable.hpp>
#include <kerbal/operators/subtractable.hpp>
#include <kerbal/type_traits/pointer_deduction.hpp>

namespace kerbal
{

	namespace iterator
	{

		template <typename Tp>
		class repeated_iterator:
				//input iterator interface
				public kerbal::operators::dereferenceable<repeated_iterator<Tp>, Tp*>, // it->
				public kerbal::operators::equality_comparable<repeated_iterator<Tp> >, // it != jt
				public kerbal::operators::incrementable<repeated_iterator<Tp> >, // it++

				//bidirectional iterator interface
				public kerbal::operators::decrementable<repeated_iterator<Tp> >, // it--

				//random access iterator interface
				public kerbal::operators::addable<
						repeated_iterator<Tp>,
						typename kerbal::iterator::iterator_traits<Tp*>::difference_type
				>, // it + N
				public kerbal::operators::addable_left<
						repeated_iterator<Tp>,
						typename kerbal::iterator::iterator_traits<Tp*>::difference_type
				>, // N + it
				public kerbal::operators::less_than_comparable<repeated_iterator<Tp> >, // it > jt, it <= jt, it >= jt
				public kerbal::operators::subtractable<
						repeated_iterator<Tp>,
						typename kerbal::iterator::iterator_traits<Tp*>::difference_type
				> // it - N
		{
			private:
				typedef kerbal::iterator::iterator_traits<Tp*> iterator_traits;

			public:
				typedef std::random_access_iterator_tag					iterator_category;
				typedef typename iterator_traits::value_type			value_type;
				typedef typename iterator_traits::difference_type		difference_type;
				typedef typename iterator_traits::pointer				pointer;
				typedef typename iterator_traits::reference				reference;

			private:
				Tp* ptr;
				difference_type n;

			public:
				KERBAL_CONSTEXPR
				repeated_iterator(Tp & val, const difference_type& n):
						ptr(&val), n(n)
				{
				}

				//===================
				//input iterator interface

				KERBAL_CONSTEXPR14
				reference operator*() const KERBAL_NOEXCEPT
				{
					return *ptr;
				}

				KERBAL_CONSTEXPR14
				repeated_iterator& operator++()
				{
					++this->n;
					return *this;
				}

				friend KERBAL_CONSTEXPR
				bool operator==(const repeated_iterator& lhs, const repeated_iterator& rhs)
				{
					return lhs.n == rhs.n;
				}

				//===================
				//bidirectional iterator interface

				KERBAL_CONSTEXPR14
				repeated_iterator& operator--()
				{
					--this->n;
					return *this;
				}

				//===================
				//random access iterator interface

				friend KERBAL_CONSTEXPR
				difference_type
				operator-(const repeated_iterator& lhs, const repeated_iterator& rhs)
				{
					return lhs.n - rhs.n;
				}

				KERBAL_CONSTEXPR14
				repeated_iterator& operator+=(const difference_type& delta)
				{
					this->n += delta;
					return *this;
				}

				KERBAL_CONSTEXPR14
				repeated_iterator& operator-=(const difference_type& delta)
				{
					this->n -= delta;
					return *this;
				}

				KERBAL_CONSTEXPR
				reference operator[](const difference_type& dist) const
				{
					return *(*this + dist);
				}

				friend KERBAL_CONSTEXPR
				bool operator<(const repeated_iterator& lhs, const repeated_iterator& rhs)
				{
					return lhs.n < rhs.n;
				}

		};


		template <typename Tp>
		KERBAL_CONSTEXPR
		repeated_iterator<Tp>
		make_repeated_iterator(Tp & val, const typename repeated_iterator<Tp>::difference_type& n)
		{
			return repeated_iterator<Tp>(val, n);
		}

	} // namespace iterator

} // namespace kerbal

#endif //KERBAL_ITERATOR_REPEATED_ITERATOR_HPP
