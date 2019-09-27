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

#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>

namespace kerbal
{
	namespace algorithm
	{

		template <typename ForwardIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		ForwardIterator
		is_heap_until(ForwardIterator first, ForwardIterator last, UnaryPredicate pred)
		{
			typedef ForwardIterator iterator;
			if (first == last) {
				return last;
			}
			iterator son(kerbal::iterator::next(first)); //left son;
			while (son != last) {
				if (pred(*first, *son)) {
					break;
				}
				++son; //right son
				if (son == last) {
					break;
				}
				if (pred(*first, *son)) {
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

		template <typename ForwardIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		bool is_heap(ForwardIterator first, ForwardIterator last, UnaryPredicate pred)
		{
			return kerbal::algorithm::is_heap_until(first, last, pred) == last;
		}

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		bool is_heap(ForwardIterator first, ForwardIterator last)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			return kerbal::algorithm::is_heap(first, last, std::less<value_type>());
		}

		template <typename BidirectionalIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		void make_heap(BidirectionalIterator first, BidirectionalIterator last, UnaryPredicate pred)
		{
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
//
//
//			do {
//				--i;
//				if (pred(*i, *left_son)) {
//					std::iter_swap(i, static_cast<bool>(pred(*left_son, *right_son)) ? right_son : left_son);
//				} else {
//					if (pred(*i, *right_son)) {
//						std::iter_swap(i, right_son);
//					}
//				}
//				right_son = kerbal::iterator::prev(left_son);
//				left_son = kerbal::iterator::prev(right_son);
//			} while (i != first);
//
//			iterator left_son(kerbal::iterator::next(first)); //left son;
//				iterator right_son(kerbal::iterator::next(left_son)); //right son;
//			while (left_son != last) {
//				iterator right_son(kerbal::iterator::next(left_son)); //right son;
//				if (right_son == last) {
//					if (pred(*first, *left_son)) {
//						std::iter_swap(first, left_son);
//					}
//					break;
//				}
//				// has right son
//				if (pred(*first, *left_son)) {
//					std::iter_swap(first, static_cast<bool>(pred(*left_son, *right_son)) ? right_son : left_son);
//				} else {
//					if (pred(*first, *right_son)) {
//						std::iter_swap(first, right_son);
//					}
//				}
//				left_son = kerbal::iterator::next(right_son);
//				++first;
//			}
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
