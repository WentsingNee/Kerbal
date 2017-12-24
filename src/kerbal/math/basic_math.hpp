#ifndef _BASIC_MATH_H_
#define _BASIC_MATH_H_

#include <cmath>
#include <string>

namespace kerbal
{
	namespace math
	{
		namespace constant
		{
#ifndef M_E
			const double M_E = 2.7182818284590452354;
			const double M_LOG2E = 1.4426950408889634074;
			const double M_LOG10E = 0.43429448190325182765;
			const double M_LN2 = 0.69314718055994530942;
			const double M_LN10 = 2.30258509299404568402;
			const double M_PI = 3.14159265358979323846;
			const double M_PI_2 = 1.57079632679489661923;
			const double M_PI_4 = 0.78539816339744830962;
			const double M_1_PI = 0.31830988618379067154;
			const double M_2_PI = 0.63661977236758134308;
			const double M_2_SQRTPI = 1.12837916709551257390;
			const double M_SQRT2 = 1.41421356237309504880;
			const double M_SQRT1_2 = 0.70710678118654752440;
#endif

			const double M_SQRT_2PI = sqrt(2 * M_PI);
		}/* namespace constant */
	}
}
using namespace kerbal::math::constant;

namespace kerbal
{
	namespace math
	{
		namespace basic_math
		{

			inline double round(double x, int digits)
			{
				double times = pow(10, -digits);
				double result = (int) (x * times + 0.5) / times;
				return x >= 0 ? result : -result;
			}

			inline bool diff(int m, int n) //m,n是否异号
			{
				return ((unsigned) (m ^ n) >> (8 * sizeof(int) - 1));
			}

			inline double decimal(double a)
			{
				return a - (int) a;
			}

			inline float decimal(float a)
			{
				return a - (int) a;
			}

			double baremainder(double numerator, double denominator); //返回两数相除的余数。结果的符号与除数相同
			unsigned short float_num(double a, double digits); //BUG
			double up(double x, int digits);
			int gcd(int a, int b); //返回两数的最大公约数
			int lcm(int a, int b); //返回两数的最小公倍数
			bool is_prime(int x);

			double big_pow(double base, double exponent, int &exponent_result);
			double big_fact(unsigned int n, int &exponent_result);

			std::string fraction(double a);

		}/* namespace basic_math */

#if __cplusplus >= 201103L //c++0x
		namespace times
		{
			constexpr long long operator"" _G(unsigned long long x)
			{
				return x * 1000000000LL;
			}

			constexpr long long operator"" _Gi(unsigned long long x)
			{
				return x * 1073741824LL;
			}
			constexpr long double operator"" _G(long double x)
			{
				return x * 10E9;
			}
			constexpr long double operator"" _Gi(long double x)
			{
				return x * 1073741824;
			}

			constexpr long long operator"" _M(unsigned long long x)
			{
				return x * 1000000LL;
			}
			constexpr long long operator"" _Mi(unsigned long long x)
			{
				return x * 1048576LL;
			}
			constexpr long double operator"" _M(long double x)
			{
				return x * 10E6;
			}
			constexpr long double operator"" _Mi(long double x)
			{
				return x * 1048576;
			}

			constexpr long long operator"" _K(unsigned long long x)
			{
				return x * 1000LL;
			}
			constexpr long long operator"" _Ki(unsigned long long x)
			{
				return x * 1024;
			}
			constexpr long double operator"" _K(long double x)
			{
				return x * 10E3;
			}
			constexpr long double operator"" _Ki(long double x)
			{
				return x * 1024;
			}

			constexpr long double operator"" _m(long double x)
			{
				return x * 10E-3;
			}
			constexpr long double operator"" _m(unsigned long long x)
			{
				return x * 10E-3;
			}

			constexpr long double operator"" _miu(long double x)
			{
				return x * 10E-6;
			}
			constexpr long double operator"" _miu(unsigned long long x)
			{
				return x * 10E-6;
			}

			constexpr long double operator"" _n(long double x)
			{
				return x * 10E-9;
			}
			constexpr long double operator"" _n(unsigned long long x)
			{
				return x * 10E-9;
			}

			constexpr long double operator"" _p(long double x)
			{
				return x * 10E-12;
			}
			constexpr long double operator"" _p(unsigned long long x)
			{
				return x * 10E-12;
			}

		}/* namespace times */

#endif //c++0x

	}/* namespace math */

}/* namespace kerbal */

#endif	/* End _BASIC_MATH_H_ */
