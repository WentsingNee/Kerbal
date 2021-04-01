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
#include <kerbal/type_traits/integral_constant.hpp>


namespace kerbal
{

	namespace random
	{

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
						state_value(seed % m == 0u ? 1u : seed)
				{
				}

				KERBAL_CONSTEXPR14
				result_type operator()() KERBAL_NOEXCEPT
				{
					// Schrage's algorithm
					const result_type q = m / a;
					const result_type r = m % a;
					const result_type t0 = a * (state_value % q);
					const result_type t1 = r * (state_value / q);
					state_value = t0 + (t0 < t1) * m - t1;
					state_value += c - (state_value >= m - c) * m;
					return state_value;
				}

				KERBAL_CONSTEXPR14
				void discard(unsigned long long times) KERBAL_NOEXCEPT
				{
					for (; times != 0ULL; --times) {
						(*this)();
					}
				}

				KERBAL_CONSTEXPR14
				void seed(const result_type & seed = 0u) KERBAL_NOEXCEPT
				{
					state_value = (seed % m == 0u ? 1u : seed);
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

#endif	// KERBAL_RANDOM_LINEAR_CONGRUENTIAL_ENGINE_HPP
