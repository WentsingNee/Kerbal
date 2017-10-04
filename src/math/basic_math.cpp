#include "basic_math.hpp"

#include <cmath>
#include "../String_serve.hpp"
#include "../except_C++0x.hpp"

namespace
{
	using namespace std;
	using namespace _String;
}

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
		//cout << float_num(-12.3456,-2)<<endl;

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

namespace Fraction
{

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

	string a_divide_b(double a) throw (int)
	{
		double x;
		int i, j;
		string result = "";
		try {
			//检查a/b型
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

	string a_PI_divide_b(double a) throw (int)
	{
		double x;
		int i, j;
		string result = "";
		try {
			//检查aπ/b型
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

	string a_divide_b_PI(double a) throw (int)
	{
		double x;
		int i, j;
		string result = "";
		try {
			//检查a/bπ型
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

	string a_E_divide_b(double a) throw (int)
	{
		double x;
		int i, j;
		string result = "";
		try {
			//检查ae/b型
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

	string a_divide_b_E(double a) throw (int)
	{
		double x;
		int i, j;
		string result = "";
		try {
			//检查a/be型
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

	string sqrt_a_divide_b(double a) throw (int)
	{
		double x;
		int i, j;
		string result = "";
		try {
			//检查√(a/b)型
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

	string sin_a_divide_b(double a) throw (int)
	{
		double x;
		int i, j;
		string result = "";
		try {
			//检查sin(a/b)型,注意a/b>90时无法识别
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

	string tan_a_divide_b(double a) throw (int)
	{
		double x;
		int i, j;
		string result = "";
		try {
			//检查tan(a/b)型,注意/*a/b>90时无法识别*/
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

	string asin_a_divide_b(double a) throw (int)
	{
		double x;
		int i, j;
		string result = "";
		try {
//检查asin(a/b)型
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

	string atan_a_divide_b(double a) throw (int)
	{
		double x;
		int i, j;
		string result = "";
		try {
//检查atan(a/b)型
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
		try {
//检查a/b型
			return a_divide_b(a);
		} catch (int) {
			goto a_PI_divide_b;
		}

		a_PI_divide_b: try {
//检查aπ/b型
			return a_PI_divide_b(a);
		} catch (int) {
			goto a_divide_b_PI;
		}

		a_divide_b_PI: try {
//检查a/bπ型
			return a_divide_b_PI(a);
		} catch (int) {
			goto a_E_divide_b;
		}

		a_E_divide_b: try {
//检查ae/b型
			return a_E_divide_b(a);
		} catch (int) {
			goto a_divide_b_E;
		}

		a_divide_b_E: try {
//检查a/be型
			return a_divide_b_E(a);
		} catch (int) {
			goto sqrt_a_divide_b;
		}

		sqrt_a_divide_b: try {
//检查√(a/b)型
			return sqrt_a_divide_b(a);
		} catch (int) {
			goto ln_a_divide_b;
		}

		ln_a_divide_b: try {
//检查ln(a/b)型
			return ln_a_divide_b(a);
		} catch (int) {
			goto log_2_a_divide_b;
		}

		log_2_a_divide_b: try {
//检查ln(a/b)型
			return log_2_a_divide_b(a);
		} catch (int) {
			goto log_10_a_divide_b;
		}

		log_10_a_divide_b: try {
//检查ln(a/b)型
			return log_10_a_divide_b(a);
		} catch (int) {
			goto sin_a_divide_b;
		}

		sin_a_divide_b: try {
//检查sin(a/b)型
			return sin_a_divide_b(a);
		} catch (int) {
			goto tan_a_divide_b;
		}

		tan_a_divide_b: try {
//检查tan(a/b)型
			return tan_a_divide_b(a);
		} catch (int) {
//cout<<"不能拆分"<<endl;
			goto asin_a_divide_b;
		}

		asin_a_divide_b: try {
//检查asin(a/b)型
			return asin_a_divide_b(a);
		} catch (int) {
			goto atan_a_divide_b;
		}

		atan_a_divide_b: try {
//检查atan(a/b)型
			return atan_a_divide_b(a);
		} catch (int) {
			goto fail;
		}

		fail:

		return to_string(a);

		//	if(x==M_LOG2E) {
		//		if(a<0) {
		//			cout<<"-";
		//		}
		//		return "M_LOG2E";
		//	} else if(x==M_LOG10E) {
		//		if(a<0) {
		//			cout<<"-";
		//		}
		//		return "M_LOG10E";
		//	} else if(x==M_2_SQRTPI) {
		//		if(a<0) {
		//			cout<<"-";
		//		}
		//		return "2/√(π)";
		//	} else {
		//		return to_string(a);
		//	}

	}
}/* namespace fraction */

