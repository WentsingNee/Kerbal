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

#include <kerbal/assign/generic_assign.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <kerbal/algorithm/modifier/detail/is_memmove_optimizable.hpp>


#if KERBAL_ALGORITHM_COPY_ENABLE_MEMMOVE_OPTIMIZATION
#	include <kerbal/compatibility/is_constant_evaluated.hpp>
#	include <kerbal/iterator/iterator_traits.hpp>

#	include <cstddef>
#	include <cstring>
#endif


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			template <typename BidirectionalIterator, typename BidirectionalOutputIterator>
			KERBAL_CONSTEXPR14
			BidirectionalOutputIterator
			move_backward_memmove_opt_dispatcher(
				BidirectionalIterator first, BidirectionalIterator last, BidirectionalOutputIterator to_last,
				kerbal::type_traits::false_type
			)
				KERBAL_CONDITIONAL_NOEXCEPT(
					noexcept(static_cast<bool>(first != last)) &&
					noexcept(--last) &&
					noexcept(--to_last) &&
					noexcept(kerbal::assign::generic_assign(*to_last, kerbal::compatibility::to_xvalue(*last)))
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

#if KERBAL_ALGORITHM_COPY_ENABLE_MEMMOVE_OPTIMIZATION

			template <typename ContiguousIterator, typename ContiguousOutputIterator>
			ContiguousOutputIterator
			move_backward_memmove_opt_dispatcher(
				ContiguousIterator first, ContiguousIterator last, ContiguousOutputIterator to_last,
				kerbal::type_traits::true_type
			)
			{
				typedef ContiguousIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

				std::size_t dist(last - first);
				ContiguousOutputIterator to_first(to_last - dist);
				std::memmove(&*to_first, &*first, dist * sizeof(value_type));
				return to_first;
			}

#endif

		} // namespace detail


		template <typename BidirectionalIterator, typename BidirectionalOutputIterator>
		KERBAL_CONSTEXPR14
		BidirectionalOutputIterator
		move_backward(BidirectionalIterator first, BidirectionalIterator last, BidirectionalOutputIterator to_last)
		{

#if KERBAL_ALGORITHM_COPY_ENABLE_MEMMOVE_OPTIMIZATION

			typedef kerbal::algorithm::detail::is_memmove_optimizable<BidirectionalIterator, BidirectionalOutputIterator> is_memmove_optimizable;

#	if __cplusplus >= 201402L

#		if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT

			return
				KERBAL_IS_CONSTANT_EVALUATED() ?
				kerbal::algorithm::detail::move_backward_memmove_opt_dispatcher(
					first, last, to_last,
					kerbal::type_traits::false_type()
				) :
				kerbal::algorithm::detail::move_backward_memmove_opt_dispatcher(
					first, last, to_last,
					is_memmove_optimizable()
				)
			;

#		else

			return kerbal::algorithm::detail::move_backward_memmove_opt_dispatcher(
				first, last, to_last,
				kerbal::type_traits::false_type()
			);

#		endif

#	else

			return kerbal::algorithm::detail::move_backward_memmove_opt_dispatcher(
				first, last, to_last,
				is_memmove_optimizable()
			);

#	endif

#else
			return kerbal::algorithm::detail::move_backward_memmove_opt_dispatcher(
				first, last, to_last,
				kerbal::type_traits::false_type()
			);
#endif
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_MODIFIER_MOVE_BACKWARD_HPP
