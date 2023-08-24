/**
 * @file       lower_bound_backward.hpp
 * @brief
 * @date       2023-08-25
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_BINARY_SEARCH_LOWER_BOUND_BACKWARD_HPP
#define KERBAL_ALGORITHM_BINARY_SEARCH_LOWER_BOUND_BACKWARD_HPP

#include <kerbal/compare/binary_type_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/iterator/iterator_traits.hpp>


namespace kerbal
{

	namespace algorithm
	{

		template <typename BidirectionalIterator, typename Tp, typename Comparator>
		KERBAL_CONSTEXPR14
		BidirectionalIterator
		lower_bound_backward(BidirectionalIterator first, BidirectionalIterator last, const Tp & value, Comparator comparator)
		{
			while (last != first) {
				--last;
				if (comparator(*last, value)) { // *last < value
					++last;
					return last;
				}
			}
			return last;
		}

		template <typename BidirectionalIterator, typename Tp>
		KERBAL_CONSTEXPR14
		BidirectionalIterator
		lower_bound_backward(BidirectionalIterator first, BidirectionalIterator last, const Tp & value)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type type;
			return kerbal::algorithm::lower_bound_backward(first, last, value, kerbal::compare::binary_type_less<type, Tp>());
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_BINARY_SEARCH_LOWER_BOUND_BACKWARD_HPP
