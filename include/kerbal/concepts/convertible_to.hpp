/**
 * @file       convertible_to.hpp
 * @brief
 * @date       2023-12-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONCEPTS_CONVERTIBLE_TO_HPP
#define KERBAL_CONCEPTS_CONVERTIBLE_TO_HPP

#include <kerbal/concepts/config.hpp>

#if KERBAL_HAS_CONCEPTS_SUPPORT

#include <kerbal/utility/declval.hpp>

#include <type_traits>


namespace kerbal
{

	namespace concepts
	{

		template <typename From, typename To>
		KERBAL_CONCEPT convertible_to =
			std::is_convertible_v<From, To> &&
			requires {
				static_cast<To>(kerbal::utility::declval<From>());
			}
		;

	} // namespace concepts

} // namespace kerbal

#endif // if KERBAL_HAS_CONCEPTS_SUPPORT

#endif // KERBAL_CONCEPTS_CONVERTIBLE_TO_HPP
