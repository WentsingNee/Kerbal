/**
 * @file       compare.hpp
 * @brief
 * @date       2020-02-29
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONCEPTS_CXX_20_COMPARE_HPP
#define KERBAL_CONCEPTS_CXX_20_COMPARE_HPP

#include <kerbal/concepts/config.hpp>
#include <kerbal/concepts/cxx_20/core.hpp>

#include <kerbal/type_traits/cv_deduction.hpp>

#if __cplusplus >= 201103L
#	include <type_traits>
#endif

namespace kerbal
{

	namespace concepts
	{

#if defined(KERBAL_ENABLE_CONCEPTS)

		template <typename B>
		KERBAL_CONCEPT boolean =
				std::movable<typename kerbal::type_traits::remove_cvref<B>::type> &&
				requires(const std::remove_reference<B>::type & b1, const std::remove_reference<B>::type & b2, const bool a) {
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
				};

#endif

	}

}

#endif // KERBAL_CONCEPTS_CXX_20_COMPARE_HPP
