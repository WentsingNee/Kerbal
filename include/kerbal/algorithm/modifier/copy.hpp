/**
 * @file       copy.hpp
 * @brief
 * @date       2023-08-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_MODIFIER_COPY_HPP
#define KERBAL_ALGORITHM_MODIFIER_COPY_HPP

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

			template <typename InputIterator, typename InputIteratorEnd, typename OutputIterator>
			KERBAL_CONSTEXPR14
			OutputIterator
			k_copy(InputIterator first, InputIteratorEnd last, OutputIterator to, std::input_iterator_tag)
				KERBAL_CONDITIONAL_NOEXCEPT(
					noexcept(static_cast<bool>(first != last)) &&
					noexcept(kerbal::assign::generic_assign(*to, *first)) &&
					noexcept(++to) &&
					noexcept(++first)
				)
			{
				while (first != last) {
					kerbal::assign::generic_assign(*to, *first); // *to = *first;
					++to;
					++first;
				}
				return to;
			}

		} // namespace detail

		template <typename InputIterator, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator
		copy(InputIterator first, InputIterator last, OutputIterator to)
		{
			return kerbal::algorithm::detail::k_copy(
				first, last, to,
				kerbal::iterator::iterator_category(first)
			);
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_MODIFIER_COPY_HPP
