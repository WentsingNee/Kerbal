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

#include <kerbal/ts/modules_ts/modules_ts.hpp>

KERBAL_MODULE_GLOBAL


#include <cstddef>


KERBAL_EXPORT_MODULE_DECLARE(kerbal.utility.in_place)


namespace kerbal
{

	namespace utility
	{

		KERBAL_MODULE_EXPORT
		struct in_place_t
		{
		};

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct in_place_type_t
		{
				typedef T type;
		};

		KERBAL_MODULE_EXPORT
		template <std::size_t I>
		struct in_place_index_t
		{
		};

	} // namespace utility

} // namespace kerbal

#endif // KERBAL_UTILITY_IN_PLACE_HPP
