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
#include <kerbal/container/vector.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/type_traits/sign_deduction.hpp>

#include <climits>


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			inline
			void ctgrs_accu(std::size_t each_bucket_cnt[], std::size_t buckets_cnt, kerbal::type_traits::integral_constant<bool, false> /*asc*/)
			{
				std::size_t sum = 0;
				for (std::size_t i = 0; i < buckets_cnt; ++i) {
					std::size_t t = each_bucket_cnt[i];
					each_bucket_cnt[i] = sum;
					sum += t;
				}
			}

			inline
			void ctgrs_accu(std::size_t each_bucket_cnt[], std::size_t buckets_cnt, kerbal::type_traits::integral_constant<bool, true> /*desc*/)
			{
				std::size_t sum = 0;
				std::size_t i = buckets_cnt;
				while (i != 0) {
					--i;
					std::size_t t = each_bucket_cnt[i];
					each_bucket_cnt[i] = sum;
					sum += t;
				}
			}

			inline
			void ctgrs_signed_final_accu(std::size_t each_bucket_cnt[], std::size_t buckets_cnt, kerbal::type_traits::integral_constant<bool, false> /*asc*/)
			{
				const std::size_t half_cnt = buckets_cnt / 2;
				std::size_t sum = 0;
				std::size_t i = half_cnt;
				for (; i < buckets_cnt; ++i) {
					std::size_t t = each_bucket_cnt[i];
					each_bucket_cnt[i] = sum;
					sum += t;
				}
				for (i = 0; i < half_cnt; ++i) {
					std::size_t t = each_bucket_cnt[i];
					each_bucket_cnt[i] = sum;
					sum += t;
				}
			}

			inline
			void ctgrs_signed_final_accu(std::size_t each_bucket_cnt[], std::size_t buckets_cnt, kerbal::type_traits::integral_constant<bool, true> /*desc*/)
			{
				const std::size_t half_cnt = buckets_cnt / 2;
				std::size_t sum = 0;
				std::size_t i = half_cnt;
				while (i != 0) {
					--i;
					std::size_t t = each_bucket_cnt[i];
					each_bucket_cnt[i] = sum;
					sum += t;
				}
				i = buckets_cnt;
				while (i != half_cnt) {
					--i;
					std::size_t t = each_bucket_cnt[i];
					each_bucket_cnt[i] = sum;
					sum += t;
				}
			}

			template <typename InputIterator, typename RandomAccessBufferIterator, bool Order>
			void ctgrs_each_round(InputIterator first, InputIterator last, std::size_t round,
								  RandomAccessBufferIterator buffer, std::size_t each_bucket_cnt[],
								  kerbal::type_traits::integral_constant<bool, Order> order)
			{
				typedef InputIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

				typedef kerbal::type_traits::integral_constant<std::size_t, 1u << 4u> BUCKETS_CNT;

				for (iterator it(first); it != last; ++it) {
					std::size_t bucket_id = (*it >> (4 * round)) % BUCKETS_CNT::value;
					++each_bucket_cnt[bucket_id];
				}

				ctgrs_accu(each_bucket_cnt, BUCKETS_CNT::value, order);

				while (first != last) {
					std::size_t bucket_id = (*first >> (4 * round)) % BUCKETS_CNT::value;
					buffer[each_bucket_cnt[bucket_id]++] = *first;
					++first;
				}
			}

			template <typename InputIterator, typename RandomAccessBufferIterator, bool Order>
			void ctgrs_signed_final_round(InputIterator first, InputIterator last, std::size_t round,
										  RandomAccessBufferIterator buffer, std::size_t each_bucket_cnt[],
										  kerbal::type_traits::integral_constant<bool, Order> order)
			{
				typedef InputIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

				typedef kerbal::type_traits::integral_constant<std::size_t, 1u << 4u> BUCKETS_CNT;

				for (iterator it(first); it != last; ++it) {
					std::size_t bucket_id = (*it >> (4 * round)) % BUCKETS_CNT::value;
					++each_bucket_cnt[bucket_id];
				}

				ctgrs_signed_final_accu(each_bucket_cnt, BUCKETS_CNT::value, order);

				while (first != last) {
					std::size_t bucket_id = (*first >> (4 * round)) % BUCKETS_CNT::value;
					buffer[each_bucket_cnt[bucket_id]++] = *first;
					++first;
				}
			}

			template <typename InputIterator, bool Order>
			void ctgrs_impl(InputIterator first, InputIterator last,
							kerbal::type_traits::integral_constant<bool, Order> order,
							kerbal::type_traits::integral_constant<bool, false> /*unsigned */,
							std::input_iterator_tag)
			{
				typedef InputIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

				typedef kerbal::type_traits::integral_constant<std::size_t, 1u << 4u> BUCKETS_CNT;
				typedef kerbal::type_traits::integral_constant<std::size_t, sizeof(value_type) * CHAR_BIT / 4> ROUNDS;

				kerbal::container::vector<value_type> buffer(kerbal::iterator::distance(first, last));

				for (std::size_t round = 0; round < ROUNDS::value; ++round) {
					std::size_t each_bucket_cnt[BUCKETS_CNT::value] = {};
					ctgrs_each_round(first, last, round, &buffer[0], each_bucket_cnt, order);
					kerbal::algorithm::copy(buffer.data(), buffer.data() + buffer.size(), first);
				}
			}

			template <typename RandomAccessIterator, bool Order>
			void ctgrs_impl(RandomAccessIterator first, RandomAccessIterator last,
							kerbal::type_traits::integral_constant<bool, Order> order,
							kerbal::type_traits::integral_constant<bool, false> /*unsigned*/,
							std::random_access_iterator_tag)
			{
				typedef RandomAccessIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

				typedef kerbal::type_traits::integral_constant<std::size_t, 1 << 4> BUCKETS_CNT;
				typedef kerbal::type_traits::integral_constant<std::size_t, sizeof(value_type) * CHAR_BIT / 4> ROUNDS;

				kerbal::container::vector<value_type> buffer(kerbal::iterator::distance(first, last));

				for (std::size_t round = 0; round < ROUNDS::value; round += 2) {
					{
						std::size_t each_bucket_cnt[BUCKETS_CNT::value] = {};
						ctgrs_each_round(first, last, round, &buffer[0], each_bucket_cnt, order);
					}
					{
						std::size_t each_bucket_cnt[BUCKETS_CNT::value] = {};
						ctgrs_each_round(buffer.data(), buffer.data() + buffer.size(), round + 1, first, each_bucket_cnt, order);
					}
				}

				if (ROUNDS::value % 2 == 1) {
					kerbal::algorithm::copy(buffer.data(), buffer.data() + buffer.size(), first);
				}
			}

			template <typename InputIterator, bool Order>
			void ctgrs_impl(InputIterator first, InputIterator last,
							kerbal::type_traits::integral_constant<bool, Order> order,
							kerbal::type_traits::integral_constant<bool, true> /*signed*/,
							std::input_iterator_tag)
			{
				typedef InputIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

				typedef kerbal::type_traits::integral_constant<std::size_t, 1u << 4u> BUCKETS_CNT;
				typedef kerbal::type_traits::integral_constant<std::size_t, sizeof(value_type) * CHAR_BIT / 4> ROUNDS;

				kerbal::container::vector<value_type> buffer(kerbal::iterator::distance(first, last));

				std::size_t round = 0;
				for (; round < ROUNDS::value - 1; ++round) {
					std::size_t each_bucket_cnt[BUCKETS_CNT::value] = {};
					ctgrs_each_round(first, last, round, &buffer[0], each_bucket_cnt, order);
					kerbal::algorithm::copy(buffer.data(), buffer.data() + buffer.size(), first);
				}

				{
					std::size_t each_bucket_cnt[BUCKETS_CNT::value] = {};
					ctgrs_signed_final_round(first, last, round, &buffer[0], each_bucket_cnt, order);
					kerbal::algorithm::copy(buffer.data(), buffer.data() + buffer.size(), first);
				}
			}

			template <typename RandomAccessIterator, bool Order>
			void ctgrs_impl(RandomAccessIterator first, RandomAccessIterator last,
							kerbal::type_traits::integral_constant<bool, Order> order,
							kerbal::type_traits::integral_constant<bool, true> /*signed*/,
							std::random_access_iterator_tag)
			{
				typedef RandomAccessIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

				typedef kerbal::type_traits::integral_constant<std::size_t, 1 << 4> BUCKETS_CNT;
				typedef kerbal::type_traits::integral_constant<std::size_t, sizeof(value_type) * CHAR_BIT / 4> ROUNDS;

				kerbal::container::vector<value_type> buffer(kerbal::iterator::distance(first, last));

				std::size_t round = 0;
				for (; round + 2 < ROUNDS::value; round += 2) {
					{
						std::size_t each_bucket_cnt[BUCKETS_CNT::value] = {};
						ctgrs_each_round(first, last, round, &buffer[0], each_bucket_cnt, order);
					}
					{
						std::size_t each_bucket_cnt[BUCKETS_CNT::value] = {};
						ctgrs_each_round(buffer.data(), buffer.data() + buffer.size(), round + 1, first, each_bucket_cnt, order);
					}
				}

				if (ROUNDS::value % 2 == 1) {
					std::size_t each_bucket_cnt[BUCKETS_CNT::value] = {};
					ctgrs_signed_final_round(first, last, round, &buffer[0], each_bucket_cnt, order);
					kerbal::algorithm::copy(buffer.data(), buffer.data() + buffer.size(), first);
				} else {
					{
						std::size_t each_bucket_cnt[BUCKETS_CNT::value] = {};
						ctgrs_each_round(first, last, round, &buffer[0], each_bucket_cnt, order);
					}
					{
						std::size_t each_bucket_cnt[BUCKETS_CNT::value] = {};
						ctgrs_signed_final_round(buffer.data(), buffer.data() + buffer.size(), round + 1, first, each_bucket_cnt, order);
					}
				}
			}

			template <typename ForwardIterator, bool Order>
			void ctgrs_impl(ForwardIterator first, ForwardIterator last, kerbal::type_traits::integral_constant<bool, Order> order)
			{
				typedef ForwardIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

				kerbal::algorithm::detail::ctgrs_impl(first, last, order, kerbal::type_traits::is_signed<value_type>(),
													  kerbal::iterator::iterator_category(first));
			}

		} // namespace detail

		template <typename ForwardIterator, typename Order>
		void contiguously_radix_sort(ForwardIterator first, ForwardIterator last, Order /*order*/)
		{
			kerbal::algorithm::detail::ctgrs_impl(first, last, kerbal::type_traits::bool_constant<Order::value>());
		}

		template <typename ForwardIterator>
		void contiguously_radix_sort(ForwardIterator first, ForwardIterator last)
		{
			kerbal::algorithm::contiguously_radix_sort(first, last, type_traits::false_type());
		}

	} // namespace algorithm

} // namespace kerbal


#endif // KERBAL_ALGORITHM_SORT_CONTIGUOUSLY_RADIX_SORT_HPP
