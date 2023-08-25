/**
 * @file       std_compare.fwd.hpp
 * @brief
 * @date       2023-08-25
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COMPARE_STD_COMPARE_STD_COMPARE_FWD_HPP
#define KERBAL_COMPARE_STD_COMPARE_STD_COMPARE_FWD_HPP

#include <kerbal/compatibility/namespace_std_scope.hpp>


KERBAL_NAMESPACE_STD_BEGIN

	template <typename T>
	struct equal_to;

	template <typename T>
	struct not_equal_to;

	template <typename T>
	struct less;

	template <typename T>
	struct less_equal;

	template <typename T>
	struct greater;

	template <typename T>
	struct greater_equal;

KERBAL_NAMESPACE_STD_END

#endif // KERBAL_COMPARE_STD_COMPARE_STD_COMPARE_FWD_HPP
