#include "Complex.hpp"

using namespace std;

//服务部分
string Complex::to_string() const
{
	stringstream output;
	if (real == 0) {
		if (imag == 0) {
			output << "0";
		} else {
			if (imag == 1) {
				output << "i";
			} else if (imag == -1) {
				output << "-i";
			} else {
				output << imag << "i";
			}
		}
	} else {
		output << real;
		if (imag < 0) {
			if (imag == -1) {
				output << "-i";
			} else {
				output << imag << "i";
			}
		} else {
			if (imag == 1) {
				output << "+i";
			} else {
				output << "+" << imag << "i";
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
	Complex z;
	z.real = a.real * b.real - a.imag * b.imag;
	z.imag = b.real * a.imag + a.real * b.imag;
	return z;
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
	Complex z;
	if (b.real == 0 && b.imag == 0) {
		throw(invalid_argument(string("Complex ") + to_string(a) + string(" is divided by Complex 0+0i")));
	}
	double temp = b.real * b.real + b.imag * b.imag;
	z.real = (a.real * b.real + a.imag * b.imag) / temp;
	z.imag = (b.real * a.imag - a.real * b.imag) / temp;
	return z;
}

Complex operator/(const Complex &a, double b) throw (invalid_argument)
{
	if (b == 0) {
		throw(invalid_argument(string("Complex ") + to_string(a) + string(" is divided by 0.0")));
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
	string src;
	input >> src;

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
short quac_equ(double a, double b, double c, Complex **x1_point_point, Complex **x2_point_point) //一元二次方程
{
	double delta;
	short num;

	if (a == 0) {
		if (b == 0) {
			if (c == 0) {
				//无穷解;

				*x1_point_point = NULL;
				*x2_point_point = NULL;
				num = 3;
			} else {
				//无解;

				*x1_point_point = NULL;
				*x2_point_point = NULL;
				num = 0;
			}
		} else {
			//x1=-c/b;

			**x1_point_point = Complex(-c / b, 0);
			*x2_point_point = NULL;
			num = 1;
		}
	} else {
		num = 2;
		delta = b * b - 4 * a * c;
		cout << "delta=" << delta << endl;
		if (delta > 0) {
			//x1=(-b+sqrt(delta))/2/a;
			//x2=(-b-sqrt(delta))/2/a;

			**x1_point_point = Complex((-b + sqrt(delta)) / 2 / a, 0);
			**x2_point_point = Complex((-b - sqrt(delta)) / 2 / a, 0);
		} else if (delta < 0) {
			//x1=(-b/2/a,sqrt(-delta)/2/a)
			//x2=~x1;

			**x1_point_point = Complex(-b / 2 / a, sqrt(-delta) / 2 / a);
			**x2_point_point = Complex(-b / 2 / a, -sqrt(-delta) / 2 / a);
		} else {
			//x1=-b/2/a;
			//x2=-b/2/a;

			**x1_point_point = Complex(-b / 2 / a, 0);
			**x2_point_point = Complex(-b / 2 / a, 0);
		}
	}

	return num;

	/*example
	 Complex x1,x2;
	 Complex *x1_point=&x1,*x2_point=&x2;

	 int a,b,c;
	 cin >> a >> b >> c;
	 cout << "a=" << a << ",b=" << b << ",c=" <<c<<endl;
	 cout << quac_equ(a,b,c,&x1_point,&x2_point)<<endl;

	 if(x1_point!=NULL)
	 {
	 (x1_point)->display();
	 }
	 if(x2_point!=NULL)
	 {
	 (x2_point)->display();
	 }
	 */
}

