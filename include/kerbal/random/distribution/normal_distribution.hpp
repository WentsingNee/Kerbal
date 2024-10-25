/**
 * @file       normal_distribution.hpp
 * @brief
 * @date       2019-12-01
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_DISTRIBUTION_NORMAL_DISTRIBUTION_HPP
#define KERBAL_RANDOM_DISTRIBUTION_NORMAL_DISTRIBUTION_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/random/distribution/uniform_real_distribution.hpp>

#include <cmath>
#include <limits>

namespace kerbal
{

	namespace random
	{

		template <typename ResultType = double>
		class normal_distribution
		{
			public:
				typedef ResultType result_type;

			private:
				result_type mean;
				result_type stddev;

				template <typename Engine>
				static double std_normal_distribution(Engine & eg) KERBAL_NOEXCEPT
				{
					KERBAL_CONSTEXPR const double M_2PI = 6.283185307179586476925286766559;
					kerbal::random::uniform_real_distribution<result_type> real_distribution(0.0, 1.0);
					result_type u(real_distribution(eg)), v(real_distribution(eg));
					return std::sqrt(-2 * std::log(1.0 - u)) * std::sin(M_2PI * v); // sq(-2 log(u)) * sin(2 pi v)
				}

			public:
				KERBAL_CONSTEXPR
				normal_distribution() KERBAL_NOEXCEPT :
					mean(0.0), stddev(1.0)
				{
				}

				KERBAL_CONSTEXPR
				explicit
				normal_distribution(const result_type & mean, const result_type & stddev = 1.0) KERBAL_NOEXCEPT :
					mean(mean), stddev(stddev)
				{
				}

				template <typename Engine>
				result_type operator()(Engine & eg) const
				{
					return std_normal_distribution(eg) * stddev + mean;
				}

				KERBAL_CONSTEXPR
				result_type min() const KERBAL_NOEXCEPT
				{
					return std::numeric_limits<result_type>::min();
				}

				KERBAL_CONSTEXPR
				result_type max() const KERBAL_NOEXCEPT
				{
					return std::numeric_limits<result_type>::max();
				}

		};

	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_DISTRIBUTION_NORMAL_DISTRIBUTION_HPP
