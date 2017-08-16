#include "Complex.hpp"

using namespace std;

namespace complex
{
	//服务部分
	string Complex::to_string() const
	{
		stringstream output;
		if (real == 0) {
			if (imag == 0) {
				output << '0';
			} else {
				if (imag == 1) {
					output << 'i';
				} else if (imag == -1) {
					output << "-i";
				} else {
					output << imag << 'i';
				}
			}
		} else {
			output << real;
			if (imag < 0) {
				if (imag == -1) {
					output << "-i";
				} else {
					output << imag << 'i';
				}
			} else if (imag > 0) {
				if (imag == 1) {
					output << "+i";
				} else {
					output << '+' << imag << 'i';
				}
			}
		}

		string result;
		output >> result;
		return result;
	}

	void Complex::display() const
	{
		cout << this->to_string() << endl;
	}

	//方法部分
	double Complex::moudle() const //返回复数的模长
	{
		return hypot(real, imag);
	}

	double Complex::argz() const //返回复数的幅角
	{
		return atan2(imag, real); //弧度制
	}

	//运算符重载部分
	Complex operator+(const Complex &a, const Complex &b)
	{
		return Complex(a.real + b.real, a.imag + b.imag);
	}

	Complex operator+(const Complex &a, double b)
	{
		return Complex(a.real + b, a.imag);
	}

	Complex operator+(double a, const Complex &b)
	{
		return Complex(a + b.real, b.imag);
	}

	Complex operator-(const Complex &a, const Complex &b)
	{
		return Complex(a.real - b.real, a.imag - b.imag);
	}

	Complex operator-(const Complex &a, double b)
	{
		return Complex(a.real - b, a.imag);
	}

	Complex operator-(double a, const Complex &b)
	{
		return Complex(a - b.real, -b.imag);
	}

	Complex operator*(const Complex &a, const Complex &b)
	{
		return Complex(

		a.real * b.real - a.imag * b.imag,

		b.real * a.imag + a.real * b.imag);
	}

	Complex operator*(const Complex &a, double b)
	{
		return Complex(a.real * b, a.imag * b);
	}

	Complex operator*(double a, const Complex &b)
	{
		return Complex(a * b.real, a * b.imag);
	}

	Complex operator/(const Complex &a, const Complex &b) throw (invalid_argument)
	{
		if (b.real == 0 && b.imag == 0) {
			throw(invalid_argument(string("Complex ") + a.to_string() + string(" is divided by Complex 0+0i")));
		}
		double temp = b.real * b.real + b.imag * b.imag;

		return Complex(

		(a.real * b.real + a.imag * b.imag) / temp,

		(b.real * a.imag - a.real * b.imag) / temp);
	}

	Complex operator/(const Complex &a, double b) throw (invalid_argument)
	{
		if (b == 0) {
			throw(invalid_argument(string("Complex ") + a.to_string() + string(" is divided by 0.0")));
		}

		return Complex(a.real / b, a.imag / b);
	}

	Complex operator/(double a, const Complex &b) throw (invalid_argument)
	{
		if (b.real == 0 && b.imag == 0) {
			throw(invalid_argument(string("double ") + to_string(a) + string(" is divided by Complex 0+0i")));
		}
		double temp = b.real * b.real + b.imag * b.imag;
		return Complex((a * b.real) / temp, (-a * b.imag) / temp);
	}

	bool operator==(const Complex &a, const Complex &b)
	{
		//	if(a.real==b.real) {
		//		if(a.imag==b.imag) {
		//			return true;
		//		}
		//	}
		//	return false;
		return a.real == b.real && a.imag == b.imag;
	}

	bool operator==(const Complex &a, double b)
	{
		return a.real == b && a.imag == 0;
	}

	bool operator==(double a, const Complex &b)
	{
		return a == b.real && 0 == b.imag;
	}

	bool operator!=(const Complex &a, const Complex &b)
	{
		//	if(a.real==b.real) {
		//		if(a.imag==b.imag) {
		//			return false;
		//		}
		//	}
		//	return true;
		return a.real != b.real || a.imag != b.imag;
	}

	bool operator!=(const Complex &a, double b)
	{
		return a.real != b || a.imag != 0;
	}

	bool operator!=(double a, const Complex &b)
	{
		return a != b.real || 0 != b.imag;
	}

	Complex operator-(const Complex &a)
	{
		return Complex(-a.real, -a.imag);
	}

	Complex operator~(const Complex &a) //计算一个复数的共轭复数
	{
		return Complex(a.real, -a.imag);
	}

	ostream& operator <<(ostream &output, const Complex &z)
	{
		output << z.to_string();
		return output;
	}

	istream& operator >>(istream &input, Complex &z)
	{
		//	string src;
		//	input >> src;
		input >> z.real >> z.imag;

		return input;
	}

	//函数部分

	Complex trans(double r, double sigma) //根据模长和幅角返回一个复数
	{
		return Complex(r * cos(sigma), r * sin(sigma));
	}

	Complex zpow(const Complex &z, int n) //计算一个复数的幂
	{
		return Complex(z.moudle() * cos(n * z.argz()), z.moudle() * sin(n * z.argz()));
	}

	Complex zln(const Complex &z) //Lnz=lnz+2*k*pi*i , lnz=ln|z|+i*argz(z)
	{
		return Complex(log(z.moudle()), z.argz());
	}

	string to_string(const Complex &z)
	{
		return z.to_string();
	}

	//应用部分
	void quac_equ(double a, double b, double c, Complex &x1, Complex &x2, short &num) throw (invalid_argument)
	{
		//一元二次方程

		if (a == 0) {
			if (b == 0) {
				if (c == 0) {
					num = 3;
					throw invalid_argument("infinite solutions"); //无穷多解
				} else {
					num = 0;
					throw invalid_argument("no solution"); //无解
				}
			} else {
				//x1=-c/b;
				num = 1;
				x1 = Complex(-c / b, 0);
				throw invalid_argument("only one solution"); //只有一解
			}
		} else {
			num = 2;
			double delta = b * b - 4 * a * c;
			if (delta > 0) {
				//x1=(-b+sqrt(delta))/2/a;
				//x2=(-b-sqrt(delta))/2/a;

				x1 = Complex((-b + sqrt(delta)) / 2 / a, 0);
				x2 = Complex((-b - sqrt(delta)) / 2 / a, 0);
			} else if (delta < 0) {
				//x1=(-b/2/a,sqrt(-delta)/2/a)
				//x2=~x1;

				x1 = Complex(-b / 2 / a, sqrt(-delta) / 2 / a);
				x2 = Complex(-b / 2 / a, -sqrt(-delta) / 2 / a);
			} else {
				//x1=-b/2/a;
				//x2=-b/2/a;

				x1 = Complex(-b / 2 / a, 0);
				x2 = Complex(-b / 2 / a, 0);
			}
		}

		/* //Example
		 Complex x1, x2;
		 int a, b, c;
		 short num;
		 cin >> a >> b >> c;
		 cout << "a = " << a << " ,b = " << b << " ,c = " << c << endl;
		 try {
		 quac_equ(a, b, c, x1, x2, num);
		 cout << "x1 = " << x1 << " , x2 =" << x2 << endl;
		 } catch (const exception &exct) {
		 cout << exct.what() << endl;
		 if (num == 1) {
		 cout << "x = " << x1 << endl;
		 }
		 }
		 cout << "num = " << num << endl;
		 */
	}

} /* End of namespace complex */
