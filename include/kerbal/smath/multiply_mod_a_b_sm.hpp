/**
 * @file       multiply_mod_a_b_sm.hpp
 * @brief
 * @date       2022-12-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_SMATH_MULTIPLY_MOD_A_B_SM_HPP
#define KERBAL_SMATH_MULTIPLY_MOD_A_B_SM_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/numeric/numeric_limits.hpp>
#include <kerbal/type_traits/sign_deduction.hpp>
#include <kerbal/type_traits/type_identity.hpp>

#include <kerbal/smath/detail/is_never_overflow_for_mul_mod.hpp>


namespace kerbal
{

	namespace smath
	{

		namespace detail
		{

			template <typename ResultType, ResultType m, bool = (m == 0)>
			struct multiply_mod_a_b_sm_impl;

			template <typename ResultType, ResultType m>
			struct multiply_mod_a_b_sm_impl<ResultType, m, true> // m == 0
			{
				private:
					KERBAL_STATIC_ASSERT(m == 0, "static check failed");

				public:
					KERBAL_CONSTEXPR
					static
					ResultType f(ResultType a, ResultType b) KERBAL_NOEXCEPT
					{
						return a * b;
					}
			};

			template <typename ResultType, ResultType m>
			struct multiply_mod_a_b_sm_impl<ResultType, m, false> // m != 0
			{
				private:
					KERBAL_STATIC_ASSERT(m != 0, "static check failed");

					KERBAL_CONSTEXPR14
					static
					ResultType f_impl2(ResultType a, ResultType b) KERBAL_NOEXCEPT
					{
						// a * s % m
						// a < m, s < m

						if (a == 0) {
							return 0;
						}

						if (b <= kerbal::numeric::numeric_limits<ResultType>::MAX::value / a) {
							return a * b % m;
						}

						ResultType q = m / a;
						ResultType r = m % a;

						ResultType t0 = a * (b % q);
						ResultType t1 =
							r <= q ?
							r * (b / q) :
							f_impl2(r, b / q);
						return t0 - t1 + (t0 < t1) * m;
					}

					KERBAL_CONSTEXPR14
					static
					ResultType f_impl(ResultType a, ResultType b, kerbal::type_traits::type_identity<void>) KERBAL_NOEXCEPT
					{
						return f_impl2(a, b);
					}

					template <typename T>
					KERBAL_CONSTEXPR14
					static
					ResultType f_impl(ResultType a, ResultType b, kerbal::type_traits::type_identity<T>) KERBAL_NOEXCEPT
					{
						// a * b will not overflow under T
						return T(a) * T(b) % m;
					}

				public:
					KERBAL_CONSTEXPR14
					static
					ResultType f(ResultType a, ResultType b) KERBAL_NOEXCEPT
					{
						typedef typename detail::find_never_overflow_integer_type_for_mul_mod<ResultType, m - 1, m>::type T;
						return f_impl(a, b, kerbal::type_traits::type_identity<T>());
					}
			};

		} // namespace detail

		KERBAL_MODULE_EXPORT
		template <typename ResultType, ResultType m>
		struct multiply_mod_a_b_sm
		{
			private:
				KERBAL_STATIC_ASSERT(
					kerbal::type_traits::is_unsigned<ResultType>::value,
					"ResultType should be unsigned"
				);

			public:
				/**
				 * @precondition a = a % m, b == b % m
				 */
				KERBAL_CONSTEXPR14
				static
				ResultType f(ResultType a, ResultType b) KERBAL_NOEXCEPT
				{
					return detail::multiply_mod_a_b_sm_impl<ResultType, m>::f(a, b);
				}
		};

	} // namespace smath

} // namespace kerbal

#endif // KERBAL_SMATH_MULTIPLY_MOD_A_B_SM_HPP
