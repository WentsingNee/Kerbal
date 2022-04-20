/**
 * @file       shell_sort.hpp
 * @brief
 * @date       2020-5-30, can be traced back to at latest 2020-4-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_SORT_SHELL_SORT_HPP
#define KERBAL_ALGORITHM_SORT_SHELL_SORT_HPP

#include <kerbal/algorithm/sort/insertion_sort.hpp>
#include <kerbal/compare/basic_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/stride_iterator.hpp>
#include <kerbal/numeric/bit.hpp>


namespace kerbal
{

	namespace algorithm
	{

		template <typename differece_type>
		struct shell_sort_reduce_by_half_policy
		{
				KERBAL_CONSTEXPR
				static differece_type init_stride(differece_type dist)
				{
					return dist / 2;
				}

				KERBAL_CONSTEXPR14
				bool operator()(differece_type & stride) const
				{
					if (stride == 0 || stride == 1) {
						return false;
					}
					stride /= 2;
					return true;
				}
		};

		template <typename differece_type>
		struct shell_sort_q_policy
		{
				KERBAL_CONSTEXPR
				static differece_type init_stride(differece_type dist)
				{
					return dist / 4;
				}

				KERBAL_CONSTEXPR14
				bool operator()(differece_type & stride) const
				{
					if (stride == 0 || stride == 1) {
						return false;
					}
					stride /= 4;
					return true;
				}
		};

		template <typename differece_type>
		struct shell_sort_hibbard_policy
		{
				KERBAL_CONSTEXPR14
				static differece_type init_stride(differece_type dist)
				{
					if (dist == 0) {
						return 0;
					}

					unsigned int cnt = 0;
					while ((dist >> cnt) != 1) {
						++cnt;
					}
					dist |= kerbal::numeric::mask<differece_type>(cnt);
					return dist / 2;
				}

				KERBAL_CONSTEXPR14
				bool operator()(differece_type & stride) const
				{
					if (stride == 0 || stride == 1) {
						return false;
					}
					stride = (stride + 1) / 2 - 1;
					return true;
				}
		};

		template <typename differece_type>
		struct shell_sort_minimun_limit_hibbard_policy
		{
			differece_type limit;

			KERBAL_CONSTEXPR
			explicit shell_sort_minimun_limit_hibbard_policy(differece_type limit = 8)
					: limit(limit)
			{
			}

			KERBAL_CONSTEXPR14
			differece_type init_stride(differece_type dist) const
			{
				if (dist == 0) {
					return 0;
				}

				if (dist <= limit) {
					return 1;
				}

				unsigned int cnt = 0;
				while ((dist >> cnt) != 1) {
					++cnt;
				}
				dist |= kerbal::numeric::mask<differece_type>(cnt);
				return dist;
			}

			KERBAL_CONSTEXPR14
			bool operator()(differece_type & stride) const
			{
				if (stride == 0 || stride == 1) {
					return false;
				}
				if (stride <= limit) {
					stride = 1;
					return true;
				}
				stride = (stride + 1) / 2 - 1;
				return true;
			}
		};

		template <typename BidirectionalIterator, typename Compare, typename GapReducePolicy>
		KERBAL_CONSTEXPR14
		void shell_sort(BidirectionalIterator first, BidirectionalIterator last, Compare cmp, GapReducePolicy gap_reduce_policy)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

			difference_type dist(kerbal::iterator::distance(first, last));
			difference_type stride(gap_reduce_policy.init_stride(dist));
			do {
				if (stride == 0 || stride == 1) {
					break;
				}
				iterator section_first(first); // first + i
				for (difference_type i = 0; i < stride; ++i) {
					kerbal::iterator::stride_iterator<iterator> stride_first(first, section_first, last, stride);
					difference_type m((dist - i) % stride);
					difference_type out((m != 0) ? (stride - m) : 0);
					kerbal::iterator::stride_iterator<iterator> stride_last(first, last, last, stride, out);
					kerbal::algorithm::directly_insertion_sort(stride_first, stride_last, cmp);
					++section_first;
				}
			} while (gap_reduce_policy(stride));
			kerbal::algorithm::directly_insertion_sort(first, last, cmp);
		}

		template <typename BidirectionalIterator, typename Compare>
		KERBAL_CONSTEXPR14
		void shell_sort(BidirectionalIterator first, BidirectionalIterator last, Compare cmp)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

			kerbal::algorithm::shell_sort(first, last, cmp, shell_sort_hibbard_policy<difference_type>());
		}

		template <typename BidirectionalIterator>
		KERBAL_CONSTEXPR14
		void shell_sort(BidirectionalIterator first, BidirectionalIterator last)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			kerbal::algorithm::shell_sort(first, last, kerbal::compare::less<value_type>());
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_SORT_SHELL_SORT_HPP
