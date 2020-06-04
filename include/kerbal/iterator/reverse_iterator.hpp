/**
 * @file       reverse_iterator.hpp
 * @brief
 * @date       2020-4-20
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ITERATOR_REVERSE_ITERATOR_HPP
#define KERBAL_ITERATOR_REVERSE_ITERATOR_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/operators/addable.hpp>
#include <kerbal/operators/dereferenceable.hpp>
#include <kerbal/operators/incr_decr.hpp>
#include <kerbal/operators/subtractable.hpp>

#if __cplusplus >= 201103L
#	include <type_traits>
#endif

namespace kerbal
{

	namespace iterator
	{

		template <typename Iter>
		class reverse_iterator;

		namespace detail
		{

			template <typename BidirectionalIterator>
			struct is_inplace: kerbal::type_traits::false_type
			{
			};

			template <typename Tp>
			struct is_inplace<Tp*>: kerbal::type_traits::true_type
			{
			};

			template <typename BidirectionalIterator, bool inplace = is_inplace<BidirectionalIterator>::value>
			class __reverse_iterator_base
			{
				private:
					typedef BidirectionalIterator iterator_type;
					typedef kerbal::iterator::iterator_traits<iterator_type> iterator_traits;

					typedef typename iterator_traits::reference				reference;

				protected:
					iterator_type iter;

					KERBAL_CONSTEXPR
					explicit __reverse_iterator_base()
							KERBAL_CONDITIONAL_NOEXCEPT(
									std::is_nothrow_default_constructible<iterator_type>::value
							)
							: iter()
					{
					}

					KERBAL_CONSTEXPR
					explicit __reverse_iterator_base(const iterator_type & iter)
							KERBAL_CONDITIONAL_NOEXCEPT(
									std::is_nothrow_copy_constructible<iterator_type>::value
							)
							: iter(iter)
					{
					}

				public:
					KERBAL_CONSTEXPR
					reference operator*() const
					{
						return *kerbal::iterator::prev(iter);
					}

					KERBAL_CONSTEXPR
					iterator_type base() const KERBAL_NOEXCEPT
					{
						return this->iter;
					}
			};

			template <typename BidirectionalIterator>
			class __reverse_iterator_base<BidirectionalIterator, true>
			{
				private:
					typedef BidirectionalIterator iterator_type;
					typedef kerbal::iterator::iterator_traits<iterator_type> iterator_traits;

					typedef typename iterator_traits::reference				reference;

				protected:
					iterator_type iter;

					KERBAL_CONSTEXPR
					explicit __reverse_iterator_base()
							: iter(kerbal::iterator::prev(iterator_type()))
					{
					}

					KERBAL_CONSTEXPR
					explicit __reverse_iterator_base(const iterator_type & iter)
							: iter(kerbal::iterator::prev(iter))
					{
					}

				public:
					KERBAL_CONSTEXPR
					reference operator*() const
					{
						return *iter;
					}

					KERBAL_CONSTEXPR
					iterator_type base() const
					{
						return kerbal::iterator::next(this->iter);
					}
			};

			template <typename BidirectionalIterator, typename IteratorTag>
			class __reverse_iterator;

			template <typename Iter>
			class __reverse_iterator<Iter, std::bidirectional_iterator_tag> :
					public kerbal::iterator::detail::__reverse_iterator_base<Iter>,

					public kerbal::operators::dereferenceable<
							kerbal::iterator::reverse_iterator<Iter>,
							typename kerbal::iterator::iterator_traits<Iter>::pointer
					>, // it->
					public kerbal::operators::incrementable<
							kerbal::iterator::reverse_iterator<Iter>
					>, // it++

					public kerbal::operators::decrementable<
							kerbal::iterator::reverse_iterator<Iter>
					> // it--
			{
				private:
					typedef kerbal::iterator::detail::__reverse_iterator_base<Iter> super;
					typedef __reverse_iterator this_type;
					typedef kerbal::iterator::reverse_iterator<Iter> derived;
					typedef kerbal::iterator::iterator_traits<Iter> iterator_traits;

				protected:
					typedef std::bidirectional_iterator_tag					iterator_category;
					typedef typename iterator_traits::value_type			value_type;
					typedef typename iterator_traits::difference_type		difference_type;
					typedef typename iterator_traits::pointer				pointer;
					typedef typename iterator_traits::reference				reference;

				protected:
					KERBAL_CONSTEXPR
					explicit __reverse_iterator() :
							super()
					{
					}

					KERBAL_CONSTEXPR
					explicit __reverse_iterator(const Iter& iter) :
							super(iter)
					{
					}

				public:
					KERBAL_CONSTEXPR14 derived& operator++()
							KERBAL_CONDITIONAL_NOEXCEPT(noexcept(--(kerbal::utility::declthis<this_type>()->iter)))
					{
						--this->iter;
						return static_cast<derived&>(*this);
					}

					KERBAL_CONSTEXPR14 derived& operator--()
							KERBAL_CONDITIONAL_NOEXCEPT(noexcept(++kerbal::utility::declthis<this_type>()->iter))
					{
						++this->iter;
						return static_cast<derived&>(*this);
					}

					friend KERBAL_CONSTEXPR
					bool operator==(const derived& lhs, const derived& rhs)
							KERBAL_CONDITIONAL_NOEXCEPT(noexcept(lhs.iter == rhs.iter))
					{
						return lhs.iter == rhs.iter;
					}

					friend KERBAL_CONSTEXPR
					bool operator!=(const derived& lhs, const derived& rhs)
							KERBAL_CONDITIONAL_NOEXCEPT(noexcept(lhs.iter != rhs.iter))
					{
						return lhs.iter != rhs.iter;
					}
			};

			template <typename Iter>
			class __reverse_iterator<Iter, std::random_access_iterator_tag> :
					public __reverse_iterator<Iter, std::bidirectional_iterator_tag>,

					public kerbal::operators::addable<
							kerbal::iterator::reverse_iterator<Iter>,
							typename kerbal::iterator::iterator_traits<Iter>::difference_type
					>, // it + N
					public kerbal::operators::addable_left<
							kerbal::iterator::reverse_iterator<Iter>,
							typename kerbal::iterator::iterator_traits<Iter>::difference_type
					>, // N + it
					public kerbal::operators::subtractable<
							kerbal::iterator::reverse_iterator<Iter>,
							typename kerbal::iterator::iterator_traits<Iter>::difference_type
					> // it - N
			{
				private:
					typedef __reverse_iterator<Iter, std::bidirectional_iterator_tag> super;
					typedef __reverse_iterator this_type;
					typedef kerbal::iterator::reverse_iterator<Iter> derived;
					typedef kerbal::iterator::iterator_traits<Iter> iterator_traits;

				protected:
					typedef std::random_access_iterator_tag					iterator_category;
					typedef typename iterator_traits::value_type			value_type;
					typedef typename iterator_traits::difference_type		difference_type;
					typedef typename iterator_traits::pointer				pointer;
					typedef typename iterator_traits::reference				reference;

				protected:
					KERBAL_CONSTEXPR
					explicit __reverse_iterator()
							: super()
					{
					}

					KERBAL_CONSTEXPR
					explicit __reverse_iterator(const Iter& iter)
							: super(iter)
					{
					}

				public:
					/*
					 * @precondition lhs.stride == rhs.stride
					 */
					friend KERBAL_CONSTEXPR
					difference_type
					operator-(const derived& lhs, const derived& rhs)
							KERBAL_CONDITIONAL_NOEXCEPT(noexcept(rhs.iter - lhs.iter))
					{
						return rhs.iter - lhs.iter;
					}

					KERBAL_CONSTEXPR14 derived& operator+=(const difference_type& delta)
							KERBAL_CONDITIONAL_NOEXCEPT(noexcept(kerbal::utility::declthis<this_type>()->iter -= delta))
					{
						this->iter -= delta;
						return static_cast<derived&>(*this);
					}

					KERBAL_CONSTEXPR14 derived& operator-=(const difference_type& delta)
							KERBAL_CONDITIONAL_NOEXCEPT(noexcept(kerbal::utility::declthis<this_type>()->iter += delta))
					{
						this->iter += delta;
						return static_cast<derived&>(*this);
					}

					KERBAL_CONSTEXPR reference operator[](const difference_type& dist) const
					{
						return *(static_cast<const derived&>(*this) + dist);
					}

					friend KERBAL_CONSTEXPR
					bool operator<(const derived& lhs, const derived& rhs)
							KERBAL_CONDITIONAL_NOEXCEPT(noexcept(lhs.iter > rhs.iter))
					{
						return lhs.iter > rhs.iter;
					}

					friend KERBAL_CONSTEXPR
					bool operator<=(const derived& lhs, const derived& rhs)
							KERBAL_CONDITIONAL_NOEXCEPT(noexcept(lhs.iter >= rhs.iter))
					{
						return lhs.iter >= rhs.iter;
					}

					friend KERBAL_CONSTEXPR
					bool operator>(const derived& lhs, const derived& rhs)
							KERBAL_CONDITIONAL_NOEXCEPT(noexcept(lhs.iter < rhs.iter))
					{
						return lhs.iter < rhs.iter;
					}

					friend KERBAL_CONSTEXPR
					bool operator>=(const derived& lhs, const derived& rhs)
							KERBAL_CONDITIONAL_NOEXCEPT(noexcept(lhs.iter <= rhs.iter))
					{
						return lhs.iter <= rhs.iter;
					}

			};

		} // namespace detail

		template <typename Iter>
		class reverse_iterator :
				public kerbal::iterator::detail::__reverse_iterator<Iter, typename kerbal::iterator::iterator_traits<Iter>::iterator_category>
		{
			public:
				typedef Iter iterator_type;

			private:
				typedef kerbal::iterator::detail::__reverse_iterator<iterator_type, typename kerbal::iterator::iterator_traits<iterator_type>::iterator_category> super;

			public:
				typedef typename super::iterator_category		iterator_category;
				typedef typename super::value_type				value_type;
				typedef typename super::difference_type			difference_type;
				typedef typename super::pointer					pointer;
				typedef typename super::reference				reference;

			public:
				KERBAL_CONSTEXPR
				explicit reverse_iterator()
						: super()
				{
				}

				KERBAL_CONSTEXPR
				explicit reverse_iterator(const iterator_type& iter)
						: super(iter)
				{
				}

		};

#	if __cplusplus >= 201703L

		template <typename BidirectionalIterator>
		reverse_iterator(const BidirectionalIterator&) -> reverse_iterator<BidirectionalIterator>;

#	endif

		template <typename Iter>
		KERBAL_CONSTEXPR
		reverse_iterator<Iter>
		make_reverse_iterator(const Iter& iter)
		{
			return reverse_iterator<Iter>(iter);
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR
		reverse_iterator<Tp*>
		make_reverse_iterator(Tp (&arr) [N])
		{
			return reverse_iterator<Tp*>(arr);
		}

	} // namespace iterator

} // namespace kerbal

#endif // KERBAL_ITERATOR_REVERSE_ITERATOR_HPP
