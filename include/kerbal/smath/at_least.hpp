/**
 * @file       at_least.hpp
 * @brief
 * @date       2025-08-16
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_SMATH_AT_LEAST_HPP
#define KERBAL_SMATH_AT_LEAST_HPP

#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/sign_deduction.hpp>


namespace kerbal
{

	namespace smath
	{

		template <typename T, T N>
		struct at_least;

		namespace detail
		{

			template <typename T, T N, bool is_zero>
			struct at_least_impl;

			template <typename T, T N>
			struct at_least_impl<T, N, false> :
				public at_least<T, N - 1>,
				public kerbal::type_traits::integral_constant<T, N>
			{
			};

			template <typename T, T N>
			struct at_least_impl<T, N, true> :
				public kerbal::type_traits::integral_constant<T, 0>
			{
			};

		} // namespace detail

		template <typename T, T N>
		struct at_least :
			public kerbal::smath::detail::at_least_impl<T, N, N == 0>
		{
			KERBAL_STATIC_ASSERT(kerbal::type_traits::is_unsigned<T>::value, "T must be unsigned");
		};

	} // namespace smath

} // namespace kerbal

#endif // KERBAL_SMATH_AT_LEAST_HPP
