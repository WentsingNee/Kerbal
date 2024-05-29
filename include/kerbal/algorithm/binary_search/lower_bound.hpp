/**
 * @file       lower_bound.hpp
 * @brief
 * @date       2023-08-25
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_BINARY_SEARCH_LOWER_BOUND_HPP
#define KERBAL_ALGORITHM_BINARY_SEARCH_LOWER_BOUND_HPP

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
			lower_bound_helper(ForwardIterator first, ForwardIterator last, const T & value, Comparator comparator,
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

			template <typename RandomAccessIterator, typename T, typename Comparator>
			KERBAL_CONSTEXPR14
			RandomAccessIterator
			lower_bound_helper(RandomAccessIterator first, RandomAccessIterator last, const T & value, Comparator comparator,
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
		 * @param comparator requires: comparator(value_type, T)
		 */
		template <typename ForwardIterator, typename T, typename Comparator>
		KERBAL_CONSTEXPR14
		ForwardIterator
		lower_bound(ForwardIterator first, ForwardIterator last, const T & value, Comparator comparator)
		{
			return kerbal::algorithm::detail::lower_bound_helper(first, last, value, comparator, kerbal::iterator::iterator_category(first));
		}

		template <typename ForwardIterator, typename T>
		KERBAL_CONSTEXPR14
		ForwardIterator
		lower_bound(ForwardIterator first, ForwardIterator last, const T & value)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type type;
			return kerbal::algorithm::lower_bound(first, last, value, kerbal::compare::binary_type_less<type, T>());
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_BINARY_SEARCH_LOWER_BOUND_HPP
