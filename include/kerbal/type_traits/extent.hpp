/**
 * @file       extent.hpp
 * @brief
 * @date       2022-10-22
 * @author     Peter
 * @remark     split up from kerbal/type_traits/array_traits.hpp, 2019-5-5
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_EXTENT_HPP
#define KERBAL_TYPE_TRAITS_EXTENT_HPP

#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>


namespace kerbal
{

	namespace type_traits
	{

		template <typename T, std::size_t I = 0>
		struct extent;

		template <typename T>
		struct extent<T, 0> :
			kerbal::type_traits::integral_constant<std::size_t, 0>
		{
		};

		template <typename T>
		struct extent<T[], 0> :
			kerbal::type_traits::integral_constant<std::size_t, 0>
		{
		};

		template <typename T, std::size_t I>
		struct extent<T[], I> :
			kerbal::type_traits::extent<T, I - 1>
		{
		};

		template <typename T, std::size_t N>
		struct extent<T[N], 0> :
			kerbal::type_traits::integral_constant<std::size_t, N>
		{
		};

		template <typename T, std::size_t N, std::size_t I>
		struct extent<T[N], I> :
			kerbal::type_traits::extent<T, I - 1>
		{
		};

	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_EXTENT_HPP
