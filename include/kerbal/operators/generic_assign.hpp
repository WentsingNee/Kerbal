/**
 * @file       generic_assign.hpp
 * @brief
 * @date       2020-6-6
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OPERATORS_GENERIC_ASSIGN_HPP
#define KERBAL_OPERATORS_GENERIC_ASSIGN_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>

#include <cstddef>

#if __cplusplus >= 201103L
#	include <type_traits>
#endif

namespace kerbal
{

	namespace operators
	{

		template <typename Tp, typename Up>
		KERBAL_CONSTEXPR14
		Tp& generic_assign(Tp& lhs, const Up& rhs);

		template <typename Tp, typename Up, size_t N>
		KERBAL_CONSTEXPR14
		Tp (& generic_assign(Tp (& lhs)[N], const Up (& rhs)[N]))[N];

		template <typename Tp, typename Up>
		KERBAL_CONSTEXPR14
		Tp& generic_assign(Tp & lhs, const Up & rhs)
		{
			lhs = rhs;
			return lhs;
		}

		template <typename Tp, typename Up, size_t N>
		KERBAL_CONSTEXPR14
		Tp (& generic_assign(Tp (& lhs)[N], const Up (& rhs)[N])
			)[N]
		{
			for (size_t i = 0; i < N; ++i) {
				kerbal::operators::generic_assign(lhs[i], rhs[i]);
			}
			return lhs;
		}

	} // namespace operators

} // namespace kerbal

#endif // KERBAL_OPERATORS_GENERIC_ASSIGN_HPP
