/**
 * @file       inplace_merge.hpp
 * @brief
 * @date       2023-08-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_MODIFIER_INPLACE_MERGE_HPP
#define KERBAL_ALGORITHM_MODIFIER_INPLACE_MERGE_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/algorithm/binary_search/lower_bound.hpp>
#include <kerbal/algorithm/binary_search/upper_bound.hpp>
#include <kerbal/algorithm/modifier/rotate.hpp>
#include <kerbal/algorithm/swap.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compare/basic_compare.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			template <typename ForwardIterator, typename BinaryPredict>
			KERBAL_CONSTEXPR14
			void k_inplace_merge_fwd_iter_loop(ForwardIterator first, ForwardIterator mid, ForwardIterator last, BinaryPredict cmp)
			{
				typedef ForwardIterator iterator;

				while (static_cast<bool>(first != mid) && static_cast<bool>(mid != last)) {

					if (kerbal::iterator::next(first) == mid) {
						while (mid != last) {
							if (cmp(*mid, *first)) { // *first > *mid
								kerbal::algorithm::iter_swap(first, mid);
								++first;
								++mid;
							} else {
								break;
							}
						}
						return;
					}

					iterator lmid(kerbal::iterator::midden_iterator(first, mid));
					iterator rmid(kerbal::algorithm::lower_bound(mid, last, *lmid, cmp));
					mid = kerbal::algorithm::rotate(lmid, mid, rmid);
					k_inplace_merge_fwd_iter_loop(first, lmid, mid, cmp);

					first = mid;
					mid = rmid; // kerbal::algorithm::inplace_merge(mid, rmid, last, cmp);
				}
			}

			template <typename ForwardIterator, typename BinaryPredict>
			KERBAL_CONSTEXPR14
			void k_inplace_merge(ForwardIterator first, ForwardIterator mid, ForwardIterator last, BinaryPredict cmp, std::forward_iterator_tag)
			{
				k_inplace_merge_fwd_iter_loop(first, mid, last, cmp);
			}

			template <typename RandomAccessIterator, typename BinaryPredict>
			KERBAL_CONSTEXPR14
			void k_inplace_merge_ras_iter_loop(RandomAccessIterator first, RandomAccessIterator mid, RandomAccessIterator last, BinaryPredict cmp)
			{
				typedef RandomAccessIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

				while (true) {
					difference_type left_len(kerbal::iterator::distance(first, mid));
					difference_type right_len(kerbal::iterator::distance(mid, last));

					if (left_len == 0 || right_len == 0) {
						return;
					}

					if (left_len == 1 && right_len == 1) {
						if (cmp(*mid, *first)) { // *first > *mid
							kerbal::algorithm::iter_swap(first, mid);
						}
						return;
					}

					iterator lmid(first);
					iterator rmid(mid);

					if (left_len >= right_len) {
						lmid = kerbal::iterator::midden_iterator(first, mid);
						rmid = kerbal::algorithm::lower_bound(mid, last, *lmid, cmp);
					} else {
						rmid = kerbal::iterator::midden_iterator(mid, last);
						lmid = kerbal::algorithm::upper_bound(first, mid, *rmid, cmp);
					}
					mid = kerbal::algorithm::rotate(lmid, mid, rmid);
					k_inplace_merge_ras_iter_loop(first, lmid, mid, cmp);

					first = mid;
					mid = rmid; // kerbal::algorithm::inplace_merge(mid, rmid, last, cmp);
				}
			}

			template <typename RandomAccessIterator, typename BinaryPredict>
			KERBAL_CONSTEXPR14
			void k_inplace_merge(RandomAccessIterator first, RandomAccessIterator mid, RandomAccessIterator last, BinaryPredict cmp, std::random_access_iterator_tag)
			{
				k_inplace_merge_ras_iter_loop(first, mid, last, cmp);
			}

		} // namespace detail

		KERBAL_MODULE_EXPORT
		template <typename ForwardIterator, typename BinaryPredict>
		KERBAL_CONSTEXPR14
		void inplace_merge(ForwardIterator first, ForwardIterator mid, ForwardIterator last, BinaryPredict cmp)
		{
			kerbal::algorithm::detail::k_inplace_merge(first, mid, last, cmp, kerbal::iterator::iterator_category(first));
		}

		KERBAL_MODULE_EXPORT
		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void inplace_merge(ForwardIterator first, ForwardIterator mid, ForwardIterator last)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			kerbal::algorithm::inplace_merge(first, mid, last, kerbal::compare::less<value_type>());
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_MODIFIER_INPLACE_MERGE_HPP
