/**
 * @file       geometric_distribution.hpp
 * @brief
 * @date       2020-6-16
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_GEOMETRIC_DISTRIBUTION_HPP
#define KERBAL_RANDOM_GEOMETRIC_DISTRIBUTION_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/random/uniform_real_distribution.hpp>
#include <kerbal/type_traits/fundamental_deduction.hpp>
#include <kerbal/utility/declval.hpp>

#include <limits>

namespace kerbal
{

	namespace random
	{

		template <typename IntType = int>
		class geometric_distribution
		{
				KERBAL_STATIC_ASSERT(kerbal::type_traits::is_integral<IntType>::value, "IntType must be an integral type");

			public:
				typedef IntType result_type;

			private:
				double _p;

			public:

				// 0 < _p < 1
				KERBAL_CONSTEXPR
				explicit
				geometric_distribution(double p = 0.5) KERBAL_NOEXCEPT
						: _p(p)
				{
				}

				KERBAL_CONSTEXPR
				double p() const KERBAL_NOEXCEPT
				{
					return this->_p;
				}

				template <typename Engine>
				KERBAL_CONSTEXPR14
				result_type operator()(Engine & eg) const
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::utility::declval<kerbal::random::uniform_real_distribution<double> >()(eg))
						)
				{
					kerbal::random::uniform_real_distribution<double> urdis(0, 1.0 / _p);
					double s = urdis(eg);
					double one_m_p = 1 - this->_p;
					for (result_type i = 0; i < std::numeric_limits<result_type>::max(); ++i) {
						if (s < 1) {
							return i;
						}
						s -= 1;
						s /= one_m_p;
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
				bool operator==(const geometric_distribution& lhs, const geometric_distribution& rhs) KERBAL_NOEXCEPT
				{
					return lhs._p == rhs._p;
				}

				KERBAL_CONSTEXPR
				friend
				bool operator!=(const geometric_distribution& lhs, const geometric_distribution& rhs) KERBAL_NOEXCEPT
				{
					return lhs._p != rhs._p;
				}

		};

	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_GEOMETRIC_DISTRIBUTION_HPP
