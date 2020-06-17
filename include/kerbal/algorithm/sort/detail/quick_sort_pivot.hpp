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

			template <typename Iterator, typename CompareFunction>
			struct __quick_sort_compare_with_pivot
			{
					typedef Iterator iterator;
					typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
					typedef const value_type& const_reference;

					const iterator& pivot;
					CompareFunction& cmp;

					KERBAL_CONSTEXPR
					__quick_sort_compare_with_pivot(const iterator& pivot, CompareFunction& cmp) KERBAL_NOEXCEPT
							: pivot(pivot), cmp(cmp)
					{
					}

					KERBAL_CONSTEXPR
					bool operator()(const_reference val) const
					KERBAL_CONDITIONAL_NOEXCEPT(noexcept(cmp(val, *pivot)))
					{
						return cmp(val, *pivot);
					}
			};

			template <typename BidirectionalIterator, typename Compare>
			KERBAL_CONSTEXPR14
			void __quick_sort_adjust_pivot(BidirectionalIterator first, BidirectionalIterator back, Compare cmp)
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

		} // namespace detail

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_SORT_DETAIL_QUICK_SORT_PIVOT_HPP
