/**
 * @file       constructible_from.hpp
 * @brief
 * @date       2023-12-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONCEPTS_CONSTRUCTIBLE_FROM_HPP
#define KERBAL_CONCEPTS_CONSTRUCTIBLE_FROM_HPP

#include <kerbal/concepts/config.hpp>

#if KERBAL_HAS_CONCEPTS_SUPPORT

#include <kerbal/concepts/destructible.hpp>
#include <kerbal/type_traits/is_constructible.hpp>


namespace kerbal
{

	namespace concepts
	{

		template <typename T, typename ... Args>
		KERBAL_CONCEPT constructible_from =
			kerbal::concepts::destructible<T> &&
			kerbal::type_traits::is_constructible<T, Args...>::value
		;

	} // namespace concepts

} // namespace kerbal

#endif // if KERBAL_HAS_CONCEPTS_SUPPORT

#endif // KERBAL_CONCEPTS_CONSTRUCTIBLE_FROM_HPP
