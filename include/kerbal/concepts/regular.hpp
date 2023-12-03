/**
 * @file       regular.hpp
 * @brief
 * @date       2024-01-29
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONCEPTS_REGULAR_HPP
#define KERBAL_CONCEPTS_REGULAR_HPP

#include <kerbal/concepts/config.hpp>

#if KERBAL_HAS_CONCEPTS_SUPPORT

#include <kerbal/concepts/equality_comparable.hpp>
#include <kerbal/concepts/semiregular.hpp>


namespace kerbal
{

	namespace concepts
	{

		template <typename T>
		KERBAL_CONCEPT regular =
			kerbal::concepts::semiregular<T> &&
			kerbal::concepts::equality_comparable<T>
		;

	} // namespace concepts

} // namespace kerbal

#endif // if KERBAL_HAS_CONCEPTS_SUPPORT

#endif // KERBAL_CONCEPTS_REGULAR_HPP
