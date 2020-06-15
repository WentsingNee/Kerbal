/**
 * @file       radix_sort.hpp
 * @brief
 * @date       2020-5-30, can be traced back to at latest 2020-4-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_SORT_RADIX_SORT_HPP
#define KERBAL_ALGORITHM_SORT_RADIX_SORT_HPP

#include <kerbal/algorithm/modifier.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/type_traits/sign_deduction.hpp>

#include <vector>

namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			template <typename ForwardIterator>
			void __radix_sort_back_fill(ForwardIterator first,
					kerbal::type_traits::false_type /*asc*/,
					kerbal::type_traits::false_type /*unsigned*/,
					std::vector<typename kerbal::iterator::iterator_traits<ForwardIterator>::value_type> buckets[], size_t BUCKETS_NUM)
			{
				for (size_t i = 0; i < BUCKETS_NUM; ++i) {
					first = kerbal::algorithm::copy(buckets[i].begin(), buckets[i].end(), first);
				}
			}

			template <typename ForwardIterator>
			void __radix_sort_back_fill(ForwardIterator first,
					kerbal::type_traits::true_type /*desc*/,
					kerbal::type_traits::false_type /*unsigned*/,
					std::vector<typename kerbal::iterator::iterator_traits<ForwardIterator>::value_type> buckets[], size_t BUCKETS_NUM)
			{
				size_t i = BUCKETS_NUM;
				while (i > 0) {
					--i;
					first = kerbal::algorithm::reverse_copy(buckets[i].begin(), buckets[i].end(), first);
				}
			}

			template <typename ForwardIterator>
			void __radix_sort_back_fill(ForwardIterator first,
					kerbal::type_traits::false_type /*asc*/,
					kerbal::type_traits::true_type /*signed*/,
					std::vector<typename kerbal::iterator::iterator_traits<ForwardIterator>::value_type> buckets[], size_t BUCKETS_NUM)
			{
				for (size_t i = BUCKETS_NUM / 2; i < BUCKETS_NUM; ++i) {
					first = kerbal::algorithm::copy(buckets[i].begin(), buckets[i].end(), first);
				}
				for (size_t i = 0; i < BUCKETS_NUM / 2; ++i) {
					first = kerbal::algorithm::copy(buckets[i].begin(), buckets[i].end(), first);
				}
			}

			template <typename ForwardIterator>
			void __radix_sort_back_fill(ForwardIterator first,
					kerbal::type_traits::true_type /*desc*/,
					kerbal::type_traits::true_type /*signed*/,
					std::vector<typename kerbal::iterator::iterator_traits<ForwardIterator>::value_type> buckets[], size_t BUCKETS_NUM)
			{
				{
					size_t i = BUCKETS_NUM / 2;
					while (i > 0) {
						--i;
						first = kerbal::algorithm::reverse_copy(buckets[i].begin(), buckets[i].end(), first);
					}
				}
				{
					size_t i = BUCKETS_NUM;
					while (i > BUCKETS_NUM / 2) {
						--i;
						first = kerbal::algorithm::reverse_copy(buckets[i].begin(), buckets[i].end(), first);
					}
				}
			}

		} // namespace detail

		template <typename ForwardIterator, typename Order, int RADIX_BIT_WIDTH>
		void radix_sort(ForwardIterator first, ForwardIterator last,
						Order order, kerbal::type_traits::integral_constant<int, RADIX_BIT_WIDTH> /*radix_bit_width*/)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			typedef kerbal::type_traits::integral_constant<size_t, 1 << RADIX_BIT_WIDTH> BUCKETS_NUM;
			std::vector<value_type> buckets[2][BUCKETS_NUM::value];

			typedef kerbal::type_traits::integral_constant<size_t, sizeof(value_type) * CHAR_BIT> VALUE_TYPE_BIT_WIDTH;
			typedef kerbal::type_traits::integral_constant<int, VALUE_TYPE_BIT_WIDTH::value / RADIX_BIT_WIDTH + (VALUE_TYPE_BIT_WIDTH::value % RADIX_BIT_WIDTH != 0)> ROUNDS;

//			size_t dist = kerbal::iterator::distance(first, last) /*/ BUCKETS_NUM::value*/;
//			for (size_t i = 0; i < BUCKETS_NUM::value; ++i) {
//				buckets[0][i].reserve(dist);
//				buckets[1][i].reserve(dist);
//			}

			for (iterator it(first); it != last; ++it) {
				int bucket_id = *it % BUCKETS_NUM::value;
				buckets[0][bucket_id].push_back(*it);
			}

			for (int round = 1; round < ROUNDS::value; ++round) {
				std::vector<value_type> (& buckets_from)[BUCKETS_NUM::value] = buckets[(round + 1) % 2];
				std::vector<value_type> (& buckets_to)[BUCKETS_NUM::value] = buckets[round % 2];

				for (size_t i = 0; i < BUCKETS_NUM::value; ++i) {
					buckets_to[i].clear();
				}
				for (size_t i = 0; i < BUCKETS_NUM::value; ++i) {
					typename std::vector<value_type>::iterator it(buckets_from[i].begin());
					typename std::vector<value_type>::iterator end(buckets_from[i].end());
					while (it != end) {
						int bucket_id = (*it >> (RADIX_BIT_WIDTH * round)) % BUCKETS_NUM::value;
						buckets_to[bucket_id].push_back(*it);
						++it;
					}
				}
			}

			kerbal::algorithm::detail::__radix_sort_back_fill(first, order,
															kerbal::type_traits::is_signed<value_type>(),
															buckets[(ROUNDS::value + 1) % 2], BUCKETS_NUM::value);
		}

		template <typename ForwardIterator, typename Order>
		void radix_sort(ForwardIterator first, ForwardIterator last, Order order)
		{
			kerbal::algorithm::radix_sort(first, last, order, kerbal::type_traits::integral_constant<int, CHAR_BIT>());
		}

		template <typename ForwardIterator>
		void radix_sort(ForwardIterator first, ForwardIterator last)
		{
			kerbal::algorithm::radix_sort(first, last, type_traits::false_type());
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_SORT_RADIX_SORT_HPP
