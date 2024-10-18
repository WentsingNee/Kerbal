/**
 * @file       transform_iterator.decl.hpp
 * @brief
 * @date       2024-10-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ITERATOR_TRANSFORM_ITERATOR_TRANSFORM_ITERATOR_DECL_HPP
#define KERBAL_ITERATOR_TRANSFORM_ITERATOR_TRANSFORM_ITERATOR_DECL_HPP

#include <kerbal/iterator/transform_iterator/transform_iterator.fwd.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/iterator/iterator_traits.hpp>

#include <cstddef>

#include <kerbal/iterator/transform_iterator/detail/transform_iterator_impl._0_input.part.hpp>
#include <kerbal/iterator/transform_iterator/detail/transform_iterator_impl._1_forward.part.hpp>
#include <kerbal/iterator/transform_iterator/detail/transform_iterator_impl._2_bid.part.hpp>
#include <kerbal/iterator/transform_iterator/detail/transform_iterator_impl._3_random.part.hpp>


namespace kerbal
{

	namespace iterator
	{

		template <typename BaseIter, typename Transformer>
		class transform_iterator :
			public kerbal::iterator::detail::transform_iterator_impl<
				BaseIter, Transformer, transform_iterator<BaseIter, Transformer>,
				typename kerbal::iterator::iterator_traits<BaseIter>::iterator_category
			>
		{
			private:
				typedef kerbal::iterator::detail::transform_iterator_impl<
					BaseIter, Transformer, transform_iterator<BaseIter, Transformer>,
					typename kerbal::iterator::iterator_traits<BaseIter>::iterator_category
				> super;

			public:
				typedef BaseIter iterator_type;

				typedef typename super::iterator_category		iterator_category;
				typedef typename super::value_type				value_type;
				typedef typename super::difference_type			difference_type;
				typedef typename super::pointer					pointer;
				typedef typename super::reference				reference;

			public:

				KERBAL_CONSTEXPR
				explicit
				transform_iterator() :
					super()
				{
				}

				KERBAL_CONSTEXPR
				explicit
				transform_iterator(const BaseIter & iter) :
					super(iter)
				{
				}

				KERBAL_CONSTEXPR
				explicit
				transform_iterator(const BaseIter & iter, Transformer const & transformer) :
					super(iter, transformer)
				{
				}

		};


#	if __cplusplus >= 201703L

		template <typename InputIterator, typename Transformer>
		transform_iterator(InputIterator const &, Transformer const &) ->
		transform_iterator<InputIterator, Transformer>;

#	endif


		template <typename BaseIter, typename Transformer>
		KERBAL_CONSTEXPR
		transform_iterator<BaseIter, Transformer>
		make_transform_iterator(BaseIter const & base_iter, Transformer const & transformer)
		{
			return transform_iterator<BaseIter, Transformer>(base_iter, transformer);
		}

		template <typename T, std::size_t N, typename Transformer>
		KERBAL_CONSTEXPR
		transform_iterator<T *, Transformer>
		make_transform_iterator(T (&arr) [N], Transformer const & transformer)
		{
			return transform_iterator<T *, Transformer>(arr, transformer);
		}

	} // namespace iterator

} // namespace kerbal

#endif // KERBAL_ITERATOR_TRANSFORM_ITERATOR_TRANSFORM_ITERATOR_DECL_HPP
