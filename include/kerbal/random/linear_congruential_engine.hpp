/**
 * @file       linear_congruential_engine.hpp
 * @brief
 * @date       2019-11-23
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_LINEAR_CONGRUENTIAL_ENGINE_HPP
#define KERBAL_RANDOM_LINEAR_CONGRUENTIAL_ENGINE_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/numeric/numeric_limits.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/type_identity.hpp>


namespace kerbal
{

	namespace random
	{

		namespace detail
		{

			// check whether a * (m - 1) will exceed the representation range of Integer type
			template <typename ResultType, ResultType a, ResultType m, typename Integer>
			struct is_never_overflow_for_mul_mod :
					kerbal::type_traits::bool_constant<
							m - 1 <= kerbal::numeric::numeric_limits<Integer>::MAX::value / a
					>
			{
			};

			template <typename ResultType, ResultType a, ResultType m>
			struct find_never_overflow_integer_type_for_mul_mod
			{
				private:
					template <typename Integer>
					struct is_never_overflow :
							is_never_overflow_for_mul_mod<ResultType, a, m, Integer>
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


			template <typename ResultType, ResultType a, ResultType m>
			struct static_mul_mod_selector
			{
					typedef kerbal::type_traits::integral_constant<
							int,
							m != 0 ?
								((a % m != 0) ? 0 : 1) :
								2
					> type;
			};

			template <typename ResultType, ResultType a, ResultType m, int>
			struct static_mul_mod_impl_dispatch;

			template <typename ResultType, ResultType a, ResultType m>
			struct static_mul_mod_impl :
					static_mul_mod_impl_dispatch<ResultType, a, m, static_mul_mod_selector<ResultType, a, m>::type::value>
			{
			};

			template <typename ResultType, ResultType a, ResultType m>
			struct static_mul_mod_impl_dispatch<ResultType, a, m, 0> // m != 0 && a % m != 0
			{
				private:
					KERBAL_STATIC_ASSERT(m != 0 && a % m != 0 && a % m == a, "static check failed");

					KERBAL_CONSTEXPR14
					static ResultType cacl_impl(ResultType s, kerbal::type_traits::type_identity<void>) KERBAL_NOEXCEPT
					{
						if (s <= kerbal::numeric::numeric_limits<ResultType>::MAX::value / a) {
							return a * s % m;
						}

						/*  Schrage's algorithm
						 *
						 *   let m = a * q + r (q and r are all integers, obviously q = m / a, r = m % a)
						 *   a * s = a * (q * (s / q) + s % q)
						 *         = a * q * (s / q) + a * (s % q)
						 *         = (m - r) * (s / q) + a * (s % q)
						 *         = a * (s % q) - r * (s / q)   (mod m)
						 *   when r <= q, both terms are less than m so it does not overflow.
						 */
						typedef kerbal::type_traits::integral_constant<ResultType, m / a> Q;
						typedef kerbal::type_traits::integral_constant<ResultType, m % a> R;

						ResultType t0 = a * (s % Q::value);
						ResultType t1 =
								R::value <= Q::value ?
								R::value * (s / Q::value) :
								static_mul_mod_impl<ResultType, R::value, m>::cacl(s / Q::value);
						return t0 - t1 + (t0 < t1) * m;
					}

					template <typename T>
					KERBAL_CONSTEXPR14
					static ResultType cacl_impl(ResultType s, kerbal::type_traits::type_identity<T>) KERBAL_NOEXCEPT
					{
						// a * (m - 1) will not overflow under T
						return T(a) * T(s) % m;
					}

				public:
					// a %= m, s %= m
					KERBAL_CONSTEXPR14
					static ResultType cacl(ResultType s) KERBAL_NOEXCEPT
					{
						typedef typename find_never_overflow_integer_type_for_mul_mod<ResultType, a, m>::type T;
						return cacl_impl(s, kerbal::type_traits::type_identity<T>());
					}

			};

			template <typename ResultType, ResultType a, ResultType m>
			struct static_mul_mod_impl_dispatch<ResultType, a, m, 1> // m != 0 && a % m == 0
			{
				private:
					KERBAL_STATIC_ASSERT(m != 0 && a % m == 0, "static check failed");

				public:
					// a %= m, s %= m
					KERBAL_CONSTEXPR
					static ResultType cacl(ResultType s) KERBAL_NOEXCEPT
					{
						return 0;
					}
			};

			template <typename ResultType, ResultType a, ResultType m>
			struct static_mul_mod_impl_dispatch<ResultType, a, m, 2> // m == 0
			{
				private:
					KERBAL_STATIC_ASSERT(m == 0, "static check failed");

				public:
					KERBAL_CONSTEXPR
					static ResultType cacl(ResultType s) KERBAL_NOEXCEPT
					{
						return a * s;
					}
			};

			template <typename ResultType, ResultType a, ResultType m>
			struct static_mul_mod
			{
					KERBAL_CONSTEXPR14
					static ResultType cacl(ResultType s) KERBAL_NOEXCEPT
					{
						return detail::static_mul_mod_impl<ResultType, m == 0 ? a : a % m, m>::cacl(s);
					}
			};

		} // namespace detail


		template <typename ResultType, ResultType a, ResultType c, ResultType m>
		class linear_congruential_engine
		{
			private:
				KERBAL_STATIC_ASSERT(
					m == 0 || (a < m && c < m),
					"If the template parameter m is not 0, the following relations shall hold: a < m and c < m"
				);

			public:
				typedef ResultType result_type;

				typedef kerbal::type_traits::integral_constant<result_type, a> MULTIPLIER;
				typedef kerbal::type_traits::integral_constant<result_type, c> INCREMENT;
				typedef kerbal::type_traits::integral_constant<result_type, m> MODULUS;

				typedef kerbal::type_traits::integral_constant<result_type, 1u> DEFAULT_SEED;

			private:
				result_type state_value;

			public:

				KERBAL_CONSTEXPR
				explicit
				linear_congruential_engine(const result_type & seed = DEFAULT_SEED::value) KERBAL_NOEXCEPT :
						state_value(
								m == 0u ?
								(seed == 0u ? 1u : seed) :
								(seed % m == 0u ? 1u : seed)
						)
				{
				}

				KERBAL_CONSTEXPR14
				result_type operator()() KERBAL_NOEXCEPT
				{
					if (m == 0) {
						state_value = a * state_value + c;
					} else {
						state_value = detail::static_mul_mod<result_type, a, m>::cacl(state_value);
						state_value += c - (state_value >= m - c) * m;
					}
					return state_value;
				}

				KERBAL_CONSTEXPR14
				void discard(unsigned long long times) KERBAL_NOEXCEPT
				{
					while (times != 0) {
						--times;
						(*this)();
					}
				}

				KERBAL_CONSTEXPR14
				void seed(const result_type & seed = 0u) KERBAL_NOEXCEPT
				{
					state_value = (
							m == 0u ?
							(seed == 0u ? 1u : seed) :
							(seed % m == 0u ? 1u : seed)
					);
				}

				KERBAL_CONSTEXPR
				static result_type min() KERBAL_NOEXCEPT
				{
					return c == 0u ? 1u : 0u;
				}

				KERBAL_CONSTEXPR
				static result_type max() KERBAL_NOEXCEPT
				{
					return m - 1u;
				}

				KERBAL_CONSTEXPR
				bool operator==(const linear_congruential_engine & rhs) const KERBAL_NOEXCEPT
				{
					return this->state_value == rhs.state_value;
				}

				KERBAL_CONSTEXPR
				bool operator!=(const linear_congruential_engine & rhs) const KERBAL_NOEXCEPT
				{
					return this->state_value != rhs.state_value;
				}

		};

		typedef kerbal::random::linear_congruential_engine<kerbal::compatibility::uint32_t, 16807, 0, 2147483647>
										minstd_rand0;
		typedef kerbal::random::linear_congruential_engine<kerbal::compatibility::uint32_t, 48271, 0, 2147483647>
										minstd_rand;

	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_LINEAR_CONGRUENTIAL_ENGINE_HPP
