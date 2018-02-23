#include "randnum.hpp"

#include "basic_math.hpp"

time_t seed()
{
	time_t k = time(NULL);
	srand(k);
	return k;
}

#define TIMES 10
static double weight[TIMES];
static time_t rand_init();
static time_t current_seed = rand_init();

static time_t rand_init()
{
	weight[0] = 1.0 / RAND_MAX;
	for (unsigned int i = 0; i < TIMES - 1; ++i) {
		weight[i + 1] = weight[i] / RAND_MAX;
	}
	current_seed = 0;
	return seed();
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
	double std_normdist(double x) //标准正态分布的概率密度函数, miu=ave, sigma=expect
	{
		return exp(x * x / (-2)) * M_1_SQRT_2PI;
	}
}

double normdist_rand(double sigma, double miu) //miu=ave,sigma=expect
{
	double x, y, y_available;

	do {
		x = rand_between(miu - 6 * sigma, miu + 6 * sigma);
		y = rand_between(0, 1.01 * M_1_SQRT_2PI / sigma);
		y_available = std_normdist((x - miu) / sigma) / sigma;
	} while (y > y_available);
	return x;
}

