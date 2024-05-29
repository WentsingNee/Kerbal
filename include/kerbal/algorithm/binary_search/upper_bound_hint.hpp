/**
 * @file       upper_bound_hint.hpp
 * @brief
 * @date       2023-08-25
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_BINARY_SEARCH_UPPER_BOUND_HINT_HPP
#define KERBAL_ALGORITHM_BINARY_SEARCH_UPPER_BOUND_HINT_HPP

#include <kerbal/algorithm/binary_search/upper_bound.hpp>
#include <kerbal/algorithm/binary_search/upper_bound_backward.hpp>
#include <kerbal/compare/binary_type_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			template <typename ForwardIterator, typename T, typename Comparator>
			KERBAL_CONSTEXPR14
			ForwardIterator
			upper_bound_hint(ForwardIterator first, ForwardIterator last, const T& value,
								ForwardIterator hint, Comparator comparator, std::forward_iterator_tag)
			{
				if (hint == last) {
				} else if (comparator(value, *hint)) { // *hint > value
					last = hint;
				} else { // *hint <= value
					first = kerbal::iterator::next(hint);
				}
				return kerbal::algorithm::detail::upper_bound_helper(first, last, value, comparator,
																	kerbal::iterator::iterator_category(first));
			}

			template <typename BidirectionalIterator, typename T, typename Comparator>
			KERBAL_CONSTEXPR14
			BidirectionalIterator
			upper_bound_hint(BidirectionalIterator first, BidirectionalIterator last, const T& value,
							BidirectionalIterator hint, Comparator comparator, std::bidirectional_iterator_tag)
			{
				if (hint == last) {
				} else if (comparator(value, *hint)) { // *hint > value
				} else { // *hint <= value
					++hint;
					return kerbal::algorithm::detail::upper_bound_helper(hint, last, value, comparator,
																		kerbal::iterator::iterator_category(first));
				}
				return kerbal::algorithm::upper_bound_backward(first, hint, value, comparator);
			}

			template <typename RandomAccessIterator, typename T, typename Comparator>
			KERBAL_CONSTEXPR14
			RandomAccessIterator
			upper_bound_hint(RandomAccessIterator first, RandomAccessIterator last, const T& value,
							RandomAccessIterator hint, Comparator comparator, std::random_access_iterator_tag)
			{
				typedef RandomAccessIterator iterator;

				if (hint == last) {
				} else if (comparator(value, *hint)) { // *hint > value
				} else { //*hint <= value
					++hint;
					if (kerbal::iterator::distance(hint, last) > 4) {
						iterator hint_4(hint + 4);
						if (comparator(value, *hint_4)) { // value < hint[4]
							last = hint_4;
						} else {
							return kerbal::algorithm::detail::upper_bound_helper(kerbal::iterator::next(hint_4), last, value, comparator,
																				std::random_access_iterator_tag());
						}
					}
					return kerbal::algorithm::detail::upper_bound_helper(hint, last, value, comparator, std::forward_iterator_tag());
				}
				if (kerbal::iterator::distance(first, hint) > 4) {
					iterator hint_4(hint - 4);
					if (comparator(value, *hint_4)) { // value < hint[-4]
						return kerbal::algorithm::detail::upper_bound_helper(first, hint_4, value, comparator,
																			std::random_access_iterator_tag());
					} else {
						first = hint_4;
					}
				}
				return kerbal::algorithm::upper_bound_backward(first, hint, value, comparator);
			}

		} // namespace detail

		template <typename ForwardIterator, typename T, typename Comparator>
		KERBAL_CONSTEXPR14
		ForwardIterator
		upper_bound_hint(ForwardIterator first, ForwardIterator last, const T& value, ForwardIterator hint, Comparator comparator)
		{
			return kerbal::algorithm::detail::upper_bound_hint(first, last, value, hint, comparator,
																kerbal::iterator::iterator_category(first));
		}

		template <typename ForwardIterator, typename T>
		KERBAL_CONSTEXPR14
		ForwardIterator
		upper_bound_hint(ForwardIterator first, ForwardIterator last, const T& value, ForwardIterator hint)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type type;
			return upper_bound_hint(first, last, value, hint, kerbal::compare::binary_type_less<T, type>());
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_BINARY_SEARCH_UPPER_BOUND_HINT_HPP
