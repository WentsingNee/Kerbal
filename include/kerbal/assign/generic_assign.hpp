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

#ifndef KERBAL_ASSIGN_GENERIC_ASSIGN_HPP
#define KERBAL_ASSIGN_GENERIC_ASSIGN_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/assign/generic_assign/generic_assign.fwd.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/compatibility/static_assert.hpp>
#	include <kerbal/type_traits/extent.hpp>
#	include <kerbal/type_traits/integral_constant.hpp>
#	include <kerbal/type_traits/is_array.hpp>
#	include <kerbal/type_traits/remove_reference.hpp>
#	include <kerbal/utility/forward.hpp>
#endif

#include <cstddef>


namespace kerbal
{

	namespace assign
	{

		KERBAL_MODULE_EXPORT
		template <typename T, typename U>
		KERBAL_CONSTEXPR14
		T & generic_assign(T & lhs, const U & rhs)
			KERBAL_CONDITIONAL_NOEXCEPT(
				noexcept(lhs = rhs)
			)
		{
			lhs = rhs;
			return lhs;
		}

		KERBAL_MODULE_EXPORT
		template <typename T, typename U, std::size_t N>
		KERBAL_CONSTEXPR14
		T (& generic_assign(T (& lhs)[N], const U (& rhs)[N]))[N]
		{
			for (std::size_t i = 0; i < N; ++i) {
				kerbal::assign::generic_assign(lhs[i], rhs[i]);
			}
			return lhs;
		}

#	if __cplusplus >= 201103L

		namespace detail
		{

			template <typename T, typename U>
			KERBAL_CONSTEXPR14
			void k_generic_assign(T & lhs, U && rhs, kerbal::type_traits::false_type)
				KERBAL_CONDITIONAL_NOEXCEPT(
					noexcept(lhs = kerbal::utility::forward<U>(rhs))
				)
			{
				lhs = kerbal::utility::forward<U>(rhs);
			}

			template <typename T, typename U>
			KERBAL_CONSTEXPR14
			void k_generic_assign(T & lhs, U && rhs, kerbal::type_traits::true_type)
				KERBAL_CONDITIONAL_NOEXCEPT(
					noexcept(
						kerbal::assign::generic_assign(
							lhs[0],
							kerbal::utility::forward<decltype(rhs[0])>(rhs[0])
						)
					)
				)
			{
				typedef kerbal::type_traits::extent<T, 0> TP_EXTENT;
				typedef kerbal::type_traits::extent<
					typename kerbal::type_traits::remove_reference<U>::type, 0
				> UP_EXTENT;
				KERBAL_STATIC_ASSERT(TP_EXTENT::value == UP_EXTENT::value, "T and U must have same length");
				for (std::size_t i = 0; i < TP_EXTENT::value; ++i) {
					kerbal::assign::generic_assign(
						lhs[i],
						kerbal::utility::forward<decltype(rhs[i])>(rhs[i])
					);
				}
			}

		} // namespace detail

		KERBAL_MODULE_EXPORT
		template <typename T, typename U>
		KERBAL_CONSTEXPR14
		T & generic_assign(T & lhs, U && rhs)
			KERBAL_CONDITIONAL_NOEXCEPT(
				noexcept(
					kerbal::assign::detail::k_generic_assign(
						lhs, kerbal::utility::forward<U>(rhs), kerbal::type_traits::is_array<T>()
					)
				)
			)
		{
			kerbal::assign::detail::k_generic_assign(
				lhs,
				kerbal::utility::forward<U>(rhs),
				kerbal::type_traits::is_array<T>()
			);
			return lhs;
		}

#	endif

	} // namespace assign

} // namespace kerbal

#endif // KERBAL_ASSIGN_GENERIC_ASSIGN_HPP
