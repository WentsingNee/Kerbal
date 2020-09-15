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

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/algorithm/sort/detail/quick_sort_pivot.hpp>
#include <kerbal/algorithm/sort/insertion_sort.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator.hpp>

#include <stack>

#ifndef ENABLE_PMR_NONRECURSIVE_QSORT
#	if __cplusplus >= 201703L
#		if __has_include(<memory_resource>)
#			include <memory_resource>
#			define ENABLE_PMR_NONRECURSIVE_QSORT 1
#		endif
#	endif
#endif

namespace kerbal
{

	namespace algorithm
	{

		template <typename BidirectionalIterator, typename Compare>
		KERBAL_CONSTEXPR14
		void quick_sort(BidirectionalIterator first, BidirectionalIterator last, Compare cmp)
		{
			typedef BidirectionalIterator iterator;

			while (kerbal::iterator::distance_greater_than(first, last, 16)) {
				iterator back(kerbal::iterator::prev(last));
				detail::quick_sort_select_pivot(first, back, cmp);
				iterator partition_point(detail::quick_sort_partition(first, back, *back, cmp));

				if (partition_point != back) {
					if (cmp(*back, *partition_point)) {
						kerbal::algorithm::iter_swap(back, partition_point);
					}
					kerbal::algorithm::quick_sort(kerbal::iterator::next(partition_point), last, cmp);
				}
				last = partition_point;
			}
			// dist <= 16
			kerbal::algorithm::directly_insertion_sort(first, last, cmp);
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
		void __nonrecursive_qsort(BidirectionalIterator first, BidirectionalIterator last, Compare cmp, StackBuffer & st)
		{
			typedef BidirectionalIterator iterator;

			st.push(std::make_pair(first, last));

			while (!st.empty()) {
				first = st.top().first;
				last = st.top().second;
				st.pop();

				while (kerbal::iterator::distance_greater_than(first, last, 16)) {
					iterator back(kerbal::iterator::prev(last));
					detail::quick_sort_select_pivot(first, back, cmp);
					iterator partition_point(detail::quick_sort_partition(first, back, *back, cmp));

					st.push(std::make_pair(first, partition_point));
					if (partition_point != back) {
						if (cmp(*back, *partition_point)) {
							kerbal::algorithm::iter_swap(back, partition_point);
						}
						first = kerbal::iterator::next(partition_point);
					}
				}

				kerbal::algorithm::directly_insertion_sort(first, last, cmp);
			}
		}

		template <typename BidirectionalIterator, typename Compare>
		void nonrecursive_qsort(BidirectionalIterator first, BidirectionalIterator last, Compare cmp)
		{
			typedef BidirectionalIterator iterator;
			typedef std::pair<iterator, iterator> callee_info;
			typedef std::stack<callee_info> StackBuffer;
			StackBuffer st;
			kerbal::algorithm::__nonrecursive_qsort(first, last, cmp, st);
		}

		template <typename BidirectionalIterator>
		void nonrecursive_qsort(BidirectionalIterator first, BidirectionalIterator last)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			kerbal::algorithm::nonrecursive_qsort(first, last, std::less<value_type>());
		}

#	if ENABLE_PMR_NONRECURSIVE_QSORT

		namespace pmr
		{

			template <typename BidirectionalIterator, typename Compare>
			void nonrecursive_qsort(BidirectionalIterator first, BidirectionalIterator last, Compare cmp)
			{
				typedef BidirectionalIterator iterator;
				typedef std::pair<iterator, iterator> callee_info;
				typedef std::stack<callee_info, std::pmr::deque<callee_info> > StackBuffer;
				constexpr size_t stack_buff_length = 32 * sizeof(callee_info);
				std::byte stack_buff[stack_buff_length];
				std::pmr::monotonic_buffer_resource resource(stack_buff, stack_buff_length);
				StackBuffer st(&resource);
				kerbal::algorithm::__nonrecursive_qsort<BidirectionalIterator, Compare, StackBuffer>(first, last, cmp, st);
			}

			template <typename BidirectionalIterator>
			void nonrecursive_qsort(BidirectionalIterator first, BidirectionalIterator last)
			{
				typedef BidirectionalIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

				kerbal::algorithm::pmr::nonrecursive_qsort(first, last, std::less<value_type>());
			}

		} // namespace pmr

#	endif

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_SORT_QUICK_SORT_HPP
