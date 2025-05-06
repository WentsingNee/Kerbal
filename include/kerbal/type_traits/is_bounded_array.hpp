/**
 * @file       is_bounded_array.hpp
 * @brief
 * @date       2022-10-22
 * @author     Peter
 * @remark     split up from kerbal/type_traits/array_traits.hpp, 2019-5-5
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_IS_BOUNDED_ARRAY_HPP
#define KERBAL_TYPE_TRAITS_IS_BOUNDED_ARRAY_HPP

#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>


namespace kerbal
{

	namespace type_traits
	{

		template <typename>
		struct is_bounded_array : kerbal::type_traits::false_type
		{
		};

		template <typename T, std::size_t N>
		struct is_bounded_array<T[N]> : kerbal::type_traits::true_type
		{
		};

	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_IS_BOUNDED_ARRAY_HPP
