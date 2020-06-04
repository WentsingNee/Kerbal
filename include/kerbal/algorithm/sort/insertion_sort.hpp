/**
 * @file       insertion_sort.hpp
 * @brief
 * @date       2020-5-30
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_SORT_INSERTION_SORT_HPP
#define KERBAL_ALGORITHM_SORT_INSERTION_SORT_HPP

#include <kerbal/algorithm/binary_search.hpp>
#include <kerbal/algorithm/modifier.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/iterator/iterator.hpp>

namespace kerbal
{

	namespace algorithm
	{

		template <typename BidirectionalIterator, typename Compare>
		KERBAL_CONSTEXPR14
		void directly_insertion_sort(BidirectionalIterator first, BidirectionalIterator last, Compare cmp)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			for (iterator i(first); i != last; ++i) {
				iterator insert_pos(i);
				while (insert_pos != first) {
					--insert_pos;
					if (!static_cast<bool>(cmp(*i, *insert_pos))) {
						// *i >= *insert_pos
						++insert_pos;
						break;
					}
				}
				if (insert_pos != i) {
					value_type value(kerbal::compatibility::to_xvalue(*i));
					kerbal::algorithm::move_backward(insert_pos, i, kerbal::iterator::next(i));
					*insert_pos = kerbal::compatibility::to_xvalue(value);
				}
			}
		}

		template <typename BidirectionalIterator>
		KERBAL_CONSTEXPR14
		void directly_insertion_sort(BidirectionalIterator first, BidirectionalIterator last)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			kerbal::algorithm::directly_insertion_sort(first, last, std::less<value_type>());
		}


		template <typename BidirectionalIterator, typename Compare>
		KERBAL_CONSTEXPR14
		void insertion_sort(BidirectionalIterator first, BidirectionalIterator last, Compare cmp)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			for (iterator i(first); i != last; ++i) {
				iterator insert_pos(kerbal::algorithm::upper_bound(first, i, *i, cmp));
				if (insert_pos != i) {
					value_type value(kerbal::compatibility::to_xvalue(*i));
					kerbal::algorithm::move_backward(insert_pos, i, kerbal::iterator::next(i));
					*insert_pos = kerbal::compatibility::to_xvalue(value);
				}
			}
		}

		template <typename BidirectionalIterator>
		KERBAL_CONSTEXPR14
		void insertion_sort(BidirectionalIterator first, BidirectionalIterator last)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			kerbal::algorithm::insertion_sort(first, last, std::less<value_type>());
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_SORT_INSERTION_SORT_HPP
