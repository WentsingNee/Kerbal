/**
 * @file       transform_iterator.decl.hpp
 * @brief
 * @date       2024-10-18
 * @author     peter
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

#include <kerbal/iterator/transform_iterator/detail/transform_iterator_impl._0_input.part.hpp>
#include <kerbal/iterator/transform_iterator/detail/transform_iterator_impl._1_forward.part.hpp>
#include <kerbal/iterator/transform_iterator/detail/transform_iterator_impl._2_bid.part.hpp>
#include <kerbal/iterator/transform_iterator/detail/transform_iterator_impl._3_random.part.hpp>


namespace kerbal
{

	namespace iterator
	{

		template <typename Iter, typename Transformer>
		class transform_iterator :
			public kerbal::iterator::detail::transform_iterator_impl<
				Iter, Transformer,
				typename kerbal::iterator::iterator_traits<Iter>::iterator_category
			>
		{
			public:
				typedef Iter iterator_type;

			private:
				typedef kerbal::iterator::detail::transform_iterator_impl<
					iterator_type, Transformer,
					typename kerbal::iterator::iterator_traits<iterator_type>::iterator_category
				> super;

			public:
				typedef typename super::iterator_category		iterator_category;
				typedef typename super::value_type				value_type;
				typedef typename super::difference_type			difference_type;
				typedef typename super::pointer					pointer;
				typedef typename super::reference				reference;

			public:

				KERBAL_CONSTEXPR14
				explicit
				transform_iterator() :
					super()
				{
				}

				KERBAL_CONSTEXPR14
				explicit
				transform_iterator(const Iter & iter) :
					super(iter)
				{
				}

				KERBAL_CONSTEXPR14
				explicit
				transform_iterator(const Iter & iter, Transformer const & transformer) :
					super(iter, transformer)
				{
				}

		};

	} // namespace iterator

} // namespace kerbal

#endif // KERBAL_ITERATOR_TRANSFORM_ITERATOR_TRANSFORM_ITERATOR_DECL_HPP
