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

#ifndef KERBAL_RANDOM_MERSENNE_TWISTER_ENGINE_HPP
#define KERBAL_RANDOM_MERSENNE_TWISTER_ENGINE_HPP

#include <kerbal/algorithm/sequence_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/nonmember_container_access.hpp>
#include <kerbal/numeric/bit.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

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
					typedef kerbal::type_traits::integral_constant<UIntType, (~UIntType()) << R> UPPER_MASK; // most significant w-r bits
					typedef kerbal::type_traits::integral_constant<UIntType, ~UPPER_MASK::value> LOWER_MASK; // least significant r bits

					const UIntType mag01[2] = {0x0UL, A};

					size_t i = 0;

					for (i = 0; i < N - M; ++i) {
						result_type y = (this->mt[i] & UPPER_MASK::value) | (this->mt[i + 1] & LOWER_MASK::value);
						this->mt[i] = this->mt[i + M] ^ (y >> 1) ^ mag01[y & 0x1UL];
					}
					for (; i < N - 1; ++i) {
						result_type y = (this->mt[i] & UPPER_MASK::value) | (this->mt[i + 1] & LOWER_MASK::value);
						this->mt[i] = this->mt[i + (M - N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
					}
					result_type y = (this->mt[N - 1] & UPPER_MASK::value) | (this->mt[0] & LOWER_MASK::value);
					this->mt[N - 1] = this->mt[M - 1] ^ (y >> 1) ^ mag01[y & 0x1UL];
				}


			private:
				KERBAL_CONSTEXPR14
				void init_mt()
				{
					for (size_t i = 1; i < N; ++i) {
						UIntType x = this->mt[i - 1];
						x ^= x >> (W - 2);
						x *= F;
						x += i;
						this->mt[i] = x;
					}
				}

			public:

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				explicit mersenne_twister_engine(result_type seed = DEFAULT_SEED::value) KERBAL_NOEXCEPT
						: mt{seed}, mti(N)
				{
					this->init_mt();
				}

#		else

				explicit mersenne_twister_engine(result_type seed = DEFAULT_SEED::value) KERBAL_NOEXCEPT
						: mti(N)
				{
					this->mt[0] = seed;
					this->init_mt();
				}

#		endif

				KERBAL_CONSTEXPR14
				void seed(result_type seed = DEFAULT_SEED::value) KERBAL_NOEXCEPT
				{
					this->mt[0] = seed;
					this->mti = N;
					this->init_mt();
				}

				KERBAL_CONSTEXPR14
				result_type operator()() KERBAL_NOEXCEPT
				{
					if (this->mti == N) {
						this->twist(); /* generate N words at one time */
						this->mti = 0;
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
						this->twist();
						this->mti = 0;
					}
					this->mti++;
				}

				KERBAL_CONSTEXPR14
				void discard(unsigned long long z) KERBAL_NOEXCEPT
				{
					for (unsigned long long i = 0; i < z / N; ++i) {
						this->twist();
					}
					unsigned long long i = z % N;
					size_t left = N - this->mti;
					if (i <= left) {
						this->mti += i;
					} else {
						this->twist();
						this->mti = i - left;
					}
				}

				static KERBAL_CONSTEXPR result_type min() KERBAL_NOEXCEPT
				{
					return 0;
				}

				static KERBAL_CONSTEXPR result_type max() KERBAL_NOEXCEPT
				{
					return kerbal::numeric::mask<result_type>(W);
				}

				KERBAL_CONSTEXPR14
				bool operator==(const mersenne_twister_engine & rhs) const
				{
					return this->mti == rhs.mti && static_cast<bool>(
								kerbal::algorithm::sequence_equal_to(
									kerbal::container::cbegin(this->mt),
									kerbal::container::cend(this->mt),
									kerbal::container::cbegin(rhs.mt),
									kerbal::container::cend(rhs.mt)
							));
				}

				KERBAL_CONSTEXPR14
				bool operator!=(const mersenne_twister_engine & rhs) const
				{
					return this->mti != rhs.mti || static_cast<bool>(
								kerbal::algorithm::sequence_not_equal_to(
									kerbal::container::cbegin(this->mt),
									kerbal::container::cend(this->mt),
									kerbal::container::cbegin(rhs.mt),
									kerbal::container::cend(rhs.mt)
							));
				}

		};


		typedef kerbal::random::mersenne_twister_engine<kerbal::compatibility::uint32_t, 32, 624, 397, 31,
				0x9908b0dfUL, 11, 0xffffffffUL, 7,
				0x9d2c5680UL, 15,
				0xefc60000UL, 18, 1812433253UL> mt19937;

		typedef kerbal::random::mersenne_twister_engine<kerbal::compatibility::uint64_t, 64, 312, 156, 31,
				0xb5026f5aa96619e9ULL, 29, 0x5555555555555555ULL, 17,
				0x71d67fffeda60000ULL, 37,
				0xfff7eee000000000ULL, 43, 6364136223846793005ULL> mt19937_64;


	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_MERSENNE_TWISTER_ENGINE_HPP
