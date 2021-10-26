/**
 * @file       sync_mersenne_twister_engine.hpp
 * @brief
 * @date       2021-10-26
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_SYNC_MERSENNE_TWISTER_ENGINE_HPP
#define KERBAL_RANDOM_SYNC_MERSENNE_TWISTER_ENGINE_HPP

#include <kerbal/algorithm/sequence_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/container/nonmember_container_access.hpp>
#include <kerbal/numeric/numeric_limits.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>
#include <atomic>


namespace kerbal
{

	namespace random
	{

		template <
				typename UIntType,
				std::size_t W, std::size_t N, std::size_t M, std::size_t R,
				UIntType A, std::size_t U, UIntType D, std::size_t S,
				UIntType B, std::size_t T,
				UIntType C, std::size_t L, UIntType F
		>
		class sync_mersenne_twister_engine
		{
			private:
				KERBAL_STATIC_ASSERT(0 < M,     "the following relations shall hold: 0 < M");
				KERBAL_STATIC_ASSERT(M <= N,    "the following relations shall hold: M <= N");
				KERBAL_STATIC_ASSERT(2 * U < W, "the following relations shall hold: 2 * U < W");
				KERBAL_STATIC_ASSERT(R <= W,    "the following relations shall hold: R <= W");
				KERBAL_STATIC_ASSERT(U <= W,    "the following relations shall hold: U <= W");
				KERBAL_STATIC_ASSERT(S <= W,    "the following relations shall hold: S <= W");
				KERBAL_STATIC_ASSERT(T <= W,    "the following relations shall hold: T <= W");
				KERBAL_STATIC_ASSERT(L <= W,    "the following relations shall hold: L <= W");
				KERBAL_STATIC_ASSERT(W <= kerbal::numeric::numeric_limits<UIntType>::DIGITS::value,
						"the following relations shall hold: w <= numeric_limits<UIntType>::digits");

				// (1 << W) - 1u
				struct _1_shift_W_minus_1 :
						public kerbal::type_traits::integral_constant<
							UIntType,
							W == kerbal::numeric::numeric_limits<UIntType>::DIGITS::value ?
								~static_cast<UIntType>(0u) :
								((static_cast<UIntType>(1u) << W) - 1u)
						>
				{
				};

				KERBAL_STATIC_ASSERT(A <= _1_shift_W_minus_1::value, "the following relations shall hold: A <= (1u << W) - 1u");
				KERBAL_STATIC_ASSERT(B <= _1_shift_W_minus_1::value, "the following relations shall hold: B <= (1u << W) - 1u");
				KERBAL_STATIC_ASSERT(C <= _1_shift_W_minus_1::value, "the following relations shall hold: C <= (1u << W) - 1u");
				KERBAL_STATIC_ASSERT(D <= _1_shift_W_minus_1::value, "the following relations shall hold: D <= (1u << W) - 1u");
				KERBAL_STATIC_ASSERT(F <= _1_shift_W_minus_1::value, "the following relations shall hold: F <= (1u << W) - 1u");

			public:
				typedef UIntType result_type;

				typedef kerbal::type_traits::integral_constant<std::size_t, W>		WORD_SIZE;
				typedef kerbal::type_traits::integral_constant<std::size_t, N>		STATE_SIZE;
				typedef kerbal::type_traits::integral_constant<std::size_t, M>		SHIFT_SIZE;
				typedef kerbal::type_traits::integral_constant<std::size_t, R>		MASK_BITS;

				typedef kerbal::type_traits::integral_constant<result_type, A>	XOR_MASK;
				typedef kerbal::type_traits::integral_constant<std::size_t, U>		TEMPERING_U;
				typedef kerbal::type_traits::integral_constant<result_type, D>	TEMPERING_D;
				typedef kerbal::type_traits::integral_constant<std::size_t, S>		TEMPERING_S;

				typedef kerbal::type_traits::integral_constant<result_type, B>	TEMPERING_B;
				typedef kerbal::type_traits::integral_constant<std::size_t, T>		TEMPERING_T;

				typedef kerbal::type_traits::integral_constant<result_type, C>	TEMPERING_C;
				typedef kerbal::type_traits::integral_constant<std::size_t, L>		TEMPERING_L;
				typedef kerbal::type_traits::integral_constant<result_type, F>	INITIALIZATION_MULTIPLIER;

				typedef kerbal::type_traits::integral_constant<result_type, 5489u>		DEFAULT_SEED;

			private:
				result_type mt[N];
				std::atomic<std::size_t> mti;

				KERBAL_CONSTEXPR14
				void twist() KERBAL_NOEXCEPT
				{
					typedef kerbal::type_traits::integral_constant<result_type, (~static_cast<result_type>(0)) << R> UPPER_MASK; // most significant w-r bits
					typedef kerbal::type_traits::integral_constant<result_type, ~UPPER_MASK::value> LOWER_MASK; // least significant r bits

					const result_type mag01[2] = {0x0UL, A};

					std::size_t i = 0;

					for (; i < N - M; ++i) {
						result_type y = (this->mt[i] & UPPER_MASK::value) | (this->mt[i + 1] & LOWER_MASK::value);
						this->mt[i] = this->mt[i + M] ^ (y >> 1) ^ mag01[y & 0x1UL];
					}
					for (; i < N - 1; ++i) {
						result_type y = (this->mt[i] & UPPER_MASK::value) | (this->mt[i + 1] & LOWER_MASK::value);
						this->mt[i] = this->mt[i - (N - M)] ^ (y >> 1) ^ mag01[y & 0x1UL];
					}
					result_type y = (this->mt[N - 1] & UPPER_MASK::value) | (this->mt[0] & LOWER_MASK::value);
					this->mt[N - 1] = this->mt[M - 1] ^ (y >> 1) ^ mag01[y & 0x1UL];
				}


			private:
				KERBAL_CONSTEXPR14
				void init_mt() KERBAL_NOEXCEPT
				{
					for (std::size_t i = 1; i < N; ++i) {
						result_type x = this->mt[i - 1];
						x ^= x >> (W - 2);
						x *= F;
						x += static_cast<result_type>(i);
						this->mt[i] = x;
					}
				}

			public:

#		if __cplusplus >= 201103L

				explicit sync_mersenne_twister_engine(result_type seed = DEFAULT_SEED::value) KERBAL_NOEXCEPT
						: mt{seed}, mti(N)
				{
					this->init_mt();
				}

#		else

				explicit sync_mersenne_twister_engine(result_type seed = DEFAULT_SEED::value) KERBAL_NOEXCEPT
						: mti(N)
				{
					this->mt[0] = seed;
					this->init_mt();
				}

#		endif

				void sync_seed(result_type seed = DEFAULT_SEED::value) KERBAL_NOEXCEPT
				{
					std::size_t mti_old = this->mti.load();
					while (true) {
						if (mti_old == -1) {
							mti_old = this->mti.load();
							continue; // spin
						}
						if (this->mti.compare_exchange_weak(mti_old, -1)) {
							break;
						}
					}
					// enter critical section
					this->mt[0] = seed;
					this->init_mt();
					this->mti.store(N);
					// exit critical section
				}

				result_type sync_next() KERBAL_NOEXCEPT
				{
					std::size_t mti_old = this->mti.load();
					while (true) {
						if (mti_old == -1) {
							mti_old = this->mti.load();
							continue; // spin
						}
						result_type y;
						if (mti_old == N) {
							if (!this->mti.compare_exchange_weak(mti_old, -1)) {
								continue;
							}
							// enter critical section
							this->twist(); /* generate N words at one time */
							y = this->mt[0];
							this->mti.store(1);
							// exit critical section
						} else {
							y = this->mt[mti_old];
							if (!this->mti.compare_exchange_weak(mti_old, mti_old + 1)) {
								continue;
							}
						}
						y ^= (y >> U) & D;
						y ^= (y << S) & B;
						y ^= (y << T) & C;
						y ^= y >> L;
						return y;
					}
				}

				result_type operator()() KERBAL_NOEXCEPT
				{
					return this->sync_next();
				}

				void sync_discard() KERBAL_NOEXCEPT
				{
					std::size_t mti_old = this->mti.load();
					while (true) {
						if (mti_old == -1) {
							mti_old = this->mti.load();
							continue; // spin
						}
						if (mti_old == N) {
							if (!this->mti.compare_exchange_weak(mti_old, -1)) {
								continue;
							}
							// enter critical section
							this->twist(); /* generate N words at one time */
							this->mti.store(1);
							// exit critical section
						} else {
							if (!this->mti.compare_exchange_weak(mti_old, mti_old + 1)) {
								continue;
							}
						}
						return;
					}
				}

				void sync_discard(unsigned long long times) KERBAL_NOEXCEPT
				{
					std::size_t mti_old = this->mti.load();
					while (true) {
						if (mti_old == -1) {
							mti_old = this->mti.load();
							continue; // spin
						}
						if (!this->mti.compare_exchange_weak(mti_old, -1)) {
							continue;
						}
						// enter critical section
						unsigned long long twist_times = times / N;
						unsigned long long remain = times % N;
						std::size_t left = N - mti_old;
						bool flag = remain > left;
						twist_times += flag;
						while (twist_times) {
							--twist_times;
							this->twist();
						}
						this->mti.store(flag ? (remain - left) : (mti_old + remain));
						// exit critical section
						return;
					}
				}

				KERBAL_CONSTEXPR
				static result_type min() KERBAL_NOEXCEPT
				{
					return 0u;
				}

				KERBAL_CONSTEXPR
				static result_type max() KERBAL_NOEXCEPT
				{
					return _1_shift_W_minus_1::value;
				}

		};


//		template <
//				typename UIntType,
//				std::size_t W, std::size_t N, std::size_t M, std::size_t R,
//				UIntType A, std::size_t U, UIntType D, std::size_t S,
//				UIntType B, std::size_t T,
//				UIntType C, std::size_t L, UIntType F
//		>
//		class sync_mersenne_twister_engine;

		typedef kerbal::random::sync_mersenne_twister_engine<kerbal::compatibility::uint32_t, 32, 624, 397, 31,
				0x9908b0dfUL, 11, 0xffffffffUL, 7,
				0x9d2c5680UL, 15,
				0xefc60000UL, 18, 1812433253UL> sync_mt19937;

		typedef kerbal::random::sync_mersenne_twister_engine<kerbal::compatibility::uint64_t, 64, 312, 156, 31,
				0xb5026f5aa96619e9ULL, 29, 0x5555555555555555ULL, 17,
				0x71d67fffeda60000ULL, 37,
				0xfff7eee000000000ULL, 43, 6364136223846793005ULL> sync_mt19937_64;


	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_SYNC_MERSENNE_TWISTER_ENGINE_HPP
