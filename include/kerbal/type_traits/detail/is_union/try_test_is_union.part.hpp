/**
 * @file       try_test_is_union.part.hpp
 * @brief
 * @date       2023-04-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_UNION_TRY_TEST_IS_UNION_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_UNION_TRY_TEST_IS_UNION_PART_HPP

#include <kerbal/type_traits/detail/is_union/is_union.part.hpp>

#if KERBAL_SUPPORTS_IS_UNION
#	include <kerbal/type_traits/detail/is_union/try_test_is_union.defi.part.hpp>
#else
#	include <kerbal/type_traits/detail/is_union/try_test_is_union.guess.part.hpp>
#endif

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_UNION_TRY_TEST_IS_UNION_PART_HPP
