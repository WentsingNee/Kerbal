/**
 * @file       querier.hpp
 * @brief
 * @date       2019-11-11
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OMPALGO_QUERIER_HPP
#define KERBAL_OMPALGO_QUERIER_HPP

#include <kerbal/openmp/disable_warning.hpp>

#include <kerbal/algorithm/querier.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <omp.h>
#include <vector>

#define SECTIONS_ALLOC_FORWARD_ITERATOR \
	threads_num = omp_get_num_threads(); \
	per = (dist / threads_num) + (dist % threads_num != 0); \
	section_ranges.reserve(threads_num); \
	section_ranges.push_back(first); \
	for (int i = 0; i < threads_num - 1; ++i) { \
		section_ranges.push_back(kerbal::iterator::next(section_ranges.back(), per)); \
	} \
	section_ranges.push_back(last);        \


namespace kerbal
{

	namespace ompalgo
	{

		template <typename ForwardIterator, typename UnaryPredicate>
		size_t
		__count_if(ForwardIterator first, ForwardIterator last, UnaryPredicate pred, std::forward_iterator_tag)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

			const difference_type dist(kerbal::iterator::distance(first, last));
			int threads_num = 0;
			difference_type per = 0;
			std::vector<iterator> section_ranges;

			size_t cnt = 0;

#			pragma omp parallel
			{
#				pragma omp single
				{
					SECTIONS_ALLOC_FORWARD_ITERATOR
				}
#				pragma omp barrier

				int thrd_id = omp_get_thread_num();
				size_t section_cnt = kerbal::algorithm::__count_if(
						section_ranges[thrd_id], section_ranges[thrd_id + 1], pred,
						kerbal::iterator::iterator_category(first));

#				pragma omp critical
				{
					cnt += section_cnt;
				}

			}; // omp parallel

			return cnt;
		}

		template <typename RandomAccessIterator, typename UnaryPredicate>
		size_t
		__count_if(RandomAccessIterator first, RandomAccessIterator last, UnaryPredicate pred, std::random_access_iterator_tag)
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

			const difference_type dist(kerbal::iterator::distance(first, last));
			int threads_num = 0;
			difference_type per = 0;

			size_t cnt = 0;

#			pragma omp parallel
			{
#				pragma omp single
				{
					threads_num = omp_get_num_threads();
					per = (dist / threads_num) + (dist % threads_num != 0);
				}
#				pragma omp barrier

				int thrd_id = omp_get_thread_num();
				iterator section_first(kerbal::iterator::next(first, thrd_id * per));
				iterator section_last((thrd_id == threads_num - 1) ? last : kerbal::iterator::next(section_first, per));
				size_t section_cnt = kerbal::algorithm::__count_if(
						section_first, section_last, pred,
						kerbal::iterator::iterator_category(first));

#				pragma omp critical
				{
					cnt += section_cnt;
				}

			} // omp parallel

			return cnt;
		}

		template <typename ForwardIterator, typename UnaryPredicate>
		size_t
		count_if(ForwardIterator first, ForwardIterator last, UnaryPredicate pred)
		{
			return kerbal::ompalgo::__count_if(first, last, pred, kerbal::iterator::iterator_category(first));
		}



		template <typename ForwardIterator, typename UnaryFunction>
		UnaryFunction
		__for_each(ForwardIterator first, ForwardIterator last, UnaryFunction f, std::forward_iterator_tag)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

			const difference_type dist(kerbal::iterator::distance(first, last));
			int threads_num = 0;
			difference_type per = 0;
			std::vector<iterator> section_ranges;

#			pragma omp parallel
			{
#				pragma omp single
				{
					SECTIONS_ALLOC_FORWARD_ITERATOR
				}
#				pragma omp barrier

				int thrd_id = omp_get_thread_num();
				kerbal::algorithm::__for_each(
						section_ranges[thrd_id], section_ranges[thrd_id + 1], f,
						kerbal::iterator::iterator_category(first));

			} // omp parallel

			return kerbal::compatibility::to_xvalue(f);
		}

		template <typename RandomAccessIterator, typename UnaryFunction>
		UnaryFunction
		__for_each(RandomAccessIterator first, RandomAccessIterator last, UnaryFunction f, std::random_access_iterator_tag)
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

			const difference_type dist(kerbal::iterator::distance(first, last));
			int threads_num = 0;
			difference_type per = 0;

#			pragma omp parallel
			{
#				pragma omp single
				{
					threads_num = omp_get_num_threads();
					per = (dist / threads_num) + (dist % threads_num != 0);
				}
#				pragma omp barrier

				int thrd_id = omp_get_thread_num();
				iterator section_first(kerbal::iterator::next(first, thrd_id * per));
				iterator section_last((thrd_id == threads_num - 1) ? last : kerbal::iterator::next(section_first, per));
				kerbal::algorithm::__for_each(section_first, section_last, f, kerbal::iterator::iterator_category(first));
			} // omp parallel

			return kerbal::compatibility::to_xvalue(f);
		}

		template <typename ForwardIterator, typename UnaryFunction>
		UnaryFunction
		for_each(ForwardIterator first, ForwardIterator last, UnaryFunction f)
		{
			return kerbal::ompalgo::__for_each(first, last, f, kerbal::iterator::iterator_category(first));
		}

	} // namespace ompalgo

} // namespace kerbal



#endif // KERBAL_OMPALGO_QUERIER_HPP
