/**
 * @file       transform_iterator_impl._3_random.part.hpp
 * @brief
 * @date       2024-10-18
 * @author     peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ITERATOR_TRANSFORM_ITERATOR_DETAIL_TRANSFORM_ITERATOR_IMPL__3_RANDOM_PART_HPP
#define KERBAL_ITERATOR_TRANSFORM_ITERATOR_DETAIL_TRANSFORM_ITERATOR_IMPL__3_RANDOM_PART_HPP

#include <kerbal/iterator/transform_iterator/detail/transform_iterator_impl._2_bid.part.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/config/compiler_id.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/operators/addable.hpp>
#include <kerbal/operators/subtractable.hpp>
#include <kerbal/utility/declval.hpp>


namespace kerbal
{

	namespace iterator
	{

		namespace detail
		{

			template <typename Iter, typename Transformer>
			class transform_iterator_impl<Iter, Transformer, std::random_access_iterator_tag> :
				public transform_iterator_impl<Iter, Transformer, std::bidirectional_iterator_tag>,

				// random access iterator interface
				public kerbal::operators::addable<
					kerbal::iterator::transform_iterator<Iter, Transformer>,
					typename kerbal::iterator::iterator_traits<Iter>::difference_type
				>, // it + N
				public kerbal::operators::addable_left<
					kerbal::iterator::transform_iterator<Iter, Transformer>,
					typename kerbal::iterator::iterator_traits<Iter>::difference_type
				>, // N + it
				public kerbal::operators::subtractable<
					kerbal::iterator::transform_iterator<Iter, Transformer>,
					typename kerbal::iterator::iterator_traits<Iter>::difference_type
				> // it - N
			{
				private:
					typedef transform_iterator_impl<Iter, Transformer, std::bidirectional_iterator_tag> super;
					typedef transform_iterator_impl this_type;
					typedef kerbal::iterator::transform_iterator<Iter, Transformer> transform_iterator;
					typedef kerbal::iterator::iterator_traits<Iter> base_iterator_traits;

				protected:
					typedef std::random_access_iterator_tag		iterator_category;
					typedef typename super::value_type			value_type;
					typedef typename super::difference_type		difference_type;
					typedef typename super::pointer				pointer;
					typedef typename super::reference			reference;

				protected:

					KERBAL_CONSTEXPR14
					explicit
					transform_iterator_impl() :
						super()
					{
					}

					KERBAL_CONSTEXPR14
					explicit
					transform_iterator_impl(const Iter & iter) :
						super(iter)
					{
					}

					KERBAL_CONSTEXPR14
					explicit
					transform_iterator_impl(const Iter & iter, Transformer const & transformer) :
						super(iter, transformer)
					{
					}


				public:

				//===================
				// random access iterator interface

					KERBAL_CONSTEXPR
					friend
					difference_type
					operator-(
						const transform_iterator & lhs,
						const transform_iterator & rhs
					)
#		if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC && __cplusplus >= 201703L
						KERBAL_CONDITIONAL_NOEXCEPT(noexcept(lhs.iter - rhs.iter))
#		endif
					{
						return lhs.iter - rhs.iter;
					}

					KERBAL_CONSTEXPR14
					transform_iterator &
					operator+=(const difference_type & delta)
						KERBAL_CONDITIONAL_NOEXCEPT(noexcept(kerbal::utility::declthis<this_type>()->iter += delta))
					{
						this->iter += delta;
						return static_cast<transform_iterator &>(*this);
					}

					KERBAL_CONSTEXPR14
					transform_iterator &
					operator-=(const difference_type & delta)
						KERBAL_CONDITIONAL_NOEXCEPT(noexcept(kerbal::utility::declthis<this_type>()->iter -= delta))
					{
						this->iter -= delta;
						return static_cast<transform_iterator &>(*this);
					}

					KERBAL_CONSTEXPR14
					reference
					operator[](const difference_type & dist) const
					{
						return *(static_cast<const transform_iterator &>(*this) + dist);
					}

					KERBAL_CONSTEXPR14
					friend
					bool operator<(
						const transform_iterator & lhs,
						const transform_iterator & rhs
					)
#		if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC && __cplusplus >= 201703L
						KERBAL_CONDITIONAL_NOEXCEPT(noexcept(lhs.iter < rhs.iter))
#		endif
					{
						return lhs.iter < rhs.iter;
					}

					KERBAL_CONSTEXPR14
					friend
					bool operator<=(
						const transform_iterator & lhs,
						const transform_iterator & rhs
					)
#		if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC && __cplusplus >= 201703L
						KERBAL_CONDITIONAL_NOEXCEPT(noexcept(lhs.iter <= rhs.iter))
#		endif
					{
						return lhs.iter <= rhs.iter;
					}

					KERBAL_CONSTEXPR14
					friend
					bool operator>(
						const transform_iterator & lhs,
						const transform_iterator & rhs
					)
#		if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC && __cplusplus >= 201703L
						KERBAL_CONDITIONAL_NOEXCEPT(noexcept(lhs.iter > rhs.iter))
#		endif
					{
						return lhs.iter > rhs.iter;
					}

					KERBAL_CONSTEXPR14
					friend
					bool operator>=(
						const transform_iterator & lhs,
						const transform_iterator & rhs
					)
#		if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC && __cplusplus >= 201703L
						KERBAL_CONDITIONAL_NOEXCEPT(noexcept(lhs.iter >= rhs.iter))
#		endif
					{
						return lhs.iter >= rhs.iter;
					}

			};

		} // namespace detail

	} // namespace iterator

} // namespace kerbal

#endif // KERBAL_ITERATOR_TRANSFORM_ITERATOR_DETAIL_TRANSFORM_ITERATOR_IMPL__3_RANDOM_PART_HPP
