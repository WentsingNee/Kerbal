/**
 * @file       reverse.plain.hpp
 * @brief
 * @date       2024-02-17
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_MODIFIER_DETAIL_REVERSE_REVERSE_PLAIN_HPP
#define KERBAL_ALGORITHM_MODIFIER_DETAIL_REVERSE_REVERSE_PLAIN_HPP

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			namespace plain
			{

				template <typename BidirectionalIterator>
				KERBAL_CONSTEXPR14
				void k_reverse_itercate_dispatch(BidirectionalIterator first, BidirectionalIterator last, std::bidirectional_iterator_tag)
				{
					while (first != last) {
						--last;
						if (first != last) {
							kerbal::algorithm::iter_swap(first, last);
							++first;
						} else {
							break;
						}
					}
				}

				template <typename RandomAccessIterator>
				KERBAL_CONSTEXPR14
				void k_reverse_itercate_dispatch(RandomAccessIterator first, RandomAccessIterator last, std::random_access_iterator_tag)
				{
					typedef RandomAccessIterator iterator;
					typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

					difference_type dist(kerbal::iterator::distance(first, last) >> 1);
					for (difference_type i = 0; i < dist; ++i) {
						--last;
						kerbal::algorithm::iter_swap(first, last);
						++first;
					}
				}

				template <typename BidirectionalIterator>
				KERBAL_CONSTEXPR14
				void reverse(BidirectionalIterator first, BidirectionalIterator last)
				{
					kerbal::algorithm::detail::plain::k_reverse_itercate_dispatch(first, last, kerbal::iterator::iterator_category(first));
				}

			} // namespace plain

		} // namespace detail

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_MODIFIER_DETAIL_REVERSE_REVERSE_PLAIN_HPP
