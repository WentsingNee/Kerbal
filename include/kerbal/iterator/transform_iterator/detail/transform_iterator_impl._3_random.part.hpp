/**
 * @file       transform_iterator_impl._3_random.part.hpp
 * @brief
 * @date       2024-10-18
 * @author     Peter
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

			template <typename BaseIter, typename Transformer, typename TargetIter>
			class transform_iterator_impl<BaseIter, Transformer, TargetIter, std::random_access_iterator_tag> :
				public transform_iterator_impl<BaseIter, Transformer, TargetIter, std::bidirectional_iterator_tag>,

				// random access iterator interface
				public kerbal::operators::addable<
					TargetIter,
					typename kerbal::iterator::iterator_traits<BaseIter>::difference_type
				>, // it + N
				public kerbal::operators::addable_left<
					TargetIter,
					typename kerbal::iterator::iterator_traits<BaseIter>::difference_type
				>, // N + it
				public kerbal::operators::subtractable<
					TargetIter,
					typename kerbal::iterator::iterator_traits<BaseIter>::difference_type
				> // it - N
			{
				private:
					typedef transform_iterator_impl<BaseIter, Transformer, TargetIter, std::bidirectional_iterator_tag>
																super;
					typedef transform_iterator_impl				this_type;

				protected:
					typedef std::random_access_iterator_tag		iterator_category;
					typedef typename super::value_type			value_type;
					typedef typename super::difference_type		difference_type;
					typedef typename super::pointer				pointer;
					typedef typename super::reference			reference;

				protected:

					KERBAL_CONSTEXPR
					explicit
					transform_iterator_impl() :
						super()
					{
					}

					KERBAL_CONSTEXPR
					explicit
					transform_iterator_impl(BaseIter const & base_iter) :
						super(base_iter)
					{
					}

					KERBAL_CONSTEXPR
					explicit
					transform_iterator_impl(BaseIter const & base_iter, Transformer const & transformer) :
						super(base_iter, transformer)
					{
					}


				public:

				//===================
				// random access iterator interface

					KERBAL_CONSTEXPR
					friend
					difference_type
					operator-(
						const TargetIter & lhs,
						const TargetIter & rhs
					)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(lhs.k_base_iter - rhs.k_base_iter)
						)
					{
						return lhs.k_base_iter - rhs.k_base_iter;
					}

					KERBAL_CONSTEXPR14
					TargetIter &
					operator+=(const difference_type & delta)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(
								kerbal::utility::declthis<this_type>()->k_base_iter += delta
							)
						)
					{
						this->k_base_iter += delta;
						return static_cast<TargetIter &>(*this);
					}

					KERBAL_CONSTEXPR14
					TargetIter &
					operator-=(const difference_type & delta)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(
								kerbal::utility::declthis<this_type>()->k_base_iter -= delta
							)
						)
					{
						this->k_base_iter -= delta;
						return static_cast<TargetIter &>(*this);
					}

					KERBAL_CONSTEXPR14
					reference
					operator[](const difference_type & dist) const
					{
						return *(static_cast<const TargetIter &>(*this) + dist);
					}

					KERBAL_CONSTEXPR
					friend
					bool operator<(
						const TargetIter & lhs,
						const TargetIter & rhs
					)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(lhs.k_base_iter < rhs.k_base_iter)
						)
					{
						return lhs.k_base_iter < rhs.k_base_iter;
					}

					KERBAL_CONSTEXPR
					friend
					bool operator<=(
						const TargetIter & lhs,
						const TargetIter & rhs
					)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(lhs.k_base_iter <= rhs.k_base_iter)
						)
					{
						return lhs.k_base_iter <= rhs.k_base_iter;
					}

					KERBAL_CONSTEXPR
					friend
					bool operator>(
						const TargetIter & lhs,
						const TargetIter & rhs
					)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(lhs.k_base_iter > rhs.k_base_iter)
						)
					{
						return lhs.k_base_iter > rhs.k_base_iter;
					}

					KERBAL_CONSTEXPR
					friend
					bool operator>=(
						const TargetIter & lhs,
						const TargetIter & rhs
					)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(lhs.k_base_iter >= rhs.k_base_iter)
						)
					{
						return lhs.k_base_iter >= rhs.k_base_iter;
					}

			};

		} // namespace detail

	} // namespace iterator

} // namespace kerbal

#endif // KERBAL_ITERATOR_TRANSFORM_ITERATOR_DETAIL_TRANSFORM_ITERATOR_IMPL__3_RANDOM_PART_HPP
