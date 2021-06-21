/**
 * @file       find_if_not.hpp
 * @brief
 * @date       2021-06-19
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_QUERIER_FIND_IF_NOT_HPP
#define KERBAL_ALGORITHM_QUERIER_FIND_IF_NOT_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/container/nonmember_container_access.hpp>

#include <cstddef>


namespace kerbal
{

	namespace algorithm
	{

		template <typename InputIterator, typename SentinelIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		InputIterator
		find_if_not(InputIterator first, SentinelIterator last, UnaryPredicate pred)
		{
			while (first != last) {
				if (pred(*first)) {
					++first;
				} else {
					break;
				}
			}
			return first;
		}

		template <typename T, std::size_t N, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		T* find_if_not(T (&a) [N], UnaryPredicate pred)
		{
			return kerbal::algorithm::find_if_not(kerbal::container::begin(a), kerbal::container::end(a), pred);
		}

		template <typename InputRange, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		typename kerbal::container::range_traits<InputRange>::iterator
		find_if_not(InputRange & range, UnaryPredicate pred)
		{
			return kerbal::algorithm::find_if_not(kerbal::container::begin(range), kerbal::container::end(range), pred);
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_QUERIER_FIND_IF_NOT_HPP
