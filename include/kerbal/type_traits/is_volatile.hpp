/**
 * @file       is_volatile.hpp
 * @brief
 * @date       2022-10-29
 * @author     Peter
 * @remark     split up from kerbal/type_traits/volatile_deduction.hpp, 2019-4-29
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_IS_VOLATILE_HPP
#define KERBAL_TYPE_TRAITS_IS_VOLATILE_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <kerbal/config/compiler_id.hpp>

#if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC // VS2012 compatible
#	include <cstddef>
#endif


namespace kerbal
{

	namespace type_traits
	{

		MODULE_EXPORT
		template <typename >
		struct is_volatile: kerbal::type_traits::false_type
		{
		};

		MODULE_EXPORT
		template <typename T>
		struct is_volatile<volatile T> : kerbal::type_traits::true_type
		{
		};

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC // VS2012 compatible

		MODULE_EXPORT
		template <typename T>
		struct is_volatile<volatile T[]> : kerbal::type_traits::true_type
		{
		};

		MODULE_EXPORT
		template <typename T, std::size_t N>
		struct is_volatile<volatile T[N]> : kerbal::type_traits::true_type
		{
		};

#	endif

	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_IS_VOLATILE_HPP
