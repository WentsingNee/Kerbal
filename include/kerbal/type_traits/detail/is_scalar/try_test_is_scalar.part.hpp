/**
 * @file       try_test_is_scalar.part.hpp
 * @brief
 * @date       2023-05-04
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_SCALAR_TRY_TEST_IS_SCALAR_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_SCALAR_TRY_TEST_IS_SCALAR_PART_HPP

#include <kerbal/type_traits/detail/is_scalar/is_scalar.part.hpp>

#if KERBAL_HAS_IS_SCALAR_SUPPORT
#	include <kerbal/type_traits/detail/is_scalar/try_test_is_scalar.defi.part.hpp>
#else
#	include <kerbal/type_traits/detail/is_scalar/try_test_is_scalar.guess.part.hpp>
#endif

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_SCALAR_TRY_TEST_IS_SCALAR_PART_HPP
