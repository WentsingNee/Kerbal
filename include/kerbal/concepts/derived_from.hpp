/**
 * @file       derived_from.hpp
 * @brief
 * @date       2020-02-29
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONCEPTS_DERIVED_FROM_HPP
#define KERBAL_CONCEPTS_DERIVED_FROM_HPP

#include <kerbal/concepts/config.hpp>

#if KERBAL_HAS_CONCEPTS_SUPPORT

#if __cplusplus >= 201103L
#	include <type_traits>
#endif


namespace kerbal
{

	namespace concepts
	{

#	if __cplusplus >= 201103L

		template <typename Derived, typename Base>
		KERBAL_CONCEPT derived_from =
			std::is_base_of<Base, Derived>::value &&
			std::is_convertible<const volatile Derived *, const volatile Base *>::value
		;

#	endif

	} // namespace concepts

} // namespace kerbal

#endif // if KERBAL_HAS_CONCEPTS_SUPPORT

#endif // KERBAL_CONCEPTS_DERIVED_FROM_HPP
