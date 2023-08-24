/**
 * @file       copy_backward.hpp
 * @brief
 * @date       2023-08-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_MODIFIER_COPY_BACKWARD_HPP
#define KERBAL_ALGORITHM_MODIFIER_COPY_BACKWARD_HPP

#include <kerbal/assign/generic_assign.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
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
			k_copy_backward(BidirectionalIterator first, BidirectionalIterator last, OutputIterator to_last, std::bidirectional_iterator_tag)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(static_cast<bool>(first != last)) &&
						noexcept(--last) &&
						noexcept(--to_last) &&
						noexcept(kerbal::assign::generic_assign(*to_last, *last))
					)
			{
				while (first != last) {
					--last;
					--to_last;
					kerbal::assign::generic_assign(*to_last, *last); // *to_last = *last;
				}
				return to_last;
			}

		} // namespace detail

		template <typename BidirectionalIterator, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator
		copy_backward(BidirectionalIterator first, BidirectionalIterator last, OutputIterator to_last)
		{
			return kerbal::algorithm::detail::k_copy_backward(first, last, to_last, kerbal::iterator::iterator_category(first));
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_MODIFIER_COPY_BACKWARD_HPP
