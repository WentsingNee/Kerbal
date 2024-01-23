/**
 * @file       foreach.hpp
 * @brief
 * @date       2019-11-11
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OMPALGO_QUERIER_FOREACH_HPP
#define KERBAL_OMPALGO_QUERIER_FOREACH_HPP

#include <kerbal/openmp/disable_warning.hpp>

#include <kerbal/algorithm/querier/for_each.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/iterator/iterator.hpp>

#include <omp.h>


namespace kerbal
{

	namespace ompalgo
	{

		namespace detail
		{

			template <typename RandomAccessIterator, typename UnaryFunction>
			UnaryFunction
			k_for_each(RandomAccessIterator first, RandomAccessIterator last, UnaryFunction f, std::random_access_iterator_tag)
			{
				typedef RandomAccessIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

				const difference_type dist(kerbal::iterator::distance(first, last));
				int threads_num = 0;
				difference_type per = 0;

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
					kerbal::algorithm::for_each(section_first, section_last, f);
				} // omp parallel

				return kerbal::compatibility::to_xvalue(f);
			}

		} // namespace detail


		template <typename ForwardIterator, typename UnaryFunction>
		UnaryFunction
		for_each(ForwardIterator first, ForwardIterator last, UnaryFunction f)
		{
			return kerbal::ompalgo::detail::k_for_each(first, last, f, kerbal::iterator::iterator_category(first));
		}

	} // namespace ompalgo

} // namespace kerbal



#endif // KERBAL_OMPALGO_QUERIER_FOREACH_HPP
