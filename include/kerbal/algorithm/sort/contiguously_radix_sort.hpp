/**
 * @file       contiguously_radix_sort.hpp
 * @brief
 * @date       2020-09-23
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_SORT_CONTIGUOUSLY_RADIX_SORT_HPP
#define KERBAL_ALGORITHM_SORT_CONTIGUOUSLY_RADIX_SORT_HPP

#include <kerbal/algorithm/modifier.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/iterator/iterator.hpp>

#include <climits>
#include <vector>


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			template <typename InputIterator, typename RandomAccessBufferIterator>
			void contiguously_radix_sort_each_round(InputIterator first, InputIterator last, size_t round,
										RandomAccessBufferIterator buffer, size_t each_bucket_cnt[])
			{
				typedef InputIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

				typedef kerbal::type_traits::integral_constant<size_t, 1u << 4u> BUCKETS_CNT;

				kerbal::algorithm::fill(each_bucket_cnt, each_bucket_cnt + BUCKETS_CNT::value, 0);

				for (iterator it(first); it != last; ++it) {
					size_t bucket_id = (*it >> (4 * round)) % BUCKETS_CNT::value;
					++each_bucket_cnt[bucket_id];
				}

				{ // accumulate
					size_t sum = 0;
					for (size_t i = 0; i < BUCKETS_CNT::value; ++i) {
						size_t t = each_bucket_cnt[i];
						each_bucket_cnt[i] = sum;
						sum += t;
					}
				}

				while (first != last) {
					size_t bucket_id = (*first >> (4 * round)) % BUCKETS_CNT::value;
					buffer[each_bucket_cnt[bucket_id]++] = *first;
					++first;
				}
			}

			template <typename InputIterator, bool Order>
			void contiguously_radix_sort(InputIterator first, InputIterator last,
										kerbal::type_traits::integral_constant<bool, Order> /*order*/, std::input_iterator_tag)
			{
				typedef InputIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

				typedef kerbal::type_traits::integral_constant<size_t, 1u << 4u> BUCKETS_CNT;
				typedef kerbal::type_traits::integral_constant<size_t, sizeof(value_type) * CHAR_BIT / 4> ROUNDS;

				std::vector<value_type> buffer(kerbal::iterator::distance(first, last));

				size_t each_bucket_cnt[BUCKETS_CNT::value] = {};

				for (size_t round = 0; round < ROUNDS::value; ++round) {
					contiguously_radix_sort_each_round(first, last, round, buffer.begin(), each_bucket_cnt);
					kerbal::algorithm::copy(buffer.begin(), buffer.end(), first);
				}
			}

			template <typename RandomAccessIterator, bool Order>
			void contiguously_radix_sort(RandomAccessIterator first, RandomAccessIterator last,
										kerbal::type_traits::integral_constant<bool, Order> /*order*/, std::random_access_iterator_tag)
			{
				typedef RandomAccessIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

				typedef kerbal::type_traits::integral_constant<size_t, 1 << 4> BUCKETS_CNT;
				typedef kerbal::type_traits::integral_constant<size_t, sizeof(value_type) * CHAR_BIT / 4> ROUNDS;

				std::vector<value_type> buffer(kerbal::iterator::distance(first, last));

				size_t each_bucket_cnt[BUCKETS_CNT::value] = {};

				for (size_t round = 0; round < ROUNDS::value; round += 2) {
#			if __cplusplus >= 201103L
					contiguously_radix_sort_each_round(first, last, round, buffer.data(), each_bucket_cnt);
					contiguously_radix_sort_each_round(buffer.data(), buffer.data() + buffer.size(), round + 1, first, each_bucket_cnt);
#			else
					contiguously_radix_sort_each_round(first, last, round, buffer.begin(), each_bucket_cnt);
					contiguously_radix_sort_each_round(buffer.begin(), buffer.end(), round + 1, first, each_bucket_cnt);
#			endif
				}

				if (ROUNDS::value % 2 == 1) {
					kerbal::algorithm::copy(buffer.begin(), buffer.end(), first);
				}
			}

			template <typename ForwardIterator, bool Order>
			void contiguously_radix_sort(ForwardIterator first, ForwardIterator last, kerbal::type_traits::integral_constant<bool, Order> order)
			{
				typedef ForwardIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

				kerbal::algorithm::detail::contiguously_radix_sort(first, last, order,
														kerbal::iterator::iterator_category(first));
			}

		} // namespace detail

		template <typename ForwardIterator, typename Order>
		void contiguously_radix_sort(ForwardIterator first, ForwardIterator last, Order /*order*/)
		{
			kerbal::algorithm::detail::contiguously_radix_sort(first, last, kerbal::type_traits::bool_constant<Order::value>());
		}

		template <typename ForwardIterator>
		void contiguously_radix_sort(ForwardIterator first, ForwardIterator last)
		{
			kerbal::algorithm::contiguously_radix_sort(first, last, type_traits::false_type());
		}

	} // namespace algorithm

} // namespace kerbal


#endif // KERBAL_ALGORITHM_SORT_CONTIGUOUSLY_RADIX_SORT_HPP
