/**
 * @file       add_mod_sm.hpp
 * @brief
 * @date       2022-12-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_SMATH_ADD_MOD_SM_HPP
#define KERBAL_SMATH_ADD_MOD_SM_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>


namespace kerbal
{

	namespace smath
	{

		KERBAL_MODULE_EXPORT
		template <typename ResultType, ResultType m>
		struct add_mod_sm
		{

				/**
				 * @precondition a == a % m && b == b % m
				 */
				KERBAL_CONSTEXPR
				static
				ResultType f(ResultType a, ResultType b) KERBAL_NOEXCEPT
				{
					return a + b - (a >= m - b) * m;
				}
		};

	} // namespace smath

} // namespace kerbal


#endif // KERBAL_SMATH_ADD_MOD_SM_HPP
