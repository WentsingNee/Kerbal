/**
 * @file       move_backward.hpp
 * @brief
 * @date       2023-08-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_MODIFIER_MOVE_BACKWARD_HPP
#define KERBAL_ALGORITHM_MODIFIER_MOVE_BACKWARD_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/assign/generic_assign.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/iterator/iterator_traits.hpp>


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			template <typename BidirectionalIterator, typename OutputIterator>
			KERBAL_CONSTEXPR14
			OutputIterator
			k_move_backward(
				BidirectionalIterator first, BidirectionalIterator last, OutputIterator to_last,
				std::bidirectional_iterator_tag
			)
			{
				while (first != last) {
					--last;
					--to_last;
					kerbal::assign::generic_assign(*to_last, kerbal::compatibility::to_xvalue(*last));
					// *to_last = kerbal::compatibility::to_xvalue(*last);
				}
				return to_last;
			}

		} // namespace detail

		KERBAL_MODULE_EXPORT
		template <typename BidirectionalIterator, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator
		move_backward(BidirectionalIterator first, BidirectionalIterator last, OutputIterator to_last)
		{
			return kerbal::algorithm::detail::k_move_backward(
				first, last, to_last,
				kerbal::iterator::iterator_category(first)
			);
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_MODIFIER_MOVE_BACKWARD_HPP
