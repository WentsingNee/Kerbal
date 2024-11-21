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
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/numeric/numeric_limits.hpp>

#include <cstddef>

#if __cplusplus >= 201103L
#	include <kerbal/type_traits/is_nothrow_constructible.hpp>
#	include <kerbal/type_traits/is_nothrow_copy_constructible.hpp>
#	include <kerbal/type_traits/is_nothrow_default_constructible.hpp>
#	include <kerbal/type_traits/is_nothrow_move_constructible.hpp>
#endif


namespace kerbal
{

	namespace random
	{

		template <typename Engine, std::size_t P, std::size_t R>
		class discard_block_engine
		{
			private:
				KERBAL_STATIC_ASSERT(R <= P, "R Must be greater than 0 and not greater than P");

			public:
				typedef typename Engine::result_type result_type;

			private:
				Engine k_base_eg;
				std::size_t k_idx;

			public:

				KERBAL_CONSTEXPR
				discard_block_engine()
					KERBAL_CONDITIONAL_NOEXCEPT(
						kerbal::type_traits::try_test_is_nothrow_default_constructible<Engine>::IS_TRUE::value
					) :
					k_base_eg(), k_idx(0)
				{
				}

				KERBAL_CONSTEXPR
				explicit discard_block_engine(const result_type & seed)
					KERBAL_CONDITIONAL_NOEXCEPT((
						kerbal::type_traits::try_test_is_nothrow_constructible<Engine, result_type>::IS_TRUE::value
					)) :
					k_base_eg(seed), k_idx(0)
				{
				}

				KERBAL_CONSTEXPR
				explicit discard_block_engine(const Engine & engine)
					KERBAL_CONDITIONAL_NOEXCEPT(
						kerbal::type_traits::try_test_is_nothrow_copy_constructible<Engine>::IS_TRUE::value
					) :
					k_base_eg(engine), k_idx(0)
				{
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR
				explicit discard_block_engine(Engine && engine)
					KERBAL_CONDITIONAL_NOEXCEPT(
						kerbal::type_traits::try_test_is_nothrow_move_constructible<Engine>::IS_TRUE::value
					) :
					k_base_eg(kerbal::compatibility::move(engine)), k_idx(0)
				{
				}

#		endif

				KERBAL_CONSTEXPR14
				void seed()
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(k_base_eg.seed())
					)
				{
					this->k_base_eg.seed();
				}

				KERBAL_CONSTEXPR14
				void seed(const result_type & seed)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(k_base_eg.seed(seed))
					)
				{
					this->k_base_eg.seed(seed);
				}

				KERBAL_CONSTEXPR14
				const Engine & base() const KERBAL_NOEXCEPT
				{
					return this->k_base_eg;
				}

				KERBAL_CONSTEXPR14
				result_type operator()()
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(k_base_eg.discard(P - R)) &&
						noexcept(k_base_eg())
					)
				{
					if (this->k_idx == R) {
						this->k_base_eg.discard(P - R);
						this->k_idx = 0;
					}
					++this->k_idx;
					return this->k_base_eg();
				}

				KERBAL_CONSTEXPR14
				void discard(unsigned long long times)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(k_base_eg.discard(times))
					)
				{
/*
					// plain version that the calculation may overflow
					unsigned long long rounds = times / R;
					times %= R;
					unsigned long long base_discard_times = rounds * P + times;
					unsigned long long retreat = R - times;
					bool once_more_rewind = this->k_idx > retreat;
					if (once_more_rewind) {
						base_discard_times += P - R;
					}
					this->k_base_eg.discard(base_discard_times);
					if (once_more_rewind) {
						this->k_idx -= retreat;
					} else {
						this->k_idx += times;
					}
*/

					typedef kerbal::numeric::numeric_limits<unsigned long long>::MAX MAX;

					unsigned long long rounds = times / R;
					times %= R;
					unsigned long long retreat = R - times;
					bool once_more_rewind = this->k_idx > retreat;
					unsigned long long base_remain_discard_times = times; // times' = times % R
					if (once_more_rewind) {
						base_remain_discard_times += P - R;
					}
					if (rounds <= MAX::value / P) { // P * rounds will overflow?
						this->k_base_eg.discard(rounds * P);
					} else {
						for (std::size_t i = 0; i < P; ++i) {
							this->k_base_eg.discard(rounds);
						}
					}
					this->k_base_eg.discard(base_remain_discard_times);
					if (once_more_rewind) {
						this->k_idx -= retreat;
					} else {
						this->k_idx += times;
					}

				}

			private:
				template <typename OutputIterator>
				KERBAL_CONSTEXPR14
				void k_generate(OutputIterator first, OutputIterator last, std::output_iterator_tag)
				{
					while (first != last) {
						*first = (*this)();
						++first;
					}
				}

				template <typename RandomAccessIterator>
				KERBAL_CONSTEXPR14
				void k_generate(RandomAccessIterator first, RandomAccessIterator last, std::random_access_iterator_tag)
				{
					this->generate_n(first, kerbal::iterator::distance(first, last));
				}

			public:

				template <typename OutputIterator>
				KERBAL_CONSTEXPR14
				void generate(OutputIterator first, OutputIterator last)
				{
					this->k_generate(first, last, kerbal::iterator::iterator_category(first));
				}

				template <typename OutputIterator>
				KERBAL_CONSTEXPR14
				OutputIterator generate_n(OutputIterator first, typename kerbal::iterator::iterator_traits<OutputIterator>::difference_type n)
				{
					std::size_t this_round_remain = R - this->k_idx;
					if (std::size_t(n) <= this_round_remain) {
						this->k_idx += n;
						return this->k_base_eg.generate_n(first, n);
					}
					this->k_idx = R;
					first = this->k_base_eg.generate_n(first, this_round_remain);
					n -= this_round_remain;
					this->k_base_eg.discard(P - R);
					this->k_idx = 0;

					for (std::size_t round = 0; round < n / R; ++round) {
						this->k_idx = R;
						first = this->k_base_eg.generate_n(first, R);
						this->k_base_eg.discard(P - R);
						this->k_idx = 0;
					}
					n %= R;
					this->k_idx = n;
					return this->k_base_eg.generate_n(first, n);
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

				KERBAL_CONSTEXPR
				bool operator==(const discard_block_engine & rhs) const
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(
							static_cast<bool>(k_base_eg == rhs.k_base_eg)
						)
					)
				{
					return
						this->k_idx == rhs.k_idx &&
						static_cast<bool>(this->k_base_eg == rhs.k_base_eg)
					;
				}

				KERBAL_CONSTEXPR
				bool operator!=(const discard_block_engine & rhs) const
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(
							static_cast<bool>(k_base_eg != rhs.k_base_eg)
						)
					)
				{
					return
						this->k_idx != rhs.k_idx ||
						static_cast<bool>(this->k_base_eg != rhs.k_base_eg)
					;
				}

		};

	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_DISCARD_BLOCK_ENGINE_HPP
