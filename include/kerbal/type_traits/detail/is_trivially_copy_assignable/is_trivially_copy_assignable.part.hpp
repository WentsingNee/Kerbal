/**
 * @file       is_trivially_copy_assignable.part.hpp
 * @brief
 * @date       2023-05-04
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_COPY_ASSIGNABLE_IS_TRIVIALLY_COPY_ASSIGNABLE_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_COPY_ASSIGNABLE_IS_TRIVIALLY_COPY_ASSIGNABLE_PART_HPP

#include <kerbal/type_traits/detail/is_trivially_copy_assignable/is_trivially_copy_assignable.intrin.part.hpp>
#include <kerbal/type_traits/detail/is_trivially_copy_assignable/is_trivially_copy_assignable.istria.part.hpp>
#include <kerbal/type_traits/detail/is_trivially_copy_assignable/is_trivially_copy_assignable.std.part.hpp>

#ifndef KERBAL_SUPPORTS_IS_TRIVIALLY_COPY_ASSIGNABLE
#	define KERBAL_SUPPORTS_IS_TRIVIALLY_COPY_ASSIGNABLE 0

#	if KERBAL_TYPE_TRAITS_DEBUG_WARNING

#		include <kerbal/config/compiler_id.hpp>

#		if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC
#			pragma message ("Kerbal Warning: " "kerbal::type_traits::is_trivially_copy_assignable is not supported")
#		else
#			warning "Kerbal Warning: " "kerbal::type_traits::is_trivially_copy_assignable is not supported"
#		endif

#	endif

#endif


#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_COPY_ASSIGNABLE_IS_TRIVIALLY_COPY_ASSIGNABLE_PART_HPP
