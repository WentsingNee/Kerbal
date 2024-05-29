/**
 * @file       try_test_is_nothrow_destructible.part.hpp
 * @brief
 * @date       2023-05-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_NOTHROW_DESTRUCTIBLE_TRY_TEST_IS_NOTHROW_DESTRUCTIBLE_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_NOTHROW_DESTRUCTIBLE_TRY_TEST_IS_NOTHROW_DESTRUCTIBLE_PART_HPP

#include <kerbal/type_traits/detail/is_nothrow_destructible/is_nothrow_destructible.part.hpp>

#if KERBAL_SUPPORTS_IS_NOTHROW_DESTRUCTIBLE
#	include <kerbal/type_traits/detail/is_nothrow_destructible/try_test_is_nothrow_destructible.defi.part.hpp>
#else
#	include <kerbal/type_traits/detail/is_nothrow_destructible/try_test_is_nothrow_destructible.guess.part.hpp>
#endif

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_NOTHROW_DESTRUCTIBLE_TRY_TEST_IS_NOTHROW_DESTRUCTIBLE_PART_HPP
