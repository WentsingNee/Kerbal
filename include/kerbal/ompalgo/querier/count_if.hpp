/**
 * @file       count_if.hpp
 * @brief
 * @date       2019-11-11
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OMPALGO_QUERIER_COUNT_IF_HPP
#define KERBAL_OMPALGO_QUERIER_COUNT_IF_HPP

#include <kerbal/openmp/disable_warning.hpp>

#include <kerbal/algorithm/querier/count_if.hpp>
#include <kerbal/iterator/iterator.hpp>

#include <cstddef>

#include <omp.h>


namespace kerbal
{

	namespace ompalgo
	{

		namespace detail
		{

			template <typename RandomAccessIterator, typename UnaryPredicate>
			std::size_t
			k_count_if(RandomAccessIterator first, RandomAccessIterator last, UnaryPredicate pred, std::random_access_iterator_tag)
			{
				typedef RandomAccessIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

				const difference_type dist(kerbal::iterator::distance(first, last));
				int threads_num = 0;
				difference_type per = 0;

				std::size_t cnt = 0;

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
					std::size_t section_cnt = kerbal::algorithm::count_if(
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
		size_t
		count_if(ForwardIterator first, ForwardIterator last, UnaryPredicate pred)
		{
			return kerbal::ompalgo::detail::k_count_if(first, last, pred, kerbal::iterator::iterator_category(first));
		}

	} // namespace ompalgo

} // namespace kerbal



#endif // KERBAL_OMPALGO_QUERIER_COUNT_IF_HPP
