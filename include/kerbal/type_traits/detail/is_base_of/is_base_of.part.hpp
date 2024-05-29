/**
 * @file       is_base_of.part.hpp
 * @brief
 * @date       2023-04-27
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_BASE_OF_IS_BASE_OF_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_BASE_OF_IS_BASE_OF_PART_HPP

#include <kerbal/type_traits/detail/is_base_of/is_base_of.intrin.part.hpp>
#include <kerbal/type_traits/detail/is_base_of/is_base_of.std.part.hpp>

#ifndef KERBAL_SUPPORTS_IS_BASE_OF
#	define KERBAL_SUPPORTS_IS_BASE_OF 0

#	if KERBAL_TYPE_TRAITS_DEBUG_WARNING

#		include <kerbal/config/compiler_id.hpp>

#		if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC
#			pragma message ("Kerbal Warning: " "kerbal::type_traits::is_base_of is not supported")
#		else
#			warning "Kerbal Warning: " "kerbal::type_traits::is_base_of is not supported"
#		endif

#	endif

#endif


#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_BASE_OF_IS_BASE_OF_PART_HPP
