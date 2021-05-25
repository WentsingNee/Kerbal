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
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/config/exceptions.hpp>

#if __cplusplus >= 201103L && KERBAL_HAS_EXCEPTIONS_SUPPORT
#	include <kerbal/type_traits/is_nothrow_move_constructible.hpp>
#endif


namespace kerbal
{

	namespace algorithm
	{

		template <typename BidirectionalIterator, typename OutputIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		OutputIterator
		copy_backward_if(
			BidirectionalIterator first, BidirectionalIterator last,
			OutputIterator to_last, UnaryPredicate pred
		)
			KERBAL_CONDITIONAL_NOEXCEPT(
				noexcept(static_cast<bool>(first != last)) &&
				noexcept(--last) &&
				noexcept(static_cast<bool>(pred(*last))) &&
				noexcept(--to_last) &&
				noexcept(kerbal::assign::generic_assign(*to_last, *last)) &&
				kerbal::type_traits::try_test_is_nothrow_move_constructible<OutputIterator>::IS_TRUE::value
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
