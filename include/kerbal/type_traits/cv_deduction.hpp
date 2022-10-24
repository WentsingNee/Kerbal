/**
 * @file       cv_deduction.hpp
 * @brief
 * @date       2019-4-29
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_CV_DEDUCTION_HPP
#define KERBAL_TYPE_TRAITS_CV_DEDUCTION_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/type_traits/add_const.hpp>
#include <kerbal/type_traits/copy_const.hpp>
#include <kerbal/type_traits/volatile_deduction.hpp>
#include <kerbal/type_traits/reference_deduction.hpp>
#include <kerbal/type_traits/remove_const.hpp>


namespace kerbal
{

	namespace type_traits
	{

		MODULE_EXPORT
		template <typename >
		struct is_cv: kerbal::type_traits::false_type
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_cv<Tp const volatile> : kerbal::type_traits::true_type
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct remove_cv: kerbal::type_traits::remove_const<typename kerbal::type_traits::remove_volatile<Tp>::type>
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct remove_cvref: kerbal::type_traits::remove_cv<typename kerbal::type_traits::remove_reference<Tp>::type>
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct add_cv: kerbal::type_traits::add_const<typename kerbal::type_traits::add_volatile<Tp>::type>
		{
		};

		MODULE_EXPORT
		template <typename From, typename To>
		struct copy_cv:
				kerbal::type_traits::copy_const<
					From, typename kerbal::type_traits::copy_volatile<From, To>::type
				>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_CV_DEDUCTION_HPP
