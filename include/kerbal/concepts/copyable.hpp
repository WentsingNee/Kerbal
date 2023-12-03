/**
 * @file       copyable.hpp
 * @brief
 * @date       2024-01-29
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONCEPTS_COPYABLE_HPP
#define KERBAL_CONCEPTS_COPYABLE_HPP

#include <kerbal/concepts/config.hpp>

#if KERBAL_HAS_CONCEPTS_SUPPORT

#include <kerbal/concepts/assignable_from.hpp>
#include <kerbal/concepts/copy_constructible.hpp>
#include <kerbal/concepts/movable.hpp>


namespace kerbal
{

	namespace concepts
	{

		template <typename T>
		KERBAL_CONCEPT copyable =
			kerbal::concepts::copy_constructible<T> &&
			kerbal::concepts::movable<T> &&
			kerbal::concepts::assignable_from<T &, T &> &&
			kerbal::concepts::assignable_from<T &, const T &> &&
			kerbal::concepts::assignable_from<T &, const T> &&
		;

	} // namespace concepts

} // namespace kerbal

#endif // if KERBAL_HAS_CONCEPTS_SUPPORT

#endif // KERBAL_CONCEPTS_COPYABLE_HPP
