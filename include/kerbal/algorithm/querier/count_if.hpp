/**
 * @file       count_if.hpp
 * @brief
 * @date       2023-08-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_QUERIER_COUNT_IF_HPP
#define KERBAL_ALGORITHM_QUERIER_COUNT_IF_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/compatibility/constexpr.hpp>

#include <cstddef>


namespace kerbal
{

	namespace algorithm
	{

		KERBAL_MODULE_EXPORT
		template <typename InputIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		std::size_t count_if(InputIterator first, InputIterator last, UnaryPredicate pred)
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

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_QUERIER_COUNT_IF_HPP
