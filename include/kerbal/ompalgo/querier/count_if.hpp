/**
 * @file       count_if.hpp
 * @brief
 * @date       count_if.hpp
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OMPALGO_QUERIER_COUNT_IF_HPP
#define KERBAL_OMPALGO_QUERIER_COUNT_IF_HPP

#include <kerbal/algorithm/querier/count_if.hpp>
#include <kerbal/container/vector.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>

#include <cstddef>

#include <omp.h>


namespace kerbal
{

	namespace ompalgo
	{

		namespace detail
		{

			template <typename ForwardIterator, typename UnaryPredicate>
			std::size_t
			count_if_iterator_dispatch(ForwardIterator first, ForwardIterator last, UnaryPredicate pred, std::forward_iterator_tag)
			{
				typedef ForwardIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

				const difference_type dist(kerbal::iterator::distance(first, last));
				int threads_num = 0;
				difference_type per = 0;
				kerbal::container::vector<iterator> section_ranges;

				size_t cnt = 0;

#				pragma omp parallel
				{
#					pragma omp single
					{
						SECTIONS_ALLOC_FORWARD_ITERATOR
					}
#					pragma omp barrier

					int thrd_id = omp_get_thread_num();
					size_t section_cnt = kerbal::algorithm::count_if(
							section_ranges[thrd_id], section_ranges[thrd_id + 1], pred);

#					pragma omp critical
					{
						cnt += section_cnt;
					}

				} // omp parallel

				return cnt;
			}

			template <typename RandomAccessIterator, typename UnaryPredicate>
			std::size_t
			count_if_iterator_dispatch(RandomAccessIterator first, RandomAccessIterator last, UnaryPredicate pred, std::random_access_iterator_tag)
			{
				typedef RandomAccessIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

				const difference_type dist(kerbal::iterator::distance(first, last));
				int threads_num = 0;
				difference_type per = 0;

				size_t cnt = 0;

#				pragma omp parallel
				{
#					pragma omp single
					{
						threads_num = omp_get_num_threads();
						per = (dist / threads_num) + (dist % threads_num != 0);
					}
#					pragma omp barrier

					int thrd_id = omp_get_thread_num();
					iterator section_first(kerbal::iterator::next(first, thrd_id * per));
					iterator section_last((thrd_id == threads_num - 1) ? last : kerbal::iterator::next(section_first, per));
					size_t section_cnt = kerbal::algorithm::count_if(
							section_first, section_last, pred);

#					pragma omp critical
					{
						cnt += section_cnt;
					}

				} // omp parallel

				return cnt;
			}

		} // namespace detail


		template <typename ForwardIterator, typename UnaryPredicate>
		std::size_t
		count_if(ForwardIterator first, ForwardIterator last, UnaryPredicate pred)
		{
			return kerbal::ompalgo::detail::count_if_iterator_dispatch(first, last, pred, kerbal::iterator::iterator_category(first));
		}

	} // namespace ompalgo

} // namespace kerbal

#endif // KERBAL_OMPALGO_QUERIER_COUNT_IF_HPP
