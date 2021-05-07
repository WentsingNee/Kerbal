/**
 * @file       find.plain.part.hpp
 * @brief
 * @date       2021-05-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_QUERIER_DETAIL_FIND_FIND_PLAIN_PART_HPP
#define KERBAL_ALGORITHM_QUERIER_DETAIL_FIND_FIND_PLAIN_PART_HPP

#include <kerbal/compatibility/constexpr.hpp>


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			namespace plain
			{

				template <typename InputIterator, typename SentinelIterator, typename T>
				KERBAL_CONSTEXPR14
				InputIterator find(InputIterator first, SentinelIterator last, const T & x)
				{
					while (first != last) {
						if (*first == x) {
							break;
						}
						++first;
					}
					return first;
				}

			} // namespace plain

		} // namespace detail

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_QUERIER_DETAIL_FIND_FIND_PLAIN_PART_HPP
