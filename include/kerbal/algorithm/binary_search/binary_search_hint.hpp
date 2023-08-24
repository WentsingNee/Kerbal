/**
 * @file       binary_search_hint.hpp
 * @brief
 * @date       2023-08-25
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_BINARY_SEARCH_BINARY_SEARCH_HINT_HPP
#define KERBAL_ALGORITHM_BINARY_SEARCH_BINARY_SEARCH_HINT_HPP

#include <kerbal/algorithm/binary_search/lower_bound_hint.hpp>
#include <kerbal/compare/binary_type_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>


namespace kerbal
{

	namespace algorithm
	{

		template <typename ForwardIterator, typename Tp, typename Comparator>
		KERBAL_CONSTEXPR14
		bool binary_search_hint(ForwardIterator first, ForwardIterator last, const Tp& value, ForwardIterator hint,
								Comparator comparator)
		{
			typedef ForwardIterator iterator;
			iterator lb(kerbal::algorithm::lower_bound_hint(first, last, value, hint, comparator));
			return static_cast<bool>(lb != last) && !static_cast<bool>(comparator(value, *lb));
		}

		template <typename ForwardIterator, typename Tp>
		KERBAL_CONSTEXPR14
		bool binary_search_hint(ForwardIterator first, ForwardIterator last, const Tp & value, ForwardIterator hint)
		{
			return kerbal::algorithm::binary_search_hint(first, last, value, hint, kerbal::compare::binary_type_less<void, void>());
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_BINARY_SEARCH_BINARY_SEARCH_HINT_HPP
