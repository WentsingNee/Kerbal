/**
 * @file       shuffle_order_engine.hpp
 * @brief
 * @date       2021-02-17
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_SHUFFLE_ORDER_ENGINE_HPP
#define KERBAL_RANDOM_SHUFFLE_ORDER_ENGINE_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>

#include <cstddef>

#if __cplusplus >= 201103L
#	include <type_traits>
#endif

namespace kerbal
{

	namespace random
	{

		template <typename Engine, std::size_t K>
		class shuffle_order_engine
		{
			public:
				typedef typename Engine::result_type result_type;

			private:
				Engine _K_base_eg;
				result_type _K_stored[K];
				result_type _K_stored_y;

			private:
				KERBAL_CONSTEXPR14
				void _K_init()
				{
					for (std::size_t i = 0; i < K; ++i) {
						_K_stored[i] = _K_base_eg();
					}
					_K_stored_y = _K_base_eg();
				}

			public:
				KERBAL_CONSTEXPR14
				shuffle_order_engine() :
						_K_base_eg(), _K_stored_y()
				{
					_K_init();
				}

				KERBAL_CONSTEXPR14
				explicit shuffle_order_engine(result_type seed) :
						_K_base_eg(seed), _K_stored_y()
				{
					_K_init();
				}

				KERBAL_CONSTEXPR14
				explicit shuffle_order_engine(const Engine & engine)
							KERBAL_CONDITIONAL_NOEXCEPT(
								std::is_nothrow_copy_constructible<Engine>::value
							)
						: _K_base_eg(engine), _K_stored_y()
				{
					_K_init();
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				explicit shuffle_order_engine(Engine && engine)
							KERBAL_CONDITIONAL_NOEXCEPT(
								std::is_nothrow_move_constructible<Engine>::value
							)
						: _K_base_eg(kerbal::compatibility::move(engine)), _K_stored_y()
				{
					_K_init();
				}

#		endif

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

				KERBAL_CONSTEXPR14
				const Engine& base() const KERBAL_NOEXCEPT
				{
					return this->_K_base_eg;
				}

				KERBAL_CONSTEXPR14
				result_type operator()()
				{
					const result_type min = _K_base_eg.min();
					const result_type max = _K_base_eg.max();
					std::size_t J = K * (_K_stored_y - min) / (max - min + 1.0);
					_K_stored_y = _K_stored[J];
					_K_stored[J] = _K_base_eg();
					return _K_stored_y;
				}

				KERBAL_CONSTEXPR
				static result_type min()
							KERBAL_CONDITIONAL_NOEXCEPT(
									noexcept(Engine::min())
							)
				{
					return Engine::min();
				}

				KERBAL_CONSTEXPR
				static result_type max()
							KERBAL_CONDITIONAL_NOEXCEPT(
									noexcept(Engine::max())
							)
				{
					return Engine::max();
				}

		};

	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_SHUFFLE_ORDER_ENGINE_HPP
