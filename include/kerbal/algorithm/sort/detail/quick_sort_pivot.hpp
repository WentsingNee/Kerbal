/**
 * @file       quick_sort_pivot.hpp
 * @brief
 * @date       2020-6-9
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_SORT_DETAIL_QUICK_SORT_PIVOT_HPP
#define KERBAL_ALGORITHM_SORT_DETAIL_QUICK_SORT_PIVOT_HPP

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator.hpp>


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			template <typename BidirectionalIterator, typename Compare>
			KERBAL_CONSTEXPR14
			void quick_sort_select_pivot(BidirectionalIterator first, BidirectionalIterator back, Compare cmp)
			{
				typedef BidirectionalIterator iterator;
				iterator mid(kerbal::iterator::midden_iterator(first, back));
				if (cmp(*first, *mid)) {
					if (cmp(*mid, *back)) {
						// first < mid < back
						// 0 1 2
						kerbal::algorithm::iter_swap(mid, back);
						// 0 2 1
					} else {
						if (cmp(*first, *back)) {
							// first < back < mid
							// 0 2 1
						} else {
							// back < first < mid
							// 1 2 0
							kerbal::algorithm::iter_swap(first, back);
							// 0 2 1
						}
					}
				} else {
					if (cmp(*first, *back)) {
						// mid < first < back
						// 1 0 2
						kerbal::algorithm::iter_swap(first, back);
						// 2 0 1
					} else {
						if (cmp(*mid, *back)) {
							// back
							// mid < back < first
							// 2 0 1
						} else {
							// back < mid < first
							// 2 1 0
							kerbal::algorithm::iter_swap(mid, back);
							// 2 0 1
						}
					}
					kerbal::algorithm::iter_swap(first, mid);
					// 0 2 1
				}
			}



			template <typename BidirectionalIterator, typename Tp, typename Compare>
			KERBAL_CONSTEXPR14
			bool quick_sort_partition_move_first_iter(BidirectionalIterator &first, BidirectionalIterator &last,
													const Tp & pivot, Compare & cmp)
			{
				while (first != last) {
					if (cmp(*first, pivot)) {
						++first;
					} else {
						return false;
					}
				}
				return true;
			}

			template <typename BidirectionalIterator, typename Tp, typename Compare>
			KERBAL_CONSTEXPR14
			bool quick_sort_partition_move_last_iter(BidirectionalIterator &first, BidirectionalIterator &last,
													const Tp & pivot, Compare & cmp)
			{
				while (first != last) {
					if (cmp(pivot, *last)) {
						--last;
					} else {
						return false;
					}
				}
				return true;
			}

			template <typename BidirectionalIterator, typename Tp, typename Compare>
			KERBAL_CONSTEXPR14
			BidirectionalIterator
			quick_sort_partition(BidirectionalIterator first, BidirectionalIterator last,
								const Tp & pivot, Compare & cmp)
			{
				while (true) {
					if (kerbal::algorithm::detail::quick_sort_partition_move_first_iter(first, last, pivot, cmp)) {
						return first;
					}
					--last;
					if (kerbal::algorithm::detail::quick_sort_partition_move_last_iter(first, last, pivot, cmp)) {
						return first;
					}
					kerbal::algorithm::iter_swap(first, last);
					++first;
				}
			}


		} // namespace detail

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_SORT_DETAIL_QUICK_SORT_PIVOT_HPP
