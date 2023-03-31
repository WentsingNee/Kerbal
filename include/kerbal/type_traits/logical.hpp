/**
 * @file       logical.hpp
 * @brief
 * @date       2019-4-29
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_LOGICAL_HPP
#define KERBAL_TYPE_TRAITS_LOGICAL_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/type_traits/conditional.hpp>

namespace kerbal
{

	namespace type_traits
	{

		KERBAL_MODULE_EXPORT
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

		KERBAL_MODULE_EXPORT
		template <typename ...Args>
		struct conjunction;

		KERBAL_MODULE_EXPORT
		template <>
		struct conjunction<> : kerbal::type_traits::true_type
		{
		};

		KERBAL_MODULE_EXPORT
		template <typename Tp, typename ...Args>
		struct conjunction<Tp, Args...> : kerbal::type_traits::conditional<
															Tp::value,
															conjunction <Args...>,
															kerbal::type_traits::false_type
													>::type
		{
		};

		KERBAL_MODULE_EXPORT
		template <typename ...Args>
		struct disjunction;

		KERBAL_MODULE_EXPORT
		template <>
		struct disjunction<> : kerbal::type_traits::true_type
		{
		};

		KERBAL_MODULE_EXPORT
		template <typename Tp>
		struct disjunction<Tp> : kerbal::type_traits::bool_constant<Tp::value>
		{
		};

		KERBAL_MODULE_EXPORT
		template <typename Tp, typename ...Args>
		struct disjunction<Tp, Args...> : kerbal::type_traits::conditional<
															Tp::value,
															kerbal::type_traits::true_type,
															disjunction <Args...>
													>::type
		{
		};

#	endif

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_LOGICAL_HPP
