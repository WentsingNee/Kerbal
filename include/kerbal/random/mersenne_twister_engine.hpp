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

#include <kerbal/compare/sequence_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/numeric/numeric_limits.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>

#include <kerbal/random/detail/mt_generate_copy_n_helper.hpp>
#include <kerbal/random/detail/mt_twist_helper.hpp>


namespace kerbal
{

	namespace random
	{

		namespace detail
		{

			template <typename UIntType, std::size_t W, bool /* W == digits(UIntType) */>
			struct _1_shift_W_minus_1_helper;

			template <typename UIntType, std::size_t W>
			struct _1_shift_W_minus_1_helper<UIntType, W, true>
			{
					typedef kerbal::type_traits::integral_constant<
							UIntType,
							~static_cast<UIntType>(0u)
					> type;
			};

			template <typename UIntType, std::size_t W>
			struct _1_shift_W_minus_1_helper<UIntType, W, false>
			{
					typedef kerbal::type_traits::integral_constant<
							UIntType,
							(static_cast<UIntType>(1u) << W) - 1u
					> type;
			};

			template <typename UIntType, std::size_t W>
			struct _1_shift_W_minus_1 :
					public _1_shift_W_minus_1_helper<UIntType, W, (W == kerbal::numeric::numeric_limits<UIntType>::DIGITS::value)>::type
			{
			};

		} // namespace detail


		template <
				typename UIntType,
				std::size_t W, std::size_t N, std::size_t M, std::size_t R,
				UIntType A, std::size_t U, UIntType D, std::size_t S,
				UIntType B, std::size_t T,
				UIntType C, std::size_t L, UIntType F
		>
		class mersenne_twister_engine :
				detail::mt_twist_helper<UIntType, N, M, R, A>,
				detail::mt_generate_copy_n_helper<UIntType, U, D, S, B, T, C, L>
		{
			private:
				typedef detail::mt_twist_helper<UIntType, N, M, R, A> mt_twist_helper;
				typedef detail::mt_generate_copy_n_helper<UIntType, U, D, S, B, T, C, L> mt_generate_copy_n_helper;

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
				typedef detail::_1_shift_W_minus_1<UIntType, W> _1_shift_W_minus_1;

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

				typedef kerbal::type_traits::integral_constant<result_type, A>		XOR_MASK;
				typedef kerbal::type_traits::integral_constant<std::size_t, U>		TEMPERING_U;
				typedef kerbal::type_traits::integral_constant<result_type, D>		TEMPERING_D;
				typedef kerbal::type_traits::integral_constant<std::size_t, S>		TEMPERING_S;

				typedef kerbal::type_traits::integral_constant<result_type, B>		TEMPERING_B;
				typedef kerbal::type_traits::integral_constant<std::size_t, T>		TEMPERING_T;

				typedef kerbal::type_traits::integral_constant<result_type, C>		TEMPERING_C;
				typedef kerbal::type_traits::integral_constant<std::size_t, L>		TEMPERING_L;
				typedef kerbal::type_traits::integral_constant<result_type, F>		INITIALIZATION_MULTIPLIER;

				typedef kerbal::type_traits::integral_constant<result_type, 5489u>		DEFAULT_SEED;

			private:
				result_type mt[N];
				std::size_t mti;

				KERBAL_CONSTEXPR14
				void twist() KERBAL_NOEXCEPT
				{
					mt_twist_helper::twist(mt);
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
					this->init_mt();
					this->mti = N;
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
				void discard(unsigned long long times) KERBAL_NOEXCEPT
				{
					unsigned long long twist_times = times / N;
					unsigned long long remain = times % N;
					std::size_t mti_old = this->mti;
					std::size_t left = N - mti_old;
					bool flag = remain > left;
					twist_times += flag;
					while (twist_times != 0) {
						--twist_times;
						this->twist();
					}
					this->mti = (flag ? (remain - left) : (mti_old + remain));
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

			private:

				template <typename OutputIterator>
				KERBAL_CONSTEXPR14
				OutputIterator k_generate_n_helper(OutputIterator first, typename kerbal::iterator::iterator_traits<OutputIterator>::difference_type n)
				{
					first = mt_generate_copy_n_helper::mt_generate_copy_n(this->mt + this->mti, first, n);
					this->mti += n;
					return first;
				}

			public:

				template <typename OutputIterator>
				KERBAL_CONSTEXPR14
				OutputIterator generate_n(OutputIterator first, typename kerbal::iterator::iterator_traits<OutputIterator>::difference_type n)
				{
					std::size_t this_round_remain = N - this->mti;
					if (static_cast<std::size_t>(n) <= this_round_remain) {
						return this->k_generate_n_helper(first, n);
					}
					first = this->k_generate_n_helper(first, this_round_remain);
					n -= this_round_remain;
					this->twist();
					this->mti = 0;

					for (std::size_t round = 0; round < n / N; ++round) {
						first = this->k_generate_n_helper(first, N);
						this->twist();
						this->mti = 0;
					}
					n %= N;
					return this->k_generate_n_helper(first, n);
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

				KERBAL_CONSTEXPR14
				bool operator==(const mersenne_twister_engine & rhs) const KERBAL_NOEXCEPT
				{
					return this->mti == rhs.mti &&
							static_cast<bool>(kerbal::compare::sequence_equal_to(this->mt, rhs.mt));
				}

				KERBAL_CONSTEXPR14
				bool operator!=(const mersenne_twister_engine & rhs) const KERBAL_NOEXCEPT
				{
					return this->mti != rhs.mti ||
							static_cast<bool>(kerbal::compare::sequence_not_equal_to(this->mt, rhs.mt));
				}

		};


//		template <
//				typename UIntType,
//				std::size_t W, std::size_t N, std::size_t M, std::size_t R,
//				UIntType A, std::size_t U, UIntType D, std::size_t S,
//				UIntType B, std::size_t T,
//				UIntType C, std::size_t L, UIntType F
//		>
//		class mersenne_twister_engine;

		typedef kerbal::random::mersenne_twister_engine<
				kerbal::compatibility::uint32_t,
				32, 624, 397, 31,
				0x9908b0dfUL, 11, 0xffffffffUL, 7,
				0x9d2c5680UL, 15,
				0xefc60000UL, 18, 1812433253UL> mt19937;

		typedef kerbal::random::mersenne_twister_engine<
				kerbal::compatibility::uint64_t,
				64, 312, 156, 31,
				0xb5026f5aa96619e9ULL, 29, 0x5555555555555555ULL, 17,
				0x71d67fffeda60000ULL, 37,
				0xfff7eee000000000ULL, 43, 6364136223846793005ULL> mt19937_64;


	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_MERSENNE_TWISTER_ENGINE_HPP
