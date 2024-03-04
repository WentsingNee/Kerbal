/**
 * @file       countr_zero.hpp
 * @brief
 * @date       2024-03-04
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_SMATH_COUNTR_ZERO_HPP
#define KERBAL_SMATH_COUNTR_ZERO_HPP

#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/type_traits/sign_deduction.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <climits>


namespace kerbal
{

	namespace smath
	{

		namespace detail
		{

			template <typename Unsigned, Unsigned x, bool /*IS_EVEN*/ = (x % 2 == 0)>
			struct countr_zero_is_zero_impl;

			template <typename Unsigned, Unsigned x>
			struct countr_zero_is_zero_impl<Unsigned, x, false> :
					kerbal::type_traits::integral_constant<int, 0>
			{
			};

			template <typename Unsigned, Unsigned x>
			struct countr_zero_is_zero_impl<Unsigned, x, true> :
					kerbal::type_traits::integral_constant<
						int,
						countr_zero_is_zero_impl<
							Unsigned,
							(x >> 1) | (
								static_cast<Unsigned>(1u) << (sizeof(Unsigned) * CHAR_BIT - 1)
							)
						>::value + 1
					>
			{
			};



			template <typename Unsigned, Unsigned x, bool /*IS_ZERO*/ = (x == 0)>
			struct countr_zero_is_zero_handler;

			template <typename Unsigned, Unsigned x>
			struct countr_zero_is_zero_handler<Unsigned, x, false> :
					countr_zero_is_zero_impl<Unsigned, x>
			{
			};

			template <typename Unsigned, Unsigned x>
			struct countr_zero_is_zero_handler<Unsigned, x, true> :
					kerbal::type_traits::integral_constant<
						int,
						CHAR_BIT * sizeof(Unsigned)
					>
			{
			};

		} // namespace detail

		template <typename Unsigned, Unsigned x>
		struct countr_zero :
				kerbal::smath::detail::countr_zero_is_zero_handler<Unsigned, x>
		{
			private:
				KERBAL_STATIC_ASSERT(kerbal::type_traits::is_unsigned<Unsigned>::value, "Type should be unsigned");
		};

	} // namespace smath

} // namespace kerbal

#endif // KERBAL_SMATH_COUNTR_ZERO_HPP
