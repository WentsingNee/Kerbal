#include <cmath>
#include "randnum.h"
#include "basic_math.h"

using namespace std;

int seed()
{
	int k = GetTickCount() % 1000;
	srand(k);
	return k;
}

static bool first = true;

double ave_rand(bool if_include_0, bool if_include_1)
{
	if (first == true) {
		seed();
		first = false;
	}

#define TIMES 10
	int a[TIMES];

	double fenmu = 1.0, result = 0.0;
	for (int i = 0; i < TIMES; i++) {
		fenmu *= RAND_MAX;
		a[i] = rand();
		result += a[i] / fenmu;
	}

	if (result > 1) {
		return ave_rand(if_include_0, if_include_1);
	}
	if (result == 0 && if_include_0 == false) {
		return ave_rand(if_include_0, if_include_1);
	}
	if (result == 1 && if_include_1 == false) {
		return ave_rand(if_include_0, if_include_1);
	}
	return result;
}

double normdist_rand(double sigma, double miu = 0) //miu=ave,sigma=expect
{
	double x, y, y_available;

	do {
		x = rand_between(miu - 6 * sigma, miu + 6 * sigma);
		y = rand_between(0, 1.0 / sqrt(2 * M_PI) / sigma * 1.01);
		y_available = normdist(x, sigma, miu);
	} while (y > y_available);
	return x;
}

double normdist_noise(double former, double sigma, double miu)
{
	double x, y, y_range_max;
	x = rand_between(miu - 6 * sigma, miu + 6 * sigma);
	if (miu * miu / sigma / sigma > 2 * log(2)) {
		y_range_max = 2.0 * exp(pow(miu / sigma, 2) / (-2)) / sqrt(2 * M_PI) / sigma; //Ë«·å
	} else {
		y_range_max = 1.0 / sqrt(2 * M_PI) / sigma; //µ¥·å
	}
	y = rand_between(0, y_range_max);
	double y_available = normdist(x, sigma, miu) + normdist(x, sigma, -miu);
	if (y <= y_available) {
		return former + x;
	} else {
		return normdist_noise(former, sigma, miu);
	}
}
