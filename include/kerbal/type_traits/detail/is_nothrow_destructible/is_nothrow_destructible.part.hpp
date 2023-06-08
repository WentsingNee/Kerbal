/**
 * @file       is_nothrow_destructible.part.hpp
 * @brief
 * @date       2023-05-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_NOTHROW_DESTRUCTIBLE_IS_NOTHROW_DESTRUCTIBLE_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_NOTHROW_DESTRUCTIBLE_IS_NOTHROW_DESTRUCTIBLE_PART_HPP

#include <kerbal/type_traits/detail/is_nothrow_destructible/is_nothrow_destructible.noexcept.part.hpp>
#include <kerbal/type_traits/detail/is_nothrow_destructible/is_nothrow_destructible.intrin.part.hpp>
#include <kerbal/type_traits/detail/is_nothrow_destructible/is_nothrow_destructible.isdes.part.hpp>

#ifndef KERBAL_HAS_IS_NOTHROW_DESTRUCTIBLE_SUPPORT
#	define KERBAL_HAS_IS_NOTHROW_DESTRUCTIBLE_SUPPORT 0

#	if KERBAL_TYPE_TRAITS_DEBUG_WARNING

#		include <kerbal/config/compiler_id.hpp>

#		if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC
#			pragma message ("Kerbal Warning: " "kerbal::type_traits::is_nothrow_destructible is not supported")
#		else
#			warning "Kerbal Warning: " "kerbal::type_traits::is_nothrow_destructible is not supported"
#		endif

#	endif

#endif


#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_NOTHROW_DESTRUCTIBLE_IS_NOTHROW_DESTRUCTIBLE_PART_HPP
