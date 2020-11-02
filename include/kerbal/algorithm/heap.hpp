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

#ifndef KERBAL_ALGORITHM_HEAP_HPP
#define KERBAL_ALGORITHM_HEAP_HPP

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>

namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR14
			ForwardIterator
			heap_left_son(ForwardIterator first, ForwardIterator parent, ForwardIterator last,
							std::forward_iterator_tag)
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

			template <typename RandomAccessIterator>
			KERBAL_CONSTEXPR
			RandomAccessIterator
			heap_left_son(RandomAccessIterator first, RandomAccessIterator parent, RandomAccessIterator last,
							std::random_access_iterator_tag)
			{
				return kerbal::iterator::next_at_most(parent, kerbal::iterator::distance(first, parent) + 1, last);
			}

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR
			ForwardIterator
			heap_left_son(ForwardIterator first, ForwardIterator parent, ForwardIterator last)
			{
				return kerbal::algorithm::detail::heap_left_son(first, parent, last, kerbal::iterator::iterator_category(first));
			}

			/**
			 * @require first != last
			 */
			template <typename ForwardIterator, typename Compare>
			KERBAL_CONSTEXPR14
			void adjust_down_unguarded(ForwardIterator first, ForwardIterator current_adjust, ForwardIterator last,
										Compare cmp, std::forward_iterator_tag)
			{
				typedef ForwardIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

				difference_type step = kerbal::iterator::distance(first, current_adjust);
				iterator left_son(kerbal::algorithm::detail::heap_left_son(first, current_adjust, last));
				while (left_son != last) {
					iterator right_son(kerbal::iterator::next(left_son));
					if (right_son != last) { // current adjust have both left and right son
						bool max_one_is_right = cmp(*left_son, *right_son);
						iterator max_one(max_one_is_right ? right_son : left_son);
						if (cmp(*current_adjust, *max_one)) { // current < max_one
							kerbal::algorithm::iter_swap(current_adjust, max_one);
							current_adjust = max_one;
							step += max_one_is_right;
							left_son = kerbal::iterator::next_at_most(current_adjust, step + 1, last);
							step = step * 2 + 1;
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

			template <typename RandomAccessIterator, typename Compare>
			KERBAL_CONSTEXPR14
			void adjust_down_unguarded(RandomAccessIterator first, RandomAccessIterator current_adjust,
										RandomAccessIterator last, Compare cmp, std::random_access_iterator_tag)
			{
				typedef RandomAccessIterator iterator;

				iterator left_son(kerbal::algorithm::detail::heap_left_son(first, current_adjust, last));
				while (left_son != last) {
					iterator right_son(kerbal::iterator::next(left_son));
					if (right_son != last) { // current adjust have both left and right son
						iterator max_one(cmp(*left_son, *right_son) ? right_son : left_son);
						if (cmp(*current_adjust, *max_one)) { // current < max_one
							kerbal::algorithm::iter_swap(current_adjust, max_one);
							current_adjust = max_one;
							left_son = kerbal::algorithm::detail::heap_left_son(first, current_adjust, last);
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

			template <typename ForwardIterator, typename Compare>
			KERBAL_CONSTEXPR14
			void adjust_down_unguarded(ForwardIterator first, ForwardIterator current_adjust, ForwardIterator last,
										Compare cmp)
			{
				adjust_down_unguarded(first, current_adjust, last, cmp, kerbal::iterator::iterator_category(first));
			}

			/**
			 * @require first != last
			 */
			template <typename ForwardIterator, typename Compare>
			KERBAL_CONSTEXPR14
			void adjust_top_down_unguarded(ForwardIterator first, ForwardIterator last, Compare cmp,
											std::forward_iterator_tag)
			{
				typedef ForwardIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

				iterator current_adjust(first);
				difference_type step = 1;
				iterator left_son(kerbal::iterator::next(current_adjust));
				while (left_son != last) {
					iterator right_son(kerbal::iterator::next(left_son));
					if (right_son != last) { // current adjust have both left and right son
						bool max_one_is_right = cmp(*left_son, *right_son);
						iterator max_one(max_one_is_right ? right_son : left_son);
						if (cmp(*current_adjust, *max_one)) { // current < max_one
							kerbal::algorithm::iter_swap(current_adjust, max_one);
							current_adjust = max_one;
							step += max_one_is_right;
							left_son = kerbal::iterator::next_at_most(current_adjust, step + 1, last);
							step = step * 2 + 1;
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

			/**
			 * @require first != last
			 */
			template <typename RandomAccessIterator, typename Compare>
			KERBAL_CONSTEXPR14
			void adjust_top_down_unguarded(RandomAccessIterator first, RandomAccessIterator last, Compare cmp,
											std::random_access_iterator_tag)
			{
				typedef RandomAccessIterator iterator;

				iterator current_adjust(first);
				iterator left_son(kerbal::iterator::next(current_adjust));
				while (left_son != last) {
					iterator right_son(kerbal::iterator::next(left_son));
					if (right_son != last) { // current adjust have both left and right son
						iterator max_one(cmp(*left_son, *right_son) ? right_son : left_son);
						if (cmp(*current_adjust, *max_one)) { // current < max_one
							kerbal::algorithm::iter_swap(current_adjust, max_one);
							current_adjust = max_one;
							left_son = kerbal::algorithm::detail::heap_left_son(first, current_adjust, last);
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

			template <typename ForwardIterator, typename Compare>
			KERBAL_CONSTEXPR14
			void adjust_top_down_unguarded(ForwardIterator first, ForwardIterator last, Compare cmp)
			{
				kerbal::algorithm::detail::adjust_top_down_unguarded(first, last, cmp, kerbal::iterator::iterator_category(first));
			}

		} // namespace detail

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
					kerbal::algorithm::detail::adjust_top_down_unguarded(first, last, cmp);
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
			iterator next_after_first(kerbal::iterator::next(first));
			while (next_after_first != last) {
				--last;
				kerbal::algorithm::iter_swap(first, last);
				kerbal::algorithm::detail::adjust_top_down_unguarded(first, last, cmp);
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

		namespace detail
		{

			template <typename BidirectionalIterator, typename Compare>
			KERBAL_CONSTEXPR14
			void make_heap(BidirectionalIterator first, BidirectionalIterator last, Compare cmp, std::bidirectional_iterator_tag)
			{
				typedef BidirectionalIterator iterator;

				iterator current_adjust(first);
				while (current_adjust != last) {
					kerbal::algorithm::push_heap(first, current_adjust, cmp);
					++current_adjust;
				}
				kerbal::algorithm::push_heap(first, last, cmp);
			}

			template <typename RandomAccessIterator, typename Compare>
			KERBAL_CONSTEXPR14
			void make_heap(RandomAccessIterator first, RandomAccessIterator last, Compare cmp, std::random_access_iterator_tag)
			{
				typedef RandomAccessIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

				difference_type dist(kerbal::iterator::distance(first, last));

				if (dist == 0) {
					return;
				}

				iterator current_adjust(first + ((dist - 1) / 2));
				if (dist % 2 == 0) {
					iterator back(last - 1);
					if (cmp(*current_adjust, *back)) { //back' < parent back
						kerbal::algorithm::iter_swap(back, current_adjust);
					}
				}

				while (current_adjust != first) {
					--current_adjust;
					kerbal::algorithm::detail::adjust_down_unguarded(first, current_adjust, last, cmp);
				}

			}

		} // namespace detail

		template <typename BidirectionalIterator, typename Compare>
		KERBAL_CONSTEXPR14
		void make_heap(BidirectionalIterator first, BidirectionalIterator last, Compare cmp)
		{
			kerbal::algorithm::detail::make_heap(first, last, cmp, kerbal::iterator::iterator_category(first));
		}

		template <typename BidirectionalIterator>
		KERBAL_CONSTEXPR14
		void make_heap(BidirectionalIterator first, BidirectionalIterator last)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			kerbal::algorithm::make_heap(first, last, std::less<value_type>());
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_HEAP_HPP
