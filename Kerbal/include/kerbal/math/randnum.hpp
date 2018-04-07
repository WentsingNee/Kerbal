#ifndef _RANDNUM_HPP_
#define _RANDNUM_HPP_

#include <utility>
#include <kerbal/utility/real_functor.hpp>
#include <time.h>

namespace kerbal
{
	namespace math
	{
		namespace randnum
		{

			unsigned int seed();
//			time_t seed();

			double _0_1_rand();

			std::pair<double, double> std_normdist_rand_pair();

			double std_normdist_rand();

			inline double rand_between(double min, double max)
			{
				return (max - min) * _0_1_rand() + min;
			}

			template <typename type = double>
			struct rand_type_between: public kerbal::utility::Functor<type>
			{
					rand_type_between(const type & min, const type & max)
					{
						do {
							kerbal::utility::Functor<type>::value = (type) rand_between(min, max);
						} while (kerbal::utility::Functor<type>::value == max);
					}
			};

			template <>
			struct rand_type_between<double> : public kerbal::utility::Functor<double>
			{
					rand_type_between(double min, double max) :
							init(rand_between(min, max))
					{
					}
			};

			inline bool rand_true(double probability)
			{
				return _0_1_rand() <= probability ? true : false;
			}

			inline std::pair<double, double> normdist_rand_pair(double sigma = 1, double miu = 0)
			{
				std::pair<double, double> std_rand_pair(std_normdist_rand_pair());
				std_rand_pair.first = std_rand_pair.first * sigma + miu;
				std_rand_pair.second = std_rand_pair.second * sigma + miu;
				return std_rand_pair;
			}

			inline double normdist_rand(double sigma = 1, double miu = 0) //miu=ave,sigma=expect
			{
				return std_normdist_rand() * sigma + miu;
			}

		} /* end namesapce randnum */

	} /* end namesapce math */

} /* end namesapce kerbal */

#endif	/* End _RANDNUM_HPP_ */
