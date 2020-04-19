/**
 * @file       member_pointer_deduction.hpp
 * @brief
 * @date       2019-7-3
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_MEMBER_POINTER_DEDUCTION_HPP
#define KERBAL_TYPE_TRAITS_MEMBER_POINTER_DEDUCTION_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/type_traits/cv_deduction.hpp>
#include <kerbal/type_traits/function_deduction.hpp>

namespace kerbal
{

	namespace type_traits
	{

		template <typename >
		struct __is_member_pointer_helper: kerbal::type_traits::false_type
		{
		};

		template <typename Tp, typename Up>
		struct __is_member_pointer_helper<Tp Up::*> : kerbal::type_traits::true_type
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_member_pointer: kerbal::type_traits::__is_member_pointer_helper<
												typename kerbal::type_traits::remove_cv<Tp>::type
										>
		{
		};

		template <typename >
		struct __is_member_function_pointer_helper: kerbal::type_traits::false_type
		{
		};

		template <typename Tp, typename Up>
		struct __is_member_function_pointer_helper<Tp Up::*> : kerbal::type_traits::is_function<Tp>
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_member_function_pointer: kerbal::type_traits::__is_member_function_pointer_helper<
															typename kerbal::type_traits::remove_cv<Tp>::type
													>
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_member_object_pointer: kerbal::type_traits::bool_constant<
														kerbal::type_traits::is_member_pointer<Tp>::value &&
														!kerbal::type_traits::is_member_function_pointer<Tp>::value
													>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_MEMBER_POINTER_DEDUCTION_HPP
