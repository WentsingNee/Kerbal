/**
 * @file       same_as.hpp
 * @brief
 * @date       2020-02-29
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONCEPTS_SAME_AS_HPP
#define KERBAL_CONCEPTS_SAME_AS_HPP

#include <kerbal/concepts/config.hpp>

#if KERBAL_HAS_CONCEPTS_SUPPORT

#include <kerbal/type_traits/is_same.hpp>


namespace kerbal
{

	namespace concepts
	{

		template <typename T, typename U>
		KERBAL_CONCEPT same_as =
			kerbal::type_traits::is_same<T, U>::value &&
			kerbal::type_traits::is_same<U, T>::value
		;

	} // namespace concepts

} // namespace kerbal

#endif // if KERBAL_HAS_CONCEPTS_SUPPORT

#endif // KERBAL_CONCEPTS_SAME_AS_HPP
