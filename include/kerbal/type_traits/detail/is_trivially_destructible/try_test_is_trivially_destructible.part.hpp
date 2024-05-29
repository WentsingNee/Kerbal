/**
 * @file       try_test_is_trivially_destructible.part.hpp
 * @brief
 * @date       2023-05-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_DESTRUCTIBLE_TRY_TEST_IS_TRIVIALLY_DESTRUCTIBLE_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_DESTRUCTIBLE_TRY_TEST_IS_TRIVIALLY_DESTRUCTIBLE_PART_HPP

#include <kerbal/type_traits/detail/is_trivially_destructible/is_trivially_destructible.part.hpp>

#if KERBAL_SUPPORTS_IS_TRIVIALLY_DESTRUCTIBLE
#	include <kerbal/type_traits/detail/is_trivially_destructible/try_test_is_trivially_destructible.defi.part.hpp>
#else
#	include <kerbal/type_traits/detail/is_trivially_destructible/try_test_is_trivially_destructible.guess.part.hpp>
#endif

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_DESTRUCTIBLE_TRY_TEST_IS_TRIVIALLY_DESTRUCTIBLE_PART_HPP
