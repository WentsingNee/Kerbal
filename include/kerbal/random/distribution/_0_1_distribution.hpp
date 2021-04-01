/**
 * @file       _0_1_distribution.hpp
 * @brief
 * @date       2019-12-01
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_DISTRIBUTION__0_1_DISTRIBUTION_HPP
#define KERBAL_RANDOM_DISTRIBUTION__0_1_DISTRIBUTION_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>


namespace kerbal
{

	namespace random
	{

		template <typename ResultType = double, unsigned int Times = 10>
		class _0_1_distribution
		{
			public:
				typedef ResultType result_type;

			public:
				KERBAL_CONSTEXPR
				_0_1_distribution() KERBAL_NOEXCEPT
				{
				}

				template <typename Engine>
				KERBAL_CONSTEXPR14
				result_type operator()(Engine & eg) const
				{
					result_type result = 0.0;
					const result_type per = 1.0 / eg.max();
					result_type weight = per;
					for (unsigned int i = 0; i < Times - 1; ++i) {
						result_type unit = eg();
						while (unit == eg.max()) {
							unit = eg();
						}
						result += unit * weight;
						weight *= per;
					}
					{
						result_type unit = eg();
						while (unit == eg.max()) {
							unit = eg();
						}
						result += unit * weight;
					}
					return result;
				}

				KERBAL_CONSTEXPR
				result_type min() const KERBAL_NOEXCEPT
				{
					return 0;
				}

				KERBAL_CONSTEXPR
				result_type max() const KERBAL_NOEXCEPT
				{
					return 1;
				}

		};

	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_DISTRIBUTION__0_1_DISTRIBUTION_HPP
