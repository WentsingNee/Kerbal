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

#ifndef KERBAL_RANDOM_ENGINE_LINEAR_CONGRUENTIAL_ENGINE_HPP
#define KERBAL_RANDOM_ENGINE_LINEAR_CONGRUENTIAL_ENGINE_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/numeric/numeric_limits.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/smath/add_mod_sm.hpp>
#include <kerbal/smath/multiply_mod_sa_b_sm.hpp>
#include <kerbal/smath/pow_mod_sa_n_sm.hpp>
#include <kerbal/smath/sigma_pow_mod_sa_n_sm.hpp>
#include <kerbal/smath/xmod.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/type_identity.hpp>

#include <climits>


namespace kerbal
{

	namespace random
	{

		KERBAL_MODULE_EXPORT
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
						kerbal::smath::xmod<result_type, m>::f(seed) == 0u ? 1u : seed
					)
				{
				}

				KERBAL_CONSTEXPR14
				result_type operator()() KERBAL_NOEXCEPT
				{
					state_value = kerbal::smath::multiply_mod_sa_b_sm<result_type, a, m>::f(state_value);
					state_value = kerbal::smath::add_mod_sm<result_type, m>::f(state_value, c);
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
					result_type a_pow_times_mod_m = kerbal::smath::pow_mod_sa_n_sm<result_type, a, m>::f(times);
					state_value = kerbal::smath::multiply_mod_a_b_sm<ResultType, m>::f(a_pow_times_mod_m, state_value);
					if (c != 0) {
						result_type sigma = kerbal::smath::sigma_pow_mod_sa_n_sm<result_type, a, m>::f(times);
						sigma = kerbal::smath::multiply_mod_sa_b_sm<result_type, c, m>::f(sigma);
						state_value = kerbal::smath::add_mod_sm<result_type, m>::f(state_value, sigma);
					}
				}

				KERBAL_CONSTEXPR14
				void seed(const result_type & seed = 0u) KERBAL_NOEXCEPT
				{
					state_value = kerbal::smath::xmod<result_type, m>::f(seed) == 0u ? 1u : seed;
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

		KERBAL_MODULE_EXPORT
		typedef
		kerbal::random::linear_congruential_engine<
			kerbal::compatibility::uint32_t,
			16807, 0, 2147483647
		> minstd_rand0;

		KERBAL_MODULE_EXPORT
		typedef
		kerbal::random::linear_congruential_engine<
			kerbal::compatibility::uint32_t,
			48271, 0, 2147483647
		> minstd_rand;

	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_ENGINE_LINEAR_CONGRUENTIAL_ENGINE_HPP
