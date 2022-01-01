/**
 * @file       partial_sort.hpp
 * @brief
 * @date       2022-01-01
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_SORT_PARTIAL_SORT_HPP
#define KERBAL_ALGORITHM_SORT_PARTIAL_SORT_HPP

#include <kerbal/algorithm/sort.hpp>
#include <kerbal/algorithm/swap.hpp>
#include <kerbal/compare/basic_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/iterator/iterator.hpp>

#include <kerbal/algorithm/sort/detail/quick_sort_pivot.hpp>
#include <kerbal/algorithm/sort/insertion_sort.hpp>


namespace kerbal
{

	namespace algorithm
	{

		template <typename RandomAccessIterator, typename BinaryPredic>
		KERBAL_CONSTEXPR14
		void partial_sort(RandomAccessIterator first, RandomAccessIterator nth, RandomAccessIterator last, BinaryPredic cmp)
		{
			typedef RandomAccessIterator iterator;

			while (true) {

				if (kerbal::iterator::distance_less_than(first, last, 16)) {
					kerbal::algorithm::insertion_sort(first, last, cmp);
					return;
				}

				iterator back(kerbal::iterator::prev(last));
				kerbal::algorithm::detail::quick_sort_select_pivot(first, back, cmp);
				iterator partition_point(kerbal::algorithm::detail::quick_sort_partition(first, back, *back, cmp));

				if (partition_point != back) {
					if (cmp(*back, *partition_point)) {
						kerbal::algorithm::iter_swap(back, partition_point);
					}
				}

				if (partition_point < nth) {
					kerbal::algorithm::sort(first, partition_point, cmp);
					first = kerbal::iterator::next(partition_point);
				} else {
					last = partition_point;
				}
			}
		}

		template <typename RandomAccessIterator>
		KERBAL_CONSTEXPR14
		void partial_sort(RandomAccessIterator first, RandomAccessIterator nth, RandomAccessIterator last)
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			kerbal::algorithm::partial_sort(first, nth, last, kerbal::compare::less<value_type>());
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_SORT_PARTIAL_SORT_HPP
