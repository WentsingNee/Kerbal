/**
 * @file       rand48.hpp
 * @brief
 * @date       2021-11-07
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_RAND48_HPP
#define KERBAL_RANDOM_RAND48_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/random/linear_congruential_engine.hpp>
#include <kerbal/type_traits/is_nothrow_constructible.hpp>
#include <kerbal/utility/declval.hpp>


namespace kerbal
{

	namespace random
	{

		class rand48
		{
			private:
				typedef kerbal::compatibility::uint64_t uint64_t;
				typedef kerbal::random::linear_congruential_engine<uint64_t, 0x5deece66d, 0xb, 1ull << 48> rand48_base;

			public:
				typedef kerbal::compatibility::uint32_t result_type;

				rand48_base k_base_eg;

			public:

				KERBAL_CONSTEXPR
				rand48()
						KERBAL_CONDITIONAL_NOEXCEPT((
							kerbal::type_traits::is_nothrow_constructible<rand48_base, result_type>::value
						)) :
						k_base_eg((1 << 16) | 0x330e)
				{
				}

				KERBAL_CONSTEXPR
				explicit rand48(result_type seed)
						KERBAL_CONDITIONAL_NOEXCEPT((
							kerbal::type_traits::is_nothrow_constructible<rand48_base, result_type>::value
						)) :
						k_base_eg((seed << 16) | 0x330e)
				{
				}

				KERBAL_CONSTEXPR14
				void seed(result_type seed)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(k_base_eg.seed(seed))
						)
				{
					k_base_eg.seed((seed << 16) | 0x330e);
				}

				KERBAL_CONSTEXPR14
				result_type operator()()
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(k_base_eg())
						)
				{
					return static_cast<result_type>(k_base_eg() >> 17);
				}

				KERBAL_CONSTEXPR14
				void discard(unsigned long long times)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(k_base_eg.discard(times))
						)
				{
					k_base_eg.discard(times);
				}

				KERBAL_CONSTEXPR
				static result_type min() KERBAL_NOEXCEPT
				{
					return 0u;
				}

				KERBAL_CONSTEXPR
				static result_type max() KERBAL_NOEXCEPT
				{
					return (1ull << 31) - 1;
				}

				KERBAL_CONSTEXPR
				bool operator==(const rand48 & rhs) const
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::utility::declval<rand48_base>() == kerbal::utility::declval<rand48_base>())
						)
				{
					return this->k_base_eg == rhs.k_base_eg;
				}

				KERBAL_CONSTEXPR
				bool operator!=(const rand48 & rhs) const
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::utility::declval<rand48_base>() != kerbal::utility::declval<rand48_base>())
						)
				{
					return this->k_base_eg != rhs.k_base_eg;
				}

		};

	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_RAND48_HPP
