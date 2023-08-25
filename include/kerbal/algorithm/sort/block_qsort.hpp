/**
 * @file       block_qsort.hpp
 * @brief
 * @date       block_qsort.hpp
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_SORT_BLOCK_QSORT_HPP
#define KERBAL_ALGORITHM_SORT_BLOCK_QSORT_HPP

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/algorithm/sort/heap_sort.hpp>
#include <kerbal/algorithm/sort/insertion_sort.hpp>
#include <kerbal/compare/basic_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/container/static_stack.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>

#include <climits>

#include <kerbal/algorithm/sort/detail/block_qsort_partition.hpp>


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			template <typename Size>
			KERBAL_CONSTEXPR14
			Size block_qsort_lg(Size n)
			{
				Size k = 0;
				while (n > 1) {
					++k;
					n >>= 1;
				}
				return k;
			}

			template <typename BidirectionalIterator, typename Compare>
			KERBAL_CONSTEXPR14
			void block_qsort_loop(BidirectionalIterator first, BidirectionalIterator last, Compare cmp, std::size_t depth_limit)
			{
				typedef BidirectionalIterator iterator;

				while (kerbal::iterator::distance_greater_than(first, last, 16)) {
					if (depth_limit == 0) {
						kerbal::algorithm::heap_sort(first, last, cmp);
						return;
					}

					--depth_limit;

					iterator back(kerbal::iterator::prev(last));
					detail::quick_sort_select_pivot(first, back, cmp);
					iterator partition_point(detail::block_partition(first, back, *back, cmp));

					if (partition_point != back) {
						if (cmp(*back, *partition_point)) {
							kerbal::algorithm::iter_swap(back, partition_point);
						}
						block_qsort_loop(kerbal::iterator::next(partition_point), last, cmp, depth_limit);
					}
					last = partition_point;
				}
				// dist <= 16
				kerbal::algorithm::directly_insertion_sort(first, last, cmp);
			}

		} // namespace detail

		template <typename BidirectionalIterator, typename Compare>
		KERBAL_CONSTEXPR14
		void block_qsort(BidirectionalIterator first, BidirectionalIterator last, Compare cmp)
		{
			detail::block_qsort_loop(first, last, cmp, 2 * detail::block_qsort_lg(kerbal::iterator::distance(first, last)));
		}

		template <typename BidirectionalIterator>
		KERBAL_CONSTEXPR14
		void block_qsort(BidirectionalIterator first, BidirectionalIterator last)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			kerbal::algorithm::block_qsort(first, last, kerbal::compare::less<value_type>());
		}


	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_SORT_BLOCK_QSORT_HPP
