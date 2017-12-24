#include "randnum.hpp"
#include <stdlib.h>
#include <cmath>

#include "basic_math.hpp"
#include "statistics.hpp"
#include "../tick_count.h"

unsigned int seed()
{
	unsigned int k = GetTickCount();
	srand(k);
	return k;
}

static bool rand_num_first = true;

double ave_rand(bool if_include_0, bool if_include_1)
{
	if (rand_num_first == true) {
		seed();
		rand_num_first = false;
	}

	static const int TIMES = 10;
	static double weight[TIMES + 1] = { 1.0 };
	static bool ave_rand_first = true;
	if (ave_rand_first == true) {
		for (int i = 0; i < TIMES; i++) {
			weight[i + 1] = weight[i] / RAND_MAX;
		}
		ave_rand_first = false;
	}

	double result;
	do {
		result = 0.0;
		for (int i = 1; i <= TIMES; i++) {
			result += rand() * weight[i];
		}
	} while (result > 1

	|| (result == 0 && if_include_0 == false)

	|| (result == 1 && if_include_1 == false));

	return result;
}

double normdist_rand(double sigma, double miu) //miu=ave,sigma=expect
{
	double x, y, y_available;

	do {
		x = rand_between(miu - 6 * sigma, miu + 6 * sigma);
		y = rand_between(0, 1.01 / M_SQRT_2PI / sigma);
		y_available = kerbal::math::statistics::normdist(x, sigma, miu);
	} while (y > y_available);
	return x;
}
