/**
 * @file       stride_iterator.hpp
 * @brief
 * @date       2020-03-17
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ITERATOR_STRIDE_ITERATOR_HPP
#define KERBAL_ITERATOR_STRIDE_ITERATOR_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/operators/addable.hpp>
#include <kerbal/operators/dereferenceable.hpp>
#include <kerbal/operators/incr_decr.hpp>
#include <kerbal/operators/subtractable.hpp>
#include <kerbal/type_traits/type_traits_details/pointer_deduction.hpp>

namespace kerbal
{
	namespace iterator
	{
		namespace detail
		{

			template <typename Iter, typename Tag>
			class __stride_iterator;

			template <typename Iter>
			class __stride_iterator<Iter, std::forward_iterator_tag> :
					public kerbal::operators::dereferenceable<
							__stride_iterator<Iter, std::forward_iterator_tag>,
							typename kerbal::iterator::iterator_traits<Iter>::pointer
					>, // it->
					public kerbal::operators::incrementable<
							__stride_iterator<Iter, std::forward_iterator_tag>
					> // it++
			{
				private:
					typedef kerbal::iterator::iterator_traits<Iter> iterator_traits;

				public:
					typedef std::forward_iterator_tag						iterator_category;
					typedef typename iterator_traits::value_type			value_type;
					typedef typename iterator_traits::difference_type		difference_type;
					typedef typename iterator_traits::pointer				pointer;
					typedef typename iterator_traits::reference				reference;

				protected:
					difference_type stride;
					difference_type out;
					Iter current;
					Iter end;

				public:
					KERBAL_CONSTEXPR
					__stride_iterator(const Iter& current, const Iter& end, const difference_type& stride, const difference_type& out = 0) :
							stride(stride), out(out), current(current), end(end)
					{
					}

					KERBAL_CONSTEXPR
					__stride_iterator(const Iter&, const Iter& current, const Iter& end, const difference_type& stride, const difference_type& out = 0) :
							stride(stride), out(out), current(current), end(end)
					{
					}

					KERBAL_CONSTEXPR
					reference operator*() const
					{
						return *current;
					}

				protected:
					KERBAL_CONSTEXPR14 void advance(difference_type times = 1)
					{
						difference_type strides = times * this->stride;
						if (this->out <= -strides || this->out > 0) {
							this->out += strides;
						} else { // -stride < out <= 0
							difference_type offset = strides;
							if (this->out != 0) {
								offset = strides + this->out;
								this->out = 0;
							}
							difference_type move_actual(kerbal::iterator::advance_at_most(this->current, offset, this->end));
							this->out += offset - move_actual;
						}
					}

				public:
					KERBAL_CONSTEXPR14 __stride_iterator& operator++()
					{
						this->advance();
						return *this;
					}

					friend KERBAL_CONSTEXPR
					bool operator==(const __stride_iterator& lhs, const __stride_iterator& rhs)
					{
						return static_cast<bool>(lhs.current == rhs.current) &&
								static_cast<bool>(lhs.out == rhs.out);
					}

					friend KERBAL_CONSTEXPR
					bool operator!=(const __stride_iterator& lhs, const __stride_iterator& rhs)
					{
						return static_cast<bool>(lhs.current != rhs.current) ||
							   static_cast<bool>(lhs.out != rhs.out);
					}
			};

			template <typename Iter>
			class __stride_iterator<Iter, std::bidirectional_iterator_tag> :
					public __stride_iterator<Iter, std::forward_iterator_tag>,
					public kerbal::operators::decrementable<
							__stride_iterator<Iter, std::bidirectional_iterator_tag>
					> // it--
			{
				private:
					typedef __stride_iterator<Iter, std::forward_iterator_tag> super;

				private:
					typedef kerbal::iterator::iterator_traits<Iter> iterator_traits;

				public:
					typedef std::bidirectional_iterator_tag					iterator_category;
					typedef typename iterator_traits::value_type			value_type;
					typedef typename iterator_traits::difference_type		difference_type;
					typedef typename iterator_traits::pointer				pointer;
					typedef typename iterator_traits::reference				reference;

				protected:
					Iter begin;

				public:
					KERBAL_CONSTEXPR
					__stride_iterator(const Iter& begin, const Iter& current, const Iter& end, const difference_type& stride, const difference_type& out = 0) :
							super(current, end, stride, out), begin(begin)
					{
					}

				protected:

					KERBAL_CONSTEXPR14 void retreat(difference_type times = 1)
					{
						difference_type strides = times * this->stride;
						if (this->out >= strides || this->out < 0) {
							this->out -= strides;
						} else { // 0 <= out < stride
							difference_type offset = strides;
							if (this->out != 0) {
								offset = strides - this->out;
								this->out = 0;
							}
							difference_type move_actual(kerbal::iterator::retreat_at_most(this->current, offset, this->begin));
							this->out -= offset - move_actual;
						}
					}

				public:
					KERBAL_CONSTEXPR14 __stride_iterator& operator--()
					{
						this->retreat();
						return *this;
					}
			};

			template <typename Iter>
			class __stride_iterator<Iter, std::random_access_iterator_tag> :
					public __stride_iterator<Iter, std::bidirectional_iterator_tag>,
					public kerbal::operators::addable<
							__stride_iterator<Iter, std::random_access_iterator_tag>,
							typename kerbal::iterator::iterator_traits<Iter>::difference_type
					>, // it + N
					public kerbal::operators::addable_left<
							__stride_iterator<Iter, std::random_access_iterator_tag>,
							typename kerbal::iterator::iterator_traits<Iter>::difference_type
					>, // N + it
					public kerbal::operators::subtractable<
							__stride_iterator<Iter, std::random_access_iterator_tag>,
							typename kerbal::iterator::iterator_traits<Iter>::difference_type
					> // it - N
			{
				private:
					typedef __stride_iterator<Iter, std::bidirectional_iterator_tag> super;

				private:
					typedef kerbal::iterator::iterator_traits<Iter> iterator_traits;

				public:
					typedef std::random_access_iterator_tag					iterator_category;
					typedef typename iterator_traits::value_type			value_type;
					typedef typename iterator_traits::difference_type		difference_type;
					typedef typename iterator_traits::pointer				pointer;
					typedef typename iterator_traits::reference				reference;


				public:
					KERBAL_CONSTEXPR
					__stride_iterator(const Iter& begin, const Iter& current, const Iter& end, const difference_type& stride, const difference_type& out = 0) :
							super(begin, current, end, stride, out)
					{
					}

					/*
					 * @precondition lhs.stride == rhs.stride
					 */
					friend KERBAL_CONSTEXPR14
					difference_type
					operator-(const __stride_iterator& lhs, const __stride_iterator& rhs)
					{
						difference_type dist(kerbal::iterator::distance(rhs.current, lhs.current) - rhs.out + lhs.out);
						dist /= lhs.stride;
						return dist;
					}

					KERBAL_CONSTEXPR14 __stride_iterator& operator+=(const difference_type& delta)
					{
						this->advance(delta);
						return *this;
					}

					KERBAL_CONSTEXPR14 __stride_iterator& operator-=(const difference_type& delta)
					{
						this->retreat(delta);
						return *this;
					}

					KERBAL_CONSTEXPR14 reference operator[](const difference_type& dist) const
					{
						return *(*this + dist);
					}

					friend KERBAL_CONSTEXPR14
					bool operator<(const __stride_iterator& lhs, const __stride_iterator& rhs)
					{
						if (lhs.current < rhs.current) {
							return true;
						} else if (lhs.current > rhs.current) {
							return false;
						}
						return lhs.out < rhs.out;
					}

					friend KERBAL_CONSTEXPR14
					bool operator<=(const __stride_iterator& lhs, const __stride_iterator& rhs)
					{
						if (lhs.current < rhs.current) {
							return true;
						} else if (lhs.current > rhs.current) {
							return false;
						}
						return lhs.out <= rhs.out;
					}

					friend KERBAL_CONSTEXPR14
					bool operator>(const __stride_iterator& lhs, const __stride_iterator& rhs)
					{
						if (lhs.current < rhs.current) {
							return false;
						} else if (lhs.current > rhs.current) {
							return true;
						}
						return lhs.out > rhs.out;
					}

					friend KERBAL_CONSTEXPR14
					bool operator>=(const __stride_iterator& lhs, const __stride_iterator& rhs)
					{
						if (lhs.current < rhs.current) {
							return false;
						} else if (lhs.current > rhs.current) {
							return true;
						}
						return lhs.out >= rhs.out;
					}
			};

		} // namespace detail

		template <typename Iter>
		class stride_iterator :
				public kerbal::iterator::detail::__stride_iterator<Iter, typename kerbal::iterator::iterator_traits<Iter>::iterator_category>
		{
			private:
				typedef kerbal::iterator::detail::__stride_iterator<Iter, typename kerbal::iterator::iterator_traits<Iter>::iterator_category> super;

			public:
				typedef typename super::iterator_category		iterator_category;
				typedef typename super::value_type				value_type;
				typedef typename super::difference_type			difference_type;
				typedef typename super::pointer					pointer;
				typedef typename super::reference				reference;

			public:
				KERBAL_CONSTEXPR
				stride_iterator(const Iter& begin, const Iter& current, const Iter& end, const difference_type& stride, const difference_type& out = 0) :
						super(begin, current, end, stride, out)
				{
				}

		};

		template <typename Iter>
		KERBAL_CONSTEXPR
		stride_iterator<Iter>
		make_stride_iterator(const Iter& begin, const Iter& current, const Iter& end,
							const typename kerbal::iterator::iterator_traits<Iter>::difference_type& stride,
							const typename kerbal::iterator::iterator_traits<Iter>::difference_type& out = 0)
		{
			return stride_iterator<Iter>(begin, current, end, stride, out);
		}

	} // namespace iterator

} // namespace kerbal

#endif //KERBAL_ITERATOR_STRIDE_ITERATOR_HPP
