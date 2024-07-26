/**
 * @file       uniform_real_distribution.hpp
 * @brief
 * @date       2019-12-01
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_DISTRIBUTION_UNIFORM_REAL_DISTRIBUTION_HPP
#define KERBAL_RANDOM_DISTRIBUTION_UNIFORM_REAL_DISTRIBUTION_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>


namespace kerbal
{

	namespace random
	{

		KERBAL_MODULE_EXPORT
		template <typename ResultType = double>
		class uniform_real_distribution
		{
			public:
				typedef ResultType result_type;

			private:
				result_type a;
				result_type b;

			public:
				KERBAL_CONSTEXPR
				uniform_real_distribution() KERBAL_NOEXCEPT :
					a(0.0), b(1.0)
				{
				}

				KERBAL_CONSTEXPR
				uniform_real_distribution(const result_type & a, const result_type & b) KERBAL_NOEXCEPT :
					a(a), b(b)
				{
				}

				template <typename Engine>
				KERBAL_CONSTEXPR
				result_type operator()(Engine & eg) const
				{
					return static_cast<result_type>(eg()) / (eg.max() - eg.min())
							* (b - a) + a;
				}

				KERBAL_CONSTEXPR
				result_type min() const KERBAL_NOEXCEPT
				{
					return this->a;
				}

				KERBAL_CONSTEXPR
				result_type max() const KERBAL_NOEXCEPT
				{
					return this->b;
				}

		};

	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_DISTRIBUTION_UNIFORM_REAL_DISTRIBUTION_HPP
