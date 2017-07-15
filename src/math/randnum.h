#ifndef _RANDNUM_H_
#define _RANDNUM_H_

//#pragma message(__DATE__ "  " __TIME__"  е§дкБрвы"__FILE__)

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <cmath>
#include "statistics.h"

using namespace std;

int seed();

double ave_rand(bool if_include_0, bool if_include_1);
inline double rand_between(double a, double b)
{
	return (b - a) * ave_rand(true, true) + a;
}
double normdist_rand(double sigma, double miu);
double normdist_noise(double former, double sigma, double miu);

#endif	/* End _RANDNUM_H_ */
