/**
 * @file       shell_sort.hpp
 * @brief
 * @date       2020-6-9
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OMPALGO_SORT_SHELL_SORT_HPP
#define KERBAL_OMPALGO_SORT_SHELL_SORT_HPP

#include <kerbal/openmp/disable_warning.hpp>

#include <kerbal/algorithm/sort/insertion_sort.hpp>
#include <kerbal/algorithm/sort/shell_sort.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/stride_iterator.hpp>

namespace kerbal
{

	namespace ompalgo
	{

#if !defined(_OPENMP)

		template <typename BidirectionalIterator, typename Compare, typename GapReducePolicy>
		void shell_sort(BidirectionalIterator first, BidirectionalIterator last, Compare cmp, GapReducePolicy gap_reduce_policy)
		{
			kerbal::algorithm::shell_sort(first, last, cmp, gap_reduce_policy);
		}

#else

		template <typename BidirectionalIterator, typename Compare, typename GapReducePolicy>
		void shell_sort(BidirectionalIterator first, BidirectionalIterator last, Compare cmp, GapReducePolicy gap_reduce_policy)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

			difference_type dist(kerbal::iterator::distance(first, last));
			difference_type stride(gap_reduce_policy.init_stride(dist));
			do {
				if (stride == 1) {
					kerbal::algorithm::directly_insertion_sort(first, last, cmp);
					break;
				} else {
#					pragma omp parallel for schedule(static)
					for (difference_type i = 0; i < stride; ++i) {
						iterator section_first(first + i);
						kerbal::iterator::stride_iterator<iterator> stride_first(first, section_first, last,
																				 stride);
						difference_type m((dist - i) % stride);
						difference_type out((m != 0) ? (stride - m) : 0);
						kerbal::iterator::stride_iterator<iterator> stride_last(first, last, last, stride, out);
						kerbal::algorithm::directly_insertion_sort(stride_first, stride_last, cmp);
					}
				}
			} while (gap_reduce_policy(stride));
		}

#endif

		template <typename BidirectionalIterator, typename Compare>
		void shell_sort(BidirectionalIterator first, BidirectionalIterator last, Compare cmp)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

			kerbal::ompalgo::shell_sort(first, last, cmp, kerbal::algorithm::shell_sort_reduce_by_half_policy<difference_type>());
		}

		template <typename BidirectionalIterator>
		void shell_sort(BidirectionalIterator first, BidirectionalIterator last)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			kerbal::ompalgo::shell_sort(first, last, std::less<value_type>());
		}

	} // namespace ompalgo

} // namespace kerbal

#endif // KERBAL_OMPALGO_SORT_SHELL_SORT_HPP
