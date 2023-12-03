/**
 * @file       assignable_from.hpp
 * @brief
 * @date       2020-02-29
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONCEPTS_ASSIGNABLE_FROM_HPP
#define KERBAL_CONCEPTS_ASSIGNABLE_FROM_HPP

#include <kerbal/concepts/config.hpp>

#if KERBAL_HAS_CONCEPTS_SUPPORT

#include <kerbal/concepts/same_as.hpp>
#include <kerbal/type_traits/is_lvalue_reference.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif


namespace kerbal
{

	namespace concepts
	{

		template <typename Lhs, typename Rhs>
		KERBAL_CONCEPT assignable_from =
			kerbal::type_traits::is_lvalue_reference<Lhs>::value &&
			requires (Lhs lhs, Rhs rhs) {
				{ lhs = kerbal::utility::forward<Rhs>(rhs) } -> kerbal::concepts::same_as<Lhs>;
			}
		;

	} // namespace concepts

} // namespace kerbal

#endif // if KERBAL_HAS_CONCEPTS_SUPPORT

#endif // KERBAL_CONCEPTS_ASSIGNABLE_FROM_HPP
