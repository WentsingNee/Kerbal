/**
 * @file       for_each.hpp
 * @brief
 * @date       2023-08-24
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


namespace kerbal
{

	namespace algorithm
	{

		template <typename InputIterator, typename UnaryFunction>
		KERBAL_CONSTEXPR14
		UnaryFunction
		for_each(InputIterator first, InputIterator last, UnaryFunction f)
		{
			while (first != last) {
				f(*first);
				++first;
			}
			return kerbal::compatibility::to_xvalue(f);
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_QUERIER_FOR_EACH_HPP
