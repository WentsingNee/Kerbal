/**
 * @file       default_initializable.hpp
 * @brief
 * @date       2024-01-29
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONCEPTS_DEFAULT_INITIALIZABLE_HPP
#define KERBAL_CONCEPTS_DEFAULT_INITIALIZABLE_HPP

#include <kerbal/concepts/config.hpp>

#if KERBAL_HAS_CONCEPTS_SUPPORT

#include <kerbal/concepts/constructible_from.hpp>

#include <new>


namespace kerbal
{

	namespace concepts
	{

		template <typename T>
		KERBAL_CONCEPT default_initializable =
			kerbal::concepts::constructible_from<T> &&
			requires { T{}; } &&
			requires { ::new T; } &&
		;

	} // namespace concepts

} // namespace kerbal

#endif // if KERBAL_HAS_CONCEPTS_SUPPORT

#endif // KERBAL_CONCEPTS_DEFAULT_INITIALIZABLE_HPP
