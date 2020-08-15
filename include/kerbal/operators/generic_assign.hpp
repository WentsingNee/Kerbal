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
#include <utility>

#if __cplusplus >= 201103L
#	include <kerbal/compatibility/static_assert.hpp>
#	include <kerbal/type_traits/array_traits.hpp>
#	include <kerbal/type_traits/integral_constant.hpp>
#	include <kerbal/type_traits/reference_deduction.hpp>
#	include <type_traits>
#endif

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
			void generic_assign(Tp& lhs, Up&& rhs, kerbal::type_traits::false_type)
										KERBAL_CONDITIONAL_NOEXCEPT(
												noexcept(lhs = std::forward<Up>(rhs))
										)
			;

			template <typename Tp, typename Up>
			KERBAL_CONSTEXPR14
			void generic_assign(Tp& lhs, Up&& rhs, kerbal::type_traits::true_type)
										KERBAL_CONDITIONAL_NOEXCEPT(
												noexcept(
													kerbal::operators::generic_assign(
														lhs[0],
														std::forward<decltype(rhs[0])>(rhs[0])
													)
												)
										)
			;

		} // namespace detail

		template <typename Tp, typename Up>
		KERBAL_CONSTEXPR14
		Tp& generic_assign(Tp& lhs, Up&& rhs)
										KERBAL_CONDITIONAL_NOEXCEPT(
												noexcept(
													kerbal::operators::detail::generic_assign(
														lhs, rhs, kerbal::type_traits::is_array<Tp>()
													)
												)
										)
		;

		namespace detail
		{

			template <typename Tp, typename Up>
			KERBAL_CONSTEXPR14
			void generic_assign(Tp& lhs, Up&& rhs, kerbal::type_traits::false_type)
										KERBAL_CONDITIONAL_NOEXCEPT(
												noexcept(lhs = std::forward<Up>(rhs))
										)
			{
				lhs = std::forward<Up>(rhs);
			}

			template <typename Tp, typename Up>
			KERBAL_CONSTEXPR14
			void generic_assign(Tp& lhs, Up&& rhs, kerbal::type_traits::true_type)
										KERBAL_CONDITIONAL_NOEXCEPT(
												noexcept(
													kerbal::operators::generic_assign(
														lhs[0],
														std::forward<decltype(rhs[0])>(rhs[0])
													)
												)
										)
			{
				typedef kerbal::type_traits::extent<Tp, 0> TP_EXTENT;
				typedef kerbal::type_traits::extent<
						typename kerbal::type_traits::remove_reference<Up>::type
				, 0> UP_EXTENT;
				KERBAL_STATIC_ASSERT(TP_EXTENT::value == UP_EXTENT::value, "Tp and Up must have same length");
				for (size_t i = 0; i < kerbal::type_traits::extent<Tp, 0>::value; ++i) {
					kerbal::operators::generic_assign(lhs[i], std::forward<decltype(rhs[i])>(rhs[i]));
				}
			}

		} // namespace detail

		template <typename Tp, typename Up>
		KERBAL_CONSTEXPR14
		Tp& generic_assign(Tp & lhs, Up && rhs)
										KERBAL_CONDITIONAL_NOEXCEPT(
												noexcept(
													kerbal::operators::detail::generic_assign(
														lhs, rhs, kerbal::type_traits::is_array<Tp>()
													)
												)
										)
		{
			kerbal::operators::detail::generic_assign(lhs, rhs, kerbal::type_traits::is_array<Tp>());
			return lhs;
		}

#	endif

	} // namespace operators

} // namespace kerbal

#endif // KERBAL_OPERATORS_GENERIC_ASSIGN_HPP
