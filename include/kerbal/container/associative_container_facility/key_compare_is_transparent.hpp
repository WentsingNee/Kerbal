/**
 * @file       key_compare_is_transparent.hpp
 * @brief
 * @date       2022-09-09
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_ASSOCIATIVE_CONTAINER_FACILITY_KEY_COMPARE_IS_TRANSPARENT_HPP
#define KERBAL_CONTAINER_ASSOCIATIVE_CONTAINER_FACILITY_KEY_COMPARE_IS_TRANSPARENT_HPP

#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/void_type.hpp>


namespace kerbal
{

	namespace container
	{

		template <typename KeyCompare, typename = kerbal::type_traits::void_type<>::type>
		struct key_compare_is_transparent : kerbal::type_traits::false_type
		{
		};

		template <typename KeyCompare>
		struct key_compare_is_transparent<
					KeyCompare,
					typename kerbal::type_traits::void_type<typename KeyCompare::is_transparent>::type
				> :
				kerbal::type_traits::true_type
		{
		};

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_ASSOCIATIVE_CONTAINER_FACILITY_KEY_COMPARE_IS_TRANSPARENT_HPP
