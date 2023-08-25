/**
 * @file       querier.hpp
 * @brief
 * @date       querier.hpp
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OMPALGO_QUERIER_HPP
#define KERBAL_OMPALGO_QUERIER_HPP

#include <kerbal/openmp/disable_warning.hpp>

#include <kerbal/compatibility/move.hpp>
#include <kerbal/iterator/iterator.hpp>

#include <omp.h>


#define SECTIONS_ALLOC_FORWARD_ITERATOR \
	threads_num = omp_get_num_threads(); \
	per = (dist / threads_num) + (dist % threads_num != 0); \
	section_ranges.reserve(threads_num); \
	section_ranges.push_back(first); \
	for (int i = 0; i < threads_num - 1; ++i) { \
		section_ranges.push_back(kerbal::iterator::next(section_ranges.back(), per)); \
	} \
	section_ranges.push_back(last); \


namespace kerbal
{

	namespace ompalgo
	{



	} // namespace ompalgo

} // namespace kerbal



#endif // KERBAL_OMPALGO_QUERIER_HPP
