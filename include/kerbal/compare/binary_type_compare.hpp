/**
 * @file       binary_type_compare.hpp
 * @brief
 * @date       2018-9-7
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COMPARE_BINARY_TYPE_COMPARE_HPP
#define KERBAL_COMPARE_BINARY_TYPE_COMPARE_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>


namespace kerbal
{

	namespace compare
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

	} // namespace compare

} // namespace kerbal

#endif // KERBAL_COMPARE_BINARY_TYPE_COMPARE_HPP
