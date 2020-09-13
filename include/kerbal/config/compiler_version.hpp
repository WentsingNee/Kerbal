/**
 * @file       compiler_version.hpp
 * @brief
 * @date       2020-07-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONFIG_COMPILER_VERSION_HPP
#define KERBAL_CONFIG_COMPILER_VERSION_HPP

#include <kerbal/config/compiler_id.hpp>


#if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU
#	include <kerbal/config/compiler_private/gnu/compiler_version.hpp>
#elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_CLANG
#	include <kerbal/config/compiler_private/clang/compiler_version.hpp>
#elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC
#	include <kerbal/config/compiler_private/msvc/compiler_version.hpp>
#elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC
#	include <kerbal/config/compiler_private/icc/compiler_version.hpp>
#endif


#endif // KERBAL_CONFIG_COMPILER_VERSION_HPP
