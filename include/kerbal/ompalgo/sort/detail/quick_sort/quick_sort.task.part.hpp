/**
 * @file       quick_sort.task.part.hpp
 * @brief
 * @date       2020-06-09
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OMPALGO_SORT_DETAIL_QUICK_SORT_QUICK_SORT_TASK_PART_HPP
#define KERBAL_OMPALGO_SORT_DETAIL_QUICK_SORT_QUICK_SORT_TASK_PART_HPP

#include <kerbal/algorithm/sort/insertion_sort.hpp>
#include <kerbal/algorithm/sort/quick_sort.hpp>
#include <kerbal/algorithm/swap.hpp>
#include <kerbal/iterator/iterator.hpp>


namespace kerbal
{

	namespace ompalgo
	{

		namespace detail
		{

			template <typename BidirectionalIterator, typename Compare>
			void quick_sort_task_dis(BidirectionalIterator first, BidirectionalIterator last, Compare cmp)
			{
				typedef BidirectionalIterator iterator;

				while (kerbal::iterator::distance_greater_than(first, last, 16)) {
					// if (kerbal::iterator::distance_less_than(first, last, 1024 * 1)) {
					// 	kerbal::algorithm::quick_sort(first, last, cmp);
					// 	return;
					// }

					iterator back(kerbal::iterator::prev(last));
					kerbal::algorithm::detail::quick_sort_select_pivot(first, back, cmp);
					iterator partition_point(kerbal::algorithm::detail::quick_sort_partition(first, back, *back, cmp));

					if (partition_point != back) {
#						pragma omp task firstprivate(back, partition_point, last)
						{
							if (cmp(*back, *partition_point)) {
								kerbal::algorithm::iter_swap(back, partition_point);
							}
							kerbal::ompalgo::detail::quick_sort_task_dis(kerbal::iterator::next(partition_point), last, cmp);
						}

					}
					last = partition_point;
				}
				// dist <= 16
				kerbal::algorithm::directly_insertion_sort(first, last, cmp);
			}

		} // namespace detail

		template <typename BidirectionalIterator, typename Compare>
		void quick_sort(BidirectionalIterator first, BidirectionalIterator last, Compare cmp)
		{
#			pragma omp parallel
#			pragma omp single
			kerbal::ompalgo::detail::quick_sort_task_dis(first, last, cmp);
#			pragma omp taskwait
		}

	} // namespace ompalgo

} // namespace kerbal

#endif // KERBAL_OMPALGO_SORT_DETAIL_QUICK_SORT_QUICK_SORT_TASK_PART_HPP
