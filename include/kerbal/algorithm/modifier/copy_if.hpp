/**
 * @file       copy_if.hpp
 * @brief
 * @date       2023-08-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_MODIFIER_COPY_IF_HPP
#define KERBAL_ALGORITHM_MODIFIER_COPY_IF_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/assign/generic_assign.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>


namespace kerbal
{

	namespace algorithm
	{

		KERBAL_MODULE_EXPORT
		template <typename InputIterator, typename OutputIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		OutputIterator
		copy_if(InputIterator first, InputIterator last, OutputIterator to, UnaryPredicate pred)
			KERBAL_CONDITIONAL_NOEXCEPT(
				noexcept(static_cast<bool>(first != last)) &&
				noexcept(static_cast<bool>(pred(*first))) &&
				noexcept(kerbal::assign::generic_assign(*to, *first)) &&
				noexcept(++to) &&
				noexcept(++first)
			)
		{
			while (first != last) {
				if (pred(*first)) {
					kerbal::assign::generic_assign(*to, *first); // *to = *first;
					++to;
				}
				++first;
			}
			return to;
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_MODIFIER_COPY_IF_HPP
