/**
 * @file       poisson_distribution.hpp
 * @brief
 * @date       2020-6-9
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_POISSON_DISTRIBUTION_HPP
#define KERBAL_RANDOM_POISSON_DISTRIBUTION_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/random/uniform_real_distribution.hpp>
#include <kerbal/type_traits/is_integral.hpp>
#include <kerbal/utility/declval.hpp>

#include <cmath>
#include <limits>

namespace kerbal
{

	namespace random
	{

		template <typename IntType = int>
		class poisson_distribution
		{
				KERBAL_STATIC_ASSERT(kerbal::type_traits::is_integral<IntType>::value, "IntType must be an integral type");

			public:
				typedef IntType result_type;

			private:
				double _mean;

			public:
				KERBAL_CONSTEXPR
				poisson_distribution() KERBAL_NOEXCEPT
						: _mean(1.0)
				{
				}

				KERBAL_CONSTEXPR
				explicit
				poisson_distribution(double mean) KERBAL_NOEXCEPT
						: _mean(mean)
				{
				}

				KERBAL_CONSTEXPR
				double mean() const KERBAL_NOEXCEPT
				{
					return this->_mean;
				}

				template <typename Engine>
				result_type operator()(Engine & eg) const
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::utility::declval<kerbal::random::uniform_real_distribution<double> >()(eg))
						)
				{
					kerbal::random::uniform_real_distribution<double> urdis(0, ::exp(this->_mean));
					double s = urdis(eg);
					for (result_type i = 1; i < std::numeric_limits<result_type>::max(); ++i) {
						if (s < i) {
							return i - 1;
						}
						s -= i;
						s *= i + 1;
						s /= this->_mean;
					}
					return std::numeric_limits<result_type>::max();
				}

				KERBAL_CONSTEXPR
				result_type min() const KERBAL_NOEXCEPT
				{
					return 0;
				}

				KERBAL_CONSTEXPR
				result_type max() const KERBAL_NOEXCEPT
				{
					return std::numeric_limits<result_type>::max();
				}

				KERBAL_CONSTEXPR
				friend
				bool operator==(const poisson_distribution& lhs, const poisson_distribution& rhs) KERBAL_NOEXCEPT
				{
					return lhs._mean == rhs._mean;
				}

				KERBAL_CONSTEXPR
				friend
				bool operator!=(const poisson_distribution& lhs, const poisson_distribution& rhs) KERBAL_NOEXCEPT
				{
					return lhs._mean != rhs._mean;
				}

		};

	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_POISSON_DISTRIBUTION_HPP
