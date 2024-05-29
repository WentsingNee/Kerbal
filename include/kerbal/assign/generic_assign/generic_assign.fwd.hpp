/**
 * @file       generic_assign.fwd.hpp
 * @brief
 * @date       2023-08-21
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ASSIGN_GENERIC_ASSIGN_GENERIC_ASSIGN_FWD_HPP
#define KERBAL_ASSIGN_GENERIC_ASSIGN_GENERIC_ASSIGN_FWD_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>

#if __cplusplus >= 201103L
#   include <kerbal/type_traits/integral_constant.hpp>
#	include <kerbal/type_traits/is_array.hpp>
#	include <kerbal/utility/forward.hpp>
#endif

#include <cstddef>


namespace kerbal
{

	namespace assign
	{

		template <typename T, typename U>
		KERBAL_CONSTEXPR14
		T& generic_assign(T& lhs, const U& rhs)
				KERBAL_CONDITIONAL_NOEXCEPT(
					noexcept(lhs = rhs)
				)
		;

		template <typename T, typename U, std::size_t N>
		KERBAL_CONSTEXPR14
		T (& generic_assign(T (& lhs)[N], const U (& rhs)[N]))[N];


#	if __cplusplus >= 201103L

		namespace detail
		{

			template <typename T, typename U>
			KERBAL_CONSTEXPR14
			void k_generic_assign(T& lhs, U&& rhs, kerbal::type_traits::false_type)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(lhs = kerbal::utility::forward<U>(rhs))
					)
			;

			template <typename T, typename U>
			KERBAL_CONSTEXPR14
			void k_generic_assign(T& lhs, U&& rhs, kerbal::type_traits::true_type)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(
							kerbal::assign::generic_assign(lhs[0], kerbal::utility::forward<decltype(rhs[0])>(rhs[0]))
						)
					)
			;

		} // namespace detail

		template <typename T, typename U>
		KERBAL_CONSTEXPR14
		T& generic_assign(T& lhs, U&& rhs)
				KERBAL_CONDITIONAL_NOEXCEPT(
					noexcept(
						kerbal::assign::detail::k_generic_assign(
							lhs, kerbal::utility::forward<U>(rhs), kerbal::type_traits::is_array<T>()
						)
					)
				)
		;

#	endif

	} // namespace assign

} // namespace kerbal


#endif // KERBAL_ASSIGN_GENERIC_ASSIGN_GENERIC_ASSIGN_FWD_HPP
