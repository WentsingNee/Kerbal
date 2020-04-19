/**
 * @file       conditional.hpp
 * @brief
 * @date       2019-4-29
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_CONDITIONAL_HPP
#define KERBAL_TYPE_TRAITS_CONDITIONAL_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

namespace kerbal
{

	namespace type_traits
	{

		MODULE_EXPORT
		template <bool condition, typename TrueType, typename FalseType>
		struct conditional
		{
				typedef TrueType type;
		};

		MODULE_EXPORT
		template <typename TrueType, typename FalseType>
		struct conditional<false, TrueType, FalseType>
		{
				typedef FalseType type;
		};

		MODULE_EXPORT
		template <bool condition>
		struct conditional_boolean : kerbal::type_traits::bool_constant<condition>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_CONDITIONAL_HPP
