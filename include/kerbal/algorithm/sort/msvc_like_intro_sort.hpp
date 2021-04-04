/**
 * @file       msvc_like_intro_sort.hpp
 * @brief
 * @date       2020-10-4
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_SORT_MSVC_LIKE_INTRO_SORT_HPP
#define KERBAL_ALGORITHM_SORT_MSVC_LIKE_INTRO_SORT_HPP

#include <kerbal/algorithm/sort/heap_sort.hpp>
#include <kerbal/algorithm/sort/insertion_sort.hpp>
#include <kerbal/iterator/iterator.hpp>

namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			template <typename RandomAccessIterator, typename BinaryPredict>
			void ml_intro_adjust_pivot_helper(RandomAccessIterator a, RandomAccessIterator b, RandomAccessIterator c, BinaryPredict cmp)
			{
				if (cmp(*b, *a)) { // 1 0 x
					kerbal::algorithm::iter_swap(b, a); // 0 1 x
				}

				if (cmp(*c, *b)) { // x 2 1
					kerbal::algorithm::iter_swap(c, b); // x 1 2
				}

				if (cmp(*b, *a)) { // 1 0 x
					kerbal::algorithm::iter_swap(b, a); // 0 1 x
				}
			}

			template <typename RandomAccessIterator, typename BinaryPredict>
			void ml_intro_adjust_pivot(RandomAccessIterator first, RandomAccessIterator mid, RandomAccessIterator last, BinaryPredict cmp)
			{
				typedef RandomAccessIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

				if (last - first >= 64) {
					{
						difference_type dist(kerbal::iterator::distance(first, mid));
						dist /= 3;
						ml_intro_adjust_pivot_helper(first + dist, first, first + 2 * dist, cmp);
					}
					{
						difference_type dist(kerbal::iterator::distance(mid, last));
						dist /= 3;
						ml_intro_adjust_pivot_helper(mid + dist, mid, mid + 2 * dist, cmp);
					}
				}

				--last;
				ml_intro_adjust_pivot_helper(first, mid, last, cmp);

			}


			template <typename RandomAccessIterator, typename BinaryPredict>
			void msvc_like_intro_sort_loop(RandomAccessIterator first, RandomAccessIterator last, BinaryPredict cmp, int depth_limit)
			{
				typedef RandomAccessIterator iterator;

				if (last - first <= 16) {
					kerbal::algorithm::directly_insertion_sort(first, last, cmp);
					return;
				}

				if (depth_limit == 0) {
					kerbal::algorithm::heap_sort(first, last, cmp);
					return;
				}

				--depth_limit;

				iterator mid(kerbal::iterator::midden_iterator(first, last));
				detail::ml_intro_adjust_pivot(first, mid, last, cmp);
				iterator l(mid);
				iterator r(mid); ++r;

				while (true) {

					bool l_reached_bound = true;
					while (l != first) {
						--l;
						if (cmp(*mid, *l)) { // *l > *mid
							l_reached_bound = false;
							break;
						}
					}

					if (l_reached_bound) {
						iterator t(mid);
						while (r != last) {
							if (cmp(*r, *mid)) {
								++t;

	//							if (t == r) {
	//								throw 'a';
	//							}
								kerbal::algorithm::iter_swap(t, r);
							}
							++r;
						}
	//					if (mid == t) {
	//						throw 'b';
	//					}
						kerbal::algorithm::iter_swap(mid, t);
						mid = t;
						break;
					}

					bool r_reached_bound = true;
					while (r != last) {
						if (cmp(*r, *mid)) { // *r < *mid
							r_reached_bound = false;
							break;
						}
						++r;
					}

					if (r_reached_bound) {
						iterator t(mid);
						--t;
	//					if (l == t) {
	//						throw 'c';
	//					}
						kerbal::algorithm::iter_swap(l, t);
						while (l != first) {
							--l;
							if (cmp(*mid, *l)) {
								--t;
	//							if (l == t) {
	//								throw 'd';
	//							}
								kerbal::algorithm::iter_swap(l, t);
							}
						}
	//					if (t == mid) {
	//						throw 'e';
	//					}
						kerbal::algorithm::iter_swap(t, mid);
						mid = t;
						break;
					}

					kerbal::algorithm::iter_swap(l, r);
					++r;
				}

	//			if (!(kerbal::algorithm::none_of(first, mid, [&](const auto & x) {
	//				return cmp(*mid, x);
	//			}))) {
	//				throw 0;
	//			}
	//
	//			if (!(kerbal::algorithm::none_of(kerbal::iterator::next(mid), last, [&](const auto & x) {
	//				return cmp(x, *mid);
	//			}))) {
	//				throw '0';
	//			}

				msvc_like_intro_sort_loop(first, mid, cmp, depth_limit);
				msvc_like_intro_sort_loop(kerbal::iterator::next(mid), last, cmp, depth_limit);
			}

			template <typename Size>
			KERBAL_CONSTEXPR14
			Size lg_ml(Size n)
			{
				Size k = 0;
				while (n > 1) {
					++k;
					n >>= 1;
				}
				return k;
			}

		} // namespace detail

		template <typename RandomAccessIterator, typename BinaryPredict>
		void msvc_like_intro_sort(RandomAccessIterator first, RandomAccessIterator last, BinaryPredict cmp)
		{
			detail::msvc_like_intro_sort_loop(first, last, cmp, detail::lg_ml(last - first));
		}

		template <typename RandomAccessIterator>
		void msvc_like_intro_sort(RandomAccessIterator first, RandomAccessIterator last)
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			kerbal::algorithm::msvc_like_intro_sort(first, last, std::less<value_type>());

		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_SORT_MSVC_LIKE_INTRO_SORT_HPP
