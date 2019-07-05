/*
 * logical.hpp
 *
 *  Created on: 2019年4月29日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_LOGICAL_HPP_
#define INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_LOGICAL_HPP_

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/type_traits/type_traits_details/conditional.hpp>

namespace kerbal
{

	namespace type_traits
	{

		MODULE_EXPORT
		template <typename Tp>
		struct negation: kerbal::type_traits::bool_constant<!Tp::value>
		{
		};

#	if __cplusplus < 201103L

		template <typename Tp0 = kerbal::type_traits::true_type,
					typename Tp1 = kerbal::type_traits::true_type,
					typename Tp2 = kerbal::type_traits::true_type,
					typename Tp3 = kerbal::type_traits::true_type,
					typename Tp4 = kerbal::type_traits::true_type,
					typename Tp5 = kerbal::type_traits::true_type,
					typename Tp6 = kerbal::type_traits::true_type,
					typename Tp7 = kerbal::type_traits::true_type,
					typename Tp8 = kerbal::type_traits::true_type,
					typename Tp9 = kerbal::type_traits::true_type,
					typename Tp10 = kerbal::type_traits::true_type,
					typename Tp11 = kerbal::type_traits::true_type,
					typename Tp12 = kerbal::type_traits::true_type,
					typename Tp13 = kerbal::type_traits::true_type,
					typename Tp14 = kerbal::type_traits::true_type
		>
		struct conjunction : kerbal::type_traits::conditional<
											Tp0::value,
											conjunction<Tp1, Tp2, Tp3, Tp4, Tp5, Tp6, Tp7, Tp8, Tp9, Tp10, Tp11, Tp12, Tp13, Tp14>,
											kerbal::type_traits::false_type
									>::type
		{
		};

		template <>
		struct conjunction <>: kerbal::type_traits::true_type
		{
		};


		template <typename Tp0 = kerbal::type_traits::true_type,
					typename Tp1 = kerbal::type_traits::false_type,
					typename Tp2 = kerbal::type_traits::false_type,
					typename Tp3 = kerbal::type_traits::false_type,
					typename Tp4 = kerbal::type_traits::false_type,
					typename Tp5 = kerbal::type_traits::false_type,
					typename Tp6 = kerbal::type_traits::false_type,
					typename Tp7 = kerbal::type_traits::false_type,
					typename Tp8 = kerbal::type_traits::false_type,
					typename Tp9 = kerbal::type_traits::false_type,
					typename Tp10 = kerbal::type_traits::false_type,
					typename Tp11 = kerbal::type_traits::false_type,
					typename Tp12 = kerbal::type_traits::false_type,
					typename Tp13 = kerbal::type_traits::false_type,
					typename Tp14 = kerbal::type_traits::false_type
		>
		struct disjunction : kerbal::type_traits::conditional<
											Tp0::value,
											kerbal::type_traits::true_type,
											disjunction<Tp1, Tp2, Tp3, Tp4, Tp5, Tp6, Tp7, Tp8, Tp9, Tp10, Tp11, Tp12, Tp13, Tp14>
									>::type
		{
		};

		template <>
		struct disjunction <>: kerbal::type_traits::true_type
		{
		};

		template <typename Tp>
		struct disjunction <Tp>: kerbal::type_traits::bool_constant<Tp::value>
		{
		};

#	else

		MODULE_EXPORT
		template <typename ...Args>
		struct conjunction;

		MODULE_EXPORT
		template <>
		struct conjunction<> : kerbal::type_traits::true_type
		{
		};

		MODULE_EXPORT
		template <typename Tp, typename ...Args>
		struct conjunction<Tp, Args...> : kerbal::type_traits::conditional<
															Tp::value,
															conjunction <Args...>,
															kerbal::type_traits::false_type
													>::type
		{
		};

		MODULE_EXPORT
		template <typename ...Args>
		struct disjunction;

		MODULE_EXPORT
		template <>
		struct disjunction<> : kerbal::type_traits::true_type
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct disjunction<Tp> : kerbal::type_traits::bool_constant<Tp::value>
		{
		};

		MODULE_EXPORT
		template <typename Tp, typename ...Args>
		struct disjunction<Tp, Args...> : kerbal::type_traits::conditional<
															Tp::value,
															kerbal::type_traits::true_type,
															disjunction <Args...>
													>::type
		{
		};

#	endif

	}

}



#endif /* INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_LOGICAL_HPP_ */
