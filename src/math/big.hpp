#ifndef _BIG_H_
#define _BIG_H_

#include <iostream>
#include <stdio.h>
#include <math.h>

#include "basic_math.hpp"

using namespace std;

namespace big
{
	double big_pow(double base, double exponent, int &exponent_result);
	double big_fact(unsigned int n, int &exponent_result);
}

using namespace big;

//#pragma message(__DATE__ "  " __TIME__"  ±‡“ÎÕÍ≥…"__FILE__)

#endif	/* End _BIG_H_ */
