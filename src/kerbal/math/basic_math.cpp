/**
 * @file basic_math.cpp
 * @date 2017-4-20
 * @author 倪文卿
 */

#include "basic_math.hpp"

#include <cmath>
#include <stdlib.h>
#include "../except_C++0x.hpp"
#include "../string_serve.hpp"

namespace kerbal
{
	namespace math
	{
		namespace basic_math
		{

			double baremainder(double numerator, double denominator) //返回两数相除的余数。 结果的符号与除数相同。
			{
				int quotient;
				if (numerator / denominator > 0) {
					quotient = numerator / denominator;
				} else {
					quotient = (int) (numerator / denominator) - 1;
				}
				return numerator - denominator * quotient;
			}

			unsigned short float_num(double a, double digits) //BUG
			{
				return abs((int) (10 * decimal(a * pow(10, -digits))));
			}

			double up(double x, int digits)
			{
				if (x >= 0) {

					if (float_num(x, digits - 1) <= 4) {
						x += 5 * pow(10, digits - 1);
					}

					return (int) (x * pow(10, -digits) + 0.5) / pow(10, -digits);
				} else {
					return -(int) (-x * pow(10, -digits) + 0.5) / pow(10, -digits);
				}
			}

			int gcd(int a, int b)
			{
				int temp;
				while (b) {
					temp = b;
					b = a % b;
					a = temp;
				}
				return a;
			}

			int lcm(int a, int b)
			{
				return a / gcd(a, b) * b;
			}

			bool is_prime(int x)
			{
				for (int i = 2; i * i <= x; ++i) {
					if (!(x % i)) {
						return false;
					}
				}
				return true;
			}

			double big_pow(double base, double exponent, int &exponent_result)
			{
				double exponent_temp = exponent * log10(base);
				exponent_result = (int) (exponent_temp);
				return pow(10, decimal(exponent_temp));
			}

			double big_fact(unsigned int n, int &exponent_result)
			{
				unsigned int i;
				double exponent_temp = 0;

				if (n >= 2) {
					for (i = 2; i <= n; i++) {
						exponent_temp += log10(i);
					}
				}
				exponent_result = (int) (exponent_temp);
				return pow(10, decimal(exponent_temp));
			}

			namespace Fraction
			{
				namespace
				{
					using std::string;
					using basic_math::fraction;
				}

#if __cplusplus >= 201103L //c++0x
				namespace
				{
					using std::to_string;
				}
#else
				namespace
				{
					using kerbal::string_serve::to_string;
				}
#endif //c++0x

				void fraction(double a, int &i, int &j) throw (int)
				{
					double x = fabs(a);
					int zhengshu = int(x);
					double xiaoshu = x - zhengshu;

					if (fabs(xiaoshu) <= 0.0000000000001) {
						i = x;
						j = 1;
						return;
					} else if (fabs(xiaoshu - 1) <= 0.0000000000001) {
						i = x + 1;
						j = 1;
						return;
					}

					i = 1;
					j = 2;
					double eps;
					for (int counter = 0; i < 10000 && j < 10000; counter++) {
						eps = double(i) / double(j) - xiaoshu;
						if (fabs(eps) <= 0.0000000000001) {
							i = (zhengshu * j + i);
							return;
						} else if (eps > 0) {
							j++;
						} else {
							i++;
						}
					}
					throw 0;

					//	try {
					//		fraction(n,i,j);
					//		if(n<0) {
					//			cout<<"-";
					//		}
					//		if(j==1) {
					//			cout<<i<<endl;
					//		} else {
					//			cout<<i<<"/"<<j<<endl;
					//		}
					//	} catch(int) {
					//		printf("%.25f\n",n);
					//	}
				}

				string a_divide_b(double a) throw (int)			//检查a/b型
				{
					double x;
					int i, j;
					string result = "";
					try {
						x = fabs(a);
						fraction(x, i, j);
						if (a < 0) {
							result += "-";
						}
						if (j == 1) {
							result += to_string(i);
						} else {
							result += to_string(i) + "/" + to_string(j);
						}
						return result;
					} catch (int) {
						throw 0;
					}
				}

				string a_PI_divide_b(double a) throw (int)			//检查aπ/b型
				{
					double x;
					int i, j;
					string result = "";
					try {
						x = fabs(a) / M_PI;
						fraction(x, i, j);
						if (a < 0) {
							result += "-";
						}
						if (j == 1) {
							if (i == 1) {
								result += "π";
							} else {
								result += to_string(i) + "π";
							}
						} else {
							if (i == 1) {
								result += "π/" + to_string(j);
							} else {
								result += to_string(i) + "π/" + to_string(j);
							}
						}
						return result;
					} catch (int) {
						throw 0;
					}
				}

				string a_divide_b_PI(double a) throw (int)			//检查a/bπ型
				{
					double x;
					int i, j;
					string result = "";
					try {
						x = fabs(a) * M_PI;
						fraction(x, i, j);
						if (a < 0) {
							result += "-";
						}
						if (j == 1) {
							result += to_string(i) + "/π";
						} else {
							result += to_string(i) + "/" + to_string(j) + "π";
						}
						return result;
					} catch (int) {
						throw 0;
					}
				}

				string a_E_divide_b(double a) throw (int)			//检查ae/b型
				{
					double x;
					int i, j;
					string result = "";
					try {
						x = fabs(a) / M_E;
						fraction(x, i, j);
						if (a < 0) {
							result += "-";
						}
						if (j == 1) {
							if (i == 1) {
								result += "e";
							} else {
								result += to_string(i) + "e";
							}
						} else {
							if (i == 1) {
								result += "e/" + j;
							} else {
								result += to_string(i) + "e/" + to_string(j);
							}
						}
						return result;
					} catch (int) {
						throw 0;
					}
				}

				string a_divide_b_E(double a) throw (int)			//检查a/be型
				{
					double x;
					int i, j;
					string result = "";
					try {
						x = fabs(a) * M_E;
						fraction(x, i, j);
						if (a < 0) {
							result += "-";
						}
						if (j == 1) {
							result += to_string(i) + "/e";
						} else {
							result += to_string(i) + "/" + to_string(j) + "e";
						}
						return result;
					} catch (int) {
						throw 0;
					}
				}

				string sqrt_a_divide_b(double a) throw (int)			//检查√(a/b)型
				{
					double x;
					int i, j;
					string result = "";
					try {
						x = a * a;
						fraction(x, i, j);
						if (a < 0) {
							result += "-";
						}
						if (j == 1) {
							result += "√(" + to_string(i) + ")";
						} else {
							int temp = sqrt(i);
							if (temp * temp == i) {
								//i可提出根号
								result += to_string(temp) + "/√(" + to_string(j) + ")";
							} else {
								temp = sqrt(j);
								if (temp * temp == j) {
									//j可提出根号
									result += "√(" + to_string(i) + ")/" + to_string(temp);
								} else {
									result += "√(" + to_string(i) + "/" + to_string(j) + ")";
								}
							}
						}
						return result;
					} catch (int) {
						throw 0;
					}
				}

				string ln_a_divide_b(double a) throw (int)
				{
					double x;
					int i, j;
					string result = "";
					try {
						x = exp(a);
						fraction(x, i, j);
						if (a < 0) {
							result += "-";
						}
						if (j == 1) {
							result += "ln(" + to_string(i) + ")";
						} else {
							result += "ln(" + to_string(i) + "/" + to_string(j) + ")";
						}
						return result;
					} catch (int) {
						throw 0;
					}
				}

				string log_2_a_divide_b(double a) throw (int)
				{
					double x;
					int i, j;
					string result = "";
					try {
						x = pow(2, a);
						fraction(x, i, j);
						if (a < 0) {
							result += "-";
						}
						if (j == 1) {
							result += "log_2(" + to_string(i) + ")";
						} else {
							result += "log_2(" + to_string(i) + "/" + to_string(j) + ")";
						}
						return result;
					} catch (int) {
						throw 0;
					}
				}

				string log_10_a_divide_b(double a) throw (int)
				{
					double x;
					int i, j;
					string result = "";
					try {
						x = pow(10, a);
						fraction(x, i, j);
						if (a < 0) {
							result += "-";
						}
						if (j == 1) {
							result += "log_10(" + to_string(i) + ")";
						} else {
							result += "log_10(" + to_string(i) + "/" + to_string(j) + ")";
						}
						return result;
					} catch (int) {
						throw 0;
					}
				}

				string sin_a_divide_b(double a) throw (int)			//检查sin(a/b)型,注意a/b>90时无法识别
				{
					double x;
					int i, j;
					string result = "";
					try {
						x = asin(a) * 180 / M_PI;
						fraction(x, i, j);
						if (a < 0) {
							result += "-";
						}
						if (j == 1) {
							result += "sin(" + to_string(i) + "deg)";
						} else {
							result += "sin(" + to_string(i) + "/" + to_string(j) + "deg)";
						}
						return result;
					} catch (int) {
						throw 0;
					}
				}

				string tan_a_divide_b(double a) throw (int)			//检查tan(a/b)型,注意a/b>90时无法识别
				{
					double x;
					int i, j;
					string result = "";
					try {
						x = atan(a) * 180 / M_PI;
						fraction(x, i, j);
						if (a < 0) {
							result += "-";
						}
						if (j == 1) {
							result += "tan(" + to_string(i) + "deg)";
						} else {
							result += "tan(" + to_string(i) + "/" + to_string(j) + "deg)";
						}
						return result;
					} catch (int) {
						throw 0;
					}
				}

				string asin_a_divide_b(double a) throw (int)			//检查asin(a/b)型
				{
					double x;
					int i, j;
					string result = "";
					try {
						x = sin(a);
						fraction(x, i, j);
						if (a < 0) {
							result += "-";
						}
						if (j == 1) {
							result += "asin(" + to_string(i) + ")";
						} else {
							result += "asin(" + to_string(i) + "/" + to_string(j) + ")";
						}
						return result;
					} catch (int) {
						throw 0;
					}
				}

				string atan_a_divide_b(double a) throw (int)			//检查atan(a/b)型
				{
					double x;
					int i, j;
					string result = "";
					try {
						x = tan(a);
						fraction(x, i, j);
						if (a < 0) {
							result += "-";
						}
						if (j == 1) {
							result += "atan(" + to_string(i) + ")";
						} else {
							result += "atan(" + to_string(i) + "/" + to_string(j) + ")";
						}
						return result;
					} catch (int) {
						throw 0;
					}
				}

				string fraction(double a)
				{
					//检查a/b型
					try {
						return a_divide_b(a);
					} catch (int) {
						goto a_PI_divide_b;
					}

					//检查aπ/b型
					a_PI_divide_b: try {
						return a_PI_divide_b(a);
					} catch (int) {
						goto a_divide_b_PI;
					}

					//检查a/bπ型
					a_divide_b_PI: try {
						return a_divide_b_PI(a);
					} catch (int) {
						goto a_E_divide_b;
					}

					//检查ae/b型
					a_E_divide_b: try {
						return a_E_divide_b(a);
					} catch (int) {
						goto a_divide_b_E;
					}

					//检查a/be型
					a_divide_b_E: try {
						return a_divide_b_E(a);
					} catch (int) {
						goto sqrt_a_divide_b;
					}

					//检查√(a/b)型
					sqrt_a_divide_b: try {
						return sqrt_a_divide_b(a);
					} catch (int) {
						goto ln_a_divide_b;
					}

					//检查ln(a/b)型
					ln_a_divide_b: try {
						return ln_a_divide_b(a);
					} catch (int) {
						goto log_2_a_divide_b;
					}

					//检查ln(a/b)型
					log_2_a_divide_b: try {
						return log_2_a_divide_b(a);
					} catch (int) {
						goto log_10_a_divide_b;
					}

					//检查ln(a/b)型
					log_10_a_divide_b: try {
						return log_10_a_divide_b(a);
					} catch (int) {
						goto sin_a_divide_b;
					}

					//检查sin(a/b)型
					sin_a_divide_b: try {
						return sin_a_divide_b(a);
					} catch (int) {
						goto tan_a_divide_b;
					}

					//检查tan(a/b)型
					tan_a_divide_b: try {
						return tan_a_divide_b(a);
					} catch (int) {
						goto asin_a_divide_b;
					}

					//检查asin(a/b)型
					asin_a_divide_b: try {
						return asin_a_divide_b(a);
					} catch (int) {
						goto atan_a_divide_b;
					}

					//检查atan(a/b)型
					atan_a_divide_b: try {
						return atan_a_divide_b(a);
					} catch (int) {
						goto fail;
					}

					fail:

					return to_string(a);

				}
			}/* namespace fraction */

			std::string fraction(double x)
			{
				return Fraction::fraction(x);
			}

		}/* namespace basic_math */

	}/* namespace math */

}/* namespace kerbal */
