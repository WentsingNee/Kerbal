/**
 * @file       none_of.hpp
 * @brief
 * @date       2023-08-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_QUERIER_NONE_OF_HPP
#define KERBAL_ALGORITHM_QUERIER_NONE_OF_HPP

#include <kerbal/algorithm/querier/any_of.hpp>
#include <kerbal/compatibility/constexpr.hpp>


namespace kerbal
{

	namespace algorithm
	{

		template <typename InputIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		bool none_of(InputIterator first, InputIterator last, UnaryPredicate pred)
		{
			return !kerbal::algorithm::any_of(first, last, pred);
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_QUERIER_NONE_OF_HPP
