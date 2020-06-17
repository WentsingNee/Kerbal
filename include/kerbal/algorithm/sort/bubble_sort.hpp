/**
 * @file       bubble_sort.hpp
 * @brief
 * @date       2020-5-30, can be traced back to at latest 2017-2-21
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_SORT_BUBBLE_SORT_HPP
#define KERBAL_ALGORITHM_SORT_BUBBLE_SORT_HPP

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/iterator/iterator.hpp>

namespace kerbal
{

	namespace algorithm
	{

		template <typename ForwardIterator, typename Compare>
		KERBAL_CONSTEXPR14
		void bubble_sort(ForwardIterator first, ForwardIterator last, Compare cmp)
		{
			typedef ForwardIterator iterator;

			while (first != last) {
				iterator j(first);
				iterator j_next(kerbal::iterator::next(j));
				while (j_next != last) {
					if (cmp(*j_next, *j)) {
						kerbal::algorithm::iter_swap(j_next, j);
					}
					j = j_next;
					++j_next;
				}
				last = j;
			}
		}

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void bubble_sort(ForwardIterator first, ForwardIterator last)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			kerbal::algorithm::bubble_sort(first, last, std::less<value_type>());
		}


		template <typename ForwardIterator, typename Compare>
		KERBAL_CONSTEXPR14
		void flag_bubble_sort(ForwardIterator first, ForwardIterator last, Compare cmp)
		{
			typedef ForwardIterator iterator;

			bool swit = true;

			while (static_cast<bool>(first != last) && swit) {
				iterator j(first);
				iterator j_next(kerbal::iterator::next(j));
				swit = false;
				while (j_next != last) {
					if (cmp(*j_next, *j)) {
						swit = true;
						kerbal::algorithm::iter_swap(j_next, j);
					}
					j = j_next;
					++j_next;
				}
				last = j;
			}

		}

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void flag_bubble_sort(ForwardIterator first, ForwardIterator last)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			kerbal::algorithm::flag_bubble_sort(first, last, std::less<value_type>());
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_SORT_BUBBLE_SORT_HPP
