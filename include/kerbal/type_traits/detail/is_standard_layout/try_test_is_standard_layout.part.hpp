/**
 * @file       try_test_is_standard_layout.part.hpp
 * @brief
 * @date       2023-05-05
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_STANDARD_LAYOUT_TRY_TEST_IS_STANDARD_LAYOUT_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_STANDARD_LAYOUT_TRY_TEST_IS_STANDARD_LAYOUT_PART_HPP

#include <kerbal/type_traits/detail/is_standard_layout/is_standard_layout.part.hpp>

#if KERBAL_SUPPORTS_IS_STANDARD_LAYOUT
#	include <kerbal/type_traits/detail/is_standard_layout/try_test_is_standard_layout.defi.part.hpp>
#else
#	include <kerbal/type_traits/detail/is_standard_layout/try_test_is_standard_layout.guess.part.hpp>
#endif

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_STANDARD_LAYOUT_TRY_TEST_IS_STANDARD_LAYOUT_PART_HPP
