#include <kerbal/math/randnum.hpp>

#include <stdlib.h>
#include <math.h>
#include <limits>
#include <time.h>

#include <kerbal/compatibility/tick_count.h>

namespace kerbal
{
	namespace math
	{
		namespace randnum
		{

			unsigned int seed()
			{
				unsigned int k = GetTickCount() % std::numeric_limits<unsigned int>::max();
				srand(k);
				return k;
			}

//			time_t seed()
//			{
//				time_t k = time(NULL);
//				srand(k);
//				return k;
//			}

			namespace
			{

#				define TIMES 10

				double weight[TIMES];
				unsigned int rand_init();
				unsigned int current_seed = rand_init();

				unsigned int rand_init()
				{
					weight[0] = 1.0 / RAND_MAX;
					for (unsigned int i = 0; i < TIMES - 1; ++i) {
						weight[i + 1] = weight[i] / RAND_MAX;
					}
					current_seed = 0;
					return seed();
				}
			}

			double _0_1_rand()
			{
				double result = 0.0;
				for (unsigned int i = 0; i < TIMES; ++i) {
					double unit;
					do {
						unit = rand();
					} while (unit == RAND_MAX);
					result += unit * weight[i];
				}
				return result;
			}

			namespace
			{

#				ifndef CONSTEXPR_CXX
#					if __cplusplus < 201103L
#						define CONSTEXPR_CXX const
#					else
#						define CONSTEXPR_CXX constexpr
#					endif
#				endif

				CONSTEXPR_CXX double M_2PI = 6.283185307179586476925286766559;
			}

			std::pair<double, double> std_normdist_rand_pair()
			{
				double u = _0_1_rand(), v = _0_1_rand();
				double k = sqrt(-2 * log(u));
				double _2pi_v = M_2PI * v;
				double sin_2pi_v, cos_2pi_v;

				sincos(_2pi_v, &sin_2pi_v, &cos_2pi_v);
				return std::pair<double, double>(k * sin_2pi_v, k * cos_2pi_v);
			}

			double std_normdist_rand()
			{
				double u = _0_1_rand(), v = _0_1_rand();
				double k = sqrt(-2 * log(u));

				return k * sin(M_2PI * v);
			}

		} /* end namesapce randnum */

	} /* end namesapce math */

} /* end namesapce kerbal */
