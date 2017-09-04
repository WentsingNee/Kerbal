#ifndef _BIG_H_
#define _BIG_H_

#include <math.h>

#include "basic_math.hpp"

namespace big
{
	double big_pow(double base, double exponent, int &exponent_result);
	double big_fact(unsigned int n, int &exponent_result);
}

//#pragma message(__DATE__ "  " __TIME__"  编译完成"__FILE__)

#endif	/* End _BIG_H_ */
