/**
 * @file       integral.hpp
 * @brief
 * @date       2020-02-29
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONCEPTS_INTEGRAL_HPP
#define KERBAL_CONCEPTS_INTEGRAL_HPP

#include <kerbal/concepts/config.hpp>

#if KERBAL_HAS_CONCEPTS_SUPPORT

#include <kerbal/type_traits/is_integral.hpp>


namespace kerbal
{

	namespace concepts
	{

		template <typename T>
		KERBAL_CONCEPT integral = kerbal::type_traits::is_integral<T>::value;

	} // namespace concepts

} // namespace kerbal

#endif // if KERBAL_HAS_CONCEPTS_SUPPORT

#endif // KERBAL_CONCEPTS_INTEGRAL_HPP
