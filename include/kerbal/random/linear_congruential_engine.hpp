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

#ifndef KERBAL_RANDOM_LINEAR_CONGRUENTIAL_ENGINE_HPP_
#define KERBAL_RANDOM_LINEAR_CONGRUENTIAL_ENGINE_HPP_

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>

namespace kerbal
{
	namespace random
	{

		template <typename ResultType, ResultType a, ResultType c, ResultType m>
		class linear_congruential_engine
		{
			public:
				typedef ResultType result_type;

			private:
				result_type state_value;

			public:

				KERBAL_CONSTEXPR
				explicit linear_congruential_engine(const result_type & seed = 0u) KERBAL_NOEXCEPT :
						state_value(seed % m == 0u ? 1u : seed)
				{
				}

				KERBAL_CONSTEXPR14
				result_type operator()() KERBAL_NOEXCEPT
				{
					state_value = (a * state_value + c) % m;
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

				static KERBAL_CONSTEXPR result_type min() KERBAL_NOEXCEPT
				{
					return c == 0u ? 1u : 0u;
				}

				static KERBAL_CONSTEXPR result_type max() KERBAL_NOEXCEPT
				{
					return m - 1u;
				}
		};

		typedef kerbal::random::linear_congruential_engine<unsigned int, 16807UL, 0UL, 2147483647UL>
										minstd_rand0;
		typedef kerbal::random::linear_congruential_engine<unsigned int, 48271, 0, 2147483647>
										minstd_rand;

	} // namespace random

} // namespace kerbal

#endif	/* KERBAL_RANDOM_LINEAR_CONGRUENTIAL_ENGINE_HPP_ */
