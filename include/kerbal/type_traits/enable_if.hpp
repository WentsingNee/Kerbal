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

		MODULE_EXPORT
		template <bool condition, typename Tp = void>
		struct enable_if
		{
		};

		MODULE_EXPORT
		template <typename Tp>
		struct enable_if<true, Tp>
		{
				typedef Tp type;
		};

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_ENABLE_IF_HPP
