/**
 * @file       pointer.hpp
 * @brief
 * @date       2020-02-29
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONCEPTS_POINTER_HPP
#define KERBAL_CONCEPTS_POINTER_HPP

#include <kerbal/concepts/config.hpp>

#include <kerbal/type_traits/pointer_deduction.hpp>

namespace kerbal
{

	namespace concepts
	{

#if defined(KERBAL_ENABLE_CONCEPTS)

		template <typename Tp>
		KERBAL_CONCEPT pointer = kerbal::type_traits::is_pointer<Tp>::value;

#endif

	}

}

#endif // KERBAL_CONCEPTS_POINTER_HPP
