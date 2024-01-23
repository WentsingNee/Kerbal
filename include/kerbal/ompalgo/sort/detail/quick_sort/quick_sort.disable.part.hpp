/**
 * @file       quick_sort.disable.part.hpp
 * @brief
 * @date       2020-06-09
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OMPALGO_SORT_DETAIL_QUICK_SORT_QUICK_SORT_DISABLE_PART_HPP
#define KERBAL_OMPALGO_SORT_DETAIL_QUICK_SORT_QUICK_SORT_DISABLE_PART_HPP

#include <kerbal/algorithm/sort/quick_sort.hpp>


namespace kerbal
{

	namespace ompalgo
	{

		template <typename BidirectionalIterator, typename Compare>
		void quick_sort(BidirectionalIterator first, BidirectionalIterator last, Compare cmp)
		{
			kerbal::algorithm::quick_sort(first, last, cmp);
		}

	} // namespace ompalgo

} // namespace kerbal

#endif // KERBAL_OMPALGO_SORT_DETAIL_QUICK_SORT_QUICK_SORT_DISABLE_PART_HPP
