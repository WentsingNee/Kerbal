/**
 * @file       is_empty.part.hpp
 * @brief
 * @date       2023-04-27
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_EMPTY_IS_EMPTY_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_EMPTY_IS_EMPTY_PART_HPP

#include <kerbal/type_traits/detail/is_empty/is_empty.intrin.part.hpp>
#include <kerbal/type_traits/detail/is_empty/is_empty.std.part.hpp>

#ifndef KERBAL_SUPPORTS_IS_EMPTY
#	define KERBAL_SUPPORTS_IS_EMPTY 0

#	if KERBAL_TYPE_TRAITS_DEBUG_WARNING

#		include <kerbal/config/compiler_id.hpp>

#		if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC
#			pragma message ("Kerbal Warning: " "kerbal::type_traits::is_empty is not supported")
#		else
#			warning "Kerbal Warning: " "kerbal::type_traits::is_empty is not supported"
#		endif

#	endif

#endif


#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_EMPTY_IS_EMPTY_PART_HPP
