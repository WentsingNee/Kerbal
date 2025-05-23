/**
 * @file       remove_all_extents.hpp
 * @brief
 * @date       2022-10-23
 * @author     Peter
 * @remark     split up from kerbal/type_traits/array_traits.hpp, 2019-5-5
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_REMOVE_ALL_EXTENTS_HPP
#define KERBAL_TYPE_TRAITS_REMOVE_ALL_EXTENTS_HPP


#include <cstddef>


namespace kerbal
{

	namespace type_traits
	{

		template <typename T>
		struct remove_all_extents
		{
				typedef T type;
		};

		template <typename T, std::size_t N>
		struct remove_all_extents<T[N]> :
			kerbal::type_traits::remove_all_extents<T>
		{
		};

		template <typename T>
		struct remove_all_extents<T[]> :
			kerbal::type_traits::remove_all_extents<T>
		{
		};

	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_REMOVE_ALL_EXTENTS_HPP
