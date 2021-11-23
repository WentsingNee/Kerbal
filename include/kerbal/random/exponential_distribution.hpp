/**
 * @file       exponential_distribution.hpp
 * @brief
 * @date       2019-11-23
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_EXPONENTIAL_DISTRIBUTION_HPP
#define KERBAL_RANDOM_EXPONENTIAL_DISTRIBUTION_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/random/uniform_real_distribution.hpp>

#include <cmath>
#include <limits>


namespace kerbal
{

	namespace random
	{

		template <typename RealType = double>
		class exponential_distribution
		{
			public:
				typedef RealType result_type;

			private:
				RealType lambda;

			public:

				KERBAL_CONSTEXPR exponential_distribution(RealType lambda = 1.0) KERBAL_NOEXCEPT :
						lambda(lambda)
				{
				}

				template <typename Engine>
				result_type operator()(Engine & eg) KERBAL_NOEXCEPT
				{
					kerbal::random::uniform_real_distribution<result_type> dis;
					return -std::log(result_type(1) - dis(eg)) / this->lambda;
				}

				KERBAL_CONSTEXPR result_type min() const KERBAL_NOEXCEPT
				{
					return 0;
				}

				KERBAL_CONSTEXPR result_type max() const KERBAL_NOEXCEPT
				{
					return std::numeric_limits<result_type>::max();
				}

		};

	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_EXPONENTIAL_DISTRIBUTION_HPP
