/**
 * @file       block_qsort_partition.hpp
 * @brief
 * @date       block_qsort_partition.hpp
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_SORT_DETAIL_BLOCK_QSORT_PARTITION_HPP
#define KERBAL_ALGORITHM_SORT_DETAIL_BLOCK_QSORT_PARTITION_HPP

#include <kerbal/algorithm/swap.hpp>

#include <cstddef>

#include <kerbal/algorithm/sort/detail/quick_sort_pivot.hpp>


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			template <typename RandomAccessIterator, typename T, typename Predict>
			RandomAccessIterator block_partition(RandomAccessIterator first, RandomAccessIterator last,
												 const T & pivot, Predict pred)
			{
				typedef RandomAccessIterator iterator;
				constexpr std::size_t B = 16;
				std::size_t offsets_l[B], offsets_r[B];
				std::size_t start_l = 0, start_r = 0;
				std::size_t num_l = 0, num_r = 0;

				while (last - first > 2 * B) {
					iterator back = last - 1;
					if (num_l == 0) {
						start_l = 0;
						for (std::size_t i = 0; i < B; ++i) {
							offsets_l[num_l] = i;
							num_l += static_cast<bool>(pred(pivot, *(first + i))); // pivot < first[i]
						}
					}
					if (num_r == 0) {
						start_r = 0;
						for (std::size_t i = 0; i < B; ++i) {
							offsets_r[num_r] = i;
							num_r += static_cast<bool>(pred(*(back - i), pivot)); // back[-i] < pivot
						}
					}
					std::size_t num = std::min(num_l, num_r);
					for (std::size_t i = 0; i < num; ++i) {
						kerbal::algorithm::iter_swap(
								first + offsets_l[start_l + i],
								back - offsets_r[start_r + i]
						);
					}
					start_l += num;
					start_r += num;
					num_l -= num;
					num_r -= num;
					if (num_l == 0) {
						first += B;
					}
					if (num_r == 0) {
						last -= B;
					}
				}

				return kerbal::algorithm::detail::quick_sort_partition(first, last, pivot, pred);
			}

		} // namespace detail

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_SORT_DETAIL_BLOCK_QSORT_PARTITION_HPP
