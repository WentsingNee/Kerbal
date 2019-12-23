/*
 * cv_deduction.hpp
 *
 *  Created on: 2019年4月29日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_CV_DEDUCTION_HPP_
#define INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_CV_DEDUCTION_HPP_

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/type_traits/type_traits_details/const_deduction.hpp>
#include <kerbal/type_traits/type_traits_details/volatile_deduction.hpp>
#include <kerbal/type_traits/type_traits_details/reference_deduction.hpp>

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

	}
}


#endif /* INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_CV_DEDUCTION_HPP_ */
