/**
 * @file       try_test_is_base_of.part.hpp
 * @brief
 * @date       2023-04-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_BASE_OF_TRY_TEST_IS_BASE_OF_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_BASE_OF_TRY_TEST_IS_BASE_OF_PART_HPP

#include <kerbal/type_traits/detail/is_base_of/is_base_of.part.hpp>

#if KERBAL_HAS_IS_BASE_OF_SUPPORT
#	include <kerbal/type_traits/detail/is_base_of/try_test_is_base_of.defi.part.hpp>
#else
#	include <kerbal/type_traits/detail/is_base_of/try_test_is_base_of.guess.part.hpp>
#endif

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_BASE_OF_TRY_TEST_IS_BASE_OF_PART_HPP
