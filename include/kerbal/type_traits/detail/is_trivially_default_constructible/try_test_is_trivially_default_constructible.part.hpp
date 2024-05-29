/**
 * @file       try_test_is_trivially_default_constructible.part.hpp
 * @brief
 * @date       2023-05-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TRY_TEST_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TRY_TEST_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_PART_HPP

#include <kerbal/type_traits/detail/is_trivially_default_constructible/is_trivially_default_constructible.part.hpp>

#if KERBAL_SUPPORTS_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE
#	include <kerbal/type_traits/detail/is_trivially_default_constructible/try_test_is_trivially_default_constructible.defi.part.hpp>
#else
#	include <kerbal/type_traits/detail/is_trivially_default_constructible/try_test_is_trivially_default_constructible.guess.part.hpp>
#endif

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TRY_TEST_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_PART_HPP
