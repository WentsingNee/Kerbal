/**
 * @file       is_nothrow_copy_constructible.part.hpp
 * @brief
 * @date       2023-05-04
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_NOTHROW_COPY_CONSTRUCTIBLE_IS_NOTHROW_COPY_CONSTRUCTIBLE_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_NOTHROW_COPY_CONSTRUCTIBLE_IS_NOTHROW_COPY_CONSTRUCTIBLE_PART_HPP

#include <kerbal/type_traits/detail/is_nothrow_copy_constructible/is_nothrow_copy_constructible.intrin.part.hpp>
#include <kerbal/type_traits/detail/is_nothrow_copy_constructible/is_nothrow_copy_constructible.isntc.part.hpp>

#ifndef KERBAL_HAS_IS_NOTHROW_COPY_CONSTRUCTIBLE_SUPPORT
#	define KERBAL_HAS_IS_NOTHROW_COPY_CONSTRUCTIBLE_SUPPORT 0

#	if KERBAL_TYPE_TRAITS_DEBUG_WARNING

#		include <kerbal/config/compiler_id.hpp>

#		if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC
#			pragma message ("Kerbal Warning: " "kerbal::type_traits::is_nothrow_copy_constructible is not supported")
#		else
#			warning "Kerbal Warning: " "kerbal::type_traits::is_nothrow_copy_constructible is not supported"
#		endif

#	endif

#endif


#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_NOTHROW_COPY_CONSTRUCTIBLE_IS_NOTHROW_COPY_CONSTRUCTIBLE_PART_HPP
