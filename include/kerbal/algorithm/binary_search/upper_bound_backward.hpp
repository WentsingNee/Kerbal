/**
 * @file       upper_bound_backward.hpp
 * @brief
 * @date       2023-08-25
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_BINARY_SEARCH_UPPER_BOUND_BACKWARD_HPP
#define KERBAL_ALGORITHM_BINARY_SEARCH_UPPER_BOUND_BACKWARD_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/compare/binary_type_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/iterator/iterator_traits.hpp>


namespace kerbal
{

	namespace algorithm
	{

		KERBAL_MODULE_EXPORT
		template <typename BidirectionalIterator, typename T, typename Comparator>
		KERBAL_CONSTEXPR14
		BidirectionalIterator
		upper_bound_backward(BidirectionalIterator first, BidirectionalIterator last, const T & value, Comparator comparator)
		{
			while (last != first) {
				--last;
				if (!static_cast<bool>(comparator(value, *last))) { // *last <= value
					++last;
					return last;
				}
			}
			return last;
		}

		KERBAL_MODULE_EXPORT
		template <typename BidirectionalIterator, typename T>
		KERBAL_CONSTEXPR14
		BidirectionalIterator
		upper_bound_backward(BidirectionalIterator first, BidirectionalIterator last, const T & value)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type type;
			return kerbal::algorithm::upper_bound_backward(first, last, value, kerbal::compare::binary_type_less<type, T>());
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_BINARY_SEARCH_UPPER_BOUND_BACKWARD_HPP
