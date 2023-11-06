/**
 * @file       is_trivially_move_constructible.std.part.hpp
 * @brief
 * @date       2023-05-04
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_STD_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_STD_PART_HPP

#ifndef KERBAL_HAS_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_SUPPORT

#if __cplusplus >= 201103L

#	include <kerbal/config/compiler_id.hpp>

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU
#		include <kerbal/config/compiler_private.hpp>
#		if KERBAL_GNU_VERSION_MEETS(5, 0, 0)
#			define KERBAL_HAS_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_SUPPORT 1
#		endif
#	else
#		define KERBAL_HAS_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_SUPPORT 1
#	endif

#endif // #if __cplusplus >= 201103L



#if KERBAL_HAS_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_SUPPORT

#include <kerbal/type_traits/integral_constant.hpp>

#include <type_traits>


#if KERBAL_TYPE_TRAITS_DEBUG_WARNING

#	include <kerbal/config/compiler_id.hpp>

#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC
#		pragma message ("Kerbal Warning: " "can not detect the builtin is_trivially_move_constructible function, <type_traits> header has been included")
#	else
#		warning "Kerbal Warning: " "can not detect the builtin is_trivially_move_constructible function, <type_traits> header has been included"
#	endif

#endif


namespace kerbal
{

	namespace type_traits
	{

		template <typename T>
		struct is_trivially_move_constructible :
				kerbal::type_traits::bool_constant<
					std::is_trivially_move_constructible<T>::value
				>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // #if KERBAL_HAS_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_SUPPORT

#endif // #ifndef KERBAL_HAS_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_SUPPORT

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_STD_PART_HPP
