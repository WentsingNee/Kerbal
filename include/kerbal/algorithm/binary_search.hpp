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

#ifndef KERBAL_ALGORITHM_BINARY_SEARCH_HPP
#define KERBAL_ALGORITHM_BINARY_SEARCH_HPP

#include <kerbal/algorithm/querier.hpp>
#include <kerbal/compare/binary_type_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/iterator/iterator.hpp>


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			template <typename ForwardIterator, typename Tp, typename Comparator>
			KERBAL_CONSTEXPR14
			ForwardIterator
			lower_bound_helper(ForwardIterator first, ForwardIterator last, const Tp & value, Comparator comparator,
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
			lower_bound_helper(RandomAccessIterator first, RandomAccessIterator last, const Tp & value, Comparator comparator,
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

		} // namespace detail

		/**
		 * @param comparator requires: comparator(value_type, Tp)
		 */
		template <typename ForwardIterator, typename Tp, typename Comparator>
		KERBAL_CONSTEXPR14
		ForwardIterator
		lower_bound(ForwardIterator first, ForwardIterator last, const Tp & value, Comparator comparator)
		{
			return kerbal::algorithm::detail::lower_bound_helper(first, last, value, comparator, kerbal::iterator::iterator_category(first));
		}

		template <typename ForwardIterator, typename Tp>
		KERBAL_CONSTEXPR14
		ForwardIterator
		lower_bound(ForwardIterator first, ForwardIterator last, const Tp & value)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type type;
			return kerbal::algorithm::lower_bound(first, last, value, kerbal::compare::binary_type_less<type, Tp>());
		}



		template <typename BidirectionalIterator, typename Tp, typename Comparator>
		KERBAL_CONSTEXPR14
		BidirectionalIterator
		lower_bound_backward(BidirectionalIterator first, BidirectionalIterator last, const Tp & value, Comparator comparator)
		{
			while (last != first) {
				--last;
				if (comparator(*last, value)) { // *last < value
					++last;
					return last;
				}
			}
			return last;
		}

		template <typename BidirectionalIterator, typename Tp>
		KERBAL_CONSTEXPR14
		BidirectionalIterator
		lower_bound_backward(BidirectionalIterator first, BidirectionalIterator last, const Tp & value)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type type;
			return kerbal::algorithm::lower_bound_backward(first, last, value, kerbal::compare::binary_type_less<type, Tp>());
		}



		namespace detail
		{

			template <typename ForwardIterator, typename Tp, typename Comparator>
			KERBAL_CONSTEXPR14
			ForwardIterator
			upper_bound_helper(ForwardIterator first, ForwardIterator last, const Tp & value, Comparator comparator,
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
			upper_bound_helper(RandomAccessIterator first, RandomAccessIterator last, const Tp & value, Comparator comparator,
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

		} // namespace detail

		/**
		 *
		 * @param comparator requires: comparator(Tp, value_type)
		 */
		template <typename ForwardIterator, typename Tp, typename Comparator>
		KERBAL_CONSTEXPR14
		ForwardIterator
		upper_bound(ForwardIterator first, ForwardIterator last, const Tp & value, Comparator comparator)
		{
			return kerbal::algorithm::detail::upper_bound_helper(first, last, value, comparator, kerbal::iterator::iterator_category(first));
		}

		template <typename ForwardIterator, typename Tp>
		KERBAL_CONSTEXPR14
		ForwardIterator
		upper_bound(ForwardIterator first, ForwardIterator last, const Tp & value)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type type;
			return kerbal::algorithm::upper_bound(first, last, value, kerbal::compare::binary_type_less<Tp, type>());
		}



		template <typename BidirectionalIterator, typename Tp, typename Comparator>
		KERBAL_CONSTEXPR14
		BidirectionalIterator
		upper_bound_backward(BidirectionalIterator first, BidirectionalIterator last, const Tp & value, Comparator comparator)
		{
			while (last != first) {
				--last;
				if (!static_cast<bool>(comparator(value, *last))) { // *last <= value
					++last;
					return last;
				}
			}
			return last;
		}

		template <typename BidirectionalIterator, typename Tp>
		KERBAL_CONSTEXPR14
		BidirectionalIterator
		upper_bound_backward(BidirectionalIterator first, BidirectionalIterator last, const Tp & value)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type type;
			return kerbal::algorithm::upper_bound_backward(first, last, value, kerbal::compare::binary_type_less<type, Tp>());
		}



		namespace detail
		{

			template <typename ForwardIterator, typename Tp, typename Comparator>
			KERBAL_CONSTEXPR14
			std::pair<ForwardIterator, ForwardIterator>
			equal_range_helper(ForwardIterator first, ForwardIterator last, const Tp & value, Comparator comparator,
								std::forward_iterator_tag)
			{
				ForwardIterator lb(kerbal::algorithm::lower_bound(first, last, value, comparator));
				return std::make_pair(lb, kerbal::algorithm::upper_bound(lb, last, value, comparator));
			}

			template <typename RandomAccessIterator, typename Tp, typename Comparator>
			KERBAL_CONSTEXPR14
			std::pair<RandomAccessIterator, RandomAccessIterator>
			equal_range_helper(RandomAccessIterator first, RandomAccessIterator last, const Tp & value, Comparator comparator,
								std::random_access_iterator_tag)
			{
				typedef RandomAccessIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

				difference_type len(kerbal::iterator::distance(first, last));

				while (len > 0) {
					difference_type half(len >> 1);
					iterator middle(kerbal::iterator::next(first, half));
					if (comparator(*middle, value)) { // *middle < value
						first = kerbal::iterator::next(middle);
						len -= half + 1;
					} else if (comparator(value, *middle)) { // *middle > value
						len = half;
					} else { // *middle == value
						return std::make_pair(
							kerbal::algorithm::lower_bound(first, middle, value, comparator),
							kerbal::algorithm::upper_bound(kerbal::iterator::next(middle),
															kerbal::iterator::next(first, len), value, comparator)
						);
					}
				}

				return std::make_pair(first, first);
			}

		} // namespace detail

		/**
		 *
		 * @param comparator requires: comparator(value_type, Tp) && comparator(Tp, value_type)
		 */
		template <typename ForwardIterator, typename Tp, typename Comparator>
		KERBAL_CONSTEXPR14
		std::pair<ForwardIterator, ForwardIterator>
		equal_range(ForwardIterator first, ForwardIterator last, const Tp & value, Comparator comparator)
		{
			return kerbal::algorithm::detail::equal_range_helper(first, last, value, comparator, kerbal::iterator::iterator_category(first));
		}

		template <typename ForwardIterator, typename Tp>
		KERBAL_CONSTEXPR14
		std::pair<ForwardIterator, ForwardIterator>
		equal_range(ForwardIterator first, ForwardIterator last, const Tp & value)
		{
			return kerbal::algorithm::equal_range(first, last, value, kerbal::compare::binary_type_less<void , void>());
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
			iterator lb(kerbal::algorithm::lower_bound(first, last, value, comparator));
			return static_cast<bool>(lb != last) && !static_cast<bool>(comparator(value, *lb));
		}

		template <typename ForwardIterator, typename Tp>
		KERBAL_CONSTEXPR14
		bool binary_search(ForwardIterator first, ForwardIterator last, const Tp & value)
		{
			return kerbal::algorithm::binary_search(first, last, value, kerbal::compare::binary_type_less<void, void>());
		}



		namespace detail
		{

			template <typename ForwardIterator, typename Tp, typename Comparator>
			KERBAL_CONSTEXPR14
			ForwardIterator
			lower_bound_hint(ForwardIterator first, ForwardIterator last, const Tp& value,
								ForwardIterator hint, Comparator comparator, std::forward_iterator_tag)
			{
				if (hint == last) {
				} else if (comparator(*hint, value)) { // *hint < value
					first = kerbal::iterator::next(hint);
				} else { // *hint >= value
					last = hint; // both are right if last = hint or last = next(hint)
				}
				return kerbal::algorithm::detail::lower_bound_helper(first, last, value, comparator,
																	kerbal::iterator::iterator_category(first));
			}

			template <typename BidirectionalIterator, typename Tp, typename Comparator>
			KERBAL_CONSTEXPR14
			BidirectionalIterator
			lower_bound_hint(BidirectionalIterator first, BidirectionalIterator last, const Tp& value,
								BidirectionalIterator hint, Comparator comparator, std::bidirectional_iterator_tag)
			{
				if (hint == last) {
				} else if (comparator(*hint, value)) { //*hint < value
					++hint;
					return kerbal::algorithm::detail::lower_bound_helper(hint, last, value, comparator,
																		kerbal::iterator::iterator_category(first));
				} else { // *hint >= value
				}
				return kerbal::algorithm::lower_bound_backward(first, hint, value, comparator);
			}

			template <typename RandomAccessIterator, typename Tp, typename Comparator>
			KERBAL_CONSTEXPR14
			RandomAccessIterator
			lower_bound_hint(RandomAccessIterator first, RandomAccessIterator last, const Tp& value,
								RandomAccessIterator hint, Comparator comparator, std::random_access_iterator_tag)
			{
				typedef RandomAccessIterator iterator;

				if (hint == last) {
				} else if (comparator(*hint, value)) { // *hint < value
					++hint;
					if (kerbal::iterator::distance(hint, last) > 4) {
						iterator hint_4(hint + 4);
						if (comparator(*hint_4, value)) { // hint[4] < value
							return kerbal::algorithm::detail::lower_bound_helper(kerbal::iterator::next(hint_4), last, value,
																				comparator, std::random_access_iterator_tag());
						} else {
							last = hint_4;
						}
					}
					return kerbal::algorithm::detail::lower_bound_helper(hint, last, value, comparator, std::forward_iterator_tag());
				} else { //*hint >= value
				}
				if (kerbal::iterator::distance(first, hint) > 4) {
					iterator hint_4(hint - 4);
					if (comparator(*hint_4, value)) { // hint[-4] < value
						first = hint_4;
					} else {
						return kerbal::algorithm::detail::lower_bound_helper(first, hint_4, value, comparator,
																			std::random_access_iterator_tag());
					}
				}
				return kerbal::algorithm::lower_bound_backward(first, hint, value, comparator);
			}

		} // namespace detail

		template <typename ForwardIterator, typename Tp, typename Comparator>
		KERBAL_CONSTEXPR14
		ForwardIterator
		lower_bound_hint(ForwardIterator first, ForwardIterator last, const Tp& value, ForwardIterator hint, Comparator comparator)
		{
			return kerbal::algorithm::detail::lower_bound_hint(first, last, value, hint, comparator,
																kerbal::iterator::iterator_category(first));
		}

		template <typename ForwardIterator, typename Tp>
		KERBAL_CONSTEXPR14
		ForwardIterator
		lower_bound_hint(ForwardIterator first, ForwardIterator last, const Tp& value, ForwardIterator hint)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type type;
			return lower_bound_hint(first, last, value, hint, kerbal::compare::binary_type_less<type, Tp>());
		}



		namespace detail
		{

			template <typename ForwardIterator, typename Tp, typename Comparator>
			KERBAL_CONSTEXPR14
			ForwardIterator
			upper_bound_hint(ForwardIterator first, ForwardIterator last, const Tp& value,
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

			template <typename BidirectionalIterator, typename Tp, typename Comparator>
			KERBAL_CONSTEXPR14
			BidirectionalIterator
			upper_bound_hint(BidirectionalIterator first, BidirectionalIterator last, const Tp& value,
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

			template <typename RandomAccessIterator, typename Tp, typename Comparator>
			KERBAL_CONSTEXPR14
			RandomAccessIterator
			upper_bound_hint(RandomAccessIterator first, RandomAccessIterator last, const Tp& value,
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

		template <typename ForwardIterator, typename Tp, typename Comparator>
		KERBAL_CONSTEXPR14
		ForwardIterator
		upper_bound_hint(ForwardIterator first, ForwardIterator last, const Tp& value, ForwardIterator hint,
						Comparator comparator)
		{
			return kerbal::algorithm::detail::upper_bound_hint(first, last, value, hint, comparator,
																kerbal::iterator::iterator_category(first));
		}

		template <typename ForwardIterator, typename Tp>
		KERBAL_CONSTEXPR14
		ForwardIterator
		upper_bound_hint(ForwardIterator first, ForwardIterator last, const Tp& value, ForwardIterator hint)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type type;
			return upper_bound_hint(first, last, value, hint, kerbal::compare::binary_type_less<Tp, type>());
		}



		template <typename ForwardIterator, typename Tp, typename Comparator>
		KERBAL_CONSTEXPR14
		bool binary_search_hint(ForwardIterator first, ForwardIterator last, const Tp& value, ForwardIterator hint,
								Comparator comparator)
		{
			typedef ForwardIterator iterator;
			iterator lb(kerbal::algorithm::lower_bound_hint(first, last, value, hint, comparator));
			return static_cast<bool>(lb != last) && !static_cast<bool>(comparator(value, *lb));
		}

		template <typename ForwardIterator, typename Tp>
		KERBAL_CONSTEXPR14
		bool binary_search_hint(ForwardIterator first, ForwardIterator last, const Tp & value, ForwardIterator hint)
		{
			return kerbal::algorithm::binary_search_hint(first, last, value, hint, kerbal::compare::binary_type_less<void, void>());
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_BINARY_SEARCH_HPP
