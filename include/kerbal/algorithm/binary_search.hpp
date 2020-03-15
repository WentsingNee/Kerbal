/**
 * @file       binary_search.hpp
 * @brief
 * @date       2019-4-25
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_BINARY_SEARCH_HPP_
#define KERBAL_ALGORITHM_BINARY_SEARCH_HPP_

#include <kerbal/algorithm/binary_type_predicate.hpp>
#include <kerbal/algorithm/querier.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/iterator/iterator.hpp>


namespace kerbal
{
	namespace algorithm
	{

		template <typename ForwardIterator, typename Tp, typename Comparator>
		KERBAL_CONSTEXPR14
		ForwardIterator
		__lower_bound(ForwardIterator first, ForwardIterator last, const Tp & value, Comparator comparator,
					  std::forward_iterator_tag)
		{
			while (static_cast<bool>(first != last) &&
				   static_cast<bool>(comparator(*first, value))) {
				++first;
			}
			return first;

			/*
			typedef ForwardIterator iterator;
			while (first != last) {
				iterator middle = kerbal::iterator::midden_iterator(first, last);
				if (comparator(*middle, value)) { // *middle < value
					first = kerbal::iterator::next(middle);
				} else { // *middle >= value
					last = middle;
				}
			}
			return first;
			*/
		}

		template <typename RandomAccessIterator, typename Tp, typename Comparator>
		KERBAL_CONSTEXPR14
		RandomAccessIterator
		__lower_bound(RandomAccessIterator first, RandomAccessIterator last, const Tp & value, Comparator comparator,
					  std::random_access_iterator_tag)
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;
			difference_type len(kerbal::iterator::distance(first, last));

			while (len > 0) {
				difference_type half(len >> 1);
				iterator middle(kerbal::iterator::next(first, half));
				if (comparator(*middle, value)) {
					first = kerbal::iterator::next(middle);
					len -= half + 1;
				} else {
					len = half;
				}
			}
			return first;
		}

		/**
		 * @param comparator requires: comparator(value_type, Tp)
		 */
		template <typename ForwardIterator, typename Tp, typename Comparator>
		KERBAL_CONSTEXPR14
		ForwardIterator
		lower_bound(ForwardIterator first, ForwardIterator last, const Tp & value, Comparator comparator)
		{
			return kerbal::algorithm::__lower_bound(first, last, value, comparator, kerbal::iterator::iterator_category(first));
		}

		template <typename ForwardIterator, typename Tp>
		KERBAL_CONSTEXPR14
		ForwardIterator
		lower_bound(ForwardIterator first, ForwardIterator last, const Tp & value)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type type;
			return kerbal::algorithm::lower_bound(first, last, value, kerbal::algorithm::binary_type_less<type, Tp>());
		}

		template <typename ForwardIterator, typename Tp, typename Comparator>
		KERBAL_CONSTEXPR14
		ForwardIterator
		__upper_bound(ForwardIterator first, ForwardIterator last, const Tp & value, Comparator comparator,
					  std::forward_iterator_tag)
		{
			while (static_cast<bool>(first != last) && !static_cast<bool>(comparator(value, *first))) {
				// value >= *first
				++first;
			}
			return first;
		}

		template <typename RandomAccessIterator, typename Tp, typename Comparator>
		KERBAL_CONSTEXPR14
		RandomAccessIterator
		__upper_bound(RandomAccessIterator first, RandomAccessIterator last, const Tp & value, Comparator comparator,
					  std::random_access_iterator_tag)
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

			difference_type len(kerbal::iterator::distance(first, last));

			while (len > 0) {
				difference_type half(len >> 1);
				iterator middle(kerbal::iterator::next(first, half));
				if (comparator(value, *middle)) { // *middle > value
					len = half;
				} else { // *middle <= value, namely !(*middle > value)
					first = kerbal::iterator::next(middle);
					len -= half + 1;
				}
			}
			return first;
		}

		/**
		 *
		 * @param comparator requires: comparator(Tp, value_type)
		 */
		template <typename ForwardIterator, typename Tp, typename Comparator>
		KERBAL_CONSTEXPR14
		ForwardIterator
		upper_bound(ForwardIterator first, ForwardIterator last, const Tp & value, Comparator comparator)
		{
			return kerbal::algorithm::__upper_bound(first, last, value, comparator, kerbal::iterator::iterator_category(first));
		}

		template <typename ForwardIterator, typename Tp>
		KERBAL_CONSTEXPR14
		ForwardIterator
		upper_bound(ForwardIterator first, ForwardIterator last, const Tp & value)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type type;
			return kerbal::algorithm::upper_bound(first, last, value, kerbal::algorithm::binary_type_less<Tp, type>());
		}

		/**
		 *
		 * @param comparator requires: comparator(value_type, Tp) && comparator(Tp, value_type)
		 */
		template <typename ForwardIterator, typename Tp, typename Comparator>
		KERBAL_CONSTEXPR14
		std::pair<ForwardIterator, ForwardIterator>
		equal_range(ForwardIterator first, ForwardIterator last, const Tp & value, Comparator comparator)
		{
			first = kerbal::algorithm::lower_bound(first, last, value, comparator);
			return std::make_pair(first, kerbal::algorithm::upper_bound(first, last, value, comparator));
		}

		template <typename ForwardIterator, typename Tp>
		KERBAL_CONSTEXPR14
		std::pair<ForwardIterator, ForwardIterator>
		equal_range(ForwardIterator first, ForwardIterator last, const Tp & value)
		{
			return kerbal::algorithm::equal_range(first, last, value, std::less<Tp>());
		}

		/**
		 *
		 * @param comparator requires: comparator(value_type, Tp) && comparator(Tp, value_type)
		 */
		template <typename ForwardIterator, typename Tp, typename Comparator>
		KERBAL_CONSTEXPR14
		bool binary_search(ForwardIterator first, ForwardIterator last, const Tp& value, Comparator comparator)
		{
			typedef ForwardIterator iterator;
			iterator __i = kerbal::algorithm::lower_bound(first, last, value, comparator);
			return static_cast<bool>(__i != last) && !static_cast<bool>(comparator(value, *__i));
		}

		template <typename ForwardIterator, typename Tp>
		KERBAL_CONSTEXPR14
		bool binary_search(ForwardIterator first, ForwardIterator last, const Tp & value)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			return kerbal::algorithm::binary_search(first, last, value, std::less<Tp>());
		}


		template <typename ForwardIterator, typename Tp, typename Comparator>
		KERBAL_CONSTEXPR14
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
				first = hint;
			}
			return kerbal::algorithm::__lower_bound(first, last, value, comparator, kerbal::iterator::iterator_category(first));
		}

		template <typename RandomAccessIterator, typename Tp, typename Comparator>
		KERBAL_CONSTEXPR14
		RandomAccessIterator
		__lower_bound_hint(RandomAccessIterator first, RandomAccessIterator last, const Tp& value,
						   RandomAccessIterator hint, Comparator comparator, std::random_access_iterator_tag)
		{
			typedef RandomAccessIterator iterator;

			if (static_cast<bool>(hint == last) || !static_cast<bool>(comparator(*hint, value))) { // hint == last or *hint >= value
				return kerbal::algorithm::lower_bound(first, hint, value, comparator); // both are right if lb(first, hint) or lb(first, hint + 1)
			} else {
				// for the next, hint != last && *hint < value
				++hint;
				if (kerbal::iterator::distance(hint, last) <= 4) {
					return kerbal::algorithm::__lower_bound(hint, last, value, comparator, std::forward_iterator_tag());
				} else if (!static_cast<bool>(comparator(*(hint + 4), value))) { // hint[4] >= value
					return kerbal::algorithm::__lower_bound(hint, hint + 4, value, comparator, std::forward_iterator_tag());
				} else {
					return kerbal::algorithm::__lower_bound(hint + 5, last, value, comparator, std::random_access_iterator_tag());
				}
			}
		}

		template <typename ForwardIterator, typename Tp, typename Comparator>
		KERBAL_CONSTEXPR14
		ForwardIterator
		lower_bound_hint(ForwardIterator first, ForwardIterator last, const Tp& value, ForwardIterator hint, Comparator comparator)
		{
			return kerbal::algorithm::__lower_bound_hint(first, last, value, hint, comparator,
														 kerbal::iterator::iterator_category(first));
		}

		template <typename ForwardIterator, typename Tp>
		KERBAL_CONSTEXPR14
		ForwardIterator
		lower_bound_hint(ForwardIterator first, ForwardIterator last, const Tp& value, ForwardIterator hint)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type type;
			return lower_bound_hint(first, last, value, hint, kerbal::algorithm::binary_type_less<type, Tp>());
		}

	} /* namespace algorithm */

} /* namespace kerbal */

#endif /* KERBAL_ALGORITHM_BINARY_SEARCH_HPP_ */
