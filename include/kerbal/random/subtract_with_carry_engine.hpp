/**
 * @file       subtract_with_carry_engine.hpp
 * @brief
 * @date       2021-02-16
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_SUBTRACT_WITH_CARRY_ENGINE_HPP
#define KERBAL_RANDOM_SUBTRACT_WITH_CARRY_ENGINE_HPP

#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/random/linear_congruential_engine.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>

namespace kerbal
{

	namespace random
	{

		template <typename UIntType, std::size_t W, std::size_t S, std::size_t R>
		class subtract_with_carry_engine
		{
			public:
				typedef UIntType result_type;

				// parameter values
				typedef kerbal::type_traits::integral_constant<std::size_t, W> WORD_SIZE;
				typedef kerbal::type_traits::integral_constant<std::size_t, S> SHORT_LAG;
				typedef kerbal::type_traits::integral_constant<std::size_t, R> LONG_LAG;
				typedef kerbal::type_traits::integral_constant<result_type, 19780503u> DEFAULT_SEED;

			private:
				result_type _K_state[LONG_LAG::value];
				result_type _K_carry;
				std::size_t _K_index;

			public:
				explicit
				subtract_with_carry_engine(result_type seed = DEFAULT_SEED::value)
				{
					kerbal::random::linear_congruential_engine<result_type, 40014u, 0u, 2147483563u>
							lcg(seed == 0u ? DEFAULT_SEED::value : seed);

					const std::size_t __n = (WORD_SIZE::value + 31) / 32;

					for (std::size_t i = 0; i < LONG_LAG::value; ++i) {
						result_type sum = 0u;
						result_type factor = 1u;
						for (std::size_t j = 0; j < __n; ++j) {
							sum += lcg() * factor;
//							sum += __detail::__mod<uint_least32_t,
//									__detail::_Shift<uint_least32_t, 32>::__value>
//											 (lcg()) * factor;
							factor *= __detail::_Shift<_UIntType, 32>::__value;
						}
						_K_state[i] = __detail::__mod<_UIntType,
								__detail::_Shift<_UIntType, WORD_SIZE::value>::__value>(sum);
					}
					_K_carry = (_K_state[LONG_LAG::value - 1] == 0) ? 1 : 0;
					_K_index = 0;
				}

		};

		typedef kerbal::random::subtract_with_carry_engine<kerbal::compatibility::uint32_t , 24, 10, 24> ranlux24_base;
		typedef kerbal::random::subtract_with_carry_engine<kerbal::compatibility::uint64_t, 48, 5, 12> ranlux48_base;

	} // namespace random

} // namespace kerbal


#endif // KERBAL_RANDOM_SUBTRACT_WITH_CARRY_ENGINE_HPP
