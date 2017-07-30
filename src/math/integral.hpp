#ifndef _INTEGRAL_H_
#define _INTEGRAL_H_

//#pragma message(__DATE__ "  " __TIME__"  正在编译"__FILE__)

#include <iostream>
#include <cmath>

#include "statistics.hpp"

using namespace std;

double dy(double x, double dx, double (*f)(double)); //微y
double derivative(double x, double (*f)(double), double dx = 0.001); //导数
double ladder(double a, double b, double dx, double (*f)(double)); //梯形法积分
double simpson(double a, double b, double dx, double (*f)(double)); //辛普生公式积分
double std_normdist_integral(double b, double dx); //标准正态分布积分

double B(int n); //计算伯努利数
double Stirling(double x); //斯特林公式
double logGamma(double z);
double Gamma(double z);
double Beta(double P, double Q);

#endif	/* End _INTEGRAL_H_ */
