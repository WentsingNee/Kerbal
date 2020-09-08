/**
 * @file       quick_sort.hpp
 * @brief
 * @date       2020-6-9
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OMPALGO_SORT_QUICK_SORT_HPP
#define KERBAL_OMPALGO_SORT_QUICK_SORT_HPP

#include <kerbal/openmp/disable_warning.hpp>

#include <kerbal/algorithm/sort/insertion_sort.hpp>
#include <kerbal/algorithm/sort/quick_sort.hpp>
#include <kerbal/algorithm/swap.hpp>
#include <kerbal/iterator/iterator.hpp>

#include <omp.h>

namespace kerbal
{

	namespace ompalgo
	{

#if !defined(_OPENMP)

		template <typename BidirectionalIterator, typename Compare>
		void quick_sort(BidirectionalIterator first, BidirectionalIterator last, Compare cmp)
		{
			kerbal::algorithm::quick_sort(first, last, cmp);
		}

#else

#	define KERBAL_OMP_SUPPORT_TASK_DIRECTIVE 1

#	if defined(KERBAL_OMP_SUPPORT_TASK_DIRECTIVE) && KERBAL_OMP_SUPPORT_TASK_DIRECTIVE

		namespace detail
		{

			template <typename BidirectionalIterator, typename Compare>
			void quick_sort_task_dis(BidirectionalIterator first, BidirectionalIterator last, Compare cmp)
			{
				typedef BidirectionalIterator iterator;

				while (kerbal::iterator::distance_greater_than(first, last, 16)) {
					if (kerbal::iterator::distance_less_than(first, last, 1024 * 1)) {
						kerbal::algorithm::quick_sort(first, last, cmp);
						return;
					}

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

#	else

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
						printf("%d 0s\n", level);
						kerbal::ompalgo::quick_sort(kerbal::iterator::next(partition_point), last, cmp, level + 1);
						printf("%d 0e\n", level);
					}

#					pragma omp section
					{
						printf("%d 1s\n", level);
						kerbal::ompalgo::quick_sort(first, partition_point, cmp, level + 1);
						printf("%d 1e\n", level);
					}
				}

			} else {
				printf("%d ss\n", level);
				kerbal::ompalgo::quick_sort(first, partition_point, cmp, level + 1);
				printf("%d se\n", level);
			}
		}

#	endif // KERBAL_OMP_SUPPORT_TASK_DIRECTIVE


#endif

		template <typename BidirectionalIterator>
		void quick_sort(BidirectionalIterator first, BidirectionalIterator last)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			kerbal::ompalgo::quick_sort(first, last, std::less<value_type>());
		}

	} // namespace ompalgo

} // namespace kerbal

#endif // KERBAL_OMPALGO_SORT_QUICK_SORT_HPP
