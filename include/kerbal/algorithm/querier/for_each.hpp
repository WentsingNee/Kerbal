/**
 * @file       for_each.hpp
 * @brief
 * @date       2021-06-19
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_QUERIER_FOR_EACH_HPP
#define KERBAL_ALGORITHM_QUERIER_FOR_EACH_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/container/nonmember_container_access.hpp>

#include <cstddef>


namespace kerbal
{

	namespace algorithm
	{

		template <typename InputIterator, typename SentinelIterator, typename UnaryFunction>
		KERBAL_CONSTEXPR14
		UnaryFunction
		for_each(InputIterator first, SentinelIterator last, UnaryFunction f)
		{
			while (first != last) {
				f(*first);
				++first;
			}
			return kerbal::compatibility::to_xvalue(f);
		}

		template <typename T, std::size_t N, typename UnaryFunction>
		KERBAL_CONSTEXPR14
		UnaryFunction for_each(T (&a) [N], UnaryFunction f)
		{
			return kerbal::algorithm::for_each(kerbal::container::begin(a), kerbal::container::end(a), f);
		}

		template <typename InputRange, typename UnaryFunction>
		KERBAL_CONSTEXPR14
		UnaryFunction for_each(InputRange & range, UnaryFunction f)
		{
			return kerbal::algorithm::for_each(kerbal::container::begin(range), kerbal::container::end(range), f);
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_QUERIER_FOR_EACH_HPP
