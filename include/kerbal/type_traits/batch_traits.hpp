/**
 * @file       batch_traits.hpp
 * @brief
 * @date       2019-5-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_BATCH_TRAITS_HPP
#define KERBAL_TYPE_TRAITS_BATCH_TRAITS_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/type_traits/logical.hpp>

namespace kerbal
{

	namespace type_traits
	{

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

		KERBAL_MODULE_EXPORT
		template <template <typename> typename Traits, typename ...Types>
		struct for_all_types : kerbal::type_traits::conjunction<Traits<Types>...>
		{
		};

		KERBAL_MODULE_EXPORT
		template <template <typename> typename Traits, typename ...Types>
		struct has_types : kerbal::type_traits::disjunction<Traits<Types>...>
		{
		};

#	endif

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_BATCH_TRAITS_HPP
