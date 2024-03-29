/**
 * @file       compiler_private.hpp
 * @brief
 * @date       2020-07-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONFIG_COMPILER_PRIVATE_HPP
#define KERBAL_CONFIG_COMPILER_PRIVATE_HPP

#include <kerbal/config/compiler_id.hpp>


#if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU
#	include <kerbal/config/detail/compiler_private/_0_gnu.part.hpp>
#elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_CLANG
#	include <kerbal/config/detail/compiler_private/_1_clang.part.hpp>
#elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC
#	include <kerbal/config/detail/compiler_private/_2_msvc.part.hpp>
#elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC
#	include <kerbal/config/detail/compiler_private/_3_icc.part.hpp>
#endif


#endif // KERBAL_CONFIG_COMPILER_PRIVATE_HPP
