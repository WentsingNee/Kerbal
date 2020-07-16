/**
 * @file       binomial_distribution.hpp
 * @brief
 * @date       2020-6-16
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_BINOMIAL_DISTRIBUTION_HPP
#define KERBAL_RANDOM_BINOMIAL_DISTRIBUTION_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/random/uniform_real_distribution.hpp>
#include <kerbal/type_traits/fundamental_deduction.hpp>
#include <kerbal/utility/declval.hpp>

#include <cmath>
#include <limits>

namespace kerbal
{

	namespace random
	{

		template <typename IntType = int>
		class binomial_distribution
		{
				KERBAL_STATIC_ASSERT(kerbal::type_traits::is_integral<IntType>::value, "IntType must be an integral type");

			public:
				typedef IntType result_type;

			private:
				result_type _n;
				double _p;

			public:

				// 0 < _p < 1
				KERBAL_CONSTEXPR
				explicit
				binomial_distribution(result_type n, double p = 0.5) KERBAL_NOEXCEPT
						: _n(n), _p(p)
				{
				}

				KERBAL_CONSTEXPR
				double n() const KERBAL_NOEXCEPT
				{
					return this->_n;
				}

				KERBAL_CONSTEXPR
				double p() const KERBAL_NOEXCEPT
				{
					return this->_p;
				}

				template <typename Engine>
				result_type operator()(Engine & eg) const
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::utility::declval<kerbal::random::uniform_real_distribution<double> >()(eg))
						)
				{
					kerbal::random::uniform_real_distribution<double> urdis(0, 1.0);
					double s = urdis(eg);
					double one_m_p = 1 - this->_p;
					double a = ::pow(one_m_p, this->_n);
					for (result_type i = 0; i < this->_n; ++i) {
						if (s < a) {
							return i;
						}
						s -= a;
						s /= this->_n - i;
						s *= i + 1;
						s /= this->_p;
						a /= one_m_p;
					}
					return this->_n;
				}

				KERBAL_CONSTEXPR
				result_type min() const KERBAL_NOEXCEPT
				{
					return 0;
				}

				KERBAL_CONSTEXPR
				result_type max() const KERBAL_NOEXCEPT
				{
					return this->_n;
				}

				KERBAL_CONSTEXPR
				friend
				bool operator==(const binomial_distribution& lhs, const binomial_distribution& rhs) KERBAL_NOEXCEPT
				{
					return lhs._n == rhs._n && lhs._p == rhs._p;
				}

				KERBAL_CONSTEXPR
				friend
				bool operator!=(const binomial_distribution& lhs, const binomial_distribution& rhs) KERBAL_NOEXCEPT
				{
					return lhs._n != rhs._n || lhs._p != rhs._p;
				}

		};

	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_BINOMIAL_DISTRIBUTION_HPP
