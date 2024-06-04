/**
 * @file       enable_if.hpp
 * @brief
 * @date       2019-4-29
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_ENABLE_IF_HPP
#define KERBAL_TYPE_TRAITS_ENABLE_IF_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

namespace kerbal
{

	namespace type_traits
	{

		KERBAL_MODULE_EXPORT
		template <bool Condition, typename T = void>
		struct enable_if
		{
		};

		/*KERBAL_MODULE_EXPORT*/
		template <typename T>
		struct enable_if<true, T>
		{
				typedef T type;
		};

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_ENABLE_IF_HPP
