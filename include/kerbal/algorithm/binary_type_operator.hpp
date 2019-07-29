/**
 * @file		binary_type_operator.hpp
 * @brief
 * @date		2018年9月7日
 * @author		Peter
 * @copyright	Peter
 * @copyright
 <a href="http://thinkspirit.org/">ThinkSpirit Laboratory</a>
 of
 <a href="http://www.nuist.edu.cn/">Nanjing University of Information Science & Technology</a>
 */

#ifndef INCLUDE_KERBAL_ALGORITHM_BINARY_TYPE_OPERATOR_HPP_
#define INCLUDE_KERBAL_ALGORITHM_BINARY_TYPE_OPERATOR_HPP_

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>

namespace kerbal
{
	namespace algorithm
	{
		template <typename Tp, typename Up>
		struct binary_type_equal_to
		{
				KERBAL_CONSTEXPR
				bool operator()(const Tp & x, const Up & y) const KERBAL_CONDITIONAL_NOEXCEPT(noexcept(x == y))
				{
					return x == y;
				}
		};

		template <typename Tp, typename Up>
		struct binary_type_not_equal_to
		{
				KERBAL_CONSTEXPR
				bool operator()(const Tp & x, const Up & y) const KERBAL_CONDITIONAL_NOEXCEPT(noexcept(x != y))
				{
					return x != y;
				}
		};

		template <typename Tp, typename Up>
		struct binary_type_greater
		{
				KERBAL_CONSTEXPR
				bool operator()(const Tp & x, const Up & y) const KERBAL_CONDITIONAL_NOEXCEPT(noexcept(x > y))
				{
					return x > y;
				}
		};

		template <typename Tp, typename Up>
		struct binary_type_less
		{
				KERBAL_CONSTEXPR
				bool operator()(const Tp & x, const Up & y) const KERBAL_CONDITIONAL_NOEXCEPT(noexcept(x < y))
				{
					return x < y;
				}
		};

		template <typename Tp, typename Up>
		struct binary_type_greater_equal
		{
				KERBAL_CONSTEXPR
				bool operator()(const Tp & x, const Up & y) const KERBAL_CONDITIONAL_NOEXCEPT(noexcept(x >= y))
				{
					return x >= y;
				}
		};

		template <typename Tp, typename Up>
		struct binary_type_less_equal
		{
				KERBAL_CONSTEXPR
				bool operator()(const Tp & x, const Up & y) const KERBAL_CONDITIONAL_NOEXCEPT(noexcept(x <= y))
				{
					return x <= y;
				}
		};

	} /* namespace algorithm */

} /* namespace kerbal */


#endif /* INCLUDE_KERBAL_ALGORITHM_BINARY_TYPE_OPERATOR_HPP_ */
