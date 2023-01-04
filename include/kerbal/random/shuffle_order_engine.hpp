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
#include <kerbal/utility/declval.hpp>

#include <cstddef>

#if __cplusplus >= 201103L
#	include <kerbal/type_traits/is_nothrow_constructible.hpp>
#	include <kerbal/type_traits/is_nothrow_copy_constructible.hpp>
#	include <kerbal/type_traits/is_nothrow_default_constructible.hpp>
#	include <kerbal/type_traits/is_nothrow_move_constructible.hpp>
#	include <kerbal/type_traits/tribool_constant.hpp>
#endif


namespace kerbal
{

	namespace random
	{

		namespace detail
		{

			template <typename T>
			KERBAL_CONSTEXPR
			double muldiv_final(T a, T b, T c) KERBAL_NOEXCEPT
			{
				return (double)(a) * (double)(b) / c;
			}

			template <typename T>
			KERBAL_CONSTEXPR
			T muldiv_less_b(T a, T b, T c) KERBAL_NOEXCEPT
			{
				return (c - b < b) ?
					a - muldiv_final(a, c - b, c) :
					muldiv_final(a, b, c);
			}

			template <typename T>
			KERBAL_CONSTEXPR
			T muldiv_less_a(T a, T b, T c) KERBAL_NOEXCEPT
			{
				return (c - a < a) ?
					b - muldiv_less_b(c - a, b, c) :
					muldiv_less_b(a, b, c);
			}

		} // namespace detail

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
				shuffle_order_engine()
						KERBAL_CONDITIONAL_NOEXCEPT(
								kerbal::type_traits::tribool_is_true<
									kerbal::type_traits::is_nothrow_default_constructible<Engine>
								>::value
						) :
						_K_base_eg(), _K_stored_y()
				{
					_K_init();
				}

				KERBAL_CONSTEXPR14
				explicit shuffle_order_engine(result_type seed)
						KERBAL_CONDITIONAL_NOEXCEPT((
								kerbal::type_traits::tribool_is_true<
									kerbal::type_traits::is_nothrow_constructible<Engine, result_type>
								>::value
						)) :
						_K_base_eg(seed), _K_stored_y()
				{
					_K_init();
				}

				KERBAL_CONSTEXPR14
				explicit shuffle_order_engine(const Engine & engine)
						KERBAL_CONDITIONAL_NOEXCEPT(
								kerbal::type_traits::tribool_is_true<
									kerbal::type_traits::is_nothrow_copy_constructible<Engine>
								>::value
						) :
						_K_base_eg(engine), _K_stored_y()
				{
					_K_init();
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				explicit shuffle_order_engine(Engine && engine)
						KERBAL_CONDITIONAL_NOEXCEPT(
								kerbal::type_traits::tribool_is_true<
									kerbal::type_traits::is_nothrow_move_constructible<Engine>
								>::value
						) :
						_K_base_eg(kerbal::compatibility::move(engine)), _K_stored_y()
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
				const Engine & base() const KERBAL_NOEXCEPT
				{
					return this->_K_base_eg;
				}

				KERBAL_CONSTEXPR14
				result_type operator()()
						KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(_K_base_eg())
						)
				{
					const result_type min = _K_base_eg.min();
					const result_type max = _K_base_eg.max();
					result_type R = (max - min + 1);
					result_type b = _K_stored_y - min;
					std::size_t J = R == 0 ?
									(double)(K) * (double)(_K_stored_y - min) / (max - min + 1.0) :
									(K / R) * b + detail::muldiv_less_a<result_type>(K % R, b, R);
					result_type next = _K_base_eg();
					_K_stored_y = _K_stored[J];
					_K_stored[J] = next;
					return _K_stored_y;
				}

				KERBAL_CONSTEXPR14
				void discard(unsigned long long times)
						KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(kerbal::utility::declthis<shuffle_order_engine>()->operator()())
						)
				{
					while (times != 0) {
						--times;
						(*this)();
					}
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
