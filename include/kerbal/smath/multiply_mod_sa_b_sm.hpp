/**
 * @file       multiply_mod_sa_b_sm.hpp
 * @brief
 * @date       2022-12-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_SMATH_MULTIPLY_MOD_SA_B_SM_HPP
#define KERBAL_SMATH_MULTIPLY_MOD_SA_B_SM_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/numeric/numeric_limits.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/sign_deduction.hpp>
#include <kerbal/type_traits/type_identity.hpp>

#include <kerbal/smath/detail/is_never_overflow_for_mul_mod.hpp>


namespace kerbal
{

	namespace smath
	{

		namespace detail
		{

			template <typename ResultType, ResultType a, ResultType m, int>
			struct multiply_mod_sa_b_sm_impl_dispatch;

			template <typename ResultType, ResultType a, ResultType m>
			struct multiply_mod_sa_b_sm_impl :
				multiply_mod_sa_b_sm_impl_dispatch<
					ResultType, a, m,
					multiply_mod_sa_b_sm_selector<ResultType, a, m>::value
				>
			{
			};

			template <typename ResultType, ResultType a, ResultType m>
			struct multiply_mod_sa_b_sm_impl_dispatch<ResultType, a, m, 0> // m != 0 && a % m != 0
			{
				private:
					KERBAL_STATIC_ASSERT(a % m == a, "static check failed");
					KERBAL_STATIC_ASSERT(m != 0 && a != 0, "static check failed");

					typedef kerbal::type_traits::integral_constant<ResultType, m / a> Q;
					typedef kerbal::type_traits::integral_constant<ResultType, m % a> R;

					KERBAL_CONSTEXPR14
					static
					ResultType schrage_t1_impl(ResultType b, kerbal::type_traits::false_type)
					{
						return multiply_mod_sa_b_sm_impl<ResultType, R::value, m>::f(b / Q::value);
					}

					KERBAL_CONSTEXPR
					static
					ResultType schrage_t1_impl(ResultType b, kerbal::type_traits::true_type)
					{
						return R::value * (b / Q::value);
					}

					KERBAL_CONSTEXPR14
					static
					ResultType f_impl(ResultType b, kerbal::type_traits::type_identity<void>) KERBAL_NOEXCEPT
					{
						typedef kerbal::type_traits::integral_constant<
							ResultType,
							kerbal::numeric::numeric_limits<ResultType>::MAX::value / a
						> NEVER_OVERFLOW_MAXIMUM;

						if (m / 2 <= NEVER_OVERFLOW_MAXIMUM::value) {
							if (b <= NEVER_OVERFLOW_MAXIMUM::value) {
								return a * b % m;
							}
						}

						/*  Schrage's algorithm
						 *
						 *   let m = a * q + r (q and r are all integers, obviously q = m / a, r = m % a)
						 *   a * b = a * (q * (b / q) + b % q)
						 *         = a * q * (b / q) + a * (b % q)
						 *         = (m - r) * (b / q) + a * (b % q)
						 *         = a * (b % q) - r * (b / q)   (mod m)
						 *   when r <= q, both terms are less than m so it does not overflow.
						 */

						ResultType t0 = a * (b % Q::value);
						ResultType t1 = schrage_t1_impl(b, kerbal::type_traits::bool_constant<R::value <= Q::value>());
						return t0 - t1 + (t0 < t1) * m;
					}

					template <typename T>
					KERBAL_CONSTEXPR
					static
					ResultType f_impl(ResultType b, kerbal::type_traits::type_identity<T>) KERBAL_NOEXCEPT
					{
						// a * (m - 1) will not overflow under T
						return T(a) * T(b) % m;
					}

				public:
					/**
					 * @precondition b == b % m
					 */
					KERBAL_CONSTEXPR14
					static
					ResultType f(ResultType b) KERBAL_NOEXCEPT
					{
						typedef typename find_never_overflow_integer_type_for_mul_mod<ResultType, a, m>::type T;
						return f_impl(b, kerbal::type_traits::type_identity<T>());
					}

			};

			template <typename ResultType, ResultType a, ResultType m>
			struct multiply_mod_sa_b_sm_impl_dispatch<ResultType, a, m, 1> // m != 0 && a % m == 0
			{
				private:
					KERBAL_STATIC_ASSERT(m != 0 && a % m == 0, "static check failed");

				public:
					// a %= m, b %= m
					KERBAL_CONSTEXPR
					static
					ResultType f(ResultType /*b*/) KERBAL_NOEXCEPT
					{
						return 0;
					}
			};

			template <typename ResultType, ResultType a, ResultType m>
			struct multiply_mod_sa_b_sm_impl_dispatch<ResultType, a, m, 2> // m == 0
			{
				private:
					KERBAL_STATIC_ASSERT(m == 0, "static check failed");

				public:
					KERBAL_CONSTEXPR
					static
					ResultType f(ResultType b) KERBAL_NOEXCEPT
					{
						return a * b;
					}
			};

		} // namespace detail


		template <typename ResultType, ResultType a, ResultType m>
		struct multiply_mod_sa_b_sm
		{
			private:
				KERBAL_STATIC_ASSERT(
					kerbal::type_traits::is_unsigned<ResultType>::value,
					"ResultType should be unsigned"
				);

			public:
				/**
				 * @precondition b == b % m
				 */
				KERBAL_CONSTEXPR14
				static
				ResultType f(ResultType b) KERBAL_NOEXCEPT
				{
					return detail::multiply_mod_sa_b_sm_impl<ResultType, m == 0 ? a : a % m, m>::f(b);
				}
		};

	} // namespace smath

} // namespace kerbal


#endif // KERBAL_SMATH_MULTIPLY_MOD_SA_B_SM_HPP
