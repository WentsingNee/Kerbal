/**
 * @file       quick_sort.default.hpp
 * @brief
 * @date       2020-06-09
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OMPALGO_SORT_DETAIL_QUICK_SORT_QUICK_SORT_DEFAULT_HPP
#define KERBAL_OMPALGO_SORT_DETAIL_QUICK_SORT_QUICK_SORT_DEFAULT_HPP

#include <kerbal/algorithm/sort/insertion_sort.hpp>
#include <kerbal/algorithm/sort/quick_sort.hpp>
#include <kerbal/algorithm/swap.hpp>
#include <kerbal/iterator/iterator.hpp>


namespace kerbal
{

	namespace ompalgo
	{

		template <typename BidirectionalIterator, typename Compare>
		void quick_sort(BidirectionalIterator first, BidirectionalIterator last, Compare cmp, int level = 0)
		{
			typedef BidirectionalIterator iterator;

			if (kerbal::iterator::distance_less_than(first, last, 3)) {
				kerbal::algorithm::directly_insertion_sort(first, last, cmp);
				return;
			}

			if (kerbal::iterator::distance_less_than(first, last, 1024 * 1)) {
				kerbal::algorithm::quick_sort(first, last, cmp);
				return;
			}

			iterator back(kerbal::iterator::prev(last));
			kerbal::algorithm::detail::quick_sort_select_pivot(first, back, cmp);
			iterator partition_point(kerbal::algorithm::detail::quick_sort_partition(first, back, *back, cmp));

			if (partition_point != back) {
				if (cmp(*back, *partition_point)) {
					kerbal::algorithm::iter_swap(back, partition_point);
				}

#				pragma omp parallel sections
				{
#					pragma omp section
					{
						// printf("%d 0s\n", level);
						kerbal::ompalgo::quick_sort(kerbal::iterator::next(partition_point), last, cmp, level + 1);
						// printf("%d 0e\n", level);
					}

#					pragma omp section
					{
						// printf("%d 1s\n", level);
						kerbal::ompalgo::quick_sort(first, partition_point, cmp, level + 1);
						// printf("%d 1e\n", level);
					}
				}

			} else {
				// printf("%d ss\n", level);
				kerbal::ompalgo::quick_sort(first, partition_point, cmp, level + 1);
				// printf("%d se\n", level);
			}
		}

	} // namespace ompalgo

} // namespace kerbal

#endif // KERBAL_OMPALGO_SORT_DETAIL_QUICK_SORT_QUICK_SORT_DEFAULT_HPP
