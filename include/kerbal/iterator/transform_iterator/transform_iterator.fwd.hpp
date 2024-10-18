/**
 * @file       transform_iterator.fwd.hpp
 * @brief
 * @date       2024-10-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ITERATOR_TRANSFORM_ITERATOR_TRANSFORM_ITERATOR_FWD_HPP
#define KERBAL_ITERATOR_TRANSFORM_ITERATOR_TRANSFORM_ITERATOR_FWD_HPP

namespace kerbal
{

	namespace iterator
	{

		template <typename BaseIter, typename Transformer>
		class transform_iterator;

		namespace detail
		{

			template <typename InputIterator, typename Transformer, typename TargetIter, typename IteratorTag>
			class transform_iterator_impl;

		} // namespace detail

	} // namespace iterator

} // namespace kerbal

#endif // KERBAL_ITERATOR_TRANSFORM_ITERATOR_TRANSFORM_ITERATOR_FWD_HPP
