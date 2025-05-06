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

#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/integral_constant.hpp>


namespace kerbal
{

	namespace type_traits
	{

		template <typename T>
		struct negation :
			kerbal::type_traits::bool_constant<!T::value>
		{
		};

#	if __cplusplus < 201103L

		template <
			typename T0 = kerbal::type_traits::true_type,
			typename T1 = kerbal::type_traits::true_type,
			typename T2 = kerbal::type_traits::true_type,
			typename T3 = kerbal::type_traits::true_type,
			typename T4 = kerbal::type_traits::true_type,
			typename T5 = kerbal::type_traits::true_type,
			typename T6 = kerbal::type_traits::true_type,
			typename T7 = kerbal::type_traits::true_type,
			typename T8 = kerbal::type_traits::true_type,
			typename T9 = kerbal::type_traits::true_type,
			typename T10 = kerbal::type_traits::true_type,
			typename T11 = kerbal::type_traits::true_type,
			typename T12 = kerbal::type_traits::true_type,
			typename T13 = kerbal::type_traits::true_type,
			typename T14 = kerbal::type_traits::true_type
		>
		struct conjunction :
			kerbal::type_traits::conditional<
				T0::value,
				conjunction<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14>,
				kerbal::type_traits::false_type
			>::type
		{
		};

		template <>
		struct conjunction<> : kerbal::type_traits::true_type
		{
		};


		template <
			typename T0 = kerbal::type_traits::true_type,
			typename T1 = kerbal::type_traits::false_type,
			typename T2 = kerbal::type_traits::false_type,
			typename T3 = kerbal::type_traits::false_type,
			typename T4 = kerbal::type_traits::false_type,
			typename T5 = kerbal::type_traits::false_type,
			typename T6 = kerbal::type_traits::false_type,
			typename T7 = kerbal::type_traits::false_type,
			typename T8 = kerbal::type_traits::false_type,
			typename T9 = kerbal::type_traits::false_type,
			typename T10 = kerbal::type_traits::false_type,
			typename T11 = kerbal::type_traits::false_type,
			typename T12 = kerbal::type_traits::false_type,
			typename T13 = kerbal::type_traits::false_type,
			typename T14 = kerbal::type_traits::false_type
		>
		struct disjunction :
			kerbal::type_traits::conditional<
				T0::value,
				kerbal::type_traits::true_type,
				disjunction<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14>
			>::type
		{
		};

		template <>
		struct disjunction<> : kerbal::type_traits::true_type
		{
		};

		template <typename T>
		struct disjunction<T> : kerbal::type_traits::bool_constant<T::value>
		{
		};

#	else

		template <typename ... Args>
		struct conjunction;

		template <>
		struct conjunction<> : kerbal::type_traits::true_type
		{
		};

		template <typename T, typename ... Args>
		struct conjunction<T, Args...> :
			kerbal::type_traits::conditional<
				T::value,
				conjunction<Args...>,
				kerbal::type_traits::false_type
			>::type
		{
		};

		template <typename ... Args>
		struct disjunction;

		template <>
		struct disjunction<> : kerbal::type_traits::true_type
		{
		};

		template <typename T>
		struct disjunction<T> : kerbal::type_traits::bool_constant<T::value>
		{
		};

		template <typename T, typename ... Args>
		struct disjunction<T, Args...> :
			kerbal::type_traits::conditional<
				T::value,
				kerbal::type_traits::true_type,
				disjunction<Args...>
			>::type
		{
		};

#	endif

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_LOGICAL_HPP
