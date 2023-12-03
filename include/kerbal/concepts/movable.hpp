/**
 * @file       movable.hpp
 * @brief
 * @date       2020-02-29
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONCEPTS_MOVABLE_HPP
#define KERBAL_CONCEPTS_MOVABLE_HPP

#include <kerbal/concepts/config.hpp>

#if KERBAL_HAS_CONCEPTS_SUPPORT

#include <kerbal/concepts/assignable_from.hpp>
#include <kerbal/concepts/move_constructible.hpp>
#include <kerbal/concepts/swappable.hpp>

#include <type_traits>


namespace kerbal
{

	namespace concepts
	{

		template <typename T>
		KERBAL_CONCEPT movable =
			std::is_object<T>::value &&
			kerbal::concepts::move_constructible<T> &&
			kerbal::concepts::assignable_from<T &, T> &&
			kerbal::concepts::swappable<T>
		;

	} // namespace concepts

} // namespace kerbal

#endif // if KERBAL_HAS_CONCEPTS_SUPPORT

#endif // KERBAL_CONCEPTS_MOVABLE_HPP
