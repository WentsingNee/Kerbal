/**
 * @file       quick_sort.hpp
 * @brief
 * @date       2020-06-09
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OMPALGO_SORT_QUICK_SORT_HPP
#define KERBAL_OMPALGO_SORT_QUICK_SORT_HPP

#include <kerbal/openmp/disable_warning.hpp>

#include <kerbal/compare/basic_compare.hpp>
#include <kerbal/iterator/iterator_traits.hpp>

#include <omp.h>


#ifdef _OPENMP
#	include <kerbal/openmp/config/task_directive.hpp>

#	if KERBAL_OMP_HAS_TASK_DIRECTIVE_SUPPORT
#		include <kerbal/ompalgo/sort/detail/quick_sort/quick_sort.task.part.hpp>
#	else
#		include <kerbal/ompalgo/sort/detail/quick_sort/quick_sort.default.hpp>
#	endif
#else
#	include <kerbal/ompalgo/sort/detail/quick_sort/quick_sort.disable.part.hpp>
#endif


namespace kerbal
{

	namespace ompalgo
	{

		template <typename BidirectionalIterator>
		void quick_sort(BidirectionalIterator first, BidirectionalIterator last)
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			kerbal::ompalgo::quick_sort(first, last, kerbal::compare::less<value_type>());
		}

	} // namespace ompalgo

} // namespace kerbal

#endif // KERBAL_OMPALGO_SORT_QUICK_SORT_HPP
