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
		template <typename ForwardIterator, typename Tp, typename Comparator>
		typename kerbal::type_traits::enable_if<
				kerbal::algorithm::is_compatible_iterator_type_of<ForwardIterator, std::forward_iterator_tag>::value,
				ForwardIterator>::type
		binary_search(ForwardIterator first, ForwardIterator last, const Tp & value, Comparator comparator)
		{
			typedef ForwardIterator iterator;
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

		template <typename ForwardIterator, typename Tp>
		typename kerbal::type_traits::enable_if<
				kerbal::algorithm::is_compatible_iterator_type_of<ForwardIterator, std::forward_iterator_tag>::value,
				ForwardIterator>::type
		binary_search(ForwardIterator first, ForwardIterator last, const Tp & value)
		{
			typedef ForwardIterator iterator;
			typedef typename std::iterator_traits<iterator>::value_type type;
			return kerbal::algorithm::binary_search(first, last, value, kerbal::algorithm::binary_type_less<type, type>());
		}

		/**
		 * @return first if value is not in the range and value is less than any values in the range
		 * 			  last if value is not in the range and value is greater than any values in the range
		 */
		template <typename ForwardIterator, typename Tp, typename Comparator>
		typename kerbal::type_traits::enable_if<
				kerbal::algorithm::is_compatible_iterator_type_of<ForwardIterator, std::forward_iterator_tag>::value,
				ForwardIterator>::type
		lower_bound(ForwardIterator first, ForwardIterator last, const Tp & value, Comparator comparator)
		{
			typedef ForwardIterator iterator;
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

		template <typename ForwardIterator, typename Tp>
		typename kerbal::type_traits::enable_if<
				kerbal::algorithm::is_compatible_iterator_type_of<ForwardIterator, std::forward_iterator_tag>::value,
				ForwardIterator>::type
		lower_bound(ForwardIterator first, ForwardIterator last, const Tp & value)
		{
			typedef ForwardIterator iterator;
			typedef typename std::iterator_traits<iterator>::value_type type;
			return kerbal::algorithm::lower_bound(first, last, value, kerbal::algorithm::binary_type_less<type, Tp>());
		}

		template <typename ForwardIterator, typename Tp, typename Comparator>
		typename kerbal::type_traits::enable_if<
				kerbal::algorithm::is_compatible_iterator_type_of<ForwardIterator, std::forward_iterator_tag>::value,
				ForwardIterator>::type
		upper_bound(ForwardIterator first, ForwardIterator last, const Tp & value, Comparator comparator)
		{
			typedef ForwardIterator iterator;
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

		template <typename ForwardIterator, typename Tp>
		typename kerbal::type_traits::enable_if<
				kerbal::algorithm::is_compatible_iterator_type_of<ForwardIterator, std::forward_iterator_tag>::value,
				ForwardIterator>::type
				upper_bound(ForwardIterator first, ForwardIterator last, const Tp & value)
		{
			typedef ForwardIterator iterator;
			typedef typename std::iterator_traits<iterator>::value_type type;
			return kerbal::algorithm::upper_bound(first, last, value, kerbal::algorithm::binary_type_less<type, Tp>());
		}

		template <typename InputIterator, typename Tp, typename Comparator>
		typename kerbal::type_traits::enable_if<
					kerbal::algorithm::is_compatible_iterator_type_of<InputIterator, std::input_iterator_tag>::value
				&&
					!kerbal::algorithm::is_compatible_iterator_type_of<InputIterator, std::random_access_iterator_tag>::value
				,
				InputIterator>::type
		ordered_range_lower_bound(InputIterator first, InputIterator last, const Tp & value, Comparator comparator)
		{
			typedef InputIterator iterator;
			typedef typename std::iterator_traits<iterator>::value_type type;
			while (first != last) {
				if (comparator(*first, value)) {
					++first;
				} else {
					break;
				}
			}
			return first;
		}

		template <typename RandomAccessIterator, typename Tp, typename Comparator>
		typename kerbal::type_traits::enable_if<
				kerbal::algorithm::is_compatible_iterator_type_of<RandomAccessIterator, std::random_access_iterator_tag>::value,
				RandomAccessIterator>::type
		ordered_range_lower_bound(RandomAccessIterator first, RandomAccessIterator last, const Tp & value, Comparator comparator)
		{
			typedef RandomAccessIterator iterator;
			typedef typename std::iterator_traits<iterator>::value_type type;
			return kerbal::algorithm::lower_bound(first, last, value, comparator);
		}

		/**
		 * @brief Optimized algorithm for lower_bound.
		 * @details Call kerbal::algorithm::lower_bound if the iterators to range are random access iterator,
		 *             otherwise directly search the range.
		 */
		template <typename InputIterator, typename Tp>
		typename kerbal::type_traits::enable_if<
					kerbal::algorithm::is_compatible_iterator_type_of<InputIterator, std::input_iterator_tag>::value
				,
				InputIterator>::type
		ordered_range_lower_bound(InputIterator first, InputIterator last, const Tp & value)
		{
			typedef InputIterator iterator;
			typedef typename std::iterator_traits<iterator>::value_type type;
			return kerbal::algorithm::ordered_range_lower_bound(first, last, value, kerbal::algorithm::binary_type_less<type, Tp>());
		}

		template <typename InputIterator, typename Tp, typename Comparator>
		typename kerbal::type_traits::enable_if<
					kerbal::algorithm::is_compatible_iterator_type_of<InputIterator, std::input_iterator_tag>::value
				&&
					!kerbal::algorithm::is_compatible_iterator_type_of<InputIterator, std::random_access_iterator_tag>::value
				,
				InputIterator>::type
		ordered_range_upper_bound(InputIterator first, InputIterator last, const Tp & value, Comparator comparator)
		{
			typedef InputIterator iterator;
			typedef typename std::iterator_traits<iterator>::value_type type;
			while (first != last) {
				if (comparator(value, *first)) { // *first > value
					return first;
				} else {
					++first;
				}
			}
			return last;
		}

		template <typename RandomAccessIterator, typename Tp, typename Comparator>
		typename kerbal::type_traits::enable_if<
				kerbal::algorithm::is_compatible_iterator_type_of<RandomAccessIterator, std::random_access_iterator_tag>::value,
				RandomAccessIterator>::type
		ordered_range_upper_bound(RandomAccessIterator first, RandomAccessIterator last, const Tp & value, Comparator comparator)
		{
			typedef RandomAccessIterator iterator;
			typedef typename std::iterator_traits<iterator>::value_type type;
			return kerbal::algorithm::upper_bound(first, last, value, comparator);
		}

		template <typename InputIterator, typename Tp>
		typename kerbal::type_traits::enable_if<
					kerbal::algorithm::is_compatible_iterator_type_of<InputIterator, std::input_iterator_tag>::value
				&&
					!kerbal::algorithm::is_compatible_iterator_type_of<InputIterator, std::random_access_iterator_tag>::value
				,
				InputIterator>::type
		ordered_range_upper_bound(InputIterator first, InputIterator last, const Tp & value)
		{
			typedef InputIterator iterator;
			typedef typename std::iterator_traits<iterator>::value_type type;
			return kerbal::algorithm::ordered_range_upper_bound(first, last, value, kerbal::algorithm::binary_type_less<Tp, type>());
			return last;
		}


	} /* namespace algorithm */

} /* namespace kerbal */

#endif /* INCLUDE_KERBAL_ALGORITHM_SEARCH_HPP_ */
