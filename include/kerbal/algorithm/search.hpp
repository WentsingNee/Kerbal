/*
 * search.hpp
 *
 *  Created on: 2019-4-25
 *      Author: peter
 */

#ifndef KERBAL_ALGORITHM_SEARCH_HPP_
#define KERBAL_ALGORITHM_SEARCH_HPP_

#include <kerbal/algorithm/binary_type_operator.hpp>
#include <kerbal/iterator/iterator.hpp>

namespace kerbal
{
	namespace algorithm
	{

		/**
		 * @brief Binary search algorithm.
		 * @param first       Iterator to the beginning of the range
		 * @param last        Iterator to the end of the range
		 * @param value       The search item
		 * @param comparator  Binary predicate which returns ​true if the first argument is less than
		 *                    (i.e. is ordered before) the second
		 * @return @p first if the search item is less than any other values in the range,
		 * 			  @p last if the item is greater than any other values in the range,
		 * 			  otherwise the returned iterator satisfies the condition that the all items before it are less than
		 * 			  or equal than @p value and the all items after it are greater than or equal than @p value.
		 */
		template <typename ForwardIterator, typename Tp, typename Comparator>
		ForwardIterator
		binary_search(ForwardIterator first, ForwardIterator last, const Tp & value, Comparator comparator)
		{
			typedef ForwardIterator iterator;
			while (first != last) {
				iterator middle = kerbal::iterator::midden_iterator(first, last);
				if (comparator(*middle, value)) { // *middle < value
					first = middle;
					++first;
				} else if (comparator(value, *middle)) { // *middle > value
					last = middle;
				} else { // *middle == value
					return middle;
				}
			}
			return first;
		}

		template <typename ForwardIterator, typename Tp>
		ForwardIterator
		binary_search(ForwardIterator first, ForwardIterator last, const Tp & value)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type type;
			return kerbal::algorithm::binary_search(first, last, value, std::less<type>());
		}

		/**
		 * @return first if value is not in the range and value is less than any values in the range
		 * 			  last if value is not in the range and value is greater than any values in the range
		 */
		template <typename ForwardIterator, typename Tp, typename Comparator>
		ForwardIterator
		__lower_bound(ForwardIterator first, ForwardIterator last, const Tp & value, Comparator comparator,
				std::forward_iterator_tag)
		{
			typedef ForwardIterator iterator;
			while (first != last) {
				iterator middle = kerbal::iterator::midden_iterator(first, last);
				if (comparator(*middle, value)) { // *middle < value
					first = middle;
					++first;
				} else { // *middle >= value
					last = middle;
				}
			}
			return first;
		}

		template <typename RandomAccessIterator, typename Tp, typename Comparator>
		RandomAccessIterator
		__lower_bound(RandomAccessIterator first, RandomAccessIterator last, const Tp & value, Comparator comparator,
				std::random_access_iterator_tag)
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;
			difference_type len(last - first);

			while (len) {
				difference_type step(len >> 1);
				iterator middle(first);
				middle += step;

				if (comparator(*middle, value)) {
					first = ++middle;
					len -= step + 1;
				} else {
					len = step;
				}
			}
			return first;
		}

		template <typename ForwardIterator, typename Tp, typename Comparator>
		ForwardIterator
		lower_bound(ForwardIterator first, ForwardIterator last, const Tp & value, Comparator comparator)
		{
			return kerbal::algorithm::__lower_bound(first, last, value, comparator, kerbal::iterator::iterator_category(first));
		}

		template <typename ForwardIterator, typename Tp>
		ForwardIterator
		lower_bound(ForwardIterator first, ForwardIterator last, const Tp & value)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type type;
			return kerbal::algorithm::lower_bound(first, last, value, kerbal::algorithm::binary_type_less<type, Tp>());
		}

		template <typename ForwardIterator, typename Tp, typename Comparator>
		ForwardIterator
		upper_bound(ForwardIterator first, ForwardIterator last, const Tp & value, Comparator comparator)
		{
			typedef ForwardIterator iterator;
			while (first != last) {
				iterator middle = kerbal::iterator::midden_iterator(first, last);
				if (comparator(value, *middle)) { // *middle > value
					last = middle;
				} else { // *middle <= value, namely !(*middle > value)
					first = middle;
					++first;
				}
			}
			return first;
		}

		template <typename ForwardIterator, typename Tp>
		ForwardIterator
		upper_bound(ForwardIterator first, ForwardIterator last, const Tp & value)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type type;
			return kerbal::algorithm::upper_bound(first, last, value, kerbal::algorithm::binary_type_less<Tp, type>());
		}

		template <typename InputIterator, typename Tp, typename Comparator>
		InputIterator
		__ordered_range_lower_bound(InputIterator first, InputIterator last, const Tp & value, Comparator comparator,
				std::input_iterator_tag)
		{
			while (static_cast<bool>(first != last) &&
					static_cast<bool>(comparator(*first, value))) {
				++first;
			}
			return first;
		}

		template <typename RandomAccessIterator, typename Tp, typename Comparator>
		RandomAccessIterator
		__ordered_range_lower_bound(RandomAccessIterator first, RandomAccessIterator last, const Tp & value, Comparator comparator,
				std::random_access_iterator_tag)
		{
			return kerbal::algorithm::lower_bound(first, last, value, comparator);
		}

		/**
		 * @brief Optimized algorithm for lower_bound.
		 * @details Call kerbal::algorithm::lower_bound if the iterators to range are random access iterator,
		 *             otherwise directly search the range.
		 */
		template <typename InputIterator, typename Tp, typename Comparator>
		InputIterator
		ordered_range_lower_bound(InputIterator first, InputIterator last, const Tp & value, Comparator comparator)
		{
			return kerbal::algorithm::__ordered_range_lower_bound(first, last, value, comparator,
					kerbal::iterator::iterator_category(first));
		}

		template <typename InputIterator, typename Tp>
		InputIterator
		ordered_range_lower_bound(InputIterator first, InputIterator last, const Tp & value)
		{
			typedef InputIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type type;
			return kerbal::algorithm::ordered_range_lower_bound(first, last, value, kerbal::algorithm::binary_type_less<type, Tp>());
		}

		template <typename InputIterator, typename Tp, typename Comparator>
		InputIterator
		__ordered_range_upper_bound(InputIterator first, InputIterator last, const Tp & value, Comparator comparator,
				std::input_iterator_tag)
		{
			while (static_cast<bool>(first != last) && !static_cast<bool>(comparator(value, *first))) {
				// value >= *first
				++first;
			}
			return first;
		}

		template <typename RandomAccessIterator, typename Tp, typename Comparator>
		RandomAccessIterator
		__ordered_range_upper_bound(RandomAccessIterator first, RandomAccessIterator last, const Tp & value, Comparator comparator,
				std::random_access_iterator_tag)
		{
			return kerbal::algorithm::upper_bound(first, last, value, comparator);
		}

		template <typename InputIterator, typename Tp, typename Comparator>
		InputIterator
		ordered_range_upper_bound(InputIterator first, InputIterator last, const Tp & value, Comparator comparator)
		{
			return kerbal::algorithm::__ordered_range_upper_bound(first, last, value, comparator,
					kerbal::iterator::iterator_category(first));
		}

		template <typename InputIterator, typename Tp>
		InputIterator
		ordered_range_upper_bound(InputIterator first, InputIterator last, const Tp & value)
		{
			typedef InputIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type type;
			return kerbal::algorithm::ordered_range_upper_bound(first, last, value, kerbal::algorithm::binary_type_less<Tp, type>());
		}

		template <typename ForwardIterator, typename Tp, typename Comparator>
		ForwardIterator
		__lower_bound_hint(ForwardIterator first, ForwardIterator last, const Tp& value,
				ForwardIterator hint, Comparator comparator, std::forward_iterator_tag)
		{
			typedef ForwardIterator iterator;

			if (hint == last) {
				// hint == last
			} else if (!static_cast<bool>(comparator(*hint, value))) { // *hint >= value
				last = hint; // both are right if last = hint or last = next(hint)
			} else { // *hint < value
				++hint;
				first = hint;
				// for the next, hint != last && *hint < value
				int forward_steps = 1;
				for (int i = 0; i < 3; ++i) {
					kerbal::iterator::advance_at_most(hint, forward_steps, last);
					if (hint == last) {
						break;
					} else if (!static_cast<bool>(comparator(*hint, value))) {
						last = hint;
						break;
					}
					++hint;
					first = hint;
					forward_steps *= 2;
				}
			}
			return kerbal::algorithm::lower_bound(first, last, value, comparator);
		}

		template <typename BidirectionalIterator, typename Tp, typename Comparator>
		BidirectionalIterator
		__lower_bound_hint(BidirectionalIterator first, BidirectionalIterator last, const Tp& value,
				BidirectionalIterator hint, Comparator comparator, std::bidirectional_iterator_tag)
		{
			typedef BidirectionalIterator iterator;

			if (hint == last || comparator(*hint, value) == false) { // hint == last or *hint >= value
				int backward_steps = 1;
				iterator partition_iter(hint);
				for (int i = 0; i < 3; ++i) {
					kerbal::iterator::retreat_at_most(partition_iter, backward_steps, first);
					if (partition_iter == first || comparator(*partition_iter, value) == true) {
						return kerbal::algorithm::lower_bound(partition_iter, hint, value, comparator);
					}
					hint = partition_iter;
					backward_steps *= 2;
				}
				return kerbal::algorithm::lower_bound(first, hint, value, comparator);
			} else {
				// for the next, hint != last && *hint < value
				int forward_steps = 1;
				iterator partition_iter(hint);
				for (int i = 0; i < 3; ++i) {
					kerbal::iterator::advance_at_most(partition_iter, forward_steps, last);
					if (partition_iter == last || comparator(*partition_iter, value) == false) {
						return kerbal::algorithm::lower_bound(hint, partition_iter, value, comparator);
					}
					hint = partition_iter;
					forward_steps *= 2;
				}
				return kerbal::algorithm::lower_bound(hint, last, value, comparator);
			}
		}

		template <typename ForwardIterator, typename Tp, typename Comparator>
		ForwardIterator
		lower_bound_hint(ForwardIterator first, ForwardIterator last, const Tp& value, ForwardIterator hint, Comparator comparator)
		{
			return kerbal::algorithm::__lower_bound_hint(first, last, value, hint, comparator,
					kerbal::iterator::iterator_category(first));
		}

		template <typename ForwardIterator, typename Tp>
		ForwardIterator
		lower_bound_hint(ForwardIterator first, ForwardIterator last, const Tp& value, ForwardIterator hint)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type type;
			return lower_bound_hint(first, last, value, hint, kerbal::algorithm::binary_type_less<type, Tp>());
		}

	} /* namespace algorithm */

} /* namespace kerbal */

#endif /* KERBAL_ALGORITHM_SEARCH_HPP_ */
