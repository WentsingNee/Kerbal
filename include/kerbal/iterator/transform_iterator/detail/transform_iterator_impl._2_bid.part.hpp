/**
 * @file       transform_iterator_impl._2_bid.part.hpp
 * @brief
 * @date       2024-10-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ITERATOR_TRANSFORM_ITERATOR_DETAIL_TRANSFORM_ITERATOR_IMPL__2_BID_PART_HPP
#define KERBAL_ITERATOR_TRANSFORM_ITERATOR_DETAIL_TRANSFORM_ITERATOR_IMPL__2_BID_PART_HPP

#include <kerbal/iterator/transform_iterator/detail/transform_iterator_impl._1_forward.part.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/operators/incr_decr.hpp>
#include <kerbal/utility/declval.hpp>


namespace kerbal
{

	namespace iterator
	{

		namespace detail
		{

			template <typename BaseIter, typename Transformer, typename TargetIter>
			class transform_iterator_impl<BaseIter, Transformer, TargetIter, std::bidirectional_iterator_tag> :
				public transform_iterator_impl<BaseIter, Transformer, TargetIter, std::forward_iterator_tag>,

				// bidirectional iterator interface
				public kerbal::operators::decrementable<TargetIter> // it--
			{
				private:
					typedef transform_iterator_impl<BaseIter, Transformer, TargetIter, std::forward_iterator_tag>
																super;
					typedef transform_iterator_impl				this_type;

				protected:
					typedef std::bidirectional_iterator_tag		iterator_category;
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
				// bidirectional iterator interface

					KERBAL_CONSTEXPR14
					TargetIter &
					operator--()
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(
								--kerbal::utility::declthis<this_type>()->k_base_iter
							)
						)
					{
						--this->k_base_iter;
						return static_cast<TargetIter &>(*this);
					}

			};

		} // namespace detail

	} // namespace iterator

} // namespace kerbal

#endif // KERBAL_ITERATOR_TRANSFORM_ITERATOR_DETAIL_TRANSFORM_ITERATOR_IMPL__2_BID_PART_HPP
