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


namespace kerbal
{
	namespace algorithm
	{
		template <typename Tp, typename Up>
		struct binary_type_equal_to
		{
				bool operator()(const Tp & x, const Up & y) const
				{
					return x == y;
				}
		};

		template <typename Tp, typename Up>
		struct binary_type_not_equal_to
		{
				bool operator()(const Tp & x, const Up & y) const
				{
					return x != y;
				}
		};

		template <typename Tp, typename Up>
		struct binary_type_greater
		{
				bool operator()(const Tp & x, const Up & y) const
				{
					return x > y;
				}
		};

		template <typename Tp, typename Up>
		struct binary_type_less
		{
				bool operator()(const Tp & x, const Up & y) const
				{
					return x < y;
				}
		};

		template <typename Tp, typename Up>
		struct binary_type_greater_equal
		{
				bool operator()(const Tp & x, const Up & y) const
				{
					return x >= y;
				}
		};

		template <typename Tp, typename Up>
		struct binary_type_less_equal
		{
				bool operator()(const Tp & x, const Up & y) const
				{
					return x <= y;
				}
		};

	} /* namespace algorithm */

} /* namespace kerbal */


#endif /* INCLUDE_KERBAL_ALGORITHM_BINARY_TYPE_OPERATOR_HPP_ */
