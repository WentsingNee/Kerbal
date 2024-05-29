/**
 * @file       try_test_is_nothrow_constructible.part.hpp
 * @brief
 * @date       2023-05-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_NOTHROW_CONSTRUCTIBLE_TRY_TEST_IS_NOTHROW_CONSTRUCTIBLE_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_NOTHROW_CONSTRUCTIBLE_TRY_TEST_IS_NOTHROW_CONSTRUCTIBLE_PART_HPP

#include <kerbal/type_traits/detail/is_nothrow_constructible/is_nothrow_constructible.part.hpp>

#if KERBAL_SUPPORTS_IS_NOTHROW_CONSTRUCTIBLE
#	include <kerbal/type_traits/detail/is_nothrow_constructible/try_test_is_nothrow_constructible.defi.part.hpp>
#else
#	include <kerbal/type_traits/detail/is_nothrow_constructible/try_test_is_nothrow_constructible.guess.part.hpp>
#endif

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_NOTHROW_CONSTRUCTIBLE_TRY_TEST_IS_NOTHROW_CONSTRUCTIBLE_PART_HPP
