/**
 * @file       selection_sort.hpp
 * @brief
 * @date       2020-5-30, can be traced back to at latest 2020-3-6
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_SORT_SELECTION_SORT_HPP
#define KERBAL_ALGORITHM_SORT_SELECTION_SORT_HPP

#include <kerbal/algorithm/modifier.hpp>
#include <kerbal/algorithm/querier.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/iterator/iterator.hpp>

namespace kerbal
{

	namespace algorithm
	{

		template <typename ForwardIterator, typename Compare>
		KERBAL_CONSTEXPR14
		void selection_sort(ForwardIterator first, ForwardIterator last, Compare cmp)
		{
			typedef ForwardIterator iterator;

			while (first != last) {
				iterator j(kerbal::algorithm::min_element(first, last, cmp));
				if (first != j) {
					if (cmp(*j, *first)) {
						kerbal::algorithm::iter_swap(j, first);
					}
				}
				++first;
			}
		}

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void selection_sort(ForwardIterator first, ForwardIterator last)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			kerbal::algorithm::selection_sort(first, last, std::less<value_type>());
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_SORT_SELECTION_SORT_HPP
