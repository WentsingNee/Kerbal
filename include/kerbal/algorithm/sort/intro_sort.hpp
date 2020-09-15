/**
 * @file       intro_sort.hpp
 * @brief
 * @date       2020-5-30, can be traced back to at latest 2020-5-16
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_SORT_INTRO_SORT_HPP
#define KERBAL_ALGORITHM_SORT_INTRO_SORT_HPP

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/algorithm/sort/detail/quick_sort_pivot.hpp>
#include <kerbal/algorithm/sort/heap_sort.hpp>
#include <kerbal/algorithm/sort/insertion_sort.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/container/static_stack.hpp>
#include <kerbal/iterator/iterator.hpp>

#include <climits>

namespace kerbal
{

	namespace algorithm
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
			void intro_sort(BidirectionalIterator first, BidirectionalIterator last, Compare cmp, size_t depth_limit)
			{
				typedef BidirectionalIterator iterator;

				while (kerbal::iterator::distance_greater_than(first, last, 16)) {
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
						detail::intro_sort(kerbal::iterator::next(partition_point), last, cmp, depth_limit);
					}
					last = partition_point;
				}
				// dist <= 16
				kerbal::algorithm::directly_insertion_sort(first, last, cmp);
			}

		} // namespace detail

		template <typename BidirectionalIterator, typename Compare>
		KERBAL_CONSTEXPR14
		void intro_sort(BidirectionalIterator first, BidirectionalIterator last, Compare cmp)
		{
			detail::intro_sort(first, last, cmp, 2 * detail::lg(kerbal::iterator::distance(first, last)));
		}

		template <typename BidirectionalIterator>
		KERBAL_CONSTEXPR14
		void intro_sort(BidirectionalIterator first, BidirectionalIterator last)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			kerbal::algorithm::intro_sort(first, last, std::less<value_type>());
		}


		namespace detail
		{

			template <typename BidirectionalIterator>
			struct nonrecursive_intro_sort_callee_info
			{
					typedef BidirectionalIterator iterator;

					iterator first, last;
					size_t depth_limit;

					KERBAL_CONSTEXPR
					nonrecursive_intro_sort_callee_info(iterator first, iterator last, size_t depth_limit):
							first(first), last(last), depth_limit(depth_limit)
					{
					}
			};

		} // namespace detail


		template <typename BidirectionalIterator, typename Compare>
		KERBAL_CONSTEXPR14
		void nonrecursive_intro_sort(BidirectionalIterator first, BidirectionalIterator last, Compare cmp)
		{
			typedef BidirectionalIterator iterator;
			typedef detail::nonrecursive_intro_sort_callee_info<iterator> callee_info;
			typedef kerbal::container::static_stack<callee_info, sizeof(size_t) * CHAR_BIT> StackBuffer;

			StackBuffer st;
			size_t depth_limit = 2 * detail::lg(kerbal::iterator::distance(first, last));
			st.emplace(first, last, depth_limit);

			while (!st.empty()) {
				first = st.top().first;
				last = st.top().last;
				depth_limit = st.top().depth_limit;
				st.pop();

				while (depth_limit != 0) {
					if (kerbal::iterator::distance_less_than(first, last, 16)) {
						kerbal::algorithm::directly_insertion_sort(first, last, cmp);
						break;
					}

					--depth_limit;

					iterator back(kerbal::iterator::prev(last));
					detail::quick_sort_select_pivot(first, back, cmp);
					iterator partition_point(detail::quick_sort_partition(first, back, *back, cmp));

					st.emplace(first, partition_point, depth_limit);
					if (partition_point != back) {
						if (cmp(*back, *partition_point)) {
							kerbal::algorithm::iter_swap(back, partition_point);
						}
						first = kerbal::iterator::next(partition_point);
					}
				}
				if (depth_limit == 0) {
					kerbal::algorithm::heap_sort(first, last, cmp);
				}
			}
		}

		template <typename BidirectionalIterator>
		KERBAL_CONSTEXPR14
		void nonrecursive_intro_sort(BidirectionalIterator first, BidirectionalIterator last)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			kerbal::algorithm::nonrecursive_intro_sort(first, last, std::less<value_type>());
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_SORT_INTRO_SORT_HPP
