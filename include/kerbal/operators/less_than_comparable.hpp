/**
 * @file       less_than_comparable.hpp
 * @brief      
 * @date       2019-7-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OPERATORS_LESS_THAN_COMPARABLE_HPP
#define KERBAL_OPERATORS_LESS_THAN_COMPARABLE_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>


namespace kerbal
{

	namespace operators
	{

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct less_than_comparable
		{
				KERBAL_CONSTEXPR
				friend
				bool operator>(const T & lhs, const T & rhs)
#	if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_ICC
					KERBAL_CONDITIONAL_NOEXCEPT(noexcept(static_cast<bool>(rhs < rhs)))
#	endif
				{
					return static_cast<bool>(rhs < lhs);
				}

				KERBAL_CONSTEXPR
				friend
				bool operator<=(const T & lhs, const T & rhs)
#	if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_ICC
					KERBAL_CONDITIONAL_NOEXCEPT(noexcept(static_cast<bool>(rhs < lhs)))
#	endif
				{
					return !static_cast<bool>(rhs < lhs);
				}

				KERBAL_CONSTEXPR
				friend
				bool operator>=(const T & lhs, const T & rhs)
#	if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_ICC
					KERBAL_CONDITIONAL_NOEXCEPT(noexcept(static_cast<bool>(lhs < rhs)))
#	endif
				{
					return !static_cast<bool>(lhs < rhs);
				}

		};

	} // namespace operators

} // namespace kerbal

#endif // KERBAL_OPERATORS_LESS_THAN_COMPARABLE_HPP
