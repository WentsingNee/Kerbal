#include "big.hpp"

using namespace std;

namespace big
{
	double big_pow(double base, double exponent, int &exponent_result)
	{
		double exponent_temp = exponent * log10(base);
		exponent_result = (int) (exponent_temp);
		return pow(10, decimal(exponent_temp));
	}

	double big_fact(unsigned int n, int &exponent_result)
	{
		unsigned int i;
		double exponent_temp = 0;

		if (n >= 2) {
			for (i = 2; i <= n; i++) {
				exponent_temp += log10(i);
			}
		}
		exponent_result = (int) (exponent_temp);
		return pow(10, decimal(exponent_temp));
	}
}

