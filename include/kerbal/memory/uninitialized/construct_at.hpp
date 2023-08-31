/**
 * @file       construct_at.hpp
 * @brief
 * @date       2023-08-31
 * @remark     split from <kerbal/memory/uninitalized/construct.hpp>, 2023-08-31
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_UNINITIALIZED_CONSTRUCT_AT_HPP
#define KERBAL_MEMORY_UNINITIALIZED_CONSTRUCT_AT_HPP

#if __cplusplus > 201703L
#	include <kerbal/memory/uninitialized/detail/construct_at/construct_at.cxx20.part.hpp>
#elif __cplusplus >= 201103L
#	include <kerbal/memory/uninitialized/detail/construct_at/construct_at.cxx11.part.hpp>
#else
#	include <kerbal/memory/uninitialized/detail/construct_at/construct_at.cxx98.part.hpp>
#endif

#include <kerbal/memory/uninitialized/detail/construct_at/construct_at_array.part.hpp>


#include <kerbal/memory/uninitialized/uninitialized_value_construct.hpp>
#include <kerbal/memory/uninitialized/uninitialized_copy.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/memory/uninitialized/uninitialized_move.hpp>
#endif

#endif // KERBAL_MEMORY_UNINITIALIZED_CONSTRUCT_AT_HPP
