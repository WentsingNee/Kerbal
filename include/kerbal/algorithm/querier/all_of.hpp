/**
 * @file       all_of.hpp
 * @brief
 * @date       2021-06-19
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_QUERIER_ALL_OF_HPP
#define KERBAL_ALGORITHM_QUERIER_ALL_OF_HPP

#include <kerbal/algorithm/querier/find_if_not.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/container/nonmember_container_access.hpp>

#include <cstddef>


namespace kerbal
{

	namespace algorithm
	{

		template <typename InputIterator, typename SentinelIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		bool all_of(InputIterator first, SentinelIterator last, UnaryPredicate pred)
		{
			return static_cast<bool>(kerbal::algorithm::find_if_not(first, last, pred) == last);
		}

		template <typename T, std::size_t N, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		bool all_of(const T (&a) [N], UnaryPredicate pred)
		{
			return kerbal::algorithm::all_of(kerbal::container::begin(a), kerbal::container::end(a), pred);
		}

		template <typename InputRange, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		bool all_of(const InputRange & range, UnaryPredicate pred)
		{
			return kerbal::algorithm::all_of(kerbal::container::begin(range), kerbal::container::end(range), pred);
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_QUERIER_ALL_OF_HPP
