/*
 * reference_deduction.hpp
 *
 *  Created on: 2019年4月29日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_REFERENCE_DEDUCTION_HPP_
#define INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_REFERENCE_DEDUCTION_HPP_

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/type_traits/type_traits_details/conditional.hpp>
#include <kerbal/type_traits/type_traits_details/integral_constant.hpp>

namespace kerbal
{

	namespace type_traits
	{

		MODULE_EXPORT
		template <typename>
		struct is_lvalue_reference : kerbal::type_traits::false_type
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_lvalue_reference<Tp&> : kerbal::type_traits::true_type
		{
		};

#	if __cplusplus >= 201103L

		MODULE_EXPORT
		template <typename>
		struct is_rvalue_reference : kerbal::type_traits::false_type
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_rvalue_reference<Tp&&> : kerbal::type_traits::true_type
		{
		};

#	endif

#	if __cplusplus < 201103L

		template <typename Tp>
		struct is_reference : kerbal::type_traits::is_lvalue_reference<Tp>
		{
		};

#	else

		MODULE_EXPORT
		template <typename Tp>
		struct is_reference : kerbal::type_traits::conditional_boolean<
											kerbal::type_traits::is_lvalue_reference<Tp>::value ||
											kerbal::type_traits::is_rvalue_reference<Tp>::value
									>
		{
		};

#	endif

		MODULE_EXPORT
		template <typename Tp>
		struct remove_reference
		{
				typedef Tp type;
		};

		MODULE_EXPORT
		template <typename Tp>
		struct remove_reference<Tp&>
		{
				typedef Tp type;
		};

#	if __cplusplus >= 201103L

		MODULE_EXPORT
		template <typename Tp>
		struct remove_reference<Tp&&>
		{
				typedef Tp type;
		};

#	endif

		MODULE_EXPORT
		/// add_lvalue_reference
		template <typename Tp>
		struct add_lvalue_reference
		{
				typedef Tp& type;
		};

#	if __cplusplus >= 201103L

		MODULE_EXPORT
		/// add_rvalue_reference
		template <typename Tp>
		struct add_rvalue_reference
		{
				typedef Tp&& type;
		};

#	endif

	}
}

#endif /* INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_REFERENCE_DEDUCTION_HPP_ */
