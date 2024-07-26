/**
 * @file       array.fwd.hpp
 * @brief
 * @date       2020-11-13
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_ARRAY_ARRAY_FWD_HPP
#define KERBAL_CONTAINER_ARRAY_ARRAY_FWD_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <cstddef>


namespace kerbal
{

	namespace container
	{

		KERBAL_MODULE_EXPORT
		template <typename T, std::size_t N>
		class array;

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_ARRAY_ARRAY_FWD_HPP
