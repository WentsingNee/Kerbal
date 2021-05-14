/**
 * @file       try_test_is_enum.part.hpp
 * @brief
 * @date       2023-04-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_ENUM_TRY_TEST_IS_ENUM_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_ENUM_TRY_TEST_IS_ENUM_PART_HPP

#include <kerbal/type_traits/detail/is_enum/is_enum.part.hpp>

#if KERBAL_HAS_IS_ENUM_SUPPORT
#	include <kerbal/type_traits/detail/is_enum/try_test_is_enum.defi.part.hpp>
#else
#	include <kerbal/type_traits/detail/is_enum/try_test_is_enum.guess.part.hpp>
#endif

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_ENUM_TRY_TEST_IS_ENUM_PART_HPP
