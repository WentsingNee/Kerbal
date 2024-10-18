/**
 * @file       transform_iterator_impl._1_forward.part.hpp
 * @brief
 * @date       2024-10-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ITERATOR_TRANSFORM_ITERATOR_DETAIL_TRANSFORM_ITERATOR_IMPL__1_FORWARD_PART_HPP
#define KERBAL_ITERATOR_TRANSFORM_ITERATOR_DETAIL_TRANSFORM_ITERATOR_IMPL__1_FORWARD_PART_HPP

#include <kerbal/iterator/transform_iterator/detail/transform_iterator_impl._0_input.part.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/iterator/iterator_traits.hpp>


namespace kerbal
{

	namespace iterator
	{

		namespace detail
		{

			template <typename BaseIter, typename Transformer, typename TargetIter>
			class transform_iterator_impl<BaseIter, Transformer, TargetIter, std::forward_iterator_tag> :
				public transform_iterator_impl<BaseIter, Transformer, TargetIter, std::input_iterator_tag>
			{
				private:
					typedef transform_iterator_impl<BaseIter, Transformer, TargetIter, std::input_iterator_tag>
																super;
					typedef transform_iterator_impl				this_type;

				protected:
					typedef std::forward_iterator_tag			iterator_category;
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

			};

		} // namespace detail

	} // namespace iterator

} // namespace kerbal

#endif // KERBAL_ITERATOR_TRANSFORM_ITERATOR_DETAIL_TRANSFORM_ITERATOR_IMPL__1_FORWARD_PART_HPP
