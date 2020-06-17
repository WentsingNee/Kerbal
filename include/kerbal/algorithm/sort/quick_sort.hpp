/**
 * @file       quick_sort.hpp
 * @brief
 * @date       2020-5-30, can be traced back to at latest 2018-9-5
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_SORT_QUICK_SORT_HPP
#define KERBAL_ALGORITHM_SORT_QUICK_SORT_HPP

#include <kerbal/algorithm/modifier.hpp>
#include <kerbal/algorithm/swap.hpp>
#include <kerbal/algorithm/sort/detail/quick_sort_pivot.hpp>
#include <kerbal/algorithm/sort/insertion_sort.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator.hpp>

#include <stack>

namespace kerbal
{

	namespace algorithm
	{

		template <typename BidirectionalIterator, typename Compare>
		KERBAL_CONSTEXPR14
		void quick_sort(BidirectionalIterator first, BidirectionalIterator last, Compare cmp)
		{
			typedef BidirectionalIterator iterator;

			if (kerbal::iterator::distance_less_than(first, last, 3)) { // dist < 3
				kerbal::algorithm::directly_insertion_sort(first, last, cmp);
				return;
			}

			iterator back(kerbal::iterator::prev(last));
			detail::__quick_sort_adjust_pivot(first, back, cmp);
			iterator partition_point(kerbal::algorithm::partition(first, back, detail::__quick_sort_compare_with_pivot<iterator, Compare>(back, cmp)));

			if (partition_point != back) {
				if (cmp(*back, *partition_point)) {
					kerbal::algorithm::iter_swap(back, partition_point);
				}
				kerbal::algorithm::quick_sort(kerbal::iterator::next(partition_point), last, cmp);
			}
			kerbal::algorithm::quick_sort(first, partition_point, cmp);
		}

		template <typename BidirectionalIterator>
		KERBAL_CONSTEXPR14
		void quick_sort(BidirectionalIterator first, BidirectionalIterator last)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			kerbal::algorithm::quick_sort(first, last, std::less<value_type>());
		}

		template <typename BidirectionalIterator, typename Compare, typename StackBuffer>
		KERBAL_CONSTEXPR14
		void __nonrecursive_qsort(BidirectionalIterator first, BidirectionalIterator last, Compare cmp)
		{
			typedef BidirectionalIterator iterator;

			StackBuffer st;
			st.push(std::make_pair(first, last));

			while (!st.empty()) {
				first = st.top().first;
				last = st.top().second;
				st.pop();

				if (kerbal::iterator::distance_less_than(first, last, 3)) {
					kerbal::algorithm::directly_insertion_sort(first, last, cmp);
					continue;
				}

				iterator back(kerbal::iterator::prev(last));
				detail::__quick_sort_adjust_pivot(first, back, cmp);
				iterator partition_point(kerbal::algorithm::partition(first, back, detail::__quick_sort_compare_with_pivot<iterator, Compare>(back, cmp)));

				if (partition_point != back) {
					if (cmp(*back, *partition_point)) {
						kerbal::algorithm::iter_swap(back, partition_point);
					}
					st.push(std::make_pair(kerbal::iterator::next(partition_point), last));
				}
				st.push(std::make_pair(first, partition_point));
			}
		}

		template <typename BidirectionalIterator, typename Compare>
		void nonrecursive_qsort(BidirectionalIterator first, BidirectionalIterator last, Compare cmp)
		{
			typedef BidirectionalIterator iterator;

			kerbal::algorithm::__nonrecursive_qsort
				<BidirectionalIterator, Compare, std::stack<std::pair<iterator, iterator> > >
			(first, last, cmp);
		}

		template <typename BidirectionalIterator>
		void nonrecursive_qsort(BidirectionalIterator first, BidirectionalIterator last)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			kerbal::algorithm::nonrecursive_qsort(first, last, std::less<value_type>());
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_SORT_QUICK_SORT_HPP
