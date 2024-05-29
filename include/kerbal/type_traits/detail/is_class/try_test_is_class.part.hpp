/**
 * @file       try_test_is_class.part.hpp
 * @brief
 * @date       2023-04-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_CLASS_TRY_TEST_IS_CLASS_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_CLASS_TRY_TEST_IS_CLASS_PART_HPP

#include <kerbal/type_traits/detail/is_class/is_class.part.hpp>

#if KERBAL_SUPPORTS_IS_CLASS
#	include <kerbal/type_traits/detail/is_class/try_test_is_class.defi.part.hpp>
#else
#	include <kerbal/type_traits/detail/is_class/try_test_is_class.guess.part.hpp>
#endif

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_CLASS_TRY_TEST_IS_CLASS_PART_HPP
