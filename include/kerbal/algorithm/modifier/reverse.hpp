/**
 * @file       reverse.hpp
 * @brief
 * @date       2023-08-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_MODIFIER_REVERSE_HPP
#define KERBAL_ALGORITHM_MODIFIER_REVERSE_HPP

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/assign/generic_assign.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			template <typename BidirectionalIterator>
			KERBAL_CONSTEXPR14
			void k_reverse(BidirectionalIterator first, BidirectionalIterator last, std::bidirectional_iterator_tag)
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
			void k_reverse(RandomAccessIterator first, RandomAccessIterator last, std::random_access_iterator_tag)
			{
				typedef RandomAccessIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

#		define EACH() do { \
					--last; \
					kerbal::algorithm::iter_swap(first, last); \
					++first; \
				} while (false)

				difference_type trip_count(kerbal::iterator::distance(first, last) >> 1);
				difference_type remain(trip_count & 3);
				for (trip_count >>= 2; trip_count > 0; --trip_count) {
					EACH();
					EACH();
					EACH();
					EACH();
				}

				if (remain >= 2) {
					EACH();
					EACH();
					remain -= 2;
				}
				if (remain >= 1) {
					EACH();
				}

#		undef EACH

			}

		} // namespace detail

		template <typename BidirectionalIterator>
		KERBAL_CONSTEXPR14
		void reverse(BidirectionalIterator first, BidirectionalIterator last)
		{
			kerbal::algorithm::detail::k_reverse(first, last, kerbal::iterator::iterator_category(first));
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_MODIFIER_REVERSE_HPP
