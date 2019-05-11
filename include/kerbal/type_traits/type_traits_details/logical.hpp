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


		template <typename Tp0 = kerbal::type_traits::false_type,
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

		/**
		 * @brief gcc 一个神奇的特性, 没有这个特化, disjunction<kerbal::type_traits::false_type> 会直接
		 * 套用 disjunction <>, 即 value 为 true; 而 disjunction<std::false_type> 工作正常
		 */
		template <typename Tp1,
					typename Tp2,
					typename Tp3,
					typename Tp4,
					typename Tp5,
					typename Tp6,
					typename Tp7,
					typename Tp8,
					typename Tp9,
					typename Tp10,
					typename Tp11,
					typename Tp12,
					typename Tp13,
					typename Tp14
		>
		struct disjunction <kerbal::type_traits::false_type, Tp1, Tp2, Tp3, Tp4, Tp5, Tp6, Tp7, Tp8, Tp9, Tp10, Tp11, Tp12, Tp13, Tp14> :
				kerbal::type_traits::false_type
		{
		};


		template <typename Tp>
		struct disjunction <Tp>: kerbal::type_traits::conditional_boolean<Tp::value>
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
		template <typename Tp>
		struct conjunction<Tp> : kerbal::type_traits::conditional_boolean<Tp::value>
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
		struct disjunction<Tp> : kerbal::type_traits::conditional_boolean<Tp::value>
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
