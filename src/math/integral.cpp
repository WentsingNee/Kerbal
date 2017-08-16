#include "integral.hpp"

#include <cmath>
#include "basic_math.hpp"

using namespace std;

double dy(double x, double dx, double (*f)(double))
{
	return (*f)(x + dx) - (*f)(x);
}

double derivative(double x, double (*f)(double), double dx) //导数
{
	//double x, double (*f)(double), double dx 默认 = 0.001
	//double dx=-0.001;
	return ((*f)(x + dx) - (*f)(x - dx)) / dx / 2.0;
}

double ladder(double a, double b, double dx, double (*f)(double)) //梯形法积分
{
	if (a == b) {
		return 0;
	}
	const unsigned int n = fabs(round((b - a) / dx, 0)); //调整dx
	dx = (b - a) / n;

	double sum = 0.0, x = a;
	for (unsigned int i = 1; i < n; i++) {
		x += dx;
		sum += (*f)(x);
	}
	sum += ((*f)(a) + (*f)(b)) / 2;
	return sum * dx;
}

double simpson(double a, double b, double dx, double (*f)(double)) //辛普生公式积分
{
	if (a == b) {
		return 0.0;
	}

	const unsigned int n = fabs(round((b - a) / dx, 0)); //调整dx
	dx = (b - a) / n;

	double sum_odd = 0.0, sum_double = 0.0, x = a;
	for (unsigned int i = 1; i < n; i++) {
		x += dx;
		if (i % 2) {
			sum_odd += (*f)(x); //i为奇数
		} else {
			sum_double += (*f)(x); //i为偶数
		}
	}

	return ((*f)(a) + (*f)(b) + 2 * sum_double + 4 * sum_odd) * dx / 3;
}

double std_normdist_integral(double b, double dx) //标准正态分布积分
{
	if (b == 0.0) {
		return 0.5;
	}

	const unsigned int n = fabs(round(b / dx, 0));
	dx = b / n;

	double sum_odd = 0.0, sum_double = 0.0, x = 0.0, result;
	for (unsigned int i = 1; i <= n - 1; i++) {
		x += dx;
		if (i % 2 == 0) {
			sum_double += exp(-x * x / 2);
		} else {
			sum_odd += exp(-x * x / 2);
		}
	}

	result = 0.5 + (1 + exp(-b * b / 2) + 2 * sum_double + 4 * sum_odd) * dx / 3 / sqrt(2 * M_PI);

	if (result > 1) {
		return 1.0;
	} else if (result < 0) {
		return 0.0;
	}
	return result;
}

double B(int n) //计算伯努利数
{
	if (n == 1) {
		//cout<<"B("<<n<<")=-1/2"<<endl;
		return -0.5;
	}
	if (n % 2) { //n奇
		//cout<<"B("<<n<<")=0"<<endl;
		return 0.0;
	}
	if (n == 0) {
		//cout<<"B("<<n<<")=1"<<endl;
		return 1;
	}
	//n为2，4，6，8，10...
	double result = 0.0;
	result += 1.0;		//broad_combine(n+1,0)*B(0)
	result += (n + 1) / (-2.0);		//broad_combine(n+1,1)*B(1)

	for (int k = 2; k <= n - 1; k = k + 2) {
		result += combine(n + 1, k) * B(k);

//		bc=broad_combine(n+1,k);
//		co=combine(n+1,k);
//		printf("bc=%.25f\n",bc);
//		printf("co=%ld\n",co);
//		if(bc!=co){
//			cout<<"****************************\n";
//		}
	}
	result = -result / (n + 1);
	//cout << "B(" << n << ")="<<fraction(result)<<endl;
	return result;
}

double Stirling(double x) //斯特林公式
{
	return sqrt(2 * M_PI) * exp(-x) * pow(x, x + 0.5);
}

double logGamma(double z)
{
//	double tmp = (x - 0.5) * log(x + 4.5) - (x + 4.5);
//	double ser = 1.0 + 76.18009173    / (x + 0)   - 86.50532033    / (x + 1)
//	             + 24.01409822    / (x + 2)   -  1.231739516   / (x + 3)
//	             +  0.00120858003 / (x + 4)   -  0.00000536382 / (x + 5);
//	return tmp + log(ser * sqrt(2 * M_PI));
	int n = 40000;
	double result = z * log(n) - log(z);
	for (int i = 1; i <= n; i++) {
		result += log(i / (z + i));
		//printf("%.25f\n",log(i/(z+i)));
	}
	return result;
}

double Gamma(double z)
{
	int n = 50000;
	double result = pow(n, z) / z;
	for (int i = 1; i <= n; i++) {
		result *= i / (z + i);
	}
	return result;
	//return exp(logGamma(z));
}

double Beta(double P, double Q)
{
	return Gamma(P) * Gamma(Q) / Gamma(P + Q);
}

