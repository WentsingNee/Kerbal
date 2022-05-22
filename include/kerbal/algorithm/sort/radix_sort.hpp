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
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/container/vector.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/type_traits/fundamental_deduction.hpp>
#include <kerbal/type_traits/sign_deduction.hpp>

#include <climits>
#include <cstddef>


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR20
			void __radix_sort_back_fill(ForwardIterator first,
					kerbal::type_traits::false_type /*asc*/,
					kerbal::type_traits::false_type /*unsigned*/,
					const kerbal::container::vector<typename kerbal::iterator::iterator_traits<ForwardIterator>::value_type> buckets[],
					std::size_t BUCKETS_NUM)
			{
				for (std::size_t i = 0; i < BUCKETS_NUM; ++i) {
					first = kerbal::algorithm::copy(buckets[i].data(), buckets[i].data() + buckets[i].size(), first);
				}
			}

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR20
			void __radix_sort_back_fill(ForwardIterator first,
					kerbal::type_traits::true_type /*desc*/,
					kerbal::type_traits::false_type /*unsigned*/,
					const kerbal::container::vector<typename kerbal::iterator::iterator_traits<ForwardIterator>::value_type> buckets[],
					std::size_t BUCKETS_NUM)
			{
				std::size_t i = BUCKETS_NUM;
				while (i > 0) {
					--i;
					first = kerbal::algorithm::reverse_copy(buckets[i].data(), buckets[i].data() + buckets[i].size(), first);
				}
			}

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR20
			void __radix_sort_back_fill(ForwardIterator first,
					kerbal::type_traits::false_type /*asc*/,
					kerbal::type_traits::true_type /*signed*/,
					const kerbal::container::vector<typename kerbal::iterator::iterator_traits<ForwardIterator>::value_type> buckets[],
					std::size_t BUCKETS_NUM)
			{
				for (std::size_t i = BUCKETS_NUM / 2; i < BUCKETS_NUM; ++i) {
					first = kerbal::algorithm::copy(buckets[i].data(), buckets[i].data() + buckets[i].size(), first);
				}
				for (std::size_t i = 0; i < BUCKETS_NUM / 2; ++i) {
					first = kerbal::algorithm::copy(buckets[i].data(), buckets[i].data() + buckets[i].size(), first);
				}
			}

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR20
			void __radix_sort_back_fill(ForwardIterator first,
					kerbal::type_traits::true_type /*desc*/,
					kerbal::type_traits::true_type /*signed*/,
					const kerbal::container::vector<typename kerbal::iterator::iterator_traits<ForwardIterator>::value_type> buckets[],
					std::size_t BUCKETS_NUM)
			{
				{
					std::size_t i = BUCKETS_NUM / 2;
					while (i > 0) {
						--i;
						first = kerbal::algorithm::reverse_copy(buckets[i].data(), buckets[i].data() + buckets[i].size(), first);
					}
				}
				{
					std::size_t i = BUCKETS_NUM;
					while (i > BUCKETS_NUM / 2) {
						--i;
						first = kerbal::algorithm::reverse_copy(buckets[i].data(), buckets[i].data() + buckets[i].size(), first);
					}
				}
			}

		} // namespace detail

		template <typename ValueType>
		struct is_radix_sort_acceptable_type:
				kerbal::type_traits::is_integral<ValueType>
		{
		};

		template <typename ForwardIterator, typename Order, std::size_t RADIX_BIT_WIDTH>
		KERBAL_CONSTEXPR20
		void radix_sort(ForwardIterator first, ForwardIterator last,
						Order order, kerbal::type_traits::integral_constant<std::size_t, RADIX_BIT_WIDTH> /*radix_bit_width*/)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			typedef kerbal::container::vector<value_type> bucket_type;

			KERBAL_STATIC_ASSERT(is_radix_sort_acceptable_type<value_type>::value, "radix_sort only accepts integral type");

			typedef kerbal::type_traits::integral_constant<std::size_t, 1 << RADIX_BIT_WIDTH> BUCKETS_NUM;
			bucket_type buckets[2][BUCKETS_NUM::value];

			typedef kerbal::type_traits::integral_constant<std::size_t, sizeof(value_type) * CHAR_BIT> VALUE_TYPE_BIT_WIDTH;
			typedef kerbal::type_traits::integral_constant<std::size_t, VALUE_TYPE_BIT_WIDTH::value / RADIX_BIT_WIDTH + (VALUE_TYPE_BIT_WIDTH::value % RADIX_BIT_WIDTH != 0)> ROUNDS;

//			std::size_t dist = kerbal::iterator::distance(first, last) /*/ BUCKETS_NUM::value*/;
//			for (std::size_t i = 0; i < BUCKETS_NUM::value; ++i) {
//				buckets[0][i].reserve(dist);
//				buckets[1][i].reserve(dist);
//			}

			// first round
			for (iterator it(first); it != last; ++it) {
				int bucket_id = *it % BUCKETS_NUM::value;
				buckets[0][bucket_id].push_back(*it);
			}

			for (std::size_t round = 1; round < ROUNDS::value; ++round) {
				bucket_type (& buckets_from)[BUCKETS_NUM::value] = buckets[(round + 1) % 2];
				bucket_type (& buckets_to)[BUCKETS_NUM::value] = buckets[round % 2];

				for (std::size_t i = 0; i < BUCKETS_NUM::value; ++i) {
					buckets_to[i].clear();
				}
				for (std::size_t i = 0; i < BUCKETS_NUM::value; ++i) {
					typename bucket_type::iterator it(buckets_from[i].begin());
					typename bucket_type::iterator end(buckets_from[i].end());
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
		KERBAL_CONSTEXPR20
		void radix_sort(ForwardIterator first, ForwardIterator last, Order /*order*/)
		{
			kerbal::algorithm::radix_sort(first, last, kerbal::type_traits::bool_constant<Order::value>(),
											kerbal::type_traits::integral_constant<std::size_t, CHAR_BIT>());
		}

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR20
		void radix_sort(ForwardIterator first, ForwardIterator last)
		{
			kerbal::algorithm::radix_sort(first, last, type_traits::false_type());
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_SORT_RADIX_SORT_HPP
