#include "complex.hpp"
#include <cmath>

#include "../string_serve.hpp"

namespace kerbal
{
	namespace math
	{
		namespace complex
		{
			const Complex imag(0, 1.0);

			Complex::operator double() throw (std::invalid_argument)
			{
#			if __cplusplus>= 201103L //C++0x
				using std::to_string;
#			else
				using kerbal::string_serve::to_string;
#			endif

				if (imag == 0) {
					return real;
				} else {
					throw std::invalid_argument("error:imag=" + to_string(imag));
				}
			}

			//服务部分
			std::string Complex::to_string() const
			{
#			if __cplusplus>= 201103L //C++0x
				using std::to_string;
#			else
				using kerbal::string_serve::to_string;
#			endif

				std::string result;
				if (real == 0) {
					if (imag == 0) {
						result += '0';
					} else {
						if (imag == 1) {
							result += 'i';
						} else if (imag == -1) {
							result += "-i";
						} else {
							result += to_string(imag) + 'i';
						}
					}
				} else {
					result += to_string(real);
					if (imag < 0) {
						if (imag == -1) {
							result += "-i";
						} else {
							result += to_string(imag) + 'i';
						}
					} else if (imag > 0) {
						if (imag == 1) {
							result += "+i";
						} else {
							result += '+' + to_string(imag) + 'i';
						}
					}
				}

				return result;
			}

			//方法部分
			double Complex::moudle() const throw () //返回复数的模长
			{
				return hypot(real, imag);
			}

			double Complex::argz() const //返回复数的幅角
			{
				return atan2(imag, real); //弧度制
			}

			//运算符重载部分
			const Complex operator+(const Complex &a, const Complex &b) throw ()
			{
				return Complex(a.real + b.real, a.imag + b.imag);
			}

			const Complex operator+(const Complex &a, double b) throw ()
			{
				return Complex(a.real + b, a.imag);
			}

			const Complex operator+(double a, const Complex &b) throw ()
			{
				return Complex(a + b.real, b.imag);
			}

			Complex& Complex::operator+=(const Complex &with) throw ()
			{
				this->real += with.real;
				this->imag += with.imag;
				return (*this);
			}

			Complex& Complex::operator+=(const double &with) throw ()
			{
				this->real += with;
				return (*this);
			}

			const Complex operator-(const Complex &a, const Complex &b) throw ()
			{
				return Complex(a.real - b.real, a.imag - b.imag);
			}

			const Complex operator-(const Complex &a, double b) throw ()
			{
				return Complex(a.real - b, a.imag);
			}

			const Complex operator-(double a, const Complex &b) throw ()
			{
				return Complex(a - b.real, -b.imag);
			}

			Complex& Complex::operator-=(const Complex &with) throw ()
			{
				this->real -= with.real;
				this->imag -= with.imag;
				return (*this);
			}

			Complex& Complex::operator-=(const double &with) throw ()
			{
				this->real -= with;
				return (*this);
			}

			const Complex operator*(const Complex &a, const Complex &b) throw ()
			{
				return Complex(

				a.real * b.real - a.imag * b.imag,

				b.real * a.imag + a.real * b.imag);
			}

			const Complex operator*(const Complex &a, double b) throw ()
			{
				return Complex(a.real * b, a.imag * b);
			}

			const Complex operator*(double a, const Complex &b) throw ()
			{
				return Complex(a * b.real, a * b.imag);
			}

			Complex& Complex::operator*=(const Complex &with) throw ()
			{
				*this = Complex(

				this->real * with.real - this->imag * with.imag,

				with.real * this->imag + this->real * with.imag);
				return *this;
			}

			Complex& Complex::operator*=(const double &with) throw ()
			{
				this->real *= with;
				this->imag *= with;
				return *this;
			}

			const Complex operator/(const Complex &a, const Complex &b) throw (std::invalid_argument)
			{
				if (b.real == 0 && b.imag == 0) {
					throw std::invalid_argument("Complex " + a.to_string() + " is divided by Complex 0+0i");
				}
				double temp = b.real * b.real + b.imag * b.imag;

				return Complex(

				(a.real * b.real + a.imag * b.imag) / temp,

				(b.real * a.imag - a.real * b.imag) / temp);
			}

			const Complex operator/(const Complex &a, double b) throw (std::invalid_argument)
			{
				if (b == 0) {
					throw std::invalid_argument("Complex " + a.to_string() + " is divided by 0.0");
				}

				return Complex(a.real / b, a.imag / b);
			}

			const Complex operator/(double a, const Complex &b) throw (std::invalid_argument)
			{
				if (b.real == 0 && b.imag == 0) {
					throw std::invalid_argument("double " + to_string(a) + " is divided by Complex 0+0i");
				}
				double temp = b.real * b.real + b.imag * b.imag;
				return Complex((a * b.real) / temp, (-a * b.imag) / temp);
			}

			Complex& Complex::operator/=(const Complex &with) throw (std::invalid_argument)
			{
				if (with.real == 0 && with.imag == 0) {
					throw std::invalid_argument("Complex " + this->to_string() + " is divided by Complex 0+0i");
				}
				double temp = with.real * with.real + with.imag * with.imag;

				*this = Complex(

				(this->real * with.real + this->imag * with.imag) / temp,

				(with.real * this->imag - this->real * with.imag) / temp);

				return *this;
			}

			Complex& Complex::operator/=(const double &with) throw (std::invalid_argument)
			{
				if (with == 0) {
					throw std::invalid_argument("Complex " + this->to_string() + " is divided by 0.0");
				}

				this->real /= with;
				this->imag /= with;
				return *this;
			}

			bool operator==(const Complex &a, const Complex &b) throw ()
			{
				return a.real == b.real && a.imag == b.imag;
			}

			bool operator==(const Complex &a, double b) throw ()
			{
				return a.real == b && a.imag == 0;
			}

			bool operator==(double a, const Complex &b) throw ()
			{
				return a == b.real && 0 == b.imag;
			}

			bool operator!=(const Complex &a, const Complex &b) throw ()
			{
				return a.real != b.real || a.imag != b.imag;
			}

			bool operator!=(const Complex &a, double b) throw ()
			{
				return a.real != b || a.imag != 0;
			}

			bool operator!=(double a, const Complex &b) throw ()
			{
				return a != b.real || 0 != b.imag;
			}

			const Complex operator+(const Complex &a) throw ()
			{
				return Complex(a);
			}

			const Complex operator-(const Complex &a) throw ()
			{
				return Complex(-a.real, -a.imag);
			}

			const Complex operator~(const Complex &a) throw () //计算一个复数的共轭复数
			{
				return Complex(a.real, -a.imag);
			}

			std::ostream& operator<<(std::ostream &output, const Complex &z)
			{
				output << z.to_string();
				return output;
			}

			std::istream& operator>>(std::istream &input, Complex &z)
			{
				//	string src;
				//	input >> src;
				input >> z.real >> z.imag;

				return input;
			}

			//函数部分

			const Complex trans(double r, double sigma) throw () //根据模长和幅角返回一个复数
			{
				return Complex(r * cos(sigma), r * sin(sigma));
			}

			const Complex zpow(const Complex &z, int n) //计算一个复数的幂
			{
				return Complex(z.moudle() * cos(n * z.argz()), z.moudle() * sin(n * z.argz()));
			}

			const Complex zln(const Complex &z) //Lnz=lnz+2*k*pi*i , lnz=ln|z|+i*argz(z)
			{
				return Complex(log(z.moudle()), z.argz());
			}

			std::string to_string(const Complex &z)
			{
				return z.to_string();
			}

			//应用部分
			void quac_equ(double a, double b, double c, Complex &x1, Complex &x2, short &num)
			{
				//一元二次方程

				if (a == 0) {
					if (b == 0) {
						if (c == 0) {
							num = -1; //infinite solutions//无穷多解
						} else {
							num = 0; //no solution//无解
						}
					} else {
						//x1=-c/b;
						num = 1;
						x1 = Complex(-c / b, 0); //only one solution//只有一解
					}
				} else {
					num = 2;
					double delta = b * b - 4 * a * c;
					if (delta > 0) {
						//x1=(-b+sqrt(delta))/2/a;
						//x2=(-b-sqrt(delta))/2/a;

						double sqt_delta = sqrt(delta);
						x1 = Complex((-b + sqt_delta) / 2 / a, 0);
						x2 = Complex((-b - sqt_delta) / 2 / a, 0);
					} else if (delta < 0) {
						//x1=(-b/2/a,sqrt(-delta)/2/a)
						//x2=~x1;

						double sqt_negatve_delta = sqrt(-delta);
						x1 = Complex(-b / 2 / a, sqt_negatve_delta / 2 / a);
						x2 = Complex(-b / 2 / a, -sqt_negatve_delta / 2 / a);
					} else {
						//x1=-b/2/a;
						//x2=-b/2/a;

						x1 = Complex(-b / 2 / a, 0);
						x2 = Complex(-b / 2 / a, 0);
					}
				}
			}

		}/* namespace complex */

	}/* namespace math */

}/* namespace kerbal */
