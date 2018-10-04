/**
 * @file sort.hpp
 * @date 2017-2-21
 * @author 倪文卿
 */

#ifndef _SORT_HPP_
#define _SORT_HPP_

#include <stack>
#include <iterator>
#include <memory>

#include "kerbal/math/randnum.hpp"

namespace kerbal
{
	namespace algorithm
	{
		template <typename BidirectionalIterator, typename Distance>
		BidirectionalIterator prev(BidirectionalIterator it, Distance dist)
		{
			std::advance(it, -dist);
			return it;
		}

		template <typename InputIterator, typename Distance>
		InputIterator next(InputIterator it, Distance dist)
		{
			std::advance(it, dist);
			return it;
		}

		template <typename BidirectionalIterator>
		BidirectionalIterator prev(BidirectionalIterator it)
		{
			std::advance(it, -1);
			return it;
		}

		template <typename InputIterator>
		InputIterator next(InputIterator it)
		{
			std::advance(it, 1);
			return it;
		}

		template <typename BidirectionalIterator, typename CompareFunction>
		void bubble_sort(BidirectionalIterator begin, BidirectionalIterator end, CompareFunction cmp)
		{
			typedef BidirectionalIterator iterator;
			using kerbal::algorithm::next;

			for (iterator end_of_each_loop = next(begin); end != end_of_each_loop; --end) {
				for (iterator j_next, j = begin; (j_next = next(j)) != end; j = j_next) {
					if (cmp(*j_next, *j)) {
						std::iter_swap(j_next, j);
					}
				}
			}
		}

		template <typename BidirectionalIterator>
		void bubble_sort(BidirectionalIterator begin, BidirectionalIterator end)
		{
			typedef BidirectionalIterator iterator;
			typedef typename std::iterator_traits<iterator>::value_type type;

			bubble_sort(begin, end, std::less<type>());
		}

		template <typename BidirectionalIterator, typename CompareFunction>
		void flag_bubble_sort(BidirectionalIterator begin, BidirectionalIterator end, CompareFunction cmp)
		{
			using kerbal::algorithm::next;
			typedef BidirectionalIterator iterator;

			bool swit = true;

			for (iterator end_of_each_loop = next(begin); end != end_of_each_loop && swit; --end) {
				swit = false;
				for (iterator j_next, j = begin; (j_next = next(j)) != end; j = j_next) {
					if (cmp(*j_next, *j)) {
						swit = true;
						std::iter_swap(j_next, j);
					}
				}
			}
		}

		template <typename BidirectionalIterator>
		void flag_bubble_sort(BidirectionalIterator begin, BidirectionalIterator end)
		{
			typedef BidirectionalIterator iterator;
			typedef typename std::iterator_traits<iterator>::value_type type;

			flag_bubble_sort(begin, end, std::less<type>());
		}

		template <typename RandomAccessIterator, typename CompareFuntion, typename Allocator>
		void merge_sort_using_allocator(RandomAccessIterator begin, RandomAccessIterator end, CompareFuntion cmp, Allocator & allocator)
		{
			using kerbal::algorithm::next;
			typedef RandomAccessIterator iterator;
			typedef typename std::iterator_traits<iterator>::difference_type difference_type;
			typedef typename std::iterator_traits<iterator>::value_type type;

			if (next(begin) != end) {

				difference_type len = std::distance(begin, end);

				iterator mid = next(begin, len / 2);
				merge_sort_using_allocator(begin, mid, cmp, allocator);
				merge_sort_using_allocator(mid, end, cmp, allocator);

				type * const p = allocator.allocate(len);

				iterator i = begin, j = mid;
				type * k = p;
				try {
					for (; i != mid && j != end;) {
						if (!cmp(*j, *i)) {
							allocator.construct(k, *i);
							++i;
						} else {
							allocator.construct(k, *j);
							++j;
						}
						++k;
					}
					for (; i != mid; ++i) {
						allocator.construct(k, *i);
						++k;
					}
					for (; j != end; ++j) {
						allocator.construct(k, *j);
						++k;
					}

					std::copy(p, k, begin);

				} catch (...) {
					for (type * it = p; it != k; ++it) {
						allocator.destroy(it);
					}
					allocator.deallocate(p, len);
					throw;
				}

				for (type * it = p; it != k; ++it) {
					allocator.destroy(it);
				}
				allocator.deallocate(p, len);
			}
		}

		template <typename RandomAccessIterator, typename Allocator>
		void merge_sort_using_allocator(RandomAccessIterator begin, RandomAccessIterator end, Allocator & allocator)
		{
			typedef RandomAccessIterator iterator;
			typedef typename std::iterator_traits<iterator>::value_type type;
			merge_sort_using_allocator(begin, end, std::less<type>(), allocator);
		}

		template <typename RandomAccessIterator, typename CompareFuntion>
		void merge_sort(RandomAccessIterator begin, RandomAccessIterator end, CompareFuntion cmp)
		{
			typedef RandomAccessIterator iterator;
			typedef typename std::iterator_traits<iterator>::difference_type difference_type;
			typedef typename std::iterator_traits<iterator>::value_type type;

			if (kerbal::algorithm::next(begin) != end) {
				difference_type len = std::distance(begin, end);

				iterator mid = kerbal::algorithm::next(begin, len / 2);
				merge_sort(begin, mid, cmp);
				merge_sort(mid, end, cmp);

				type * const p = (type*) malloc(len * sizeof(type));

				iterator i = begin, j = mid;
				type * k = p;
				try {
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
					for (; i != mid; ++i) {
						new (k) type(*i);
						++k;
					}
					for (; j != end; ++j) {
						new (k) type(*j);
						++k;
					}

					std::copy(p, k, begin);

				} catch (...) {
					for (type * it = p; it != k; ++it) {
						it->~type();
					}
					free(p);
					throw;
				}

				for (type * it = p; it != k; ++it) {
					it->~type();
				}
				free(p);
			}
		}

		template <typename RandomAccessIterator>
		void merge_sort(RandomAccessIterator begin, RandomAccessIterator end)
		{
			typedef RandomAccessIterator iterator;
			typedef typename std::iterator_traits<iterator>::value_type type;
			merge_sort(begin, end, std::less<type>());
		}

		template <typename BidirectionalIterator, typename CompareFunction>
		void nonrecursive_qsort(BidirectionalIterator begin, BidirectionalIterator end, CompareFunction cmp)
		{
			if(begin == end) {
				return;
			}
			using kerbal::algorithm::prev;
			using kerbal::algorithm::next;
			using kerbal::math::randnum::rand_type_between;
			typedef BidirectionalIterator iterator;
			typedef typename std::iterator_traits<iterator>::difference_type difference_type;

			std::stack<std::pair<iterator, iterator> > st;
			st.push(std::make_pair(begin, --end));

			while(!st.empty()) {
				const iterator begin = st.top().first, end = st.top().second;
				st.pop();

				difference_type distance = std::distance(begin, end);
				if(distance >= 2) {
					int delta = rand_type_between<int>(1, distance);
					std::iter_swap(begin, next(begin, delta));
				} else if(distance == 1) {
					if(cmp(*end, *begin)) {
						std::iter_swap(begin, end);
					}
					continue;
				}

				iterator i = begin, j = end;

				while(true) {
					while(!cmp(*j, *begin) && i != j) {
						--j;
					}

					while(!cmp(*begin, *i) && i != j) {
						++i;
					}

					if(i != j) {
						std::iter_swap(i, j);
					} else {
						break;
					}
				}
				if(begin != i) {
					std::iter_swap(begin, i);
				}

				if(j != end && next(i) != end) {
					st.push(std::make_pair(next(j), end));
				}
				if(begin != i && begin != prev(i)) {
					st.push(std::make_pair(begin, prev(i)));
				}
			}
			return;
		}

		template <typename BidirectionalIterator>
		void nonrecursive_qsort(BidirectionalIterator begin, BidirectionalIterator end)
		{
			typedef BidirectionalIterator iterator;
			typedef typename std::iterator_traits<iterator>::value_type type;

			nonrecursive_qsort(begin, end, std::less<type>());
		}

	}
}


#endif	/* End _SORT_HPP_ */
