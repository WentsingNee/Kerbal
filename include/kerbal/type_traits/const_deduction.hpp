/**
 * @file       const_deduction.hpp
 * @brief
 * @date       2019-4-29
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_CONST_DEDUCTION_HPP
#define KERBAL_TYPE_TRAITS_CONST_DEDUCTION_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

namespace kerbal
{

	namespace type_traits
	{

		MODULE_EXPORT
		template <typename >
		struct is_const: kerbal::type_traits::false_type
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct is_const<Tp const> : kerbal::type_traits::true_type
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct remove_const
		{
				typedef Tp type;
		};

		MODULE_EXPORT
		template <typename Tp>
		struct remove_const<Tp const>
		{
				typedef Tp type;
		};

		MODULE_EXPORT
		template <typename Tp>
		struct add_const
		{
				typedef const Tp type;
		};

		MODULE_EXPORT
		template <typename From, typename To>
		struct copy_const:
					kerbal::type_traits::conditional<
						kerbal::type_traits::is_const<From>::value,
						typename kerbal::type_traits::add_const<To>::type,
						To
					>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_CONST_DEDUCTION_HPP
