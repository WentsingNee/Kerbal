/**
 * @file       try_test_is_nothrow_move_assignable.part.hpp
 * @brief
 * @date       2023-05-04
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_NOTHROW_MOVE_ASSIGNABLE_TRY_TEST_IS_NOTHROW_MOVE_ASSIGNABLE_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_NOTHROW_MOVE_ASSIGNABLE_TRY_TEST_IS_NOTHROW_MOVE_ASSIGNABLE_PART_HPP

#include <kerbal/type_traits/detail/is_nothrow_move_assignable/is_nothrow_move_assignable.part.hpp>

#if KERBAL_SUPPORTS_IS_NOTHROW_MOVE_ASSIGNABLE
#	include <kerbal/type_traits/detail/is_nothrow_move_assignable/try_test_is_nothrow_move_assignable.defi.part.hpp>
#else
#	include <kerbal/type_traits/detail/is_nothrow_move_assignable/try_test_is_nothrow_move_assignable.guess.part.hpp>
#endif

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_NOTHROW_MOVE_ASSIGNABLE_TRY_TEST_IS_NOTHROW_MOVE_ASSIGNABLE_PART_HPP
