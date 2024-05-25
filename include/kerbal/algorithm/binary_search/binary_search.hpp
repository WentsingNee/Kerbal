/**
 * @file       binary_search.hpp
 * @brief
 * @date       2023-08-25
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_BINARY_SEARCH_BINARY_SEARCH_HPP
#define KERBAL_ALGORITHM_BINARY_SEARCH_BINARY_SEARCH_HPP

#include <kerbal/algorithm/binary_search/lower_bound.hpp>
#include <kerbal/compare/binary_type_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>


namespace kerbal
{

	namespace algorithm
	{

		/**
		 *
		 * @param comparator requires: comparator(value_type, T) && comparator(T, value_type)
		 */
		template <typename ForwardIterator, typename T, typename Comparator>
		KERBAL_CONSTEXPR14
		bool binary_search(
			ForwardIterator first, ForwardIterator last, const T & value,
			Comparator comparator
		)
		{
			typedef ForwardIterator iterator;
			iterator lb(kerbal::algorithm::lower_bound(first, last, value, comparator));
			return static_cast<bool>(lb != last) && !static_cast<bool>(comparator(value, *lb));
		}

		template <typename ForwardIterator, typename T>
		KERBAL_CONSTEXPR14
		bool binary_search(ForwardIterator first, ForwardIterator last, const T & value)
		{
			return kerbal::algorithm::binary_search(
				first, last, value,
				kerbal::compare::binary_type_less<void, void>()
			);
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_BINARY_SEARCH_BINARY_SEARCH_HPP
