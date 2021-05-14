/**
 * @file       try_test_is_abstract.part.hpp
 * @brief
 * @date       2023-05-05
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_ABSTRACT_TRY_TEST_IS_ABSTRACT_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_ABSTRACT_TRY_TEST_IS_ABSTRACT_PART_HPP

#include <kerbal/type_traits/detail/is_abstract/is_abstract.part.hpp>

#if KERBAL_HAS_IS_ABSTRACT_SUPPORT
#	include <kerbal/type_traits/detail/is_abstract/try_test_is_abstract.defi.part.hpp>
#else
#	include <kerbal/type_traits/detail/is_abstract/try_test_is_abstract.guess.part.hpp>
#endif

#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_ABSTRACT_TRY_TEST_IS_ABSTRACT_PART_HPP
