/**
 * @file       is_trivially_constructible.std.part.hpp
 * @brief
 * @date       2023-05-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_CONSTRUCTIBLE_IS_TRIVIALLY_CONSTRUCTIBLE_STD_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_CONSTRUCTIBLE_IS_TRIVIALLY_CONSTRUCTIBLE_STD_PART_HPP

#ifndef KERBAL_HAS_IS_TRIVIALLY_CONSTRUCTIBLE_SUPPORT

#if __cplusplus >= 201103L
#	define KERBAL_HAS_IS_TRIVIALLY_CONSTRUCTIBLE_SUPPORT 1
#endif



#if KERBAL_HAS_IS_TRIVIALLY_CONSTRUCTIBLE_SUPPORT

#include <kerbal/type_traits/integral_constant.hpp>

#include <type_traits>


#if KERBAL_TYPE_TRAITS_DEBUG_WARNING

#	include <kerbal/config/compiler_id.hpp>

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC
#		pragma message ("Kerbal Warning: " "can not detect the builtin is_trivially_constructible function, <type_traits> header has been included")
#	else
#		warning "Kerbal Warning: " "can not detect the builtin is_trivially_constructible function, <type_traits> header has been included"
#	endif

#endif


namespace kerbal
{

	namespace type_traits
	{

		template <typename T, typename ... Args>
		struct is_trivially_constructible :
				kerbal::type_traits::bool_constant<
					std::is_trivially_constructible<T, Args...>::value
				>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // #if KERBAL_HAS_IS_TRIVIALLY_CONSTRUCTIBLE_SUPPORT

#endif // #ifndef KERBAL_HAS_IS_TRIVIALLY_CONSTRUCTIBLE_SUPPORT

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_CONSTRUCTIBLE_IS_TRIVIALLY_CONSTRUCTIBLE_STD_PART_HPP
