/**
 * @file       in_place.hpp
 * @brief
 * @date       2020-01-08
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_IN_PLACE_HPP
#define KERBAL_UTILITY_IN_PLACE_HPP

#include <cstddef>

namespace kerbal
{

	namespace utility
	{

		struct in_place_t
		{
		};

		template <typename Tp>
		struct in_place_type_t
		{
				typedef Tp type;
		};

		template <std::size_t I>
		struct in_place_index_t
		{
		};

	} // namespace utility

} // namespace kerbal

#endif //KERBAL_UTILITY_IN_PLACE_HPP
