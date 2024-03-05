/**
 * @file       equal_range.hpp
 * @brief
 * @date       2023-08-25
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_BINARY_SEARCH_EQUAL_RANGE_HPP
#define KERBAL_ALGORITHM_BINARY_SEARCH_EQUAL_RANGE_HPP

#include <kerbal/algorithm/binary_search/lower_bound.hpp>
#include <kerbal/algorithm/binary_search/upper_bound.hpp>
#include <kerbal/compare/binary_type_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/utility/compressed_pair.hpp>


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			template <typename ForwardIterator, typename Tp, typename Comparator>
			KERBAL_CONSTEXPR14
			kerbal::utility::compressed_pair<ForwardIterator, ForwardIterator>
			equal_range_helper(ForwardIterator first, ForwardIterator last, const Tp & value, Comparator comparator,
								std::forward_iterator_tag)
			{
				ForwardIterator lb(kerbal::algorithm::lower_bound(first, last, value, comparator));
				return kerbal::utility::make_compressed_pair(lb, kerbal::algorithm::upper_bound(lb, last, value, comparator));
			}

			template <typename RandomAccessIterator, typename Tp, typename Comparator>
			KERBAL_CONSTEXPR14
			kerbal::utility::compressed_pair<RandomAccessIterator, RandomAccessIterator>
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
						return kerbal::utility::make_compressed_pair(
							kerbal::algorithm::lower_bound(first, middle, value, comparator),
							kerbal::algorithm::upper_bound(kerbal::iterator::next(middle),
															kerbal::iterator::next(first, len), value, comparator)
						);
					}
				}

				return kerbal::utility::make_compressed_pair(first, first);
			}

		} // namespace detail

		/**
		 *
		 * @param comparator requires: comparator(value_type, Tp) && comparator(Tp, value_type)
		 */
		template <typename ForwardIterator, typename Tp, typename Comparator>
		KERBAL_CONSTEXPR14
		kerbal::utility::compressed_pair<ForwardIterator, ForwardIterator>
		equal_range(ForwardIterator first, ForwardIterator last, const Tp & value, Comparator comparator)
		{
			return kerbal::algorithm::detail::equal_range_helper(first, last, value, comparator, kerbal::iterator::iterator_category(first));
		}

		template <typename ForwardIterator, typename Tp>
		KERBAL_CONSTEXPR14
		kerbal::utility::compressed_pair<ForwardIterator, ForwardIterator>
		equal_range(ForwardIterator first, ForwardIterator last, const Tp & value)
		{
			return kerbal::algorithm::equal_range(first, last, value, kerbal::compare::binary_type_less<void , void>());
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_BINARY_SEARCH_EQUAL_RANGE_HPP
