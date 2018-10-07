/**
 * @file sort.hpp
 * @date 2017-2-21
 * @author 倪文卿
 */

#ifndef _SORT_HPP_
#define _SORT_HPP_

#include <stack>
#include <memory>

#include "kerbal/math/randnum.hpp"
#include <kerbal/algorithm/iterator.hpp>

namespace kerbal
{
	namespace algorithm
	{

		template <typename BidirectionalIterator, typename CompareFunction>
		void bubble_sort(BidirectionalIterator begin, BidirectionalIterator end, CompareFunction cmp)
		{
			if(begin == end) {
				return;
			}

			typedef BidirectionalIterator iterator;

			for (iterator end_of_each_loop = kerbal::algorithm::next(begin); end != end_of_each_loop; --end) {
				iterator j = begin;
				iterator j_next = kerbal::algorithm::next(j);
				while(j_next != end) {
					if (cmp(*j_next, *j)) {
						std::iter_swap(j_next, j);
					}
					j = j_next;
					++j_next;
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
			typedef BidirectionalIterator iterator;

			bool swit = true;

			for (iterator end_of_each_loop = kerbal::algorithm::next(begin); end != end_of_each_loop && swit; --end) {
				swit = false;
				iterator j = begin;
				iterator j_next = kerbal::algorithm::next(j);
				while(j_next != end) {
					if (cmp(*j_next, *j)) {
						swit = true;
						std::iter_swap(j_next, j);
					}
					j = j_next;
					++j_next;
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
			typedef RandomAccessIterator iterator;
			typedef typename std::iterator_traits<iterator>::difference_type difference_type;
			typedef typename std::iterator_traits<iterator>::value_type type;

			if (begin == end) {
				return;
			}

			if (kerbal::algorithm::next(begin) == end) {
				return;
			}

			std::pair<iterator, difference_type> pair(kerbal::algorithm::midden_iterator_with_distance(begin, end));
			iterator const & mid = pair.first;
			difference_type const & len = pair.second;
			merge_sort_using_allocator(begin, mid, cmp, allocator);
			merge_sort_using_allocator(mid, end, cmp, allocator);

			type * const p = allocator.allocate(len);
			type * k = p;

			struct dealloc_helper
			{
					Allocator & allocator;
					difference_type const & len;
					type * const & p;
					type * const & k;

					dealloc_helper(Allocator & allocator, difference_type const & len, type * const & p, type * const & k) :
							allocator(allocator), len(len), p(p), k(k)
					{
					}

					~dealloc_helper()
					{
						for (type * it = p; it != k; ++it) {
							allocator.destroy(it);
						}
						allocator.deallocate(p, len);
					}
			} auto_deallocator(allocator, len, p, k);

			iterator i = begin, j = mid;
			while (i != mid && j != end) {
				if (!cmp(*j, *i)) {
					allocator.construct(k, *i);
					++k; // k is a pointer. The advance option of a pointer will not raise any exception
					++i; // However, i and j is iterator. The advance of them may be raise exceptions
					     // so, k must advance before i or j otherwise it may lead to memory leak because
					     // k is not pointing to the last constructed object.
				} else {
					allocator.construct(k, *j);
					++k;
					++j;
				}
			}
			while (i != mid) {
				allocator.construct(k, *i);
				++k;
				++i;
			}
			while (j != end) {
				allocator.construct(k, *j);
				++k;
				++j;
			}

			std::copy(p, k, begin);

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

			if (begin == end) {
				return;
			}

			if (kerbal::algorithm::next(begin) == end) {
				return;
			}

			std::pair<iterator, difference_type> pair(kerbal::algorithm::midden_iterator_with_distance(begin, end));
			iterator & mid = pair.first;
			difference_type & len = pair.second;
			merge_sort(begin, mid, cmp);
			merge_sort(mid, end, cmp);

			type * const p = (type*) malloc(len * sizeof(type));
			type * k = p;

			struct dealloc_helper
			{
					type * const & p;
					type * const & k;

					dealloc_helper(type * const & p, type * const & k) :
							p(p), k(k)
					{
					}

					~dealloc_helper()
					{
						for (type * it = p; it != k; ++it) {
							it->~type();
						}
						free(p);
					}
			} auto_deallocator(p, k);

			iterator i = begin, j = mid;
			while (i != mid && j != end) {
				if (!cmp(*j, *i)) {
					new (k) type(*i);
					++k;
					++i;
				} else {
					new (k) type(*j);
					++k;
					++j;
				}
			}
			while (i != mid) {
				new (k) type(*i);
				++k;
				++i;
			}
			while (j != end) {
				new (k) type(*j);
				++k;
				++j;
			}

			std::copy(p, k, begin);
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
					std::iter_swap(begin, kerbal::algorithm::next(begin, delta));
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

				if(j != end && kerbal::algorithm::next(i) != end) {
					st.push(std::make_pair(kerbal::algorithm::next(j), end));
				}
				if(begin != i && begin != kerbal::algorithm::prev(i)) {
					st.push(std::make_pair(begin, kerbal::algorithm::prev(i)));
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

	} /* namespace algorithm */

} /* namespace kerbal */

#endif	/* End _SORT_HPP_ */
