/**
 * @file       try_test_is_nothrow_copy_constructible.part.hpp
 * @brief
 * @date       2023-05-04
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_NOTHROW_COPY_CONSTRUCTIBLE_TRY_TEST_IS_NOTHROW_COPY_CONSTRUCTIBLE_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_NOTHROW_COPY_CONSTRUCTIBLE_TRY_TEST_IS_NOTHROW_COPY_CONSTRUCTIBLE_PART_HPP

#include <kerbal/type_traits/detail/is_nothrow_copy_constructible/is_nothrow_copy_constructible.part.hpp>

#include <kerbal/config/exceptions.hpp>

#if KERBAL_HAS_IS_NOTHROW_COPY_CONSTRUCTIBLE_SUPPORT
#	include <kerbal/type_traits/detail/is_nothrow_copy_constructible/try_test_is_nothrow_copy_constructible.defi.part.hpp>
#elif KERBAL_HAS_EXCEPTIONS_SUPPORT
#	include <kerbal/type_traits/detail/is_nothrow_copy_constructible/try_test_is_nothrow_copy_constructible.noexcept.part.hpp>
#else
#	include <kerbal/type_traits/detail/is_nothrow_copy_constructible/try_test_is_nothrow_copy_constructible.guess.part.hpp>
#endif

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_NOTHROW_COPY_CONSTRUCTIBLE_TRY_TEST_IS_NOTHROW_COPY_CONSTRUCTIBLE_PART_HPP
