/**
 * @file       heap.hpp
 * @brief
 * @date       2019-9-21
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_HEAP_HPP_
#define KERBAL_ALGORITHM_HEAP_HPP_

#include <kerbal/algorithm/modifiers.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>

namespace kerbal
{

	namespace algorithm
	{

		template <typename RandomAccessIterator>
		KERBAL_CONSTEXPR14
		RandomAccessIterator
		__heap_left_son(RandomAccessIterator first, RandomAccessIterator parent, RandomAccessIterator last, std::random_access_iterator_tag)
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

			difference_type dist(kerbal::iterator::distance(first, parent) + 1);
			if (dist < kerbal::iterator::distance(parent, last)) {
				return kerbal::iterator::next(parent, dist);
			}
			return last;
		}

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator
		__heap_left_son(ForwardIterator first, ForwardIterator parent, ForwardIterator last, std::forward_iterator_tag)
		{
			if (parent == last) {
				return last;
			}

			typedef ForwardIterator iterator;
			iterator adv(kerbal::iterator::next(parent));

			while (first != parent) {
				if (adv != last) {
					++adv;
				} else {
					return last;
				}
				++first;
			}
			return adv;
		}

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator
		__heap_left_son(ForwardIterator first, ForwardIterator parent, ForwardIterator last)
		{
			return kerbal::algorithm::__heap_left_son(first, parent, last, kerbal::iterator::iterator_category(first));
		}

		template <typename ForwardIterator, typename Compare>
		KERBAL_CONSTEXPR14
		void __adjust_top_down(ForwardIterator first, ForwardIterator last, Compare cmp)
		{
			typedef ForwardIterator iterator;

			iterator current_adjust(first);
			iterator left_son(kerbal::algorithm::__heap_left_son(first, current_adjust, last));
			while (left_son != last) {
				iterator right_son(kerbal::iterator::next(left_son));
				if (right_son != last) { // current adjust have both left and right son
					iterator & max_one(cmp(*left_son, *right_son) ? right_son : left_son);
					if (cmp(*current_adjust, *max_one)) { // current < max_one
						kerbal::algorithm::iter_swap(current_adjust, max_one);
						current_adjust = max_one;
						left_son = kerbal::algorithm::__heap_left_son(first, current_adjust, last);
					} else {
						break;
					}
				} else { // current adjust only have left son
					if (cmp(*current_adjust, *left_son)) { // current < left
						kerbal::algorithm::iter_swap(current_adjust, left_son);
					}
					break;
				}
			}
		}

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void __adjust_top_down(ForwardIterator first, ForwardIterator last)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			kerbal::algorithm::__adjust_top_down(first, last, std::less<value_type>());
		}

		template <typename BidirectionalIterator, typename Compare>
		KERBAL_CONSTEXPR14
		void push_heap(BidirectionalIterator first, BidirectionalIterator last, Compare cmp)
		{
			if (first == last) {
				return;
			}
			typedef BidirectionalIterator iterator;
			iterator current_adjust(kerbal::iterator::prev(last));
			while (current_adjust != first) {
				iterator parent(kerbal::iterator::prev(
						kerbal::iterator::midden_iterator(first, kerbal::iterator::next(current_adjust))));
				if (cmp(*parent, *current_adjust)) {
					kerbal::algorithm::iter_swap(parent, current_adjust);
					current_adjust = parent;
				} else {
					break;
				}
			}
		}

		template <typename BidirectionalIterator>
		KERBAL_CONSTEXPR14
		void push_heap(BidirectionalIterator first, BidirectionalIterator last)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			kerbal::algorithm::push_heap(first, last, std::less<value_type>());
		}

		template <typename BidirectionalIterator, typename Compare>
		KERBAL_CONSTEXPR14
		void pop_heap(BidirectionalIterator first, BidirectionalIterator last, Compare cmp)
		{
			if (first != last) {
				--last;
				if (first != last) {
					kerbal::algorithm::iter_swap(first, last);
					kerbal::algorithm::__adjust_top_down(first, last, cmp);
				}
			}
		}

		template <typename BidirectionalIterator>
		KERBAL_CONSTEXPR14
		void pop_heap(BidirectionalIterator first, BidirectionalIterator last)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			kerbal::algorithm::pop_heap(first, last, std::less<value_type>());
		}

		template <typename BidirectionalIterator, typename Compare>
		KERBAL_CONSTEXPR14
		void sort_heap(BidirectionalIterator first, BidirectionalIterator last, Compare cmp)
		{
			typedef BidirectionalIterator iterator;
			if (first == last) {
				return;
			}
			iterator end(kerbal::iterator::next(first));
			while (end != last) {
				--last;
				kerbal::algorithm::iter_swap(first, last);
				kerbal::algorithm::__adjust_top_down(first, last, cmp);
			}
		}

		template <typename BidirectionalIterator>
		KERBAL_CONSTEXPR14
		void sort_heap(BidirectionalIterator first, BidirectionalIterator last)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			kerbal::algorithm::sort_heap(first, last, std::less<value_type>());
		}

		template <typename ForwardIterator, typename Compare>
		KERBAL_CONSTEXPR14
		ForwardIterator
		is_heap_until(ForwardIterator first, ForwardIterator last, Compare cmp)
		{
			typedef ForwardIterator iterator;
			if (first == last) {
				return last;
			}
			iterator son(kerbal::iterator::next(first)); //left son;
			while (son != last) {
				if (cmp(*first, *son)) {
					break;
				}
				++son; //right son
				if (son == last) {
					break;
				}
				if (cmp(*first, *son)) {
					break;
				}
				++son; //left son;
				++first;
			}
			return son;
		}

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator
		is_heap_until(ForwardIterator first, ForwardIterator last)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			return kerbal::algorithm::is_heap_until(first, last, std::less<value_type>());
		}

		template <typename ForwardIterator, typename Compare>
		KERBAL_CONSTEXPR14
		bool is_heap(ForwardIterator first, ForwardIterator last, Compare cmp)
		{
			return kerbal::algorithm::is_heap_until(first, last, cmp) == last;
		}

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		bool is_heap(ForwardIterator first, ForwardIterator last)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			return kerbal::algorithm::is_heap(first, last, std::less<value_type>());
		}

		template <typename BidirectionalIterator, typename Compare>
		KERBAL_CONSTEXPR14
		void make_heap(BidirectionalIterator first, BidirectionalIterator last, Compare cmp)
		{
			typedef BidirectionalIterator iterator;

			iterator current_adjust(first);
			while (current_adjust != last) {
				kerbal::algorithm::push_heap(first, current_adjust);
				++current_adjust;
			}

			/*
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

			if (first == last) {
				return;
			}

			std::pair<iterator, difference_type> p(kerbal::iterator::midden_iterator_with_distance(first, last));
			iterator & i = p.first;
			difference_type & len = p.second;

			iterator left_son(last); //left son;
			if ((len & 1) == 0) { // len is even, the last one is left son
				--i;
				--left_son;
				if (pred(*i, *left_son)) {
					std::iter_swap(i, left_son);
				}
				if (i == first) {
					return;
				}
			}
			iterator right_son(kerbal::iterator::prev(left_son)); //right son;
			left_son = kerbal::iterator::prev(right_son);

			do {
				--i;
				printf("%d %d %d\n", *i, *left_son, *right_son);
				if (pred(*i, *left_son)) {
					std::iter_swap(i, static_cast<bool>(pred(*left_son, *right_son)) ? right_son : left_son);
				} else if (pred(*i, *right_son)) {
					std::iter_swap(i, right_son);
				}
				right_son = kerbal::iterator::prev(left_son);
				left_son = kerbal::iterator::prev(right_son);
			} while (i != first);


			do {
				--i;
				if (pred(*i, *left_son)) {
					std::iter_swap(i, static_cast<bool>(pred(*left_son, *right_son)) ? right_son : left_son);
				} else {
					if (pred(*i, *right_son)) {
						std::iter_swap(i, right_son);
					}
				}
				right_son = kerbal::iterator::prev(left_son);
				left_son = kerbal::iterator::prev(right_son);
			} while (i != first);

			iterator left_son(kerbal::iterator::next(first)); //left son;
				iterator right_son(kerbal::iterator::next(left_son)); //right son;
			while (left_son != last) {
				iterator right_son(kerbal::iterator::next(left_son)); //right son;
				if (right_son == last) {
					if (pred(*first, *left_son)) {
						std::iter_swap(first, left_son);
					}
					break;
				}
				// has right son
				if (pred(*first, *left_son)) {
					std::iter_swap(first, static_cast<bool>(pred(*left_son, *right_son)) ? right_son : left_son);
				} else {
					if (pred(*first, *right_son)) {
						std::iter_swap(first, right_son);
					}
				}
				left_son = kerbal::iterator::next(right_son);
				++first;
			}
			 */

		}

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void make_heap(ForwardIterator first, ForwardIterator last)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			kerbal::algorithm::make_heap(first, last, std::less<value_type>());
		}


	} /* namespace algorithm */

} /* namespace kerbal */

#endif /* KERBAL_ALGORITHM_HEAP_HPP_ */
