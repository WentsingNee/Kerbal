/**
 * @file       discard_block_engine.hpp
 * @brief
 * @date       2020-05-29
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_DISCARD_BLOCK_ENGINE_HPP
#define KERBAL_RANDOM_DISCARD_BLOCK_ENGINE_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>

#include <cstddef>

#if __cplusplus >= 201103L
#	include <type_traits>
#endif

namespace kerbal
{

	namespace random
	{

		template <typename Engine, size_t P, size_t R>
		class discard_block_engine
		{
				KERBAL_STATIC_ASSERT(R <= P, "R Must be greater than 0 and not greater than P");

			public:
				typedef typename Engine::result_type result_type;

			private:
				Engine engine;
				size_t state_value;

			public:

				KERBAL_CONSTEXPR
				discard_block_engine()
							KERBAL_CONDITIONAL_NOEXCEPT(
								std::is_nothrow_default_constructible<Engine>::value
							)
							: engine(), state_value(0)
				{
				}

				KERBAL_CONSTEXPR
				explicit discard_block_engine(const result_type & seed)
							KERBAL_CONDITIONAL_NOEXCEPT(
								(std::is_nothrow_constructible<Engine, result_type>::value)
							)
							: engine(seed), state_value(0)
				{
				}

				KERBAL_CONSTEXPR
				explicit discard_block_engine(const Engine & engine)
							KERBAL_CONDITIONAL_NOEXCEPT(
								std::is_nothrow_copy_constructible<Engine>::value
							)
							: engine(engine), state_value(0)
				{
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR
				explicit discard_block_engine(Engine && engine)
							KERBAL_CONDITIONAL_NOEXCEPT(
								std::is_nothrow_move_constructible<Engine>::value
							)
							: engine(kerbal::compatibility::move(engine)), state_value(0)
				{
				}

#		endif

				KERBAL_CONSTEXPR14
				result_type operator()() KERBAL_NOEXCEPT
				{
					if (this->state_value == R) {
						this->engine.discard(P - R);
						this->state_value = 0;
					}
					++this->state_value;
					return this->engine();
				}

				KERBAL_CONSTEXPR14
				void discard(unsigned long long times) KERBAL_NOEXCEPT
				{
					for (; times != 0ULL; --times) {
						(*this)();
					}
				}

				KERBAL_CONSTEXPR14
				void seed() KERBAL_NOEXCEPT
				{
					this->engine.seed();
				}

				KERBAL_CONSTEXPR14
				void seed(const result_type & seed) KERBAL_NOEXCEPT
				{
					this->engine.seed(seed);
				}

				static KERBAL_CONSTEXPR result_type min() KERBAL_NOEXCEPT
				{
					return Engine::min();
				}

				static KERBAL_CONSTEXPR result_type max() KERBAL_NOEXCEPT
				{
					return Engine::max();
				}

				KERBAL_CONSTEXPR
				bool operator==(const discard_block_engine & rhs) const
				{
					return this->state_value == rhs.state_value &&
							static_cast<bool>(this->engine == rhs.engine);
				}

				KERBAL_CONSTEXPR
				bool operator!=(const discard_block_engine & rhs) const
				{
					return this->state_value != rhs.state_value ||
							static_cast<bool>(this->engine != rhs.engine);
				}

		};

	} // namespace random

} // namespace kerbal

#endif	// KERBAL_RANDOM_DISCARD_BLOCK_ENGINE_HPP
