/**
 * @file       copy_n.fwd.hpp
 * @brief
 * @date       2024-01-23
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_MODIFIER_COPY_N_COPY_N_FWD_HPP
#define KERBAL_ALGORITHM_MODIFIER_COPY_N_COPY_N_FWD_HPP

#include <kerbal/utility/compressed_pair/compressed_pair.fwd.hpp>

#include <kerbal/compatibility/constexpr.hpp>


namespace kerbal
{

	namespace algorithm
	{

		template <typename InputIterator, typename SizeType, typename OutputIterator>
		KERBAL_CONSTEXPR14
		kerbal::utility::compressed_pair<InputIterator, OutputIterator>
		copy_n(InputIterator first, SizeType n, OutputIterator to);

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_MODIFIER_COPY_N_COPY_N_FWD_HPP
