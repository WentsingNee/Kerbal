/**
 * @file       copy_backward_if.hpp
 * @brief
 * @date       2023-08-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_MODIFIER_COPY_BACKWARD_IF_HPP
#define KERBAL_ALGORITHM_MODIFIER_COPY_BACKWARD_IF_HPP

#include <kerbal/assign/generic_assign.hpp>
#include <kerbal/compatibility/constexpr.hpp>


namespace kerbal
{

	namespace algorithm
	{

		template <typename BidirectionalIterator, typename BidirectionalOutputIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		BidirectionalOutputIterator
		copy_backward_if(
			BidirectionalIterator first, BidirectionalIterator last,
			BidirectionalOutputIterator to_last, UnaryPredicate pred
		)
		{
			while (first != last) {
				--last;
				if (pred(*last)) {
					--to_last;
					kerbal::assign::generic_assign(*to_last, *last); // *to_last = *last;
				}
			}
			return to_last;
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_MODIFIER_COPY_BACKWARD_IF_HPP
