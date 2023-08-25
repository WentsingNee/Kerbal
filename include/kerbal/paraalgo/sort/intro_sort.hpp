/**
 * @file       intro_sort.hpp
 * @brief
 * @date       2023-08-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_PARAALGO_SORT_INTRO_SORT_HPP
#define KERBAL_PARAALGO_SORT_INTRO_SORT_HPP

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/algorithm/sort/detail/quick_sort_pivot.hpp>
#include <kerbal/algorithm/sort/heap_sort.hpp>
#include <kerbal/algorithm/sort/insertion_sort.hpp>
#include <kerbal/compare/basic_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/container/static_stack.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/parallel/thread_pool.hpp>
#include <kerbal/utility/compressed_pair.hpp>

#include <climits>
#include <cstddef>

#include <atomic>
#include <future>


namespace kerbal
{

	namespace paraalgo
	{

		namespace detail
		{

			template <typename Size>
			KERBAL_CONSTEXPR14
			Size lg(Size n)
			{
				Size k = 0;
				while (n > 1) {
					++k;
					n >>= 1;
				}
				return k;
			}

			template <typename BidirectionalIterator, typename Compare>
			KERBAL_CONSTEXPR14
			std::future<void> intro_sort(kerbal::parallel::thread_pool & thread_pool, BidirectionalIterator first, BidirectionalIterator last, Compare cmp, std::size_t depth_limit)
			{
				typedef BidirectionalIterator iterator;

				typedef kerbal::utility::compressed_pair<std::promise<void>, std::atomic<size_t> > subwork_info_t;
				std::shared_ptr<subwork_info_t> subwork_info = std::make_shared<subwork_info_t>(
						kerbal::utility::compressed_pair_default_construct_tag(),
						1
				);
				std::future<void> future = subwork_info->first().get_future();

				while (kerbal::iterator::distance_greater_than(first, last, 16)) {
					if (depth_limit == 0) {
						kerbal::algorithm::heap_sort(first, last, cmp);
						return future;
					}

					--depth_limit;

					iterator back(kerbal::iterator::prev(last));
					kerbal::algorithm::detail::quick_sort_select_pivot(first, back, cmp);
					iterator partition_point(kerbal::algorithm::detail::quick_sort_partition(first, back, *back, cmp));

					if (partition_point != back) {
						if (cmp(*back, *partition_point)) {
							kerbal::algorithm::iter_swap(back, partition_point);
						}
						thread_pool.commit([&thread_pool, subwork_info](BidirectionalIterator first, BidirectionalIterator last, Compare cmp, std::size_t depth_limit) {
							detail::intro_sort(thread_pool, first, last, cmp, depth_limit);
							if (subwork_info->second().fetch_sub(1, std::memory_order::memory_order_release) == 1) {
								subwork_info->first().set_value();
							}
						}, kerbal::iterator::next(partition_point), last, cmp, depth_limit);
						subwork_info->second().fetch_add(1, std::memory_order::memory_order_relaxed);
					}
					last = partition_point;
				}
				// dist <= 16
				kerbal::algorithm::directly_insertion_sort(first, last, cmp);
				if (subwork_info->second().fetch_sub(1, std::memory_order::memory_order_release) == 1) {
					subwork_info->first().set_value();
				}
				return future;
			}


/*
			template <typename BidirectionalIterator, typename Compare>
			KERBAL_CONSTEXPR14
			std::future<void> intro_sort(kerbal::parallel::thread_pool & thread_pool, BidirectionalIterator first, BidirectionalIterator last, Compare cmp, std::size_t depth_limit)
			{
				typedef BidirectionalIterator iterator;

				if (kerbal::iterator::distance_greater_than(first, last, 16)) {
					if (depth_limit == 0) {
						kerbal::algorithm::heap_sort(first, last, cmp);
						return;
					}

					--depth_limit;

					iterator back(kerbal::iterator::prev(last));
					detail::quick_sort_select_pivot(first, back, cmp);
					iterator partition_point(detail::quick_sort_partition(first, back, *back, cmp));

					if (partition_point != back) {
						if (cmp(*back, *partition_point)) {
							kerbal::algorithm::iter_swap(back, partition_point);
						}
						thread_pool.commit(detail::intro_sort, thread_pool, kerbal::iterator::next(partition_point), last, cmp, depth_limit);
						committed_subworks.fetch_add(1, std::memory_order::memory_order_relaxed);
					}
					detail::intro_sort(thread_pool, first, partition_point, cmp, depth_limit);
				} else {
					// dist <= 16
					kerbal::algorithm::directly_insertion_sort(first, last, cmp);
					return promise.get_future();
				}
			}
*/

		} // namespace detail

		template <typename BidirectionalIterator, typename Compare>
		KERBAL_CONSTEXPR14
		std::future<void> intro_sort(kerbal::parallel::thread_pool & thread_pool, BidirectionalIterator first, BidirectionalIterator last, Compare cmp)
		{
			return detail::intro_sort(thread_pool, first, last, cmp, 2 * detail::lg(kerbal::iterator::distance(first, last)));
		}

		template <typename BidirectionalIterator>
		KERBAL_CONSTEXPR14
		std::future<void> intro_sort(kerbal::parallel::thread_pool & thread_pool, BidirectionalIterator first, BidirectionalIterator last)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			return kerbal::paraalgo::intro_sort(first, last, kerbal::compare::less<value_type>());
		}

	} // namespace paraalgo

} // namespace kerbal

#endif // KERBAL_PARAALGO_SORT_INTRO_SORT_HPP
