/**
 * @file       remove_extent.hpp
 * @brief
 * @date       2022-10-23
 * @author     Peter
 * @remark     split up from kerbal/type_traits/array_traits.hpp, 2019-5-5
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_REMOVE_EXTENT_HPP
#define KERBAL_TYPE_TRAITS_REMOVE_EXTENT_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>


namespace kerbal
{

	namespace type_traits
	{

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct remove_extent
		{
				typedef T type;
		};

		KERBAL_MODULE_EXPORT
		template <typename T, std::size_t N>
		struct remove_extent<T[N]>
		{
				typedef T type;
		};

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct remove_extent<T[]>
		{
				typedef T type;
		};

	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_REMOVE_EXTENT_HPP
