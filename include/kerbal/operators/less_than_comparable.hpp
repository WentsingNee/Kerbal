/**
 * @file       less_than_comparable.hpp
 * @brief      
 * @date       2019-7-14
 * @author     peter
 * @copyright
 *      peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OPERATORS_LESS_THAN_COMPARABLE_HPP_
#define KERBAL_OPERATORS_LESS_THAN_COMPARABLE_HPP_

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>

namespace kerbal
{
	namespace operators
	{
		template <typename Tp>
		struct less_than_comparable
		{
				friend KERBAL_CONSTEXPR bool operator>(const Tp & lhs, const Tp & rhs)
						KERBAL_CONDITIONAL_NOEXCEPT(noexcept(static_cast<bool>(rhs < rhs)))
				{
					return static_cast<bool>(rhs < lhs);
				}

				friend KERBAL_CONSTEXPR bool operator<=(const Tp & lhs, const Tp & rhs)
						KERBAL_CONDITIONAL_NOEXCEPT(noexcept(static_cast<bool>(rhs < lhs)))
				{
					return !static_cast<bool>(rhs < lhs);
				}

				friend KERBAL_CONSTEXPR bool operator>=(const Tp & lhs, const Tp & rhs)
						KERBAL_CONDITIONAL_NOEXCEPT(noexcept(static_cast<bool>(lhs < rhs)))
				{
					return !static_cast<bool>(lhs < rhs);
				}

		};

	} // namespace operators

} // namespace kerbal

#endif /* KERBAL_OPERATORS_LESS_THAN_COMPARABLE_HPP_ */
