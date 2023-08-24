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
#include <kerbal/iterator/iterator_traits.hpp>


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			template <typename InputIterator, typename OutputIterator>
			KERBAL_CONSTEXPR14
			OutputIterator
			k_move(InputIterator first, InputIterator last, OutputIterator to, std::input_iterator_tag)
			{
				 while (first != last) {
					 kerbal::assign::generic_assign(*to, kerbal::compatibility::to_xvalue(*first));
					 // *to = kerbal::compatibility::to_xvalue(*first);
					++to;
					++first;
				 }
				return to;
			}

		} // namespace detail

		template <typename InputIterator, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator
		move(InputIterator first, InputIterator last, OutputIterator to)
		{
			return kerbal::algorithm::detail::k_move(first, last, to, kerbal::iterator::iterator_category(first));
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_MODIFIER_MOVE_HPP
