/*
 * sort_base.hpp
 *
 *  Created on: 2017年10月28日
 *      Author: Peter
 */

#ifndef SORT_BASE_HPP_
#define SORT_BASE_HPP_

#include <iterator>
#include <memory>

namespace kerbal
{
	namespace algorithm
	{
		template <typename BidirectionalIterator, typename CompareFunction>
		void bubble_sort(BidirectionalIterator begin, BidirectionalIterator end, CompareFunction cmp)
		{
			typedef BidirectionalIterator it_t;

			for (it_t end_end = std::next(begin); end != end_end; --end) {
				for (it_t j_next, j = begin; (j_next = std::next(j)) != end; j = j_next) {
					if (cmp(*j_next, *j)) {
						std::iter_swap(j_next, j);
					}
				}
			}
		}

		template <typename BidirectionalIterator>
		inline void bubble_sort(BidirectionalIterator begin, BidirectionalIterator end)
		{
			typedef BidirectionalIterator it_t;
			typedef typename std::iterator_traits<it_t>::value_type type;

			bubble_sort(begin, end, std::less<type>());
		}

		template <typename BidirectionalIterator, typename CompareFunction>
		void flag_bubble_sort(BidirectionalIterator begin, BidirectionalIterator end, CompareFunction cmp)
		{
			typedef BidirectionalIterator it_t;

			bool swit = true;

			for (it_t end_end = std::next(begin); end != end_end && swit; --end) {
				swit = false;
				for (it_t j_next, j = begin; (j_next = std::next(j)) != end; j = j_next) {
					if (cmp(*j_next, *j)) {
						swit = true;
						std::iter_swap(j_next, j);
					}
				}
			}
		}

		template <typename BidirectionalIterator>
		inline void flag_bubble_sort(BidirectionalIterator begin, BidirectionalIterator end)
		{
			typedef BidirectionalIterator it_t;
			typedef typename std::iterator_traits<it_t>::value_type type;

			flag_bubble_sort(begin, end, std::less<type>());
		}

		template <typename RandomAccessIterator, typename CompareFuntion>
		void merge_sort(RandomAccessIterator begin, RandomAccessIterator end, CompareFuntion cmp)
		{
			if (std::next(begin) != end) {
				typedef RandomAccessIterator it_t;
				typedef typename std::iterator_traits<it_t>::difference_type diff_t;
				typedef typename std::iterator_traits<it_t>::value_type type;

				diff_t len = std::distance(begin, end);

				it_t mid = std::next(begin, len / 2);
				merge_sort(begin, mid, cmp);
				merge_sort(mid, end, cmp);

				type * p = (type*) malloc(len * sizeof(type));

				it_t i = begin, j = mid;
				type * k = p;
				for (; i != mid && j != end;) {
					if (!cmp(*j, *i)) {
						new (k) type(*i);
						++i;
					} else {
						new (k) type(*j);
						++j;
					}
					++k;
				}

				std::uninitialized_copy(i, mid, k);
				std::uninitialized_copy(j, end, k);

				std::copy(p, p + len, begin);

				for (type * k = p; k != p + len; ++k) {
					k->~type();
				}
				free(p);
			}
		}

		template <typename RandomAccessIterator>
		void merge_sort(RandomAccessIterator begin, RandomAccessIterator end)
		{
			typedef RandomAccessIterator it_t;
			typedef typename std::iterator_traits<it_t>::value_type type;
			merge_sort(begin, end, std::less<type>());
		}

	}
}

#endif /* SORT_BASE_HPP_ */
