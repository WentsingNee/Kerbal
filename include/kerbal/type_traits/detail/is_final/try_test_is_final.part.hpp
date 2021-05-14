/**
 * @file       try_test_is_final.part.hpp
 * @brief
 * @date       2023-04-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_FINAL_TRY_TEST_IS_FINAL_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_FINAL_TRY_TEST_IS_FINAL_PART_HPP

#include <kerbal/type_traits/detail/is_final/is_final.part.hpp>

#if KERBAL_HAS_IS_FINAL_SUPPORT
#	include <kerbal/type_traits/detail/is_final/try_test_is_final.defi.part.hpp>
#else
#	include <kerbal/type_traits/detail/is_final/try_test_is_final.guess.part.hpp>
#endif

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_FINAL_TRY_TEST_IS_FINAL_PART_HPP
