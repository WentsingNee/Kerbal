/**
 * @file       rotate_copy.hpp
 * @brief
 * @date       2023-08-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_MODIFIER_ROTATE_COPY_HPP
#define KERBAL_ALGORITHM_MODIFIER_ROTATE_COPY_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/algorithm/modifier/copy.hpp>
#include <kerbal/compatibility/constexpr.hpp>


namespace kerbal
{

	namespace algorithm
	{

		KERBAL_MODULE_EXPORT
		template <typename ForwardIterator, typename OutputIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator
		rotate_copy(ForwardIterator first, ForwardIterator mid, ForwardIterator last, OutputIterator to)
		{
			to = kerbal::algorithm::copy(mid, last, to);
			return kerbal::algorithm::copy(first, mid, to);
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_MODIFIER_ROTATE_COPY_HPP
