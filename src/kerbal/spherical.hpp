/**
 * @file spherical.hpp
 * @date 2017-1-1
 * @author 倪文卿
 */

#ifndef _SPHERICAL_HPP_
#define _SPHERICAL_HPP_

#include <ostream>
#include <string>

namespace kerbal
{
	namespace spherical
	{

		inline double rad_to_angle(double rad)
		{
			static const double PI = 3.14159265358979323846;
			return 180 / PI * rad;
		}

		inline double angle(double degree, double min = 0.0, double sec = 0.0)
		{
			return degree + min / 60 + sec / 3600;
		}

		inline double MOD(double x, double y) //返回两浮点数数相除的余数,结果的符号与除数相同
		{
			double quotient = x / y;
			if (quotient > 0) {
				return x - y * (int) (quotient);
			} else {
				return x - y * ((int) (quotient) - 1);
			}
		}

		inline double standard_longitude(double x)
		{
			return MOD(x + 180, 360) - 180;
		}

		inline double standard_latitude(double x)
		{
			double fa = MOD(x + 90, 360) - 180;
			if (fa < 0) {
				fa = -fa;
			}
			return (90 - fa);
		}

		class Spherical
		{
			public:
				static const double R;   //地球半径6371004m

				double longitude, latitude, height;   //经度, 纬度
				std::string comment;

				Spherical(double longitude, double latitude, double height = 0.0, const std::string &comment =
						"");

				void standard()
				{
					longitude = standard_longitude(longitude);
					latitude = standard_latitude(latitude);
				}

				std::string to_string() const;
				friend std::ostream& operator <<(std::ostream &output, const Spherical &s);
		};

		inline std::ostream& operator<<(std::ostream &output, const Spherical &s)
		{
			output << s.to_string();
			return output;
		}

		double ball_distance(const Spherical &a, const Spherical &b);
		double real_distance(const Spherical &a, const Spherical &b);

	} /* Namespace spherical */

}
/* Namespace kerbal */

#endif 	/* End _SPHERICAL_HPP_ */
