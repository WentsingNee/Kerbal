/**
 * @file       can_be_empty_base.hpp
 * @brief
 * @date       2020-6-13
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_CAN_BE_EMPTY_BASE_HPP
#define KERBAL_TYPE_TRAITS_CAN_BE_EMPTY_BASE_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#if __cplusplus >= 201402L
#	include <type_traits>
#endif


namespace kerbal
{

	namespace type_traits
	{

#	if __cplusplus >= 201402L

		KERBAL_MODULE_EXPORT
		template <typename Tp>
		struct can_be_empty_base : kerbal::type_traits::bool_constant<
										!std::is_final<Tp>::value && std::is_empty<Tp>::value
									>
		{
		};

#	else

		template <typename Tp>
		struct can_be_empty_base : kerbal::type_traits::false_type
		{
		};

#	endif

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_CAN_BE_EMPTY_BASE_HPP
