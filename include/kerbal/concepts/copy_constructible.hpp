/**
 * @file       copy_constructible.hpp
 * @brief
 * @date       2024-01-29
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONCEPTS_COPY_CONSTRUCTIBLE_HPP
#define KERBAL_CONCEPTS_COPY_CONSTRUCTIBLE_HPP

#include <kerbal/concepts/config.hpp>

#if KERBAL_HAS_CONCEPTS_SUPPORT

#include <kerbal/concepts/constructible_from.hpp>
#include <kerbal/concepts/convertible_to.hpp>
#include <kerbal/concepts/move_constructible.hpp>


namespace kerbal
{

	namespace concepts
	{

		template <typename T>
		KERBAL_CONCEPT copy_constructible =
			kerbal::concepts::move_constructible<T> &&
			(
				kerbal::concepts::constructible_from<T, T &> &&
				kerbal::concepts::convertible_to<T &, T>
			) &&
			(
				kerbal::concepts::constructible_from<T, const T &> &&
				kerbal::concepts::convertible_to<const T &, T>
			) &&
			(
				kerbal::concepts::constructible_from<T, const T> &&
				kerbal::concepts::convertible_to<const T, T>
			)
		;

	} // namespace concepts

} // namespace kerbal

#endif // if KERBAL_HAS_CONCEPTS_SUPPORT

#endif // KERBAL_CONCEPTS_COPY_CONSTRUCTIBLE_HPP
