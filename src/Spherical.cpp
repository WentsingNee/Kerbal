#include "Spherical.hpp"

#include <cmath>
#include <string>

#include "math/basic_math.hpp"
#include "String_serve.hpp"

namespace spherical
{
	namespace
	{
		using namespace std;
	}

	const double Spherical::R = 6371004; //地球半径

	double rad_to_angle(double i)
	{
		return i * 180 / M_PI;
	}

	double angle(double degree, double min, double sec)
	{
		return degree + min / 60 + sec / 3600;
	}

//运算符重载
	ostream& operator <<(ostream &output, const Spherical &s)
	{
		output << s.to_string();
		return output;
	}

	string Spherical::to_string() const
	{
#if __cplusplus >= 201103L //C++0x
		string (*to_string)(double)=std::to_string;
#else
		string (*to_string)(double)=_String::to_string;
#endif //C++0x

		string Text = comment + ": ";

		if (longitude > 0) {
			Text += to_string(longitude) + "°E";
		} else if (longitude < 0) {
			Text += to_string(-longitude) + "°W";
		} else {
			Text += to_string(longitude) + "°";
		}

		Text += " , ";

		if (latitude > 0) {
			Text += to_string(latitude) + "°N";
		} else if (latitude < 0) {
			Text += to_string(-latitude) + "°S";
		} else {
			Text += to_string(latitude) + "°";
		}

		Text += " , ";
		Text += to_string(height) + "m";

		return Text;
	}

	double ball_distance(const Spherical &a, const Spherical &b) //返回两点投影在球面上的弧线的长度
	{
		return a.R
				* acos(
						sin(a.latitude) * sin(b.latitude)
								+ cos(a.latitude) * cos(b.latitude) * cos(a.longitude - b.longitude));
	}

	double real_distance(const Spherical &a, const Spherical &b) //返回考虑到两点间高度差的两点间距离
	{
		if (a.latitude == b.latitude && a.longitude == b.longitude) {
			return fabs(a.height - b.height);
		}

		if (a.height == b.height) {
			return ball_distance(a, b) * (a.R + a.height) / a.R;
		} else {
			double h, H;
			if (a.height < b.height) {
				h = a.height + Spherical::R;
				H = b.height + Spherical::R;
			} else {
				H = a.height + Spherical::R;
				h = b.height + Spherical::R;
			}
			double k = fabs(a.height - b.height) * a.R / ball_distance(a, b);
			double sigma1 = h / k;
			double sigma2 = H / k;
			double temp1 = sqrt(sigma1 * sigma1 + 1);
			double temp2 = sqrt(sigma2 * sigma2 + 1);
			return 0.5 * (H * temp2 - h * temp1 + k * log((sigma2 + temp2) / (sigma1 + temp1)));
		}
	}

//服务

	double MOD(double x, double y) //返回两浮点数数相除的余数,结果的符号与除数相同
	{
		int quotient;
		if (x / y > 0) {
			quotient = x / y;
		} else {
			quotient = (int) (x / y) - 1;
		}
		return x - y * quotient;
	}

//	Spherical bei(angle(116,25,29),angle(39,54,20),5.000);
//	Spherical shang(angle(122,12,0),angle(31,53,0),2.000);
//	Spherical shang1(angle(122,12,0),angle(31,53,0),10);
//	Spherical nuist_library(angle(118,42,30.499),angle(32,12,15.900));
//	cout<<bei<<endl;
//	cout<<nuist_library<<endl;
//
//	printf("ball d=%f\n",ball_distance(bei,shang));
//	printf("real d=%f\n",real_distance(bei,shang));

} /* Namespace pherical */
