/**
 * @file       find_if_not.hpp
 * @brief
 * @date       2023-08-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_QUERIER_FIND_IF_NOT_HPP
#define KERBAL_ALGORITHM_QUERIER_FIND_IF_NOT_HPP

#include <kerbal/compatibility/constexpr.hpp>


namespace kerbal
{

	namespace algorithm
	{

		template <typename InputIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		InputIterator
		find_if_not(InputIterator first, InputIterator last, UnaryPredicate pred)
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

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_QUERIER_FIND_IF_NOT_HPP
