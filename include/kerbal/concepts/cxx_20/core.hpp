/**
 * @file       core.hpp
 * @brief
 * @date       2020-02-29
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONCEPTS_CXX_20_CORE_HPP
#define KERBAL_CONCEPTS_CXX_20_CORE_HPP

#include <kerbal/concepts/config.hpp>
#include <kerbal/type_traits/is_same.hpp>
#include <kerbal/type_traits/fundamental_deduction.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif

#if __cplusplus >= 201103L
#	include <type_traits>
#endif

namespace kerbal
{

	namespace concepts
	{

#if defined(KERBAL_ENABLE_CONCEPTS)

		template <typename Tp, typename Up>
		KERBAL_CONCEPT same_as =
				kerbal::type_traits::is_same<Tp, Up>::value &&
				kerbal::type_traits::is_same<Up, Tp>::value;

#	if __cplusplus >= 201103L

		template <typename Derived, typename Base>
		KERBAL_CONCEPT derived_from =
				std::is_base_of<Base, Derived>::value &&
				std::is_convertible<const volatile Derived*, const volatile Base*>::value;

		template <typename Tp>
		KERBAL_CONCEPT destructible = std::is_nothrow_destructible<Tp>::value;

#	endif

		template <typename Tp>
		KERBAL_CONCEPT integral = kerbal::type_traits::is_integral<Tp>::value;

#endif

		template <typename Lhs, typename Rhs>
		KERBAL_CONCEPT assignable_from =
				kerbal::type_traits::is_lvalue_reference<Lhs>::value &&
				requires (Lhs lhs, Rhs rhs) {
					{lhs = kerbal::utility::forward<Rhs>(rhs)} -> kerbal::concepts::same_as<Lhs>;
				}
		;

		template <typename Tp, typename Up = Tp>
		KERBAL_CONCEPT swappable_with =
				requires (Tp && t, Up && u) {
					true;
				};
		;

		template <typename Tp>
		KERBAL_CONCEPT movable =
				std::is_object<Tp>::value &&
				std::is_move_constructible<Tp>::value &&
				kerbal::concepts::assignable_from<Tp&, Tp> &&
				swappable_with<Tp>
		;

	}

}

#endif // KERBAL_CONCEPTS_CXX_20_CORE_HPP
