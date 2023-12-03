/**
 * @file       swappable_with.hpp
 * @brief
 * @date       2020-02-29
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONCEPTS_SWAPPABLE_WITH_HPP
#define KERBAL_CONCEPTS_SWAPPABLE_WITH_HPP

#include <kerbal/concepts/config.hpp>

#if KERBAL_HAS_CONCEPTS_SUPPORT

#include <kerbal/algorithm/swap.hpp>


namespace kerbal
{

	namespace concepts
	{

		// template <typename T, typename U>
		// KERBAL_CONCEPT swappable_with =
		// 		requires (T && t, U && u) {
		// 			true;
		// 		}
		// ;

	} // namespace concepts

} // namespace kerbal

#endif // if KERBAL_HAS_CONCEPTS_SUPPORT

#endif // KERBAL_CONCEPTS_SWAPPABLE_WITH_HPP
