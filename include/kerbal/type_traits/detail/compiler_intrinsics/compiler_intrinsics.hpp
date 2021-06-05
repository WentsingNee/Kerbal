/**
 * @file       compiler_intrinsics.hpp
 * @brief
 * @date       2022-10-21
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_COMPILER_INTRINSICS_COMPILER_INTRINSICS_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_COMPILER_INTRINSICS_COMPILER_INTRINSICS_HPP

#include <kerbal/config/compiler_id.hpp>

#if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU
#	include <kerbal/type_traits/detail/compiler_intrinsics/part/_0_gnu.part.hpp>
#elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_CLANG
#	include <kerbal/type_traits/detail/compiler_intrinsics/part/_1_clang.part.hpp>
#elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC
#	include <kerbal/type_traits/detail/compiler_intrinsics/part/_2_msvc.part.hpp>
#elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC
#	include <kerbal/type_traits/detail/compiler_intrinsics/part/_3_icc.part.hpp>
#endif

#endif // KERBAL_TYPE_TRAITS_DETAIL_COMPILER_INTRINSICS_COMPILER_INTRINSICS_HPP
