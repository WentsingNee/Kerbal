/**
 * @file       adjacent_find.hpp
 * @brief
 * @date       2023-08-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_QUERIER_ADJACENT_FIND_HPP
#define KERBAL_ALGORITHM_QUERIER_ADJACENT_FIND_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/compare/basic_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>


namespace kerbal
{

	namespace algorithm
	{

		KERBAL_MODULE_EXPORT
		template <typename ForwardIterator, typename BinaryPredicate>
		KERBAL_CONSTEXPR14
		ForwardIterator
		adjacent_find(ForwardIterator first, ForwardIterator last, BinaryPredicate pred)
		{
			if (first != last) {
				ForwardIterator nxt(kerbal::iterator::next(first));
				while (nxt != last) {
					if (pred(*first, *nxt)) {
						break;
					}
					first = nxt;
					++nxt;
				}
			}
			return first;
		}

		KERBAL_MODULE_EXPORT
		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator
		adjacent_find(ForwardIterator first, ForwardIterator last)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			return kerbal::algorithm::adjacent_find(first, last, kerbal::compare::equal_to<value_type>());
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_QUERIER_ADJACENT_FIND_HPP
