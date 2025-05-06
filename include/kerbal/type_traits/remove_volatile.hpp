/**
 * @file       remove_volatile.hpp
 * @brief
 * @date       2022-10-29
 * @author     Peter
 * @remark     split up from kerbal/type_traits/volatile_deduction.hpp, 2019-4-29
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_REMOVE_VOLATILE_HPP
#define KERBAL_TYPE_TRAITS_REMOVE_VOLATILE_HPP


#include <kerbal/config/compiler_id.hpp>

#if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC // VS2012 compatible
#	include <cstddef>
#endif


namespace kerbal
{

	namespace type_traits
	{

		template <typename T>
		struct remove_volatile
		{
				typedef T type;
		};

		template <typename T>
		struct remove_volatile<volatile T>
		{
				typedef T type;
		};

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC // VS2012 compatible

		template <typename T>
		struct remove_volatile<volatile T[]>
		{
				typedef T type [];
		};

		template <typename T, std::size_t N>
		struct remove_volatile<volatile T[N]>
		{
				typedef T type [N];
		};

#	endif

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_REMOVE_VOLATILE_HPP
