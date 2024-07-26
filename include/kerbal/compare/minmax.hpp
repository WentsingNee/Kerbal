/**
 * @file       minmax.hpp
 * @brief
 * @date       2023-12-13
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COMPARE_MINMAX_HPP
#define KERBAL_COMPARE_MINMAX_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/compatibility/constexpr.hpp>


namespace kerbal
{

	namespace compare
	{

		KERBAL_MODULE_EXPORT
		template <typename T>
		KERBAL_CONSTEXPR
		const T & min(const T & lhs, const T & rhs)
		{
			return lhs < rhs ? lhs : rhs;
		}

		KERBAL_MODULE_EXPORT
		template <typename T>
		KERBAL_CONSTEXPR
		const T & max(const T & lhs, const T & rhs)
		{
			return lhs < rhs ? rhs : lhs;
		}

	} // namespace compare

} // namespace kerbal

#endif // KERBAL_COMPARE_MINMAX_HPP
