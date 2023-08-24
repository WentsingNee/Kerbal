/**
 * @file       inplace_merge_sort.hpp
 * @brief
 * @date       2021-02-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_SORT_INPLACE_MERGE_SORT_HPP
#define KERBAL_ALGORITHM_SORT_INPLACE_MERGE_SORT_HPP

#include <kerbal/algorithm/modifier/inplace_merge.hpp>
#include <kerbal/compare/basic_compare.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>


namespace kerbal
{

	namespace algorithm
	{

		template <typename ForwardIterator, typename BinaryPredict>
		void inplace_merge_sort(ForwardIterator first, ForwardIterator last, BinaryPredict cmp)
		{
			typedef ForwardIterator iterator;

			if (first == last) {
				return;
			}

			if (kerbal::iterator::next(first) == last) {
				return;
			}

			iterator mid(kerbal::iterator::midden_iterator(first, last));
			kerbal::algorithm::inplace_merge_sort(first, mid, cmp);
			kerbal::algorithm::inplace_merge_sort(mid, last, cmp);
			kerbal::algorithm::inplace_merge(first, mid, last, cmp);
		}

		template <typename ForwardIterator>
		void inplace_merge_sort(ForwardIterator first, ForwardIterator last)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			kerbal::algorithm::inplace_merge_sort(first, last, kerbal::compare::less<value_type>());
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_SORT_INPLACE_MERGE_SORT_HPP
