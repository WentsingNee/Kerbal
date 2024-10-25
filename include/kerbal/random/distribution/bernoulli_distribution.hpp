/**
 * @file       bernoulli_distribution.hpp
 * @brief
 * @date       2019-11-23
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_DISTRIBUTION_BERNOULLI_DISTRIBUTION_HPP
#define KERBAL_RANDOM_DISTRIBUTION_BERNOULLI_DISTRIBUTION_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>


namespace kerbal
{

	namespace random
	{

		class bernoulli_distribution
		{
			public:
				typedef bool result_type;

			private:
				double probability;

			public:

				KERBAL_CONSTEXPR
				bernoulli_distribution(double probability = 0.5) KERBAL_NOEXCEPT :
					probability(probability)
				{
				}

				template <typename Engine>
				KERBAL_CONSTEXPR14
				result_type operator()(Engine & eg) KERBAL_NOEXCEPT
				{
					return (eg() - eg.min() < this->probability * (eg.max() - eg.min())) ? false : true;
				}

				KERBAL_CONSTEXPR
				result_type min() const KERBAL_NOEXCEPT
				{
					return false;
				}

				KERBAL_CONSTEXPR
				result_type max() const KERBAL_NOEXCEPT
				{
					return true;
				}

		};

	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_DISTRIBUTION_BERNOULLI_DISTRIBUTION_HPP
