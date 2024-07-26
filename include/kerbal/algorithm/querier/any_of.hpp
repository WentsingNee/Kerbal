/**
 * @file       any_of.hpp
 * @brief
 * @date       2023-08-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_QUERIER_ANY_OF_HPP
#define KERBAL_ALGORITHM_QUERIER_ANY_OF_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/algorithm/querier/find_if.hpp>
#include <kerbal/compatibility/constexpr.hpp>


namespace kerbal
{

	namespace algorithm
	{

		KERBAL_MODULE_EXPORT
		template <typename InputIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		bool any_of(InputIterator first, InputIterator last, UnaryPredicate pred)
		{
			return static_cast<bool>(kerbal::algorithm::find_if(first, last, pred) != last);
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_QUERIER_ANY_OF_HPP
