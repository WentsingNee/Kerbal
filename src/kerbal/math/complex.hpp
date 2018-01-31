/**
 * @file complex.hpp
 * @date 2016-12-25
 * @author 倪文卿
 */

#ifndef _COMPLEX_H_
#define _COMPLEX_H_

#include <ostream>
#include <istream>
#include <string>

#include "../except_C++0x.hpp"

namespace kerbal
{
	namespace math
	{
		namespace complex
		{
			class Complex
			{
				public:
					//成员
					double real;
					double imag;

					Complex(double real = 0.0, double imag = 0.0) throw () :
							real(real), imag(imag)
					{ //初始化
					}

					operator double() throw (std::invalid_argument);

					//方法
					std::string to_string() const;
					double moudle() const throw (); //返回复数的模长
					double argz() const; //返回复数的幅角

					//运算符重载
					friend const Complex operator+(const Complex &a, const Complex &b) throw ();
					friend const Complex operator+(const Complex &a, double b) throw ();
					friend const Complex operator+(double a, const Complex &b) throw ();
					Complex& operator+=(const Complex &with) throw ();
					Complex& operator+=(const double &with) throw ();

					friend const Complex operator-(const Complex &a, const Complex &b) throw ();
					friend const Complex operator-(const Complex &a, double b) throw ();
					friend const Complex operator-(double a, const Complex &b) throw ();
					Complex& operator-=(const Complex &with) throw ();
					Complex& operator-=(const double &with) throw ();

					friend const Complex operator*(const Complex &a, const Complex &b) throw ();
					friend const Complex operator*(const Complex &a, double b) throw ();
					friend const Complex operator*(double a, const Complex &b) throw ();
					Complex& operator*=(const Complex &with) throw ();
					Complex& operator*=(const double &with) throw ();

					friend const Complex operator/(const Complex &a, const Complex &b)
							throw (std::invalid_argument);
					friend const Complex operator/(const Complex &a, double b)
							throw (std::invalid_argument);
					friend const Complex operator/(double a, const Complex &b)
							throw (std::invalid_argument);
					Complex& operator/=(const Complex &with) throw (std::invalid_argument);
					Complex& operator/=(const double &with) throw (std::invalid_argument);

					friend bool operator==(const Complex &a, const Complex &b) throw ();
					friend bool operator==(const Complex &a, double b) throw ();
					friend bool operator==(double a, const Complex &b) throw ();

					friend bool operator!=(const Complex &a, const Complex &b) throw ();
					friend bool operator!=(const Complex &a, double b) throw ();
					friend bool operator!=(double a, const Complex &b) throw ();

					friend std::ostream& operator<<(std::ostream &output, const Complex &z);
					friend std::istream& operator>>(std::istream &input, Complex &z);

					friend const Complex operator+(const Complex &a) throw ();
					friend const Complex operator-(const Complex &a) throw ();
					friend const Complex operator~(const Complex &a) throw ();
					//计算一个复数的共轭复数
			};

			extern const Complex imag;

			//函数

			//根据模长和幅角返回一个复数
			const Complex trans(double r, double thita) throw ();

			//计算一个复数的幂
			const Complex zpow(const Complex &z, int n);

			//计算一个复数的自然对数的主值Lnz=lnz+2*k*pi*i , lnz=ln|z|+i*argz(z)
			const Complex zln(const Complex &z);

			//转换为字符串
			std::string to_string(const Complex &z);

			//一元二次方程
			void quac_equ(double a, double b, double c, Complex &x1, Complex &x2, short &num);

		}/* namespace complex */

	}/* namespace math */

}/* namespace kerbal */

#endif	/* End _COMPLEX_H_ */
