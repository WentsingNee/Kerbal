/**
 * @file       rfor_each.hpp
 * @brief
 * @date       2023-08-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_QUERIER_RFOR_EACH_HPP
#define KERBAL_ALGORITHM_QUERIER_RFOR_EACH_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>


namespace kerbal
{

	namespace algorithm
	{

		KERBAL_MODULE_EXPORT
		template <typename BidirectionalIterator, typename UnaryFunction>
		KERBAL_CONSTEXPR14
		UnaryFunction
		rfor_each(BidirectionalIterator first, BidirectionalIterator last, UnaryFunction f)
		{
			while (first != last) {
				--last;
				f(*last);
			}
			return kerbal::compatibility::to_xvalue(f);
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_QUERIER_RFOR_EACH_HPP
