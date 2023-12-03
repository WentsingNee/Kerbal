/**
 * @file       boolean.hpp
 * @brief
 * @date       2020-02-29
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONCEPTS_BOOLEAN_HPP
#define KERBAL_CONCEPTS_BOOLEAN_HPP

#include <kerbal/concepts/config.hpp>

#if KERBAL_HAS_CONCEPTS_SUPPORT

#include <kerbal/concepts/convertible_to.hpp>
#include <kerbal/concepts/same_as.hpp>

#include <kerbal/type_traits/remove_cvref.hpp>
#include <kerbal/type_traits/remove_reference.hpp>

#if __cplusplus >= 201103L
#	include <type_traits>
#endif


namespace kerbal
{

	namespace concepts
	{

		template <typename B>
		KERBAL_CONCEPT boolean =
			std::movable<typename kerbal::type_traits::remove_cvref<B>::type> &&
			requires(
				const kerbal::type_traits::remove_reference<B>::type & b1,
				const kerbal::type_traits::remove_reference<B>::type & b2, const bool a
			) {
				{ b1 } -> kerbal::concepts::convertible_to<bool>;
				{ !b1 } -> kerbal::concepts::convertible_to<bool>;
				{ b1 && b2 } -> kerbal::concepts::same_as<bool>;
				{ b1 &&  a } -> kerbal::concepts::same_as<bool>;
				{  a && b2 } -> kerbal::concepts::same_as<bool>;
				{ b1 || b2 } -> kerbal::concepts::same_as<bool>;
				{ b1 ||  a } -> kerbal::concepts::same_as<bool>;
				{  a || b2 } -> kerbal::concepts::same_as<bool>;
				{ b1 == b2 } -> kerbal::concepts::convertible_to<bool>;
				{ b1 ==  a } -> kerbal::concepts::convertible_to<bool>;
				{  a == b2 } -> kerbal::concepts::convertible_to<bool>;
				{ b1 != b2 } -> kerbal::concepts::convertible_to<bool>;
				{ b1 !=  a } -> kerbal::concepts::convertible_to<bool>;
				{  a != b2 } -> kerbal::concepts::convertible_to<bool>;
			}
		;

	} // namespace concepts

} // namespace kerbal

#endif // if KERBAL_HAS_CONCEPTS_SUPPORT

#endif // KERBAL_CONCEPTS_BOOLEAN_HPP
