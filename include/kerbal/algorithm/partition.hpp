/**
 * @file       partition.hpp
 * @brief
 * @date       2020-07-22
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_PARTITION_HPP
#define KERBAL_ALGORITHM_PARTITION_HPP

#include <kerbal/algorithm/querier.hpp>
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

			template <typename ForwardIterator, typename UnaryPredicate>
			KERBAL_CONSTEXPR14
			ForwardIterator
			partition(ForwardIterator first, ForwardIterator last,
						UnaryPredicate pred, std::forward_iterator_tag)
			{
				first = kerbal::algorithm::find_if_not(first, last, pred);
				if (first != last) {
					ForwardIterator adv(kerbal::iterator::next(first));
					while (adv != last) {
						if (pred(*adv)) {
							kerbal::algorithm::iter_swap(first, adv);
							++first;
						}
						++adv;
					}
				}
				return first;
			}

			template <typename BidirectionalIterator, typename UnaryPredicate>
			KERBAL_CONSTEXPR14
			bool partition_move_first_iter(BidirectionalIterator &first, BidirectionalIterator &last,
											 UnaryPredicate &pred, std::bidirectional_iterator_tag)
			{
				while (first != last) {
					if (pred(*first)) {
						++first;
					} else {
						return false;
					}
				}
				return true;
			}

			template <typename BidirectionalIterator, typename UnaryPredicate>
			KERBAL_CONSTEXPR14
			bool partition_move_last_iter(BidirectionalIterator &first, BidirectionalIterator &last,
											UnaryPredicate &pred, std::bidirectional_iterator_tag)
			{
				while (first != last) {
					if (pred(*last)) {
						return false;
					} else {
						--last;
					}
				}
				return true;
			}

			template <typename BidirectionalIterator, typename UnaryPredicate>
			KERBAL_CONSTEXPR14
			BidirectionalIterator
			partition(BidirectionalIterator first, BidirectionalIterator last,
						UnaryPredicate pred, std::bidirectional_iterator_tag)
			{
				while (true) {
					if (kerbal::algorithm::detail::partition_move_first_iter(first, last, pred, kerbal::iterator::iterator_category(first))) {
						return first;
					}
					--last;
					if (kerbal::algorithm::detail::partition_move_last_iter(first, last, pred, kerbal::iterator::iterator_category(first))) {
						return first;
					}
					kerbal::algorithm::iter_swap(first, last);
					++first;
				}
			}

		} // namespace detail

		template <typename ForwardIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		ForwardIterator partition(ForwardIterator first, ForwardIterator last, UnaryPredicate pred)
		{
			return kerbal::algorithm::detail::partition(first, last, pred, kerbal::iterator::iterator_category(first));
		}



		template <typename InputIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		InputIterator is_partitioned_until(InputIterator first, InputIterator last, UnaryPredicate pred)
		{
			first = kerbal::algorithm::find_if_not(first, last, pred);
			return kerbal::algorithm::find_if(first, last, pred);
		}

		template <typename InputIterator, typename UnaryPredicate>
		KERBAL_CONSTEXPR14
		bool is_partitioned(InputIterator first, InputIterator last, UnaryPredicate pred)
		{
			return static_cast<bool>(kerbal::algorithm::is_partitioned_until(first, last, pred) == last);
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_PARTITION_HPP
