/**
 * @file       is_sorted.hpp
 * @brief
 * @date       2020-5-30, can be traced back to at latest 2019-8-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_SORT_IS_SORTED_HPP
#define KERBAL_ALGORITHM_SORT_IS_SORTED_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/compare/basic_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/iterator/iterator.hpp>


namespace kerbal
{

	namespace algorithm
	{

		KERBAL_MODULE_EXPORT
		template <typename ForwardIterator, typename Compare>
		KERBAL_CONSTEXPR14
		ForwardIterator is_sorted_until(ForwardIterator first, ForwardIterator last, Compare cmp)
		{
			if (first != last) {
				ForwardIterator nxt(kerbal::iterator::next(first));
				while (nxt != last) {
					if (cmp(*nxt, *first)) { // *first > *nxt
						return nxt;
					}
					first = nxt;
					++nxt;
				}
			}
			return last;
		}

		KERBAL_MODULE_EXPORT
		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator is_sorted_until(ForwardIterator first, ForwardIterator last)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			return kerbal::algorithm::is_sorted_until(first, last, kerbal::compare::less<value_type>());
		}

		KERBAL_MODULE_EXPORT
		template <typename ForwardIterator, typename Compare>
		KERBAL_CONSTEXPR14
		bool is_sorted(ForwardIterator first, ForwardIterator last, Compare cmp)
		{
			return static_cast<bool>(kerbal::algorithm::is_sorted_until(first, last, cmp) == last);
		}

		KERBAL_MODULE_EXPORT
		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		bool is_sorted(ForwardIterator first, ForwardIterator last)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			return kerbal::algorithm::is_sorted(first, last, kerbal::compare::less<value_type>());
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_SORT_IS_SORTED_HPP
