/**
 * @file       all_of.hpp
 * @brief
 * @date       2023-08-24
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


namespace kerbal
{

	namespace algorithm
	{

		template <typename InputIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		bool all_of(InputIterator first, InputIterator last, UnaryPredicate pred)
		{
			return static_cast<bool>(kerbal::algorithm::find_if_not(first, last, pred) == last);
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_QUERIER_ALL_OF_HPP
