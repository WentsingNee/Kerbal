/*
 * pointer_deduction.hpp
 *
 *  Created on: 2019年4月29日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_POINTER_DEDUCTION_HPP_
#define INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_POINTER_DEDUCTION_HPP_

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/type_traits/type_traits_details/cv_deduction.hpp>
#include <kerbal/type_traits/type_traits_details/reference_deduction.hpp>

namespace kerbal
{

	namespace type_traits
	{

		template <typename >
		struct __is_pointer_helper: kerbal::type_traits::false_type
		{
		};

		template <typename Tp>
		struct __is_pointer_helper<Tp*> : kerbal::type_traits::true_type
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_pointer: kerbal::type_traits::__is_pointer_helper<
										typename kerbal::type_traits::remove_cv<Tp>::type
								>
		{
		};

		template <typename Tp, typename >
		struct __remove_pointer_helper
		{
				typedef Tp type;
		};

		template <typename Tp, typename Up>
		struct __remove_pointer_helper<Tp, Up*>
		{
				typedef Up type;
		};

		MODULE_EXPORT
		/// remove_pointer
		template <typename Tp>
		struct remove_pointer: __remove_pointer_helper<Tp, typename remove_cv<Tp>::type>
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct add_pointer
		{
				typedef typename kerbal::type_traits::remove_reference<Tp>::type * type;
		};

	}
}


#endif /* INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_POINTER_DEDUCTION_HPP_ */
