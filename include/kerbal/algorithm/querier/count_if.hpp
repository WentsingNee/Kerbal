/**
 * @file       count_if.hpp
 * @brief
 * @date       2021-06-19
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_QUERIER_COUNT_IF_HPP
#define KERBAL_ALGORITHM_QUERIER_COUNT_IF_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/container/nonmember_container_access.hpp>

#include <cstddef>


namespace kerbal
{

	namespace algorithm
	{

		template <typename InputIterator, typename SentinelIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		std::size_t count_if(InputIterator first, SentinelIterator last, UnaryPredicate pred)
		{
			std::size_t cnt = 0;
			while (first != last) {
				if (pred(*first)) {
					++cnt;
				}
				++first;
			}
			return cnt;
		}

		template <typename T, std::size_t N, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		std::size_t count_if(const T (&a) [N], UnaryPredicate pred)
		{
			return kerbal::algorithm::count_if(kerbal::container::begin(a), kerbal::container::end(a), pred);
		}

		template <typename InputRange, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		std::size_t count_if(const InputRange & range, UnaryPredicate pred)
		{
			return kerbal::algorithm::count_if(kerbal::container::begin(range), kerbal::container::end(range), pred);
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_QUERIER_COUNT_IF_HPP
