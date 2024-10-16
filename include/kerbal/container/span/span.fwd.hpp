/**
 * @file       span.fwd.hpp
 * @brief
 * @date       2024-10-16
 * @author     peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_SPAN_SPAN_FWD_HPP
#define KERBAL_CONTAINER_SPAN_SPAN_FWD_HPP

#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>


namespace kerbal
{

	namespace container
	{

		struct dynamic_extent :
			kerbal::type_traits::integral_constant<std::size_t, -1>
		{
		};

		template <
			typename T,
			typename Extent = kerbal::container::dynamic_extent
		>
		class span;

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_SPAN_SPAN_FWD_HPP
