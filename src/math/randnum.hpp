#ifndef _RANDNUM_H_
#define _RANDNUM_H_

//#pragma message(__DATE__ "  " __TIME__"  е§дкБрвы"__FILE__)

#include <stdlib.h>
#include <windows.h>
#include <cmath>
#include "statistics.hpp"

using namespace std;

unsigned int seed();

double ave_rand(bool if_include_0, bool if_include_1);
inline double rand_between(double min, double max)
{
	return (max - min) * ave_rand(true, true) + min;
}

inline bool rand_true(double probability)
{
	return ave_rand(true, true) <= probability ? true : false;
}

double normdist_rand(double sigma, double miu);
double normdist_noise(double former, double sigma, double miu);

#endif	/* End _RANDNUM_H_ */
