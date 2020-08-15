/**
 * @file       can_be_pseudo_destructible.hpp
 * @brief
 * @date       2020-07-12
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_CAN_BE_PSEUDO_DESTRUCTIBLE_HPP
#define KERBAL_TYPE_TRAITS_CAN_BE_PSEUDO_DESTRUCTIBLE_HPP

#include <kerbal/type_traits/array_traits.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#if __cplusplus >= 201103L
#	include <type_traits>
#else
#	include <kerbal/type_traits/fundamental_deduction.hpp>
#	include <kerbal/type_traits/member_pointer_deduction.hpp>
#	include <kerbal/type_traits/pointer_deduction.hpp>
#	include <kerbal/type_traits/reference_deduction.hpp>
#endif

namespace kerbal
{

	namespace type_traits
	{

		namespace detail
		{

#	if __cplusplus >= 201103L

			template <typename Tp>
			struct can_be_pseudo_destructible_helper :
					kerbal::type_traits::bool_constant<
							std::is_trivially_destructible<Tp>::value
					>
			{
			};

#	else

			template <typename Tp>
			struct can_be_pseudo_destructible_helper:
					kerbal::type_traits::bool_constant<
							kerbal::type_traits::is_fundamental<Tp>::value ||
							kerbal::type_traits::is_member_pointer<Tp>::value ||
							kerbal::type_traits::is_pointer<Tp>::value ||
							kerbal::type_traits::is_reference<Tp>::value
					>
			{
			};

#	endif

		} // namespace detail

		template <typename Tp>
		struct can_be_pseudo_destructible:
				kerbal::type_traits::detail::can_be_pseudo_destructible_helper<
						typename kerbal::type_traits::remove_all_extents<Tp>::type
				>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_CAN_BE_PSEUDO_DESTRUCTIBLE_HPP
