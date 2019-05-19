/*
 * search.hpp
 *
 *  Created on: 2019年4月25日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_ALGORITHM_SEARCH_HPP_
#define INCLUDE_KERBAL_ALGORITHM_SEARCH_HPP_

#include <kerbal/algorithm/iterator.hpp>
#include <kerbal/algorithm/binary_type_operator.hpp>

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
		template <typename ForwardCompatibleIterator, typename Tp, typename Comparator>
		typename kerbal::type_traits::enable_if<
				kerbal::type_traits::is_forward_compatible_iterator<ForwardCompatibleIterator>::value,
		ForwardCompatibleIterator>::type
		binary_search(ForwardCompatibleIterator first, ForwardCompatibleIterator last, const Tp & value, Comparator comparator)
		{
			typedef ForwardCompatibleIterator iterator;
			while (first != last) {
				iterator middle = kerbal::algorithm::midden_iterator(first, last);
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

		template <typename ForwardCompatibleIterator, typename Tp>
		typename kerbal::type_traits::enable_if<
				kerbal::type_traits::is_forward_compatible_iterator<ForwardCompatibleIterator>::value,
		ForwardCompatibleIterator>::type
		binary_search(ForwardCompatibleIterator first, ForwardCompatibleIterator last, const Tp & value)
		{
			typedef ForwardCompatibleIterator iterator;
			typedef typename std::iterator_traits<iterator>::value_type type;
			return kerbal::algorithm::binary_search(first, last, value, kerbal::algorithm::binary_type_less<type, type>());
		}

		/**
		 * @return first if value is not in the range and value is less than any values in the range
		 * 			  last if value is not in the range and value is greater than any values in the range
		 */
		template <typename ForwardButNotRandomAccessCompatibleIterator, typename Tp, typename Comparator>
		typename kerbal::type_traits::enable_if<
				kerbal::type_traits::is_forward_compatible_iterator<ForwardButNotRandomAccessCompatibleIterator>::value
				&&
				!kerbal::type_traits::is_random_access_compatible_iterator<ForwardButNotRandomAccessCompatibleIterator>::value,
		ForwardButNotRandomAccessCompatibleIterator>::type
		lower_bound(ForwardButNotRandomAccessCompatibleIterator first, ForwardButNotRandomAccessCompatibleIterator last, const Tp & value, Comparator comparator)
		{
			typedef ForwardButNotRandomAccessCompatibleIterator iterator;
			while (first != last) {
				iterator middle = kerbal::algorithm::midden_iterator(first, last);
				if (comparator(*middle, value)) { // *middle < value
					first = middle;
					++first;
				} else { // *middle >= value
					last = middle;
				}
			}
			return first;
		}

		template <typename RandomAccessCompatibleIterator, typename Tp, typename Comparator>
		typename kerbal::type_traits::enable_if<
				kerbal::type_traits::is_random_access_compatible_iterator<RandomAccessCompatibleIterator>::value,
		RandomAccessCompatibleIterator>::type
		lower_bound(RandomAccessCompatibleIterator first, RandomAccessCompatibleIterator last, const Tp & value, Comparator comparator)
		{
			typedef RandomAccessCompatibleIterator iterator;
			typedef typename std::iterator_traits<iterator>::difference_type difference_type;
			difference_type len = static_cast<difference_type>(last - first);

			while (len) {
				difference_type step = len >> 1;
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

		template <typename ForwardCompatibleIterator, typename Tp>
		typename kerbal::type_traits::enable_if<
				kerbal::type_traits::is_forward_compatible_iterator<ForwardCompatibleIterator>::value,
		ForwardCompatibleIterator>::type
		lower_bound(ForwardCompatibleIterator first, ForwardCompatibleIterator last, const Tp & value)
		{
			typedef ForwardCompatibleIterator iterator;
			typedef typename std::iterator_traits<iterator>::value_type type;
			return kerbal::algorithm::lower_bound(first, last, value, kerbal::algorithm::binary_type_less<type, Tp>());
		}

		template <typename ForwardCompatibleIterator, typename Tp, typename Comparator>
		typename kerbal::type_traits::enable_if<
				kerbal::type_traits::is_forward_compatible_iterator<ForwardCompatibleIterator>::value,
		ForwardCompatibleIterator>::type
		upper_bound(ForwardCompatibleIterator first, ForwardCompatibleIterator last, const Tp & value, Comparator comparator)
		{
			typedef ForwardCompatibleIterator iterator;
			while (first != last) {
				iterator middle = kerbal::algorithm::midden_iterator(first, last);
				if (comparator(value, *middle)) { // *middle > value
					last = middle;
				} else { // *middle <= value, namely !(*middle > value)
					first = middle;
					++first;
				}
			}
			return first;
		}

		template <typename ForwardCompatibleIterator, typename Tp>
		typename kerbal::type_traits::enable_if<
				kerbal::type_traits::is_forward_compatible_iterator<ForwardCompatibleIterator>::value,
		ForwardCompatibleIterator>::type
		upper_bound(ForwardCompatibleIterator first, ForwardCompatibleIterator last, const Tp & value)
		{
			typedef ForwardCompatibleIterator iterator;
			typedef typename std::iterator_traits<iterator>::value_type type;
			return kerbal::algorithm::upper_bound(first, last, value, kerbal::algorithm::binary_type_less<Tp, type>());
		}

		template <typename InputButNotRandomAccessCompatibleIterator, typename Tp, typename Comparator>
		typename kerbal::type_traits::enable_if<
			kerbal::type_traits::is_input_compatible_iterator<InputButNotRandomAccessCompatibleIterator>::value
			&&
			!kerbal::type_traits::is_random_access_compatible_iterator<InputButNotRandomAccessCompatibleIterator>::value,
		InputButNotRandomAccessCompatibleIterator>::type
		ordered_range_lower_bound(InputButNotRandomAccessCompatibleIterator first, InputButNotRandomAccessCompatibleIterator last, const Tp & value, Comparator comparator)
		{
			while (first != last) {
				if (comparator(*first, value)) {
					++first;
				} else {
					break;
				}
			}
			return first;
		}

		template <typename RandomAccessCompatibleIterator, typename Tp, typename Comparator>
		typename kerbal::type_traits::enable_if<
				kerbal::type_traits::is_random_access_compatible_iterator<RandomAccessCompatibleIterator>::value,
		RandomAccessCompatibleIterator>::type
		ordered_range_lower_bound(RandomAccessCompatibleIterator first, RandomAccessCompatibleIterator last, const Tp & value, Comparator comparator)
		{
			return kerbal::algorithm::lower_bound(first, last, value, comparator);
		}

		/**
		 * @brief Optimized algorithm for lower_bound.
		 * @details Call kerbal::algorithm::lower_bound if the iterators to range are random access iterator,
		 *             otherwise directly search the range.
		 */
		template <typename InputCompatibleIterator, typename Tp>
		typename kerbal::type_traits::enable_if<
				kerbal::type_traits::is_input_compatible_iterator<InputCompatibleIterator>::value,
		InputCompatibleIterator>::type
		ordered_range_lower_bound(InputCompatibleIterator first, InputCompatibleIterator last, const Tp & value)
		{
			typedef InputCompatibleIterator iterator;
			typedef typename std::iterator_traits<iterator>::value_type type;
			return kerbal::algorithm::ordered_range_lower_bound(first, last, value, kerbal::algorithm::binary_type_less<type, Tp>());
		}

		template <typename InputButNotRandomAccessCompatibleIterator, typename Tp, typename Comparator>
		typename kerbal::type_traits::enable_if<
				kerbal::type_traits::is_input_compatible_iterator<InputButNotRandomAccessCompatibleIterator>::value
				&&
				!kerbal::type_traits::is_random_access_compatible_iterator<InputButNotRandomAccessCompatibleIterator>::value,
		InputButNotRandomAccessCompatibleIterator>::type
		ordered_range_upper_bound(InputButNotRandomAccessCompatibleIterator first, InputButNotRandomAccessCompatibleIterator last, const Tp & value, Comparator comparator)
		{
			while (first != last) {
				if (comparator(value, *first)) { // *first > value
					return first;
				} else {
					++first;
				}
			}
			return last;
		}

		template <typename RandomAccessCompatibleIterator, typename Tp, typename Comparator>
		typename kerbal::type_traits::enable_if<
				kerbal::type_traits::is_random_access_compatible_iterator<RandomAccessCompatibleIterator>::value,
		RandomAccessCompatibleIterator>::type
		ordered_range_upper_bound(RandomAccessCompatibleIterator first, RandomAccessCompatibleIterator last, const Tp & value, Comparator comparator)
		{
			return kerbal::algorithm::upper_bound(first, last, value, comparator);
		}

		template <typename RandomAccessCompatibleIterator, typename Tp>
		typename kerbal::type_traits::enable_if<
				kerbal::type_traits::is_random_access_compatible_iterator<RandomAccessCompatibleIterator>::value,
		RandomAccessCompatibleIterator>::type
		ordered_range_upper_bound(RandomAccessCompatibleIterator first, RandomAccessCompatibleIterator last, const Tp & value)
		{
			typedef RandomAccessCompatibleIterator iterator;
			typedef typename std::iterator_traits<iterator>::value_type type;
			return kerbal::algorithm::ordered_range_upper_bound(first, last, value, kerbal::algorithm::binary_type_less<Tp, type>());
		}

		template <typename ForwardButNotBidirectionalCompatibleIterator, typename Tp, typename Comparator>
		typename kerbal::type_traits::enable_if<
				kerbal::type_traits::is_forward_compatible_iterator<ForwardButNotBidirectionalCompatibleIterator>::value
				&&
				!kerbal::type_traits::is_birectional_compatible_iterator<ForwardButNotBidirectionalCompatibleIterator>::value,
		ForwardButNotBidirectionalCompatibleIterator>::type
		lower_bound_hint(ForwardButNotBidirectionalCompatibleIterator first, ForwardButNotBidirectionalCompatibleIterator last, const Tp& value, ForwardButNotBidirectionalCompatibleIterator hint, Comparator comparator)
		{
//			return kerbal::algorithm::lower_bound(first, last, value, comparator);

			typedef ForwardButNotBidirectionalCompatibleIterator iterator;

			if (hint == last || comparator(*hint, value) == false) { // hint == last or *hint >= value
				return kerbal::algorithm::lower_bound(first, hint, value, comparator);
			}
			// for the next, hint != last && *hint < value
			int forward_steps = 1;
			iterator partition_iter(hint);
			for (int i = 0; i < 3; ++i) {
				kerbal::algorithm::advance_at_most(partition_iter, forward_steps, last);
				if (partition_iter == last || comparator(*partition_iter, value) == false) {
					return kerbal::algorithm::lower_bound(hint, partition_iter, value, comparator);
				}
				hint = partition_iter;
				forward_steps *= 2;
			}
			return kerbal::algorithm::lower_bound(hint, last, value, comparator);
		}

		template <typename BidirectionalCompatibleIterator, typename Tp, typename Comparator>
		typename kerbal::type_traits::enable_if<
				kerbal::type_traits::is_birectional_compatible_iterator<BidirectionalCompatibleIterator>::value,
		BidirectionalCompatibleIterator>::type
		lower_bound_hint(BidirectionalCompatibleIterator first, BidirectionalCompatibleIterator last, const Tp& value, BidirectionalCompatibleIterator hint, Comparator comparator)
		{
//			return kerbal::algorithm::lower_bound(first, last, value, comparator);

			typedef BidirectionalCompatibleIterator iterator;

			if (hint == last || comparator(*hint, value) == false) { // hint == last or *hint >= value
				int backward_steps = 1;
				iterator partition_iter(hint);
				for (int i = 0; i < 3; ++i) {
					kerbal::algorithm::retreat_at_most(partition_iter, backward_steps, first);
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
					kerbal::algorithm::advance_at_most(partition_iter, forward_steps, last);
					if (partition_iter == last || comparator(*partition_iter, value) == false) {
						return kerbal::algorithm::lower_bound(hint, partition_iter, value, comparator);
					}
					hint = partition_iter;
					forward_steps *= 2;
				}
				return kerbal::algorithm::lower_bound(hint, last, value, comparator);
			}
		}

		template <typename ForwardCompatibleIterator, typename Tp>
		typename kerbal::type_traits::enable_if<
				kerbal::type_traits::is_forward_compatible_iterator<ForwardCompatibleIterator>::value,
		ForwardCompatibleIterator>::type
		lower_bound_hint(ForwardCompatibleIterator first, ForwardCompatibleIterator last, const Tp& value, ForwardCompatibleIterator hint)
		{
			typedef ForwardCompatibleIterator iterator;
			typedef typename std::iterator_traits<iterator>::value_type type;
			return lower_bound_hint(first, last, value, hint, kerbal::algorithm::binary_type_less<type, Tp>());
		}

	} /* namespace algorithm */

} /* namespace kerbal */

#endif /* INCLUDE_KERBAL_ALGORITHM_SEARCH_HPP_ */
