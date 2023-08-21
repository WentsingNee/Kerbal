/**
 * @file       merge_sort_merge.hpp
 * @brief
 * @date       2020-7-12
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_SORT_DETAIL_MERGE_SORT_MERGE_HPP
#define KERBAL_ALGORITHM_SORT_DETAIL_MERGE_SORT_MERGE_HPP

#include <kerbal/algorithm/modifier.hpp>
#include <kerbal/assign/generic_assign.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			template <typename ForwardIterator1, typename ForwardIterator2, typename Compare>
			KERBAL_CONSTEXPR14
			void merge_sort_merge(ForwardIterator1 buffer_first, ForwardIterator1 buffer_last,
									ForwardIterator2 mid, ForwardIterator2 last,
									ForwardIterator2 to, Compare cmp)
											KERBAL_CONDITIONAL_NOEXCEPT(
													noexcept(static_cast<bool>(buffer_first != buffer_last)) &&
													noexcept(static_cast<bool>(mid != last)) &&
													noexcept(static_cast<bool>(cmp(*mid, *buffer_first))) &&
													noexcept(kerbal::assign::generic_assign(*to, *mid)) &&
													noexcept(++to) &&
													noexcept(++mid) &&
													noexcept(kerbal::assign::generic_assign(*to, *buffer_first)) &&
													noexcept(++buffer_first) &&
													noexcept(kerbal::algorithm::copy(buffer_first, buffer_last, to))
											)
			{
				while (buffer_first != buffer_last) {
					if (mid != last) {
						if (cmp(*mid, *buffer_first)) { // mid < buffer_first
							kerbal::assign::generic_assign(*to, *mid); // *to = *mid;
							++to;
							++mid;
						} else { // b >= buffer_first
							kerbal::assign::generic_assign(*to, *buffer_first); // *to = *buffer_first;
							++to;
							++buffer_first;
						}
					} else {
						kerbal::algorithm::copy(buffer_first, buffer_last, to);
						return;
					}
				}
			}

		} // namespace detail

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_SORT_DETAIL_MERGE_SORT_MERGE_HPP
