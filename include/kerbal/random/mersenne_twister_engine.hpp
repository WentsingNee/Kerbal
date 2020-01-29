/**
 * @file       mersenne_twister_engine.hpp
 * @brief
 * @date       2019-11-23
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_MERSENNE_TWISTER_ENGINE_HPP_
#define KERBAL_RANDOM_MERSENNE_TWISTER_ENGINE_HPP_

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/type_traits_details/integral_constant.hpp>

#include <cstddef>

namespace kerbal
{
	namespace random
	{

		template <
				typename UIntType,
				size_t W, size_t N, size_t M, size_t R,
				UIntType A, size_t U, UIntType D, size_t S,
				UIntType B, size_t T,
				UIntType C, size_t L, UIntType F
		>
		class mersenne_twister_engine
		{
			public:
				typedef UIntType result_type;

				typedef kerbal::type_traits::integral_constant<size_t, W> WORD_SIZE;
				typedef kerbal::type_traits::integral_constant<size_t, N> STATE_SIZE;
				typedef kerbal::type_traits::integral_constant<size_t, M> SHIFT_SIZE;
				typedef kerbal::type_traits::integral_constant<size_t, R> MASK_BITS;

				typedef kerbal::type_traits::integral_constant<UIntType, A> XOR_MASK;
				typedef kerbal::type_traits::integral_constant<size_t, U> TEMPERING_U;
				typedef kerbal::type_traits::integral_constant<UIntType, D> TEMPERING_D;
				typedef kerbal::type_traits::integral_constant<size_t, S> TEMPERING_S;

				typedef kerbal::type_traits::integral_constant<UIntType, B> TEMPERING_B;
				typedef kerbal::type_traits::integral_constant<size_t, T> TEMPERING_T;

				typedef kerbal::type_traits::integral_constant<UIntType, C> TEMPERING_C;
				typedef kerbal::type_traits::integral_constant<size_t, L> TEMPERING_L;
				typedef kerbal::type_traits::integral_constant<UIntType, F> INITIALIZATION_MULTIPLIER;

				typedef kerbal::type_traits::integral_constant<UIntType, 5489u> DEFAULT_SEED;

			private:
				UIntType mt[N];
				size_t mti;

				KERBAL_CONSTEXPR14
				void twist() KERBAL_NOEXCEPT
				{
					const UIntType UPPER_MASK = (~UIntType()) << R; // most significant w-r bits
					const UIntType LOWER_MASK = ~UPPER_MASK; // least significant r bits

					const UIntType mag01[2] = {0x0UL, A};

					size_t i = 0;

					for (i = 0; i < N - M; ++i) {
						result_type y = (this->mt[i] & UPPER_MASK) | (this->mt[i + 1] & LOWER_MASK);
						this->mt[i] = this->mt[i + M] ^ (y >> 1) ^ mag01[y & 0x1UL];
					}
					for (; i < N - 1; ++i) {
						result_type y = (this->mt[i] & UPPER_MASK) | (this->mt[i + 1] & LOWER_MASK);
						this->mt[i] = this->mt[i + (M - N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
					}
					result_type y = (this->mt[N - 1] & UPPER_MASK) | (this->mt[0] & LOWER_MASK);
					this->mt[N - 1] = this->mt[M - 1] ^ (y >> 1) ^ mag01[y & 0x1UL];

					this->mti = 0;
				}


			public:
				KERBAL_CONSTEXPR14
				explicit mersenne_twister_engine(const result_type& seed = DEFAULT_SEED::value) KERBAL_NOEXCEPT
							 : mti(N)
				{
					this->mt[0] = seed;
					for (size_t i = 1; i < N; ++i) {
						UIntType x = this->mt[i - 1];
						x ^= x >> (W - 2);
						x *= F;
						x += i;
						this->mt[i] = x;
					}
				}

				KERBAL_CONSTEXPR14
				result_type operator()() KERBAL_NOEXCEPT
				{
					if (this->mti == N) {
						this->twist(); /* generate N words at one time */
					}
					result_type y = this->mt[this->mti++];
					y ^= (y >> U) & D;
					y ^= (y << S) & B;
					y ^= (y << T) & C;
					y ^= y >> L;
					return y;
				}

				KERBAL_CONSTEXPR14
				void discard() KERBAL_NOEXCEPT
				{
					if (this->mti == N) {
						this->twist(); /* generate N words at one time */
					}
					this->mti++;
				}

				KERBAL_CONSTEXPR14
				void discard(unsigned long long z) KERBAL_NOEXCEPT
				{
					for (unsigned long long i = 0; i < z; ++i) {
						if (this->mti == N) {
							this->twist(); /* generate N words at one time */
						}
						this->mti++;
					}
				}

				static KERBAL_CONSTEXPR result_type min() KERBAL_NOEXCEPT
				{
					return 0;
				}

				static KERBAL_CONSTEXPR result_type max() KERBAL_NOEXCEPT
				{
					return UIntType(UIntType(1) << W) - 1;
				}
		};


		typedef kerbal::random::mersenne_twister_engine<unsigned int, 32, 624, 397, 31,
				0x9908b0dfUL, 11, 0xffffffffUL, 7,
				0x9d2c5680UL, 15,
				0xefc60000UL, 18, 1812433253UL> mt19937;

		typedef kerbal::random::mersenne_twister_engine<unsigned long long, 64, 312, 156, 31,
				0xb5026f5aa96619e9ULL, 29, 0x5555555555555555ULL, 17,
				0x71d67fffeda60000ULL, 37,
				0xfff7eee000000000ULL, 43, 6364136223846793005ULL> mt19937_64;


	} // namespace random

} // namespace kerbal

#endif	/* KERBAL_RANDOM_MERSENNE_TWISTER_ENGINE_HPP_ */
