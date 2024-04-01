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
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/type_identity.hpp>

#include <climits>


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
					static ResultType cacl(ResultType /*s*/) KERBAL_NOEXCEPT
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


			template <typename ResultType, ResultType m, bool = (m == 0)>
			struct partial_static_mul_mod_impl;

			template <typename ResultType, ResultType m>
			struct partial_static_mul_mod_impl<ResultType, m, true> // m == 0
			{
					KERBAL_CONSTEXPR
					static ResultType cacl(ResultType a, ResultType s) KERBAL_NOEXCEPT
					{
						return a * s;
					}
			};

			template <typename ResultType, ResultType m>
			struct partial_static_mul_mod_impl<ResultType, m, false> // m != 0
			{
				private:
					KERBAL_CONSTEXPR14
					static ResultType cacl_impl2(ResultType a, ResultType s) KERBAL_NOEXCEPT
					{
						// a * s % m
						// a < m, s < m

						if (a == 0) {
							return 0;
						}

						if (s <= kerbal::numeric::numeric_limits<ResultType>::MAX::value / a) {
							return a * s % m;
						}

						ResultType q = m / a;
						ResultType r = m % a;

						ResultType t0 = a * (s % q);
						ResultType t1 =
								r <= q ?
								r * (s / q) :
								cacl_impl2(r, s / q);
						return t0 - t1 + (t0 < t1) * m;
					}

					KERBAL_CONSTEXPR14
					static ResultType cacl_impl(ResultType a, ResultType s, kerbal::type_traits::type_identity<void>) KERBAL_NOEXCEPT
					{
						return cacl_impl2(a, s);
					}

					template <typename T>
					KERBAL_CONSTEXPR14
					static ResultType cacl_impl(ResultType a, ResultType s, kerbal::type_traits::type_identity<T>) KERBAL_NOEXCEPT
					{
						// a * s will not overflow under T
						return T(a) * T(s) % m;
					}

				public:
					KERBAL_CONSTEXPR14
					static ResultType cacl(ResultType a, ResultType s) KERBAL_NOEXCEPT
					{
						typedef typename find_never_overflow_integer_type_for_mul_mod<ResultType, m - 1, m>::type T;
						return cacl_impl(a % m, s % m, kerbal::type_traits::type_identity<T>());
					}
			};

			template <typename ResultType, ResultType m>
			struct partial_static_mul_mod
			{
					KERBAL_CONSTEXPR14
					static ResultType cacl(ResultType a, ResultType s) KERBAL_NOEXCEPT
					{
						return partial_static_mul_mod_impl<ResultType, m>::cacl(a, s);
					}
			};


			template <typename ResultType, ResultType m>
			struct add_mod
			{
					KERBAL_CONSTEXPR14
					static ResultType cacl(ResultType a, ResultType b) KERBAL_NOEXCEPT
					{
						// pre: a = a % m && b = b % m
						return a + b - (a >= m - b) * m;
					}
			};


			template <typename ResultType, ResultType a, ResultType m, bool = (m == 0)>
			struct pow_mod_m_impl;

			template <typename ResultType, ResultType a, ResultType m>
			struct pow_mod_m_impl<ResultType, a, m, true>
			{
					KERBAL_CONSTEXPR14
					static ResultType cacl(unsigned long long n) KERBAL_NOEXCEPT
					{
						ResultType r = 1;
						ResultType base = a;
						while (true) {
							unsigned long long half_n = n / 2;
							if (n % 2 == 1) {
								r *= base;
							}
							if (half_n == 0) {
								break;
							}
							base = base * base;
							n = half_n;
						}
						return r;
					}
			};

			template <typename ResultType, ResultType a, ResultType m>
			struct pow_mod_m_impl<ResultType, a, m, false>
			{
					KERBAL_CONSTEXPR14
					static ResultType cacl(unsigned long long n) KERBAL_NOEXCEPT
					{
						ResultType r = 1;
						ResultType base = a;
						while (true) {
							unsigned long long half_n = n / 2;
							if (n % 2 == 1) {
								r = partial_static_mul_mod<ResultType, m>::cacl(r, base);
							}
							if (half_n == 0) {
								break;
							}
							base = partial_static_mul_mod<ResultType, m>::cacl(base, base);
							n = half_n;
						}
						return r;
					}
			};

			/*
			 * a ** n % m
			 */
			template <typename ResultType, ResultType a, ResultType m>
			struct pow_mod : pow_mod_m_impl<ResultType, a, m>
			{
			};



			// a ** (n - 1) + ... + a ** 3 + a ** 2 + a ** 1 + 1
			template <typename ResultType, ResultType a, ResultType m>
			struct sigma_pow_mod
			{
					KERBAL_CONSTEXPR14
					static ResultType cacl(unsigned long long n) KERBAL_NOEXCEPT
					{
						/*
						 *   e.g. for n = 21
						 *
						 *   16  8  4  2  1
						 *    1  0  1  0  1  r = r * a + 1
						 *       1  0  1  0  r = r * (a ** 10 + 1)
						 *          1  0  1  r = r * (a ** 5 + 1)
						 *          1  0  0  r = r * a + 1
						 *             1  0  r = r * (a ** 2 + 1)
						 *                1  r = r * a + 1
						 */

						// pre: n != 0
						int lead = CHAR_BIT * sizeof(n) - 1;
						{
							// to opt: lead = CHAR_BIT * sizeof(n) - 1 - __builtin_clzll(n);
							while (((n >> lead) & 1) == 0) {
								lead--;
							}
						}
						ResultType r = 1;
						bool b = true;
						ResultType poa = 1;
						while (lead > 0) {
							--lead;
							poa = partial_static_mul_mod<ResultType, m>::cacl(poa, poa);
							if (b) {
								poa = partial_static_mul_mod<ResultType, m>::cacl(a, poa);
							}
							r = partial_static_mul_mod<ResultType, m>::cacl(
								r,
								add_mod<ResultType, m>::cacl(poa, 1)
							);
							b = (n >> lead) & 1;
							if (b) {
								// r = r * a + 1
								r = static_mul_mod<ResultType, a, m>::cacl(r);
								r = add_mod<ResultType, m>::cacl(r, 1);
							}
						}
						return r;
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
						state_value = detail::add_mod<result_type, m>::cacl(state_value, c);
					}
					return state_value;
				}

				KERBAL_CONSTEXPR14
				void discard(unsigned long long times) KERBAL_NOEXCEPT
				{
					if (times == 0) {
						return ;
					}
					/*
					 * s_{i+n} = a^{n} \times s_i + c \times \sum_{i=0}^{n-1} a^i
					 *         = a ** n * s_i + c * (a ** (n - 1) + a ** (n - 2) + ... + a + 1)
					 */
					result_type a_pow_times_mod_m = detail::pow_mod<result_type, a, m>::cacl(times);
					state_value = detail::partial_static_mul_mod<ResultType, m>::cacl(a_pow_times_mod_m, state_value);
					if (c != 0) {
						if (a == 1) {
							if (m != 0) {
								times %= m;
							}
							result_type c_mul_times_mod_m = detail::static_mul_mod<result_type, c, m>::cacl(times);
							state_value = detail::add_mod<result_type, m>::cacl(state_value, c_mul_times_mod_m);
						} else {
							result_type sigma = detail::sigma_pow_mod<result_type, a, m>::cacl(times);
							sigma = detail::static_mul_mod<result_type, c, m>::cacl(sigma);
							state_value = detail::add_mod<result_type, m>::cacl(state_value, sigma);
						}
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

				template <typename OutputIterator>
				KERBAL_CONSTEXPR14
				void generate(OutputIterator first, OutputIterator last)
				{
					while (first != last) {
						*first = (*this)();
						++first;
					}
				}

				template <typename OutputIterator>
				KERBAL_CONSTEXPR14
				OutputIterator generate_n(OutputIterator first, typename kerbal::iterator::iterator_traits<OutputIterator>::difference_type n)
				{
					while (n != 0) {
						--n;
						*first = (*this)();
						++first;
					}
					return first;
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
