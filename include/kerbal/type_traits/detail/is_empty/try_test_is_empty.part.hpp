/**
 * @file       try_test_is_empty.part.hpp
 * @brief
 * @date       2023-04-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_EMPTY_TRY_TEST_IS_EMPTY_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_EMPTY_TRY_TEST_IS_EMPTY_PART_HPP

#include <kerbal/type_traits/detail/is_empty/is_empty.part.hpp>

#if KERBAL_HAS_IS_EMPTY_SUPPORT
#	include <kerbal/type_traits/detail/is_empty/try_test_is_empty.defi.part.hpp>
#else
#	include <kerbal/type_traits/detail/is_empty/try_test_is_empty.guess.part.hpp>
#endif

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_EMPTY_TRY_TEST_IS_EMPTY_PART_HPP
