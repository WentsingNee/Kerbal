/**
 * @file       is_void.hpp
 * @brief
 * @date       2022-10-22
 * @author     Peter
 * @remark     split up from kerbal/type_traits/fundamental_deduction.hpp, 2019-5-9
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_IS_VOID_HPP
#define KERBAL_TYPE_TRAITS_IS_VOID_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>


KERBAL_MODULE_GLOBAL


#include <kerbal/type_traits/remove_cv.hpp>


KERBAL_EXPORT_MODULE_DECLARE(kerbal.type_traits.is_void)


#if KERBAL_ENABLE_MODULES

import kerbal.type_traits.add_const;
import kerbal.type_traits.add_volatile;
import kerbal.type_traits.integral_constant;

#else

#include <kerbal/type_traits/add_const.hpp>
#include <kerbal/type_traits/add_volatile.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#endif


namespace kerbal
{

	namespace type_traits
	{

		namespace detail
		{

			template <typename >
			struct is_void_helper : kerbal::type_traits::false_type
			{
			};

			template <>
			struct is_void_helper<void> : kerbal::type_traits::true_type
			{
			};

		} // namespace detail

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct is_void :
			kerbal::type_traits::detail::is_void_helper<
				typename kerbal::type_traits::remove_cv<T>::type
			>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_IS_VOID_HPP
