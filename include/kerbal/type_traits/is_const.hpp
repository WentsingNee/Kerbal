/**
 * @file       is_const.hpp
 * @brief
 * @date       2022-10-24
 * @author     Peter
 * @remark     split up from kerbal/type_traits/const_deduction.hpp, 2019-4-29
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_IS_CONST_HPP
#define KERBAL_TYPE_TRAITS_IS_CONST_HPP

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

		KERBAL_MODULE_EXPORT
		template <typename >
		struct is_const : kerbal::type_traits::false_type
		{
		};

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct is_const<const T> : kerbal::type_traits::true_type
		{
		};

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC // VS2012 compatible

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct is_const<const T[]> : kerbal::type_traits::true_type
		{
		};

		KERBAL_MODULE_EXPORT
		template <typename T, std::size_t N>
		struct is_const<const T[N]> : kerbal::type_traits::true_type
		{
		};

#	endif

	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_IS_CONST_HPP
