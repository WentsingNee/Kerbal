/**
 * @file       copy_n.hpp
 * @brief
 * @date       2023-08-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_MODIFIER_COPY_N_HPP
#define KERBAL_ALGORITHM_MODIFIER_COPY_N_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/utility/compressed_pair.hpp>

#include <kerbal/algorithm/modifier/detail/copy_n/basic_copy_n.hpp>


namespace kerbal
{

	namespace algorithm
	{

		template <typename InputIterator, typename SizeType, typename OutputIterator>
		KERBAL_CONSTEXPR14
		kerbal::utility::compressed_pair<InputIterator, OutputIterator>
		copy_n(InputIterator first, SizeType n, OutputIterator to)
		{
			kerbal::algorithm::detail::basic_copy_n_ret<InputIterator, OutputIterator> r(
				kerbal::algorithm::detail::basic_copy_n(first, n, to)
			);
			return kerbal::utility::compressed_pair<InputIterator, OutputIterator>(r.first, r.second);
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_MODIFIER_COPY_N_HPP
