/**
 * @file       replace.hpp
 * @brief
 * @date       2023-08-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_MODIFIER_REPLACE_HPP
#define KERBAL_ALGORITHM_MODIFIER_REPLACE_HPP

#include <kerbal/assign/generic_assign.hpp>
#include <kerbal/compatibility/constexpr.hpp>


namespace kerbal
{

	namespace algorithm
	{

		template <typename ForwardIterator, typename T>
		KERBAL_CONSTEXPR14
		void replace(ForwardIterator first, ForwardIterator last, const T & old_val, const T & new_val)
		{
			while (first != last) {
				if (*first == old_val) {
					kerbal::assign::generic_assign(*first, new_val); // *first = new_val;
				}
				++first;
			}
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_MODIFIER_REPLACE_HPP
