#ifndef _COMPLEX_H_
#define _COMPLEX_H_

#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <stdexcept>
#include <sstream>

#include "../String_serve.hpp"

using namespace std;

class Complex
{
	public:
		//成员
		double real;
		double imag;

		Complex(double real = 0.0, double imag = 0.0)
		{ //初始化
			this->real = real;
			this->imag = imag;
		}

		operator double() throw (invalid_argument)
		{
			if (imag == 0) {
				return real;
			} else {
				throw invalid_argument("error:imag=" /*+ std::to_string(imag)*/);
			}
		}

		//方法
		string to_string() const;
		void display() const;
		double moudle() const; //返回复数的模长
		double argz() const; //返回复数的幅角

		//运算符重载
		friend Complex operator+(const Complex &a, const Complex &b);
		friend Complex operator+(const Complex &a, double b);
		friend Complex operator+(double a, const Complex &b);

		friend Complex operator-(const Complex &a, const Complex &b);
		friend Complex operator-(const Complex &a, double b);
		friend Complex operator-(double a, const Complex &b);

		friend Complex operator*(const Complex &a, const Complex &b);
		friend Complex operator*(const Complex &a, double b);
		friend Complex operator*(double a, const Complex &b);

		friend Complex operator/(const Complex &a, const Complex &b) throw (invalid_argument);
		friend Complex operator/(const Complex &a, double b) throw (invalid_argument);
		friend Complex operator/(double a, const Complex &b) throw (invalid_argument);

		friend bool operator==(const Complex &a, const Complex &b);
		friend bool operator==(const Complex &a, double b);
		friend bool operator==(double a, const Complex &b);

		friend bool operator!=(const Complex &a, const Complex &b);
		friend bool operator!=(const Complex &a, double b);
		friend bool operator!=(double a, const Complex &b);

		friend ostream& operator <<(ostream &output, const Complex &z);
		friend istream& operator >>(istream &input, Complex &z);

		friend Complex operator-(const Complex &a);
		friend Complex operator~(const Complex &a); //计算一个复数的共轭复数
};

const Complex imag(0, 1.0);

//函数

Complex trans(double r, double thita); //根据模长和幅角返回一个复数
Complex zpow(const Complex &z, int n); //计算一个复数的幂
Complex zln(const Complex &z); //计算一个复数的自然对数的主值Lnz=lnz+2*k*pi*i , lnz=ln|z|+i*argz(z)
string to_string(const Complex &z);

short quac_equ(double a, double b, double c, Complex **x1_point, Complex **x2_point); //一元二次方程

//#pragma message(__DATE__ "  " __TIME__"  编译完成"__FILE__)

#endif	/* End _COMPLEX_H_ */
