/**
 * @file       try_test_is_copy_constructible.part.hpp
 * @brief
 * @date       2023-06-11
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_COPY_CONSTRUCTIBLE_TRY_TEST_IS_COPY_CONSTRUCTIBLE_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_COPY_CONSTRUCTIBLE_TRY_TEST_IS_COPY_CONSTRUCTIBLE_PART_HPP

#include <kerbal/type_traits/detail/is_copy_constructible/is_copy_constructible.part.hpp>

#if KERBAL_HAS_IS_COPY_CONSTRUCTIBLE_SUPPORT
#	include <kerbal/type_traits/detail/is_copy_constructible/try_test_is_copy_constructible.defi.part.hpp>
#else
#	include <kerbal/type_traits/detail/is_copy_constructible/try_test_is_copy_constructible.guess.part.hpp>
#endif

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_COPY_CONSTRUCTIBLE_TRY_TEST_IS_COPY_CONSTRUCTIBLE_PART_HPP
