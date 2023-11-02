/**
 * @file       std_allocator.hpp
 * @brief
 * @date       2023-10-29
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_STD_ALLOCATOR_HPP
#define KERBAL_MEMORY_ALLOCATOR_STD_ALLOCATOR_HPP

#include <kerbal/config/cxx_stdlib.hpp>

#if KERBAL_CXX_STDLIB == KERBAL_CXX_STDLIB_LIBSTDCXX

#	include <bits/allocator.h>

#elif KERBAL_CXX_STDLIB == KERBAL_CXX_STDLIB_LIBCXX

#	include <__memory/allocator.h>

#else

#	include <memory>

#endif


#endif // KERBAL_MEMORY_ALLOCATOR_STD_ALLOCATOR_HPP
