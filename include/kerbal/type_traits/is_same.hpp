/**
 * @file       is_same.hpp
 * @brief
 * @date       2019-4-29
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_IS_SAME_HPP
#define KERBAL_TYPE_TRAITS_IS_SAME_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/ppexpand.hpp>
#else
#	include <kerbal/type_traits/logical.hpp>
#endif


namespace kerbal
{

	namespace type_traits
	{

#	if __cplusplus < 201103L

#		define TARGS_DECL(i) typename = Up

		template <typename Tp, typename Up,
				KERBAL_PPEXPAND_WITH_COMMA_N(TARGS_DECL, 20)
		>
		struct is_same : kerbal::type_traits::false_type
		{
		};

#		undef TARGS_DECL

#	else

		KERBAL_MODULE_EXPORT
		template <typename Tp, typename Up, typename ... Types>
		struct is_same:
				kerbal::type_traits::conjunction<
					kerbal::type_traits::is_same<Tp, Up>,
					kerbal::type_traits::is_same<Tp, Types>...
				>
		{
		};

		KERBAL_MODULE_EXPORT
		template <typename Tp, typename Up>
		struct is_same<Tp, Up> : kerbal::type_traits::false_type
		{
		};

#endif

		KERBAL_MODULE_EXPORT
		template <typename Tp>
		struct is_same<Tp, Tp> : kerbal::type_traits::true_type
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_IS_SAME_HPP
