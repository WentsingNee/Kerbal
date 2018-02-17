#ifndef _RANDNUM_HPP_
#define _RANDNUM_HPP_

#include "time.h"

time_t seed();

double _0_1_rand();
inline double rand_between(double min, double max);
inline bool rand_true(double probability);
double normdist_rand(double sigma = 1, double miu = 0);

inline double rand_between(double min, double max)
{
	return (max - min) * _0_1_rand() + min;
}

inline bool rand_true(double probability)
{
	return _0_1_rand() <= probability ? true : false;
}

#endif	/* End _RANDNUM_HPP_ */
