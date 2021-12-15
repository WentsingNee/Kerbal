/**
 * @file       addable.hpp
 * @brief
 * @date       2019-11-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OPERATORS_ADDABLE_HPP
#define KERBAL_OPERATORS_ADDABLE_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>

namespace kerbal
{

	namespace operators
	{

		template <typename Tp, typename Up = Tp>
		struct addable
		{
				KERBAL_CONSTEXPR14
				friend Tp operator+(Tp lhs, const Up& rhs)
#	if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_ICC
						KERBAL_CONDITIONAL_NOEXCEPT(noexcept(lhs += rhs))
#	endif
				{
					lhs += rhs;
					return lhs;
				}
		};

		template <typename Tp, typename Up>
		struct addable_left
		{
				KERBAL_CONSTEXPR14
				friend Tp operator+(const Up & lhs, const Tp & rhs)
#	if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_ICC
						KERBAL_CONDITIONAL_NOEXCEPT(noexcept(rhs + lhs))
#	endif
				{
					return rhs + lhs;
				}
		};

	} // namespace operators

} // namespace kerbal

#endif // KERBAL_OPERATORS_ADDABLE_HPP
