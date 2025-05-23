/**
 * @file       rank.hpp
 * @brief
 * @date       2022-10-23
 * @author     Peter
 * @remark     split up from kerbal/type_traits/array_traits.hpp, 2019-5-5
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_RANK_HPP
#define KERBAL_TYPE_TRAITS_RANK_HPP

#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>


namespace kerbal
{

	namespace type_traits
	{

		template <typename >
		struct rank : kerbal::type_traits::integral_constant<std::size_t, 0>
		{
		};

		template <typename T, std::size_t N>
		struct rank<T[N]> :
			kerbal::type_traits::integral_constant<std::size_t, 1 + rank<T>::value>
		{
		};

		template <typename T>
		struct rank<T[]> :
			kerbal::type_traits::integral_constant<std::size_t, 1 + rank<T>::value>
		{
		};

	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_RANK_HPP
