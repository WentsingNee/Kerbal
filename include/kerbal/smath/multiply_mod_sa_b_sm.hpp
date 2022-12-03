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
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/type_identity.hpp>


namespace kerbal
{

	namespace smath
	{

		namespace detail
		{

			template <typename ResultType, ResultType a, ResultType m>
			struct multiply_mod_sa_b_sm_selector :
					kerbal::type_traits::integral_constant<
							int,
							m != 0 ?
							((a % m != 0) ? 0 : 1) :
							2
					>
			{
			};



			template <typename ResultType, ResultType a, ResultType m, typename Integer, int>
			struct is_never_overflow_for_mul_mod_dispatch;

			/**
			 * check whether a * (m - 1) will exceed the representation range of Integer type
			 */
			template <typename ResultType, ResultType a, ResultType m, typename Integer>
			struct is_never_overflow_for_mul_mod :
					is_never_overflow_for_mul_mod_dispatch<
						ResultType, a, m, Integer,
						multiply_mod_sa_b_sm_selector<ResultType, a, m>::value
					>
			{
			};


			// m != 0 && a % m != 0
			template <typename ResultType, ResultType a, ResultType m, typename Integer>
			struct is_never_overflow_for_mul_mod_dispatch<ResultType, a, m, Integer, 0> :
					kerbal::type_traits::bool_constant<
						m - 1 <= kerbal::numeric::numeric_limits<Integer>::MAX::value / (a % m)
					>
			{
				private:
					KERBAL_STATIC_ASSERT(m != 0 && a % m != 0, "static check failed");
			};

			// m != 0 && a % m == 0
			template <typename ResultType, ResultType a, ResultType m, typename Integer>
			struct is_never_overflow_for_mul_mod_dispatch<ResultType, a, m, Integer, 1> :
					kerbal::type_traits::false_type
			{
				private:
					KERBAL_STATIC_ASSERT(m != 0 && a % m == 0, "static check failed");
			};

			// m == 0
			template <typename ResultType, ResultType a, ResultType m, typename Integer>
			struct is_never_overflow_for_mul_mod_dispatch<ResultType, a, m, Integer, 2> :
					kerbal::type_traits::bool_constant<
						kerbal::numeric::numeric_limits<ResultType>::MAX::value <= kerbal::numeric::numeric_limits<Integer>::MAX::value / a
					>
			{
				private:
					KERBAL_STATIC_ASSERT(m == 0, "static check failed");
			};



			template <typename ResultType, ResultType a_, ResultType m>
			struct find_never_overflow_integer_type_for_mul_mod
			{
				private:
					KERBAL_STATIC_ASSERT(m != 0, "static check failed");

					typedef kerbal::type_traits::integral_constant<ResultType, a_ % m> a;

					template <typename Integer>
					struct is_never_overflow :
							is_never_overflow_for_mul_mod<ResultType, a::value, m, Integer>
					{
					};

				public:
					typedef typename kerbal::type_traits::conditional<
						is_never_overflow<unsigned short>::value,
						unsigned short,
						typename kerbal::type_traits::conditional<
							is_never_overflow<unsigned int>::value,
							unsigned int,
							typename kerbal::type_traits::conditional<
								is_never_overflow<unsigned long>::value,
								unsigned long,
								typename kerbal::type_traits::conditional<
									is_never_overflow<unsigned long long>::value,
									unsigned long long,
									void
								>::type
							>::type
						>::type
					>::type type;

			};



			template <typename ResultType, ResultType a, ResultType m, int>
			struct multiply_mod_sa_b_sm_impl_dispatch;

			template <typename ResultType, ResultType a, ResultType m>
			struct multiply_mod_sa_b_sm_impl :
					multiply_mod_sa_b_sm_impl_dispatch<ResultType, a, m, multiply_mod_sa_b_sm_selector<ResultType, a, m>::value>
			{
			};

			template <typename ResultType, ResultType a_, ResultType m>
			struct multiply_mod_sa_b_sm_impl_dispatch<ResultType, a_, m, 0> // m != 0 && a_ % m != 0
			{
				private:
					typedef kerbal::type_traits::integral_constant<ResultType, a_ % m> a;
					KERBAL_STATIC_ASSERT(m != 0 && a::value != 0, "static check failed");

					KERBAL_CONSTEXPR14
					static ResultType cacl_impl(ResultType b, kerbal::type_traits::type_identity<void>) KERBAL_NOEXCEPT
					{
						if (b <= kerbal::numeric::numeric_limits<ResultType>::MAX::value / a::value) {
							return a::value * b % m;
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
						typedef kerbal::type_traits::integral_constant<ResultType, m / a::value> Q;
						typedef kerbal::type_traits::integral_constant<ResultType, m % a::value> R;

						ResultType t0 = a::value * (b % Q::value);
						ResultType t1 =
								R::value <= Q::value ?
								R::value * (b / Q::value) :
								multiply_mod_sa_b_sm_impl<ResultType, R::value, m>::cacl(b / Q::value);
						return t0 - t1 + (t0 < t1) * m;
					}

					template <typename T>
					KERBAL_CONSTEXPR14
					static ResultType cacl_impl(ResultType b, kerbal::type_traits::type_identity<T>) KERBAL_NOEXCEPT
					{
						// a * (m - 1) will not overflow under T
						return T(a::value) * T(b) % m;
					}

				public:
					/**
					 * @precondition b == b % m
					 */
					KERBAL_CONSTEXPR14
					static ResultType cacl(ResultType b) KERBAL_NOEXCEPT
					{
						typedef typename find_never_overflow_integer_type_for_mul_mod<ResultType, a::value, m>::type T;
						return cacl_impl(b, kerbal::type_traits::type_identity<T>());
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
					static ResultType cacl(ResultType /*b*/) KERBAL_NOEXCEPT
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
					static ResultType cacl(ResultType b) KERBAL_NOEXCEPT
					{
						return a * b;
					}
			};

		} // namespace detail


		template <typename ResultType, ResultType a, ResultType m>
		struct multiply_mod_sa_b_sm
		{
				/**
				 * @precondition b == b % m
				 */
				KERBAL_CONSTEXPR14
				static ResultType cacl(ResultType b) KERBAL_NOEXCEPT
				{
					return detail::multiply_mod_sa_b_sm_impl<ResultType, m == 0 ? a : a % m, m>::cacl(b);
				}
		};

	} // namespace smath

} // namespace kerbal


#endif // KERBAL_SMATH_MULTIPLY_MOD_SA_B_SM_HPP
