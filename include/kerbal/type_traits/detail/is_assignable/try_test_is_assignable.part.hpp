/**
 * @file       try_test_is_assignable.part.hpp
 * @brief
 * @date       2023-04-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_ASSIGNABLE_TRY_TEST_IS_ASSIGNABLE_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_ASSIGNABLE_TRY_TEST_IS_ASSIGNABLE_PART_HPP

#include <kerbal/type_traits/detail/is_assignable/is_assignable.part.hpp>

#if KERBAL_SUPPORTS_IS_ASSIGNABLE
#	include <kerbal/type_traits/detail/is_assignable/try_test_is_assignable.defi.part.hpp>
#else
#	include <kerbal/type_traits/detail/is_assignable/try_test_is_assignable.guess.part.hpp>
#endif

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_ASSIGNABLE_TRY_TEST_IS_ASSIGNABLE_PART_HPP
