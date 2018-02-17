#include "randnum.hpp"

#include "basic_math.hpp"
#include "statistics.hpp"

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
	weight[0] = 1.0 / (RAND_MAX + 1);
	for (unsigned int i = 0; i < TIMES - 1; ++i) {
		weight[i + 1] = weight[i] / (RAND_MAX + 1);
	}
	current_seed = 0;
	return seed();
}

double _0_1_rand()
{
	double result = 0.0;
	for (unsigned int i = 0; i < TIMES; ++i) {
		result += rand() * weight[i];
	}
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
