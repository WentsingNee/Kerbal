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

#include <kerbal/algorithm/modifier/copy.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/numeric/numeric_limits.hpp>
#include <kerbal/random/discard_block_engine.hpp>
#include <kerbal/random/linear_congruential_engine.hpp>
#include <kerbal/smath/add_mod_sm.hpp>
#include <kerbal/smath/multiply_mod_sa_b_sm.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_same.hpp>
#include <kerbal/type_traits/size_compressed_type.hpp>

#include <cstddef>


#define WAY 1


namespace kerbal
{

	namespace random
	{

		namespace detail
		{

			template <typename ResultType, std::size_t N, ResultType k, ResultType m>
			struct subtract_with_carry_engine_factor
			{
				typedef typename subtract_with_carry_engine_factor<ResultType, N - 1, k, m>::type last;
				typedef kerbal::type_traits::integral_constant<
					ResultType,
					kerbal::smath::multiply_mod_sa_b_sm<ResultType, k, m>::cacl(last::value)
				> type;
			};

			template <typename ResultType, ResultType k, ResultType m>
			struct subtract_with_carry_engine_factor<ResultType, 0, k, m>
			{
				typedef kerbal::type_traits::integral_constant<ResultType, 1> type;
			};

		} // namespace detail

		template <typename UIntType, std::size_t W, std::size_t S, std::size_t R>
		class subtract_with_carry_engine
		{
			private:
				KERBAL_STATIC_ASSERT((
					kerbal::type_traits::is_same<UIntType, unsigned short>::value ||
					kerbal::type_traits::is_same<UIntType, unsigned int>::value ||
					kerbal::type_traits::is_same<UIntType, unsigned long>::value ||
					kerbal::type_traits::is_same<UIntType, unsigned long long>::value),
					"The result type generated should be one of: unsigned short, unsigned int, unsigned long, or unsigned long long"
				);

				KERBAL_STATIC_ASSERT(
					10 < W && W <= kerbal::numeric::numeric_limits<UIntType>::DIGITS::value,
					"W should match the requirement: 10 < W <= kerbal::numeric::numeric_limits<UIntType>::DIGITS::value"
				);

				KERBAL_STATIC_ASSERT(
					0 < S && S < R,
					"S and R should match the requirement: 0 < S < R"
				);

			public:
				typedef UIntType result_type;

				// parameter values
				typedef kerbal::type_traits::integral_constant<std::size_t, W> WORD_SIZE;
				typedef kerbal::type_traits::integral_constant<std::size_t, S> SHORT_LAG;
				typedef kerbal::type_traits::integral_constant<std::size_t, R> LONG_LAG;
				typedef kerbal::type_traits::integral_constant<result_type, 19780503u> DEFAULT_SEED;

			private:
				typedef kerbal::type_traits::integral_constant<result_type, 1ull << W> m;
				typedef typename kerbal::type_traits::size_compressed_type<LONG_LAG::value>::type	index_type;

			private:
				result_type k_state[LONG_LAG::value];
				index_type k_index;
				unsigned char k_carry;

			public:
				KERBAL_CONSTEXPR14
				explicit
				subtract_with_carry_engine(result_type seed = DEFAULT_SEED::value) KERBAL_NOEXCEPT
#		if __cplusplus >= 201402L
						: k_state{}, k_index(0), k_carry(false)
#		endif
				{
					this->seed(seed);
				}

			private:

				typedef kerbal::random::linear_congruential_engine<result_type, 40014u, 0u, 2147483563u> LCG;

				template <result_type K, std::size_t I>
				KERBAL_CONSTEXPR14
				static
				typename kerbal::type_traits::enable_if<I == 0, result_type>::type
				expand(LCG & lcg)
				{
					return lcg() % m::value;
				}

				template <result_type K, std::size_t I>
				KERBAL_CONSTEXPR14
				static
				typename kerbal::type_traits::enable_if<I != 0, result_type>::type
				expand(LCG & lcg)
				{
					typedef typename detail::subtract_with_carry_engine_factor<result_type, I, K, m::value>::type factor;
					result_type lhs = expand<K, I - 1>(lcg);
					result_type rhs = kerbal::smath::multiply_mod_sa_b_sm<result_type, factor::value, m::value>::cacl(lcg());
					return kerbal::smath::add_mod_sm<result_type, m::value>::cacl(lhs, rhs);
				}

				KERBAL_CONSTEXPR14
				void seed(const result_type & seed = DEFAULT_SEED::value) KERBAL_NOEXCEPT
				{
					LCG lcg(seed == 0u ? DEFAULT_SEED::value : seed);

					typedef kerbal::type_traits::integral_constant<std::size_t, (WORD_SIZE::value + 31) / 32> N;

					for (std::size_t i = 0; i < LONG_LAG::value; ++i) {
						// result_type sum = lcg() % m::value;
						// result_type factor = 1u;
						// for (std::size_t j = 1; j < N::value; ++j) {
						// 	factor = detail::static_mul_mod<result_type, (1ull << 32) % m::value, m::value>::cacl(factor);
						// 	sum = detail::add_mod<result_type, m::value>::cacl(
						// 		sum,
						// 		detail::partial_static_mul_mod<result_type, m::value>::cacl(lcg(), factor)
						// 	);
						// }
						// k_state[i] = sum;
						k_state[i] = expand<(1ull << 32) % m::value, N::value - 1>(lcg);
					}
					k_carry = (k_state[LONG_LAG::value - 1] == 0) ? 1 : 0;
					k_index = 0;
#	if WAY == 1
					this->twist();
#	endif
				}

				KERBAL_CONSTEXPR14
				void twist() KERBAL_NOEXCEPT
				{
					std::size_t i = 0;
					for (; i < S; ++i) {
						result_type x_s = k_state[i + R - S]; // k_state[(i - S) % R]
						result_type x_r = k_state[i];
						result_type y = x_s - x_r - k_carry;
						result_type r = y % m::value;
						k_state[i] = r;
						k_carry = x_s < (x_r + k_carry);
					}
					for (; i < LONG_LAG::value; ++i) {
						result_type x_s = k_state[i - S]; // k_state[(i - S) % R]
						result_type x_r = k_state[i];
						result_type y = x_s - x_r - k_carry;
						result_type r = y % m::value;
						k_state[i] = r;
						k_carry = x_s < (x_r + k_carry);
					}
				}


#	if WAY == 0

			public:
				KERBAL_CONSTEXPR14
				result_type operator()() KERBAL_NOEXCEPT
				{
					result_type x_s = k_state[k_index >= S ? k_index - S : k_index + R - S]; // k_state[(k_index - S) % R]
					result_type x_r = k_state[k_index];
					result_type y = x_s - x_r - k_carry;
					result_type r = y % m::value;
					k_state[k_index] = r;
					++k_index;
					if (k_index == LONG_LAG::value) {
						k_index = 0;
					}
					k_carry = x_s < (x_r + k_carry);
					return r;
				}

#	else

			public:
				KERBAL_CONSTEXPR14
				result_type operator()() KERBAL_NOEXCEPT
				{
					if (this->k_index == LONG_LAG::value) {
						this->twist();
						this->k_index = 0;
					}
					result_type r = this->k_state[this->k_index++];
					return r;
				}

#	endif

				KERBAL_CONSTEXPR14
				void discard(unsigned long long n) KERBAL_NOEXCEPT
				{
					while (n != 0) {
						--n;
						(*this)();
					}
				}

				template <typename OutputIterator>
				KERBAL_CONSTEXPR14
				void generate(OutputIterator first, OutputIterator last)
				{
					while (first != last) {
						*first = (*this)();
						++first;
					}
				}

			private:

				template <typename OutputIterator>
				KERBAL_CONSTEXPR14
				OutputIterator k_generate_n_helper(OutputIterator first, typename kerbal::iterator::iterator_traits<OutputIterator>::difference_type n)
				{
					first = kerbal::algorithm::copy(this->k_state + this->k_index, this->k_state + this->k_index + n, first);
					this->k_index += n;
					return first;
				}

			public:

				template <typename OutputIterator>
				KERBAL_CONSTEXPR14
				OutputIterator generate_n(OutputIterator first, typename kerbal::iterator::iterator_traits<OutputIterator>::difference_type n)
				{
					std::size_t this_round_remain = LONG_LAG::value - this->k_index;
					if (static_cast<std::size_t>(n) <= this_round_remain) {
						return this->k_generate_n_helper(first, n);
					}
					first = this->k_generate_n_helper(first, this_round_remain);
					n -= this_round_remain;
					this->twist();
					this->k_index = 0;

					for (std::size_t round = 0; round < n / LONG_LAG::value; ++round) {
						first = this->k_generate_n_helper(first, LONG_LAG::value);
						this->twist();
						this->k_index = 0;
					}
					n %= LONG_LAG::value;
					return this->k_generate_n_helper(first, n);
				}

				KERBAL_CONSTEXPR
				static result_type min() KERBAL_NOEXCEPT
				{
					return 0;
				}

				KERBAL_CONSTEXPR
				static result_type max() KERBAL_NOEXCEPT
				{
					return m::value - 1u;
				}

		};

		typedef kerbal::random::subtract_with_carry_engine<kerbal::compatibility::uint32_t, 24, 10, 24> ranlux24_base;
		typedef kerbal::random::subtract_with_carry_engine<kerbal::compatibility::uint64_t, 48, 5, 12> ranlux48_base;

		typedef kerbal::random::discard_block_engine<kerbal::random::ranlux24_base, 223, 23> ranlux24;
		typedef kerbal::random::discard_block_engine<kerbal::random::ranlux48_base, 389, 11> ranlux48;

	} // namespace random

} // namespace kerbal


#endif // KERBAL_RANDOM_SUBTRACT_WITH_CARRY_ENGINE_HPP
