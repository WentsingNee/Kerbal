/**
 * @file		type_traits.hpp
 * @brief
 * @date		2018年6月23日
 * @author		Peter
 * @copyright	Peter
 * @copyright
 <a href="http://thinkspirit.org/">ThinkSpirit Laboratory</a>
 of
 <a href="http://www.nuist.edu.cn/">Nanjing University of Information Science & Technology</a>
 */

#ifndef INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_HPP_
#define INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_HPP_

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#ifdef KERBAL_ENABLE_CLANGPP_MODULES

export module kerbal.type_traits;
export namespace kerbal
{
	namespace type_traits
	{

	}
}

#endif


#include <kerbal/type_traits/type_traits_details/array_traits.hpp>
#include <kerbal/type_traits/type_traits_details/conditional.hpp>
#include <kerbal/type_traits/type_traits_details/const_deduction.hpp>
#include <kerbal/type_traits/type_traits_details/cv_deduction.hpp>
#include <kerbal/type_traits/type_traits_details/enable_if.hpp>
#include <kerbal/type_traits/type_traits_details/fundamental_deduction.hpp>
#include <kerbal/type_traits/type_traits_details/integral_constant.hpp>
#include <kerbal/type_traits/type_traits_details/is_same.hpp>
#include <kerbal/type_traits/type_traits_details/logical.hpp>
#include <kerbal/type_traits/type_traits_details/pointer_deduction.hpp>
#include <kerbal/type_traits/type_traits_details/reference_deduction.hpp>
#include <kerbal/type_traits/type_traits_details/volatile_deduction.hpp>

namespace kerbal
{
	namespace type_traits
	{


#	if __cplusplus >= 201103L

		template <unsigned long long N, typename Type0, typename ... Args>
		struct type_chooser;

		template <typename Type0, typename ... Args>
		struct type_chooser<0, Type0, Args...>
		{
				typedef Type0 type;
		};

		template <unsigned long long N, typename Type0, typename ... Args>
		struct type_chooser
		{
				static_assert(N <= sizeof...(Args), "N is larger than the number of template type arguments");
				typedef typename type_chooser<N - 1, Args...>::type type;
		};

#	endif


#	if __cplusplus < 201103L

		struct __for_all_types_has_types_empty_args_helper
		{
		};

		template <template <typename> typename Traits,
										typename T0 = __for_all_types_has_types_empty_args_helper,
										typename T1 = T0,
										typename T2 = T0,
										typename T3 = T0,
										typename T4 = T0,
										typename T5 = T0,
										typename T6 = T0,
										typename T7 = T0,
										typename T8 = T0,
										typename T9 = T0,
										typename T10 = T0,
										typename T11 = T0,
										typename T12 = T0,
										typename T13 = T0,
										typename T14 = T0>
		struct for_all_types : kerbal::type_traits::conjunction<
			Traits<T0>, Traits<T1>, Traits<T2>, Traits<T3>, Traits<T4>,
			Traits<T5>, Traits<T6>, Traits<T7>, Traits<T8>, Traits<T9>,
			Traits<T10>, Traits<T11>, Traits<T12>, Traits<T13>, Traits<T14> >
		{
		};

		template <template <typename> typename Traits>
		struct for_all_types<Traits, __for_all_types_has_types_empty_args_helper> : kerbal::type_traits::true_type
		{
		};

		template <template <typename> typename Traits,
										typename T0 = __for_all_types_has_types_empty_args_helper,
										typename T1 = T0,
										typename T2 = T0,
										typename T3 = T0,
										typename T4 = T0,
										typename T5 = T0,
										typename T6 = T0,
										typename T7 = T0,
										typename T8 = T0,
										typename T9 = T0,
										typename T10 = T0,
										typename T11 = T0,
										typename T12 = T0,
										typename T13 = T0,
										typename T14 = T0>
		struct has_types : kerbal::type_traits::disjunction<
			Traits<T0>, Traits<T1>, Traits<T2>, Traits<T3>, Traits<T4>,
			Traits<T5>, Traits<T6>, Traits<T7>, Traits<T8>, Traits<T9>,
			Traits<T10>, Traits<T11>, Traits<T12>, Traits<T13>, Traits<T14> >
		{
		};

		template <template <typename> typename Traits>
		struct has_types<Traits, __for_all_types_has_types_empty_args_helper> : kerbal::type_traits::true_type
		{
		};

#	else

		MODULE_EXPORT
		template <template <typename> typename Traits, typename ...Types>
		struct for_all_types : kerbal::type_traits::conjunction<Traits<Types>...>
		{
		};

		MODULE_EXPORT
		template <template <typename> typename Traits, typename ...Types>
		struct has_types : kerbal::type_traits::disjunction<Traits<Types>...>
		{
		};

#	endif

	}
}

#endif /* INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_HPP_ */
