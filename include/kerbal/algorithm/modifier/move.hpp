/**
 * @file       move.hpp
 * @brief
 * @date       2023-08-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_MODIFIER_MOVE_HPP
#define KERBAL_ALGORITHM_MODIFIER_MOVE_HPP

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

			template <typename InputIterator, typename OutputIterator>
			KERBAL_CONSTEXPR14
			OutputIterator
			move_memmove_opt_dispatcher(
				InputIterator first, InputIterator last, OutputIterator to,
				kerbal::type_traits::false_type
			)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(static_cast<bool>(first != last)) &&
						noexcept(kerbal::assign::generic_assign(*to, kerbal::compatibility::to_xvalue(*first))) &&
						noexcept(++to) &&
						noexcept(++first)
					)
			{
				while (first != last) {
					kerbal::assign::generic_assign(*to, kerbal::compatibility::to_xvalue(*first));
					// *to = kerbal::compatibility::to_xvalue(*first);
					++to;
					++first;
				}
				return to;
			}

#if KERBAL_ALGORITHM_COPY_ENABLE_MEMMOVE_OPTIMIZATION

			template <typename ContiguousIterator, typename ContiguousOutputIterator>
			ContiguousOutputIterator
			move_memmove_opt_dispatcher(
				ContiguousIterator first, ContiguousIterator last, ContiguousOutputIterator to,
				kerbal::type_traits::true_type
			)
			{
				typedef ContiguousIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

				std::size_t dist(last - first);
				std::memmove(&*to, &*first, dist * sizeof(value_type));
				return to + dist;
			}

#endif

		} // namespace detail


		template <typename InputIterator, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator
		move(InputIterator first, InputIterator last, OutputIterator to)
		{

#if KERBAL_ALGORITHM_COPY_ENABLE_MEMMOVE_OPTIMIZATION

			typedef kerbal::algorithm::detail::is_memmove_optimizable<InputIterator, OutputIterator> is_memmove_optimizable;

#	if __cplusplus >= 201402L

#		if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT

			return KERBAL_IS_CONSTANT_EVALUATED() ?
				kerbal::algorithm::detail::move_memmove_opt_dispatcher(first, last, to, kerbal::type_traits::false_type()) :
				kerbal::algorithm::detail::move_memmove_opt_dispatcher(first, last, to, is_memmove_optimizable());

#		else

			return kerbal::algorithm::detail::move_memmove_opt_dispatcher(first, last, to, kerbal::type_traits::false_type());

#		endif

#	else

			return kerbal::algorithm::detail::move_memmove_opt_dispatcher(first, last, to, is_memmove_optimizable());

#	endif

#else
			return kerbal::algorithm::detail::move_memmove_opt_dispatcher(first, last, to, kerbal::type_traits::false_type());
#endif

		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_MODIFIER_MOVE_HPP
