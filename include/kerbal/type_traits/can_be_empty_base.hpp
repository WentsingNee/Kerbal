/**
 * @file       can_be_empty_base.hpp
 * @brief
 * @date       2020-6-13
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_CAN_BE_EMPTY_BASE_HPP
#define KERBAL_TYPE_TRAITS_CAN_BE_EMPTY_BASE_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_empty.hpp>
#include <kerbal/type_traits/is_final.hpp>
#include <kerbal/type_traits/tribool_constant.hpp>


#if	KERBAL_HAS_IS_EMPTY_SUPPORT && KERBAL_HAS_IS_FINAL_SUPPORT
#	define KERBAL_HAS_CAN_BE_EMPTY_BASE_SUPPORT 1
#else
#	define KERBAL_HAS_CAN_BE_EMPTY_BASE_SUPPORT 0
#endif


namespace kerbal
{

	namespace type_traits
	{

#if	KERBAL_HAS_CAN_BE_EMPTY_BASE_SUPPORT

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct can_be_empty_base : kerbal::type_traits::bool_constant<
				!kerbal::type_traits::is_final<T>::value &&
				kerbal::type_traits::is_empty<T>::value
		>
		{
		};

#endif


		template <typename T>
		struct try_test_can_be_empty_base :
				kerbal::type_traits::tribool_conjunction<
					typename kerbal::type_traits::tribool_negation<
						kerbal::type_traits::try_test_is_final<T>
					>::result,
					kerbal::type_traits::try_test_is_empty<T>
				>::result
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_CAN_BE_EMPTY_BASE_HPP
