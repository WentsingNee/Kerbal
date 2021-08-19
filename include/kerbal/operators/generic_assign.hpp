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

#if __cplusplus >= 201103L
#	include <kerbal/compatibility/static_assert.hpp>
#	include <kerbal/type_traits/array_traits.hpp>
#	include <kerbal/type_traits/integral_constant.hpp>
#	include <kerbal/type_traits/reference_deduction.hpp>
#	include <kerbal/utility/forward.hpp>
#endif

#include <cstddef>

namespace kerbal
{

	namespace operators
	{

		// forward declare

		template <typename Tp, typename Up>
		KERBAL_CONSTEXPR14
		Tp& generic_assign(Tp& lhs, const Up& rhs)
								KERBAL_CONDITIONAL_NOEXCEPT(
										noexcept(lhs = rhs)
								)
		;

		template <typename Tp, typename Up, size_t N>
		KERBAL_CONSTEXPR14
		Tp (& generic_assign(Tp (& lhs)[N], const Up (& rhs)[N]))[N];


#	if __cplusplus >= 201103L

		namespace detail
		{

			template <typename Tp, typename Up>
			KERBAL_CONSTEXPR14
			void _K_generic_assign(Tp& lhs, Up&& rhs, kerbal::type_traits::false_type)
								KERBAL_CONDITIONAL_NOEXCEPT(
										noexcept(lhs = kerbal::utility::forward<Up>(rhs))
								)
			;

			template <typename Tp, typename Up>
			KERBAL_CONSTEXPR14
			void _K_generic_assign(Tp& lhs, Up&& rhs, kerbal::type_traits::true_type)
								KERBAL_CONDITIONAL_NOEXCEPT(
										noexcept(
											kerbal::operators::generic_assign(lhs[0], kerbal::utility::forward<decltype(rhs[0])>(rhs[0]))
										)
								)
			;

		} // namespace detail

		template <typename Tp, typename Up>
		KERBAL_CONSTEXPR14
		Tp& generic_assign(Tp& lhs, Up&& rhs)
								KERBAL_CONDITIONAL_NOEXCEPT(
										noexcept(
											kerbal::operators::detail::_K_generic_assign(
												lhs, kerbal::utility::forward<Up>(rhs), kerbal::type_traits::is_array<Tp>()
											)
										)
								)
		;

#	endif



		// implement

		template <typename Tp, typename Up>
		KERBAL_CONSTEXPR14
		Tp& generic_assign(Tp & lhs, const Up & rhs)
								KERBAL_CONDITIONAL_NOEXCEPT(
										noexcept(lhs = rhs)
								)
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

#	if __cplusplus >= 201103L

		namespace detail
		{

			template <typename Tp, typename Up>
			KERBAL_CONSTEXPR14
			void _K_generic_assign(Tp& lhs, Up&& rhs, kerbal::type_traits::false_type)
								KERBAL_CONDITIONAL_NOEXCEPT(
										noexcept(lhs = kerbal::utility::forward<Up>(rhs))
								)
			{
				lhs = kerbal::utility::forward<Up>(rhs);
			}

			template <typename Tp, typename Up>
			KERBAL_CONSTEXPR14
			void _K_generic_assign(Tp& lhs, Up&& rhs, kerbal::type_traits::true_type)
								KERBAL_CONDITIONAL_NOEXCEPT(
										noexcept(
											kerbal::operators::generic_assign(lhs[0], kerbal::utility::forward<decltype(rhs[0])>(rhs[0]))
										)
								)
			{
				typedef kerbal::type_traits::extent<Tp, 0> TP_EXTENT;
				typedef kerbal::type_traits::extent<
						typename kerbal::type_traits::remove_reference<Up>::type
				, 0> UP_EXTENT;
				KERBAL_STATIC_ASSERT(TP_EXTENT::value == UP_EXTENT::value, "Tp and Up must have same length");
				for (size_t i = 0; i < kerbal::type_traits::extent<Tp, 0>::value; ++i) {
					kerbal::operators::generic_assign(lhs[i], kerbal::utility::forward<decltype(rhs[i])>(rhs[i]));
				}
			}

		} // namespace detail

		template <typename Tp, typename Up>
		KERBAL_CONSTEXPR14
		Tp& generic_assign(Tp & lhs, Up && rhs)
								KERBAL_CONDITIONAL_NOEXCEPT(
										noexcept(
											kerbal::operators::detail::_K_generic_assign(
												lhs, kerbal::utility::forward<Up>(rhs), kerbal::type_traits::is_array<Tp>()
											)
										)
								)
		{
			kerbal::operators::detail::_K_generic_assign(lhs, kerbal::utility::forward<Up>(rhs), kerbal::type_traits::is_array<Tp>());
			return lhs;
		}

#	endif

	} // namespace operators

} // namespace kerbal

#endif // KERBAL_OPERATORS_GENERIC_ASSIGN_HPP
