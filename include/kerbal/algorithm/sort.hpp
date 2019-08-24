/**
 * @file       sort.hpp
 * @brief
 * @date       2017-2-21
 * @author     peter
 * @copyright
 *      peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_SORT_HPP_
#define KERBAL_ALGORITHM_SORT_HPP_

#include <stack>
#include <memory>

#include <kerbal/algorithm/search.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator.hpp>

namespace kerbal
{
	namespace algorithm
	{

		template <typename BidirectionalIterator, typename CompareFunction>
		KERBAL_CONSTEXPR14
		void bubble_sort(BidirectionalIterator first, BidirectionalIterator last, CompareFunction cmp)
		{
			if (first == last) {
				return;
			}

			typedef BidirectionalIterator iterator;

			for (iterator last_of_each_loop(kerbal::iterator::next(first)); last != last_of_each_loop; --last) {
				iterator j(first);
				iterator j_next(kerbal::iterator::next(j));
				while (j_next != last) {
					if (cmp(*j_next, *j)) {
						std::iter_swap(j_next, j);
					}
					j = j_next;
					++j_next;
				}
			}
		}

		template <typename BidirectionalIterator>
		KERBAL_CONSTEXPR14
		void bubble_sort(BidirectionalIterator first, BidirectionalIterator last)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type type;

			kerbal::algorithm::bubble_sort(first, last, std::less<type>());
		}

		template <typename BidirectionalIterator, typename CompareFunction>
		KERBAL_CONSTEXPR14
		void flag_bubble_sort(BidirectionalIterator first, BidirectionalIterator last, CompareFunction cmp)
		{
			typedef BidirectionalIterator iterator;

			bool swit = true;

			for (iterator last_of_each_loop(kerbal::iterator::next(first));
					static_cast<bool>(last != last_of_each_loop) && swit; --last) {
				swit = false;
				iterator j(first);
				iterator j_next(kerbal::iterator::next(j));
				while (j_next != last) {
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
		KERBAL_CONSTEXPR14
		void flag_bubble_sort(BidirectionalIterator first, BidirectionalIterator last)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type type;

			kerbal::algorithm::flag_bubble_sort(first, last, std::less<type>());
		}

		template <typename InputIterator1, typename InputIterator2, typename OutputIterator, typename CompareFuntion>
		OutputIterator
		merge(InputIterator1 a_first, InputIterator1 a_last,
			InputIterator2 b_first, InputIterator2 b_last,
			OutputIterator to, CompareFuntion cmp)
		{
			while (static_cast<bool>(a_first != a_last) && static_cast<bool>(b_first != b_last)) {
				if (cmp(*b_first, *a_first)) { // b < a
					*to = *b_first;
					++b_first;
				} else { // b >= a
					*to = *a_first;
					++a_first;
				}
				++to;
			}
			std::copy(a_first, a_last, to);
			return std::copy(b_first, b_last, to);
		}

		template <typename InputIterator1, typename InputIterator2, typename OutputIterator>
		OutputIterator
		merge(InputIterator1 a_first, InputIterator1 a_last,
			InputIterator2 b_first, InputIterator2 b_last,
			OutputIterator to)
		{
			typedef InputIterator1 iterator1;
			typedef InputIterator2 iterator2;
			typedef typename kerbal::iterator::iterator_traits<iterator1>::value_type type1;
			typedef typename kerbal::iterator::iterator_traits<iterator2>::value_type type2;
			return kerbal::algorithm::merge(a_first, a_last, b_first, b_last, to, kerbal::algorithm::binary_type_equal_to<type2, type1>());
		}

		template <typename ForwardIterator, typename ForwardIterator2, typename Compare>
		void merge_sort_afford_buffer(ForwardIterator first, ForwardIterator last, ForwardIterator2 buffer, Compare cmp)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type type;

			if (first == last) {
				return;
			}

			if (kerbal::iterator::next(first) == last) {
				return;
			}

			std::pair<iterator, difference_type> pair(kerbal::iterator::midden_iterator_with_distance(first, last));
			iterator const & mid = pair.first;
			difference_type const & len = pair.second;
			kerbal::algorithm::merge_sort_afford_buffer(first, mid, buffer, cmp);
			kerbal::algorithm::merge_sort_afford_buffer(mid, last, kerbal::iterator::next(buffer, len / 2), cmp);

			kerbal::algorithm::merge(first, mid, mid, last, buffer, cmp);

			while (first != last) {
				*first = kerbal::compatibility::to_xvalue(*buffer);
				++first;
				++buffer;
			}
		}

		template <typename ForwardIterator, typename ForwardIterator2>
		void merge_sort_afford_buffer(ForwardIterator first, ForwardIterator last, ForwardIterator2 buffer)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type type;
			kerbal::algorithm::merge_sort_afford_buffer(first, last, buffer, std::less<type>());
		}

		template <typename ForwardIterator, typename Allocator, typename Compare>
		void merge_sort_afford_allocator(ForwardIterator first, ForwardIterator last, Allocator & allocator, Compare cmp)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type type;
			difference_type const len = kerbal::iterator::distance(first, last);

			type * const p = allocator.allocate(len);
			type * k = p;

			struct dealloc_helper
			{
					Allocator & allocator;
					difference_type const & len;
					type * const & p;
					type * & k;

					dealloc_helper(Allocator & allocator, difference_type const & len, type * const & p, type * & k) :
							allocator(allocator), len(len), p(p), k(k)
					{
					}

					~dealloc_helper()
					{
						while (k != p) {
							--k;
							k->~type();
						}
						allocator.deallocate(p, len);
					}
			} auto_deallocator(allocator, len, p, k);

			while (k != p + len) {
				allocator.construct(k);
				++k;
			}

			kerbal::algorithm::merge_sort_afford_buffer(first, last, p, cmp);
		}

		template <typename ForwardIterator, typename Allocator>
		void merge_sort_afford_allocator(ForwardIterator first, ForwardIterator last, Allocator & allocator)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type type;
			kerbal::algorithm::merge_sort_afford_allocator(first, last, allocator, std::less<type>());
		}

		template <typename ForwardIterator, typename Compare>
		void merge_sort(ForwardIterator first, ForwardIterator last, Compare cmp)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type type;
			std::allocator<type> allocator;
			kerbal::algorithm::merge_sort_afford_allocator(first, last, allocator, cmp);
		}

		template <typename ForwardIterator>
		void merge_sort(ForwardIterator first, ForwardIterator last)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type type;
			kerbal::algorithm::merge_sort(first, last, std::less<type>());
		}

		template <typename BidirectionalIterator, typename CompareFunction>
		KERBAL_CONSTEXPR14
		void insertion_sort(BidirectionalIterator first, BidirectionalIterator last, CompareFunction cmp)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			if (first == last) {
				return;
			}

			iterator to_be_inserted(kerbal::iterator::next(first));
			while (to_be_inserted != last) {
				iterator insert_pos(kerbal::algorithm::upper_bound(first, to_be_inserted, *to_be_inserted, cmp));
				if (insert_pos != to_be_inserted) {
					value_type value(kerbal::compatibility::to_xvalue(*to_be_inserted));
					{
						iterator it(to_be_inserted);
						iterator prev(kerbal::iterator::prev(it));
						while (prev != insert_pos) {
							*it = kerbal::compatibility::to_xvalue(*prev);
							--it;
							--prev;
						}
						*it = kerbal::compatibility::to_xvalue(*prev);
					}
					*insert_pos = kerbal::compatibility::to_xvalue(value);
				}
				++to_be_inserted;
			}
		}

		template <typename BidirectionalIterator>
		KERBAL_CONSTEXPR14
		void insertion_sort(BidirectionalIterator first, BidirectionalIterator last)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type type;

			kerbal::algorithm::insertion_sort(first, last, std::less<type>());
		}

		template <typename ForwardIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		ForwardIterator __partition(ForwardIterator first, ForwardIterator last, UnaryPredicate predicate,
				std::forward_iterator_tag)
		{
			while (static_cast<bool>(first != last) && static_cast<bool>(predicate(*first))) {
				++first;
			}
			if (first != last) {
				ForwardIterator adv(kerbal::iterator::next(first));
				while (adv != last) {
					if (predicate(*adv)) {
						std::iter_swap(first, adv);
						++first;
					}
					++adv;
				}
			}
			return first;
		}

		template <typename BidirectionalIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		BidirectionalIterator __partition(BidirectionalIterator first, BidirectionalIterator last, UnaryPredicate predicate,
				std::bidirectional_iterator_tag)
		{
			while (true) {
				while (true) {
					if (first == last) {
						return first;
					} else if (predicate(*first)) {
						++first;
					} else {
						break;
					}
				}
				--last;
				while (true) {
					if (first == last) {
						return first;
					} else if (!bool(predicate(*last))) {
						--last;
					} else {
						break;
					}
				}
				std::iter_swap(first, last);
				++first;
			}
		}

		template <typename ForwardIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		ForwardIterator partition(ForwardIterator first, ForwardIterator last, UnaryPredicate predicate)
		{
			return kerbal::algorithm::__partition(first, last, predicate, kerbal::iterator::iterator_category(first));
		}

		template <typename ForwardIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		ForwardIterator is_partitioned_until(ForwardIterator first, ForwardIterator last, UnaryPredicate p)
		{
			while (static_cast<bool>(first != last) && static_cast<bool>(p(*first))) {
				++first;
			}
			while (static_cast<bool>(first != last) && !static_cast<bool>(p(*first))) {
				++first;
			}
			return first;
		}

		template <typename ForwardIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		bool is_partitioned(ForwardIterator first, ForwardIterator last, UnaryPredicate p)
		{
			return static_cast<bool>(kerbal::algorithm::is_partitioned_until(first, last, p) == last);
		}

		template <typename Iterator, typename CompareFunction>
		struct __quick_sort_U
		{
				typedef Iterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
				typedef const value_type& const_reference;

				const iterator& back;
				CompareFunction& cmp;

				KERBAL_CONSTEXPR __quick_sort_U(const iterator& back, CompareFunction& cmp) KERBAL_NOEXCEPT :
					back(back), cmp(cmp)
				{
				}

				KERBAL_CONSTEXPR bool operator()(const_reference val) const
						KERBAL_CONDITIONAL_NOEXCEPT(noexcept(cmp(val, *back)))
				{
					return cmp(val, *back);
				}
		};

		template <typename BidirectionalIterator, typename CompareFunction>
		KERBAL_CONSTEXPR14
		void quick_sort(BidirectionalIterator first, BidirectionalIterator last, CompareFunction cmp)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			if (first == last) { // distance == 0
				return;
			}

			const iterator back(kerbal::iterator::prev(last));

			{
				difference_type distance(kerbal::iterator::distance(first, back));

				if (distance < 16) {
					kerbal::algorithm::insertion_sort(first, last, cmp);
//					kerbal::algorithm::flag_bubble_sort(first, last, cmp);
					return;
				}

//				difference_type delta((distance + 2147483647UL) * 16807UL % distance);
//				std::iter_swap(back, kerbal::iterator::next(first, delta));

				iterator mid(kerbal::iterator::midden_iterator(first, last));
				std::iter_swap(back, mid);

			}

			const iterator partition_point(kerbal::algorithm::partition(first, back, __quick_sort_U<iterator, CompareFunction>(back, cmp)));

			if (partition_point != back) {
				if (cmp(*back, *partition_point)) {
					std::iter_swap(back, partition_point);
				}
				kerbal::algorithm::quick_sort(first, partition_point, cmp);
				kerbal::algorithm::quick_sort(kerbal::iterator::next(partition_point), last, cmp);
			} else {
				kerbal::algorithm::quick_sort(first, partition_point, cmp);
			}

		}

		template <typename BidirectionalIterator>
		KERBAL_CONSTEXPR14
		void quick_sort(BidirectionalIterator first, BidirectionalIterator last)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type type;

			kerbal::algorithm::quick_sort(first, last, std::less<type>());
		}

		template <typename BidirectionalIterator, typename CompareFunction, typename StackBuffer>
		KERBAL_CONSTEXPR14
		void __nonrecursive_qsort(BidirectionalIterator first, BidirectionalIterator last, CompareFunction cmp)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			StackBuffer st;
			st.push(std::make_pair(first, last));

			while (!st.empty()) {
				const iterator first(st.top().first);
				const iterator last(st.top().second);
				st.pop();

				if (first == last) { // distance == 0
					continue;
				}

				const iterator back(kerbal::iterator::prev(last));

				{
					difference_type distance(kerbal::iterator::distance(first, back));

					if (distance < 16) {
						kerbal::algorithm::bubble_sort(first, last, cmp);
						continue;
					}

					difference_type delta(distance / 2);
					std::iter_swap(back, kerbal::iterator::next(first, delta));
				}

				const iterator partition_point(kerbal::algorithm::partition(first, back, __quick_sort_U<iterator, CompareFunction>(back, cmp)));

				if (partition_point != back) {
					if (cmp(*back, *partition_point)) {
						std::iter_swap(back, partition_point);
					}
					st.push(std::make_pair(kerbal::iterator::next(partition_point), last));
					st.push(std::make_pair(first, partition_point));
				} else {
					st.push(std::make_pair(first, partition_point));
				}

			}
		}

		template <typename BidirectionalIterator, typename CompareFunction>
		void nonrecursive_qsort(BidirectionalIterator first, BidirectionalIterator last, CompareFunction cmp)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type type;

			kerbal::algorithm::__nonrecursive_qsort
				<BidirectionalIterator, CompareFunction, std::stack<std::pair<iterator, iterator> > >
			(first, last, cmp);
		}

		template <typename BidirectionalIterator>
		void nonrecursive_qsort(BidirectionalIterator first, BidirectionalIterator last)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type type;

			kerbal::algorithm::nonrecursive_qsort(first, last, std::less<type>());
		}

		template <typename ForwardIterator, typename CompareFunction>
		KERBAL_CONSTEXPR14
		ForwardIterator is_sorted_until(ForwardIterator first, ForwardIterator last, CompareFunction cmp)
		{
			if (first != last) {
				ForwardIterator nxt(kerbal::iterator::next(first));
				while (nxt != last) {
					if (cmp(*nxt, *first)) { // *first > *nxt
						return nxt;
					}
					first = nxt;
					++nxt;
				}
			}
			return last;
		}

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator is_sorted_until(ForwardIterator first, ForwardIterator last)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type type;
			return kerbal::algorithm::is_sorted_until(first, last, std::less<type>());
		}

		template <typename ForwardIterator, typename CompareFunction>
		KERBAL_CONSTEXPR14
		bool is_sorted(ForwardIterator first, ForwardIterator last, CompareFunction cmp)
		{
			return static_cast<bool>(kerbal::algorithm::is_sorted_until(first, last, cmp) == last);
		}

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		bool is_sorted(ForwardIterator first, ForwardIterator last)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type type;
			return kerbal::algorithm::is_sorted(first, last, std::less<type>());
		}

	} /* namespace algorithm */

} /* namespace kerbal */

#endif	/* End KERBAL_ALGORITHM_SORT_HPP_ */
