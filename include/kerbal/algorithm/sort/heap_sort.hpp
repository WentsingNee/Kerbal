/**
 * @file       heap_sort.hpp
 * @brief
 * @date       2020-5-30, can be traced back to at latest 2020-3-6
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_SORT_HEAP_SORT_HPP
#define KERBAL_ALGORITHM_SORT_HEAP_SORT_HPP

#include <kerbal/algorithm/heap.hpp>
#include <kerbal/compare/basic_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/iterator/iterator_traits.hpp>


namespace kerbal
{

	namespace algorithm
	{

		template <typename BidirectionalIterator, typename Compare>
		KERBAL_CONSTEXPR14
		void heap_sort(BidirectionalIterator first, BidirectionalIterator last, Compare compare)
		{
			kerbal::algorithm::make_heap(first, last, compare);
			kerbal::algorithm::sort_heap(first, last, compare);
		}

		template <typename BidirectionalIterator>
		KERBAL_CONSTEXPR14
		void heap_sort(BidirectionalIterator first, BidirectionalIterator last)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			kerbal::algorithm::heap_sort(first, last, kerbal::compare::less<value_type>());
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_SORT_HEAP_SORT_HPP
