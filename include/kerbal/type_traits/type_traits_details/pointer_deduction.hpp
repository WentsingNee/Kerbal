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
#include <kerbal/type_traits/type_traits_details/function_deduction.hpp>
#include <kerbal/type_traits/type_traits_details/reference_deduction.hpp>

#include <cstddef>

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

		//		MODULE_EXPORT
//		template <typename >
//		struct pointer_rank: kerbal::type_traits::integral_constant<size_t, 0>
//		{
//		};
//
//		MODULE_EXPORT
//		template <typename Tp>
//		struct pointer_rank<Tp*> : kerbal::type_traits::integral_constant<
//				size_t,
//				1 + pointer_rank<Tp>::value
//		>
//		{
//		};

		template <typename Tp, bool is_pointer>
		struct __pointer_rank_helper;

		MODULE_EXPORT
		template <typename Tp>
		struct pointer_rank: kerbal::type_traits::__pointer_rank_helper<
				Tp,
				kerbal::type_traits::is_pointer<Tp>::value
		>
		{
		};

		template <typename Tp>
		struct __pointer_rank_helper<Tp, true>:
				kerbal::type_traits::integral_constant<
						size_t,
						1 + kerbal::type_traits::pointer_rank<
								typename kerbal::type_traits::remove_pointer<Tp>::type
						>::value
				>
		{
		};

		template <typename Tp>
		struct __pointer_rank_helper<Tp, false>:
				kerbal::type_traits::integral_constant<
						size_t,
						0
				>
		{
		};


//		template <typename Tp, bool = kerbal::type_traits::is_function<Tp>::value >
//		struct __add_pointer_helper
//		{
//			typedef kerbal::type_traits::conditional<
//						kerbal::type_traits::function_traits<Tp>::
//			type;
//		};
//
//		template <typename Tp>
//		struct __add_pointer_helper<Tp, false>
//		{
//			typedef Tp* type;
//		};

		template <typename Tp>
		struct __add_pointer_helper
		{
			typedef Tp* type;
		};

		MODULE_EXPORT
		template <typename Tp>
		struct add_pointer:
				kerbal::type_traits::__add_pointer_helper<
						typename kerbal::type_traits::remove_reference<Tp>::type
				>
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct remove_all_pointers:
				kerbal::type_traits::conditional<
					kerbal::type_traits::is_pointer<Tp>::value,
					kerbal::type_traits::remove_all_pointers<
						typename kerbal::type_traits::remove_pointer<Tp>::type
					>,
					kerbal::type_traits::remove_pointer<Tp>
				>::type
		{
		};

	}
}


#endif /* INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_POINTER_DEDUCTION_HPP_ */
