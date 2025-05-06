/**
 * @file       remove_const.hpp
 * @brief
 * @date       2022-10-24
 * @author     Peter
 * @remark     split up from kerbal/type_traits/const_deduction.hpp, 2019-4-29
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_REMOVE_CONST_HPP
#define KERBAL_TYPE_TRAITS_REMOVE_CONST_HPP


#include <kerbal/config/compiler_id.hpp>

#if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC // VS2012 compatible
#	include <cstddef>
#endif


namespace kerbal
{

	namespace type_traits
	{

		template <typename T>
		struct remove_const
		{
				typedef T type;
		};

		template <typename T>
		struct remove_const<const T>
		{
				typedef T type;
		};

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC // VS2012 compatible

		template <typename T>
		struct remove_const<const T[]>
		{
				typedef T type [];
		};

		template <typename T, std::size_t N>
		struct remove_const<const T[N]>
		{
				typedef T type [N];
		};

#	endif

	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_REMOVE_CONST_HPP
